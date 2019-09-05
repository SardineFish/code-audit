#include "code_audit/diff.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
using namespace CodeAudit;

int main(int argc, char**argv)
{

    auto list = {
        DIFF_DEL,
        DIFF_DEL,
        DIFF_ADD,
        DIFF_ADD,
        DIFF_ADD,
        DIFF_KEP,
        DIFF_KEP,
        DIFF_DEL,
        DIFF_KEP,
        DIFF_DEL,
        DIFF_DEL,
        DIFF_DEL,
        DIFF_ADD,
        DIFF_ADD,
        DIFF_DEL,
        DIFF_ADD,
        DIFF_KEP,
    };

    vector<DiffChanges> changes;
    for(auto &p :list)
    {
        changes.push_back(p);
    }

    mergeChanges(changes);

    fstream src;
    fstream dst;
    src.open(argv[1]);
    dst.open(argv[2]);
    char textSrc[8192];
    char textDst[8192];
    cin >> textSrc;
    cin >> textDst;

    vector<DiffChanges> result;
    diff<char>(textSrc, textDst, strlen(textSrc), strlen(textDst), result, [](const char* a, const char* b) -> bool { return *a == *b; });

    for (auto p = result.begin(); p < result.end();p++)
    {
        switch (*p)
        {
        case DIFF_ADD:
            cout << "+";
            break;
        case DIFF_DEL:
            cout << "-";
            break;
        case DIFF_KEP:
            cout << " ";
            break;
        }
    }
    cout << "|" << endl;
    return 0;
}