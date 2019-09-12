#include "code_audit/syntax_analyser.h"
#include<cstdio>

using namespace CodeAudit;

int main(int argc, char** argv)
{
    SourceCode *source = new SourceCode();
    if (argc > 1)
    {
        source->open(string(argv[1]));
    }
    else{
        char buffer[8192];
        cin.get(buffer, 8192, EOF);
        delete source;
        source = new SourceCode(string(buffer));
    }

    auto analyser = new SyntaxBasedAnalyser;
    auto vulns = analyser->audit(source);
    for(auto & vuln : vulns)
    {
        printf("At:%d,%d: %s\n", vuln.line, vuln.column, vuln.description.c_str());
    }
    return 0;
}