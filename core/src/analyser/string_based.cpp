#include "code_audit/string_analyser.h"
#include <sstream>
#include <cstring>
#include <functional>

namespace CodeAudit
{



StringBasedAnalyser::StringBasedAnalyser(StringAnalyseMode mode)
{
    this->mode = mode;
}
double StringBasedAnalyser::calcSimilarity(string source, string sample)
{
    if(this->mode == STR_ANALYSE_LINE)
    {
        char buffer[MAX_LINE_LENGTH];
        stringstream sourceStream(source);
        stringstream sampleStream(sample);
        vector<string> sourceLines;
        vector<string> sampleLines;
        while(!sourceStream.eof())
        {
            sourceStream.getline(buffer, MAX_LINE_LENGTH);
            sourceLines.push_back(string(buffer));
        }
        while(!sampleStream.eof())
        {
            sampleStream.getline(buffer, MAX_LINE_LENGTH);
            sampleLines.push_back(string(buffer));
        }
    }
}

}