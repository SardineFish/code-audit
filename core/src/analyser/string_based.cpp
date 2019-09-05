#include "code_audit/string_analyser.h"
#include <sstream>
#include <cstring>
#include <functional>
#include "code_audit/diff.h"

namespace CodeAudit
{

StringBasedAnalyser::StringBasedAnalyser()
{
    this->mode = STR_ANALYSE_LINE;
}
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
        vector<DiffChanges> diffRestult;
        diff<string>(sampleLines, sourceLines, diffRestult, [](const string *a, const string *b) -> bool { return *a == *b; });
        mergeChanges(diffRestult);
        int similarLines = 0;
        for (auto &p : diffRestult)
        {
            if(p == DIFF_KEP)
                similarLines++;
        }
        return (double)similarLines / (double)diffRestult.size();
    }
}

}