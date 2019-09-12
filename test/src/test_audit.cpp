#include "code_audit/syntax_analyser.h"

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
}