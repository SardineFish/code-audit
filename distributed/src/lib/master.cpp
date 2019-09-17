#include "master.h"
#include "unistd.h"
#include <memory.h>
#include "sys/socket.h"
#include <thread>
#include <condition_variable>

using namespace std;
using namespace CodeAudit;
using namespace CodeAudit::Distributed::Master;

function<void(string)> globalLog;

void setLogger(function<void(string)> logger)
{
    globalLog = logger;
}
void log(string msg)
{
    globalLog(msg);
}

namespace CodeAudit
{
namespace Distributed
{
namespace Master
{

NodeInfo::NodeInfo(int socket, sockaddr_in addr, string name)
{
    this->net = {addr, socket};
    this->name = name;
    this->status = NODE_ONLINE;
    this->task = nullptr;
}

bool NodeInfo::process(Task &task)
{
    this->task = &task;
    this->status = NODE_BUSY;

    char buffer[65507];
    ssize_t size = 0;
    task.processor = this;
    task.status = TASK_RUNNING;
    size = task.params->serialize(buffer, 0, sizeof(buffer));
    if (size != sendto(this->net.socket, buffer, size, 0, (sockaddr *)&(this->net.addr), sizeof(this->net.addr)))
    {
        cerr << "Failed to send task to " << this->name << endl;
        return false;
    }
    cout << "Task sent to node " << this->name << endl;
    return true;
}

void NodeInfo::complete(Message &result)
{
    this->status = NODE_IDLE;
    this->task = nullptr;
}

bool CodeAuditMaster::init()
{
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock <= 0)
    {
        cerr << "Failed to open socket." << endl;
        return false;
    }

    // Set to broadcast mode
    int optVal = 1;
    if (-1 == setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &optVal, sizeof(optVal)))
    {
        cout << "Failed to open socket on broadcast mode." << endl;
        close(sock);
        return false;
    }
    return true;
}

void continiousRecv(CodeAuditMaster* master)
{
    cout << "recv start" << endl;
    master->recv();
    cout << "recv stopped" << endl;
}

void continiousUpdate(CodeAuditMaster* master)
{
    cout << "update start" << endl;
    while (master->running)
    {
        int t;
        master->updateChannel >> t;
        master->update();
    }
    cout << "update stopped" << endl;
}

void CodeAuditMaster::start()
{
    this->running = true;
    this->threadRecv = new thread(continiousRecv, this);
    this->threadUpdate = new thread(continiousUpdate, this);
    //this->threadRecv->detach();
    //this->threadUpdate->detach();
}

void CodeAuditMaster::stop()
{
    this->running = false;
    this->nodeMutex.lock();
    int t = 0;
    for(auto & node : this->nodes)
    {
        sendto(node->net.socket, &t, sizeof(t), 0, (sockaddr *)&(node->net.addr), sizeof(sockaddr_in));
    }
    this->nodeMutex.unlock();
    close(sock);
    this->updateChannel << t;
    this->threadRecv->join();
    this->threadUpdate->join();
    //close(sock);
}

bool CodeAuditMaster::scan(int timeout)
{
    if (this->running)
    {
        this->stop();
        this->init();
        this->nodeMutex.lock();
        this->nodes.clear();
        while (!this->availableNodes.empty())
            this->availableNodes.pop();
        this->nodeMutex.unlock();
    }
    // Set timeout
    timeval t;
    t.tv_sec = timeout / 1000;
    t.tv_usec = timeout % 1000 * 1000;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &t, sizeof(t)) < 0)
    {
        int x = errno;
        cerr << "Fialed to set timeout." << endl;
        close(sock);
        return false;
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    addr.sin_port = htons(DefaultPort);

    MasterBroadcast broadcast;
    broadcast.version = VERSION;
    char buffer[65507];
    memcpy(buffer, &broadcast, sizeof(broadcast));
    sendto(sock, buffer, sizeof(broadcast), 0, (sockaddr *)&addr, sizeof(addr));

    while (true)
    {
        sockaddr_in remote;
        socklen_t addrlen = sizeof(remote);
        ssize_t size = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr *)&remote, &addrlen);
        if (size <= 8)
        {
            if (errno == EAGAIN)
                break;
            cerr << "Received wrong message." << endl;
            continue;
        }
        else
        {
            SlaveHandshake handshake;
            handshake.deserialize(buffer, 0, size);
            if (handshake.version != VERSION)
            {
                cerr << "Unsupported client version." << endl;
                sendto(sock, buffer, sizeof(1), 0, (sockaddr *)&remote, sizeof(remote));
                continue;
            }
            auto node = new NodeInfo(sock, remote, handshake.name);
            this->nodes.push_back(node);
            this->availableNodes.push(node);
        }
    }
    return true;
}

Task *CodeAuditMaster::similarity(AnalyserType analyser, string source, string sample, function<void(Task*, double)> callback, function<void(Task*)>init)
{
    auto task = new Task;
    task->id = ++this->globalId;
    if(init)
        init(task);
    task->callback = [=](Task *t) -> void {
        auto result = dynamic_cast<SimilarityResult *>(t->result);
        callback(t, result->similarity);
    };
    auto request = new SimilarityRequest;
    request->analyser = analyser;
    request->source = source;
    request->sample = sample;
    auto msg = new TaskMessage;
    msg->id = task->id;
    msg->params = request;
    msg->task = (TaskType)(TASK_REQUEST | TASK_SIMILARITY);
    task->params = msg;
    this->pendingTasks.push(task);
    int t = 1;
    this->updateChannel << t;
    return task;
}

Task *CodeAuditMaster::audit(string source, function<void(Task *, vector<Vulnerability>)> callback, function<void(Task *)> init)
{
    auto task = new Task;
    task->id = ++this->globalId;
    task->callback = [=](Task *t) -> void {
        auto result = dynamic_cast<AuditResult *>(t->result);
        callback(t, result->vulns);
    };
    if(init)
        init(task);
    auto request = new AuditRequest;
    request->source = source;
    auto msg = new TaskMessage;
    msg->id = task->id;
    msg->params = request;
    msg->task = (TaskType)(TASK_REQUEST | TASK_AUDIT);
    task->params = msg;
    this->pendingTasks.push(task);
    int t = 1;
    this->updateChannel << t;
    return task;
}

void CodeAuditMaster::update()
{
    while (this->running && !this->pendingTasks.empty() && !this->availableNodes.empty())
    {
        tasksMutex.lock();
        auto task = this->pendingTasks.front();
        this->pendingTasks.pop();
        tasksMutex.unlock();

        nodeMutex.lock();
        auto node = this->availableNodes.front();
        this->availableNodes.pop();
        nodeMutex.unlock();

        tasksMutex.lock();
        this->runningTasks[task->id] = task;
        tasksMutex.unlock();


        node->process(*task);
    }
}

void CodeAuditMaster::recv()
{
    // Set timeout
    timeval t;
    t.tv_sec = 5;
    t.tv_usec = 0;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &t, sizeof(t)) < 0)
    {
        int x = errno;
        cout << "Fialed to set timeout." << endl;
        close(sock);
        return;
    }

    char buffer[65507];
    while (this->running)
    {
        sockaddr_in remote;
        socklen_t addrlen = sizeof(remote);
        ssize_t size = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr *)&remote, &addrlen);
        if (size < 8)
        {
            if (errno == EAGAIN)
                continue;
            cerr << "Received wrong message." << endl;
            continue;
        }
        TaskMessage msg;
        size_t len = msg.deserialize(buffer, 0, size);
        if (msg.task & TASK_AUDIT)
        {
            msg.params = new AuditResult;
        }
        else if (msg.task & TASK_SIMILARITY)
            msg.params = new SimilarityResult;
        msg.params->deserialize(buffer, len, size);

        tasksMutex.lock();
        auto task = this->runningTasks[msg.id];
        this->runningTasks.erase(task->id);
        tasksMutex.unlock();

        task->status = TASK_COMPLETED;
        task->processor->complete(*msg.params);
        task->result = msg.params;

        nodeMutex.lock();
        this->availableNodes.push(task->processor);
        nodeMutex.unlock();
        int t = 1;
        this->updateChannel << t;

        task->callback(task);
        delete task;
        delete msg.params;
    }
}
} // namespace Master
} // namespace Distributed
} // namespace CodeAudit