#pragma once
#include "code_audit.h"
#include <vector>
#include <queue>
#include <functional>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>

#include "message.h"

using namespace std;

namespace CodeAudit
{
namespace Distributed
{
namespace Master
{

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

class Task
{
public:
    int id;
    TaskStatus status;
    NodeInfo *processor;
    TaskMessage *params;
    Message *result;
};

class NodeInfo
{
public:
    string name;
    NodeStatus status;
    Network net;
    Task *task;
    NodeInfo(int socket, sockaddr_in addr, string name);
    void process(Task &task);
    void complete(Message &result);
};

class CodeAuditMaster
{
public:
    void scan(int timeout);
    Task *similarity(AnalyserType analyser, string source, string sample, function<void(double)> callback);
    Task *audit(string source, function<void(vector<Vulnerability>)> callback);
private:
    int globalId = 0;
    queue<Task *> pendingTasks;
    map<int, Task *> runningTasks;
    queue<NodeInfo *> availableNodes;
    vector<NodeInfo *> nodes;
};

} // namespace Master
} // nmespace Distributed

} // namespace CodeAudit