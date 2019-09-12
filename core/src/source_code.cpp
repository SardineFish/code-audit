#include "code_audit/source_code.h"
#include <fstream>

#define BUFFER_SIZE 8192

namespace CodeAudit
{

SourceCode::SourceCode(string source)
{
    this->source = source;
    this->updateLines();
}
SourceCode::SourceCode()
{
    this->source = "";
}
void SourceCode::updateLines()
{
    int lineStart = 0;
    for (int i = 0; i < this->source.length(); i++)
    {
        if (this->source[i] == '\n')
        {
            this->linePos.push_back(lineStart);
            lineStart = i;
        }
    }
    this->linePos.push_back(lineStart);
}
int SourceCode::lineAt(int pos)
{
    for (int i = 1; i < this->linePos.size(); i++)
    {
        if (pos < this->linePos[i])
            return i;
    }
    return this->linePos.size();
}
int SourceCode::columnAt(int pos)
{
    for (int i = 1; i < this->linePos.size(); i++)
    {
        if (pos < this->linePos[i])
            return pos - this->linePos[i - 1];
    }
    return pos - *(this->linePos.end());
}
void SourceCode::open(string filename)
{
    fstream fs;
    fs.open(filename);
    char buffer[BUFFER_SIZE];
    fs.get(buffer, BUFFER_SIZE, EOF);
    fs.close();
    this->source = string(buffer);
    this->updateLines();
}
} // namespace CodeAudit