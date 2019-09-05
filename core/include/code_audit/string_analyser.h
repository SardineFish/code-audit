#pragma once

#include "analyser_base.h"

namespace CodeAudit
{

#define MAX_LINE_LENGTH 1024

enum StringAnalyseMode
{
    STR_ANALYSE_LINE,
    STR_ANALYSE_CHAR,
};

class StringBasedAnalyser : public CodeAnanyser
{
  public:
    StringAnalyseMode mode;
    StringBasedAnalyser();
    StringBasedAnalyser(StringAnalyseMode mode);
    double calcSimilarity(string source, string sample) override;
};

}