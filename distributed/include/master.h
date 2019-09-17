#pragma once
#include "code_audit.h"
#include <vector>
#include <queue>
#include <functional>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <mutex>
#include <thread>
#include "channel.h"

#include "message.h"

using namespace std;

namespace CodeAudit
{
namespace Distributed
{
namespace Master
{

const int DefaultPort = 17385;
const int VERSION = 1;

enum NodeStatus
{
    NODE_OFFLINE = 0,
    NODE_ONLINE = 2,
    NODE_IDLE = NODE_ONLINE,
    NODE_BUSY = 3,
};

enum TaskStatus
{
    TASK_PENDING,
    TASK_RUNNING,
    TASK_COMPLETED,
};

struct Network
{
    sockaddr_in addr;
    int socket;
};

class Task;
class NodeInfo;
class CodeAuditMaster;

class Task
{
public:
    int id;
    TaskStatus status = TASK_PENDING;
    NodeInfo *processor = nullptr;
    TaskMessage *params = nullptr;
    Message *result = nullptr;
    function<void(Task *)> callback;
};

class NodeInfo
{
public:
    string name;
    NodeStatus status;
    Network net;
    Task *task;
    NodeInfo(int socket, sockaddr_in addr, string name);
    bool process(Task &task);
    void complete(Message &result);
};

class CodeAuditMaster
{
public:
    bool init();
    void start();
    void stop();
    bool scan(int timeout);
    void update();
    void recv();
    bool running = false;
    channel<int> updateChannel;
    vector<NodeInfo *> nodes;
    Task *similarity(AnalyserType analyser, string source, string sample, function<void(Task*, double)> callback, function<void(Task *)> init = nullptr);
    Task *audit(string source, function<void(Task *, vector<Vulnerability>)> callback, function<void(Task *)> init = nullptr);
    thread *threadRecv;
    thread *threadUpdate;

private:
    int globalId = 0;
    int sock;
    mutex tasksMutex;
    mutex nodeMutex;
    queue<Task *> pendingTasks;
    map<int, Task *> runningTasks;
    queue<NodeInfo *> availableNodes;
};

} // namespace Master
} // namespace Distributed

} // namespace CodeAudit