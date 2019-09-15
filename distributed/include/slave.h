#pragma once
#include "code_audit.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "message.h"

using namespace std;

namespace CodeAudit
{
namespace Distributed
{
namespace Slave
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

class Task
{
public:
    int id;
    TaskType type;
    Message *params;
};

class Node
{
public:
    string name;
    NodeStatus status = NODE_OFFLINE;
    Task *task = nullptr;
    int port;
    Node(string name, int port = DefaultPort);
    void start();
};



}
}
}