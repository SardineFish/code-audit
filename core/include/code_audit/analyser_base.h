#pragma once

#include <string>
#include <vector>
#include <iostream>

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
    virtual double calcSimilarity(string source, string sample);
    virtual vector<Diagnostic> diagnose(string source);
};

} // namespace CodeAudit