#include "master.h"
#include "unistd.h"
#include <memory.h>
#include "sys/socket.h"

using namespace CodeAudit;
using namespace CodeAudit::Distributed::Master;

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
    size_t size = 0;
    task.processor = this;
    task.status = TASK_RUNNING;
    size = task.params->serialize(buffer, 0, sizeof(buffer));
    if( size != sendto(this->net.socket, buffer, size, 0, (sockaddr *)&(this->net.addr), sizeof(this->net.addr)))
    {
        cerr << "Failed to send task to " << this->name << endl;
        return false;
    }
    cout << "Task sent to node " << this->name << endl;
    return true;
}

void NodeInfo::complete(Message&result)
{
    this->status = NODE_IDLE;
    this->task = nullptr;
}

bool CodeAuditMaster::start()
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

void CodeAuditMaster::stop()
{
    close(sock);
}

bool CodeAuditMaster::scan(int timeout)
{
    // Set timeout
    timeval t;
    t.tv_sec = 0;
    t.tv_usec = timeout * 1000;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &t, sizeof(t)) < 0)
    {
        cout << "Fialed to set timeout." << endl;
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

    while(true)
    {
        sockaddr_in remote;
        socklen_t addrlen = sizeof(remote);
        size_t size = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr *)&remote, &addrlen);
        if(size <= 8)
        {
            if(errno == EAGAIN)
                break;
            cerr << "Received wrong message." << endl;
            continue;
        }
        else
        {
            SlaveHandshake handshake;
            handshake.deserialize(buffer, 0, size);
            if(handshake.version != VERSION)
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

Task *CodeAuditMaster::similarity(AnalyserType analyser, string source, string sample, function<void(double)> callback)
{
    auto task = new Task;
    task->id = ++this->globalId;
    task->callback = [=](Task *t) -> void {
        auto result = dynamic_cast<SimilarityResult *>(t->result);
        callback(result->similarity);
    };
    auto request = new SimilarityRequest;
    request->analyser = analyser;
    request->source = source;
    request->sample = sample;
    auto msg = new TaskMessage;
    msg->id = task->id;
    msg->params = request;
    msg->task = (TaskType)(TASK_REQUEST | TASK_SIMILARITY);
    this->pendingTasks.push(task);
    this->update();
    return task;
}

Task *CodeAuditMaster::audit(string source, function<void(vector<Vulnerability>)>callback)
{
    auto task = new Task;
    task->id = ++this->globalId;
    task->callback = [=](Task *t) -> void {
        auto result = dynamic_cast<AuditResult *>(t->result);
        callback(result->vulns);
    };
    auto request = new AuditRequest;
    request->source = source;
    auto msg = new TaskMessage;
    msg->id = task->id;
    msg->params = request;
    msg->task = (TaskType)(TASK_REQUEST | TASK_AUDIT);
    this->pendingTasks.push(task);
    this->update();
    return task;
}

void CodeAuditMaster::update()
{
    while(!this->pendingTasks.empty() && !this->availableNodes.empty())
    {
        auto task = this->pendingTasks.front();
        this->pendingTasks.pop();
        auto node = this->availableNodes.front();
        this->availableNodes.pop();
        node->process(*task);
        this->runningTasks[task->id] = task;
    }


}

void CodeAuditMaster::recv()
{
    char buffer[65507];
    while(true)
    {
        sockaddr_in remote;
        socklen_t addrlen = sizeof(remote);
        size_t size = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr *)&remote, &addrlen);
        if(size < 8)
        {
            cerr << "Received wrong message." << endl;
            continue;
        }
        TaskMessage msg;
        size_t len = msg.deserialize(buffer, 0, size);
        if(msg.task | TASK_AUDIT)
        {
            msg.params = new AuditResult;
        }
        else if (msg.task |TASK_SIMILARITY)
            msg.params = new SimilarityResult;
        msg.params->deserialize(buffer, len, size);

        auto task = this->runningTasks[msg.id];
        this->runningTasks.erase(task->id);
        task->status = TASK_COMPLETED;
        task->processor->complete(*msg.params);
        this->availableNodes.push(task->processor);
        task->callback(task);
        delete task;
        delete msg.params;
    }
}