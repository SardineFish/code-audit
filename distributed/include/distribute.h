#include "code_audit.h"
#include <vector>
#include <queue>
#include <sys/socket.h>


using namespace std;

namespace CodeAudit
{
namespace Distributed
{
namespace Master
{

enum NodeStatus
{
    NODE_OFFLINE = 0,
    NODE_ONLINE = 2,
    NODE_IDLE = NODE_ONLINE,
    NODE_BUSY = 3,
};

struct NodeInfo
{
    NodeStatus status;
};

enum TaskType
{
    TASK_SIM = 1,
    TASK_AUDIT = 2,
};

class Task
{
public:
    NodeInfo *processor = nullptr;
    bool completed = false;
    virtual void serialize(const char *buffer, size_t size);
};


class SimilarityTask : public Task
{
};

class Controller
{
public:
    vector<NodeInfo> nodes;
};

} // namespace Master
namespace Node
{

}
}

}