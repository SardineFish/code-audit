#include "code_audit/syntax_analyser.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace CodeAudit;

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        cerr << "Invalid arguments." << endl;
        return 1;
    }
    char buffer[8192];

    fstream fs;
    fs.open(string(argv[1]));
    fs.get(buffer, 8192, EOF);
    fs.close();
    string source = string(buffer);

    fs.open(string(argv[2]));
    fs.get(buffer, 8192, EOF);
    fs.close();
    string sample = string(buffer);

    auto analyser = new SyntaxBasedAnalyser();
    cout << analyser->calcSimilarity(source, sample) << endl;

    return 0;
}