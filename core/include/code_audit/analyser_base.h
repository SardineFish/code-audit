#pragma once

#include <string>
#include <vector>

namespace CodeAudit
{

using namespace std;

struct Diagnostic
{
    int line;
    int column;
    string message;
};

class CodeAnanyser
{
  public:
    double calcSimilarity(string source, string sample);
    vector<Diagnostic> diagnose(string source);
};

} // namespace CodeAudit