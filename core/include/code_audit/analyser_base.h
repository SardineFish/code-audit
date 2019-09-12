#pragma once

#include "code_audit/source_code.h"
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
    virtual vector<Diagnostic> diagnose(SourceCode& source);
};

} // namespace CodeAudit