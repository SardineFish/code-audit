#include "code_audit/diff.h"
#include <cmath>
#include <cstdint>
#include <stack>

namespace CodeAudit
{
vector<DiffChanges> mergeChanges(vector<DiffChanges>& changes)
{
    for (auto p = changes.begin(); p < changes.end(); )
    {
        int dels = 0, adds = 0;
        auto startDeletePtr = p;
        auto endDeletePtr = p;
        for (startDeletePtr = p; *p == DIFF_DEL; p++)
        {
            endDeletePtr++;
        }
        for (auto changesPtr = startDeletePtr; changesPtr < endDeletePtr && p < changes.end() && *p == DIFF_ADD; changesPtr++)
        {
            p = changes.erase(p);
            *changesPtr = DIFF_RPL;
        }
        if(*p!=DIFF_DEL)
            p++;
    }
    return changes;
}

} // namespace CodeAudit