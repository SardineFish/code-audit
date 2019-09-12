#pragma once
#include <string>
#include <vector>

using namespace std;

namespace CodeAudit
{

class SourceCode
{
private:
    vector<int> linePos;
    void updateLines();

public:
    string source;
    SourceCode();
    SourceCode(string source);
    void open(string filename);
    int lineAt(int pos);
    int columnAt(int pos);
};

} // namespace CodeAudit
