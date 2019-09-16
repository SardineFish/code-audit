#include "distribute.h"
#include "unistd.h"
#include "limits.h"

using namespace CodeAudit::Distributed::Slave;

int main()
{
    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, LOGIN_NAME_MAX);
    auto node = new Node(string(hostname));
    node->start();
    return 0;
}