#include "../lib/args/args.hxx"
#include "code_audit.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;
using namespace CodeAudit;

args::ArgumentParser p("A tool to provide simple code audition.", "what");
args::Group command(p, "commands", args::Group::Validators::Xor);
args::Command sim(command, "sim", "Similarity analyse");
args::Group arguments(p, "arguments", args::Group::Validators::DontCare, args::Options::Global);
args::Group analyseMethod(arguments, "method", args::Group::Validators::Xor);
args::Flag stringBased(analyseMethod, "string", "Use string based analyse, with --line or --char options.", {"str", "string"});
args::Flag tokenBased(analyseMethod, "token", "Use token based analyser", {"token"});
args::Group analyserOptions(arguments, "options", args::Group::Validators::DontCare);
args::Flag tokenOnly(analyserOptions, "tokenonly", "Ignore token attribute when analysing.", {"tokenonly"});
args::Flag perChar(analyserOptions, "char", "Analyse per-character.", {"char"});
args::Flag perLine(analyserOptions, "line", "Analyse per-line.", {"line"});
args::HelpFlag h(p, "help", "Display this help menu", {'h', "help"});
args::PositionalList<string> inputFiles(arguments, "files", "Input files.");

string readFile(string file)
{
    fstream s;
    s.open(file);
    char buffer[8192];
    s.get(buffer, 8192, EOF);
    return string(buffer);
}

void similarity()
{
    auto files = args::get(inputFiles);
    if(files.size() < 2)
    {
        cerr << "Require source file & sample file." << endl;
        exit(1);
    }
    string source = readFile(files[0]);
    string sample = readFile(files[1]);

    CodeAnanyser* analyser;
    if(stringBased)
    {
        StringBasedAnalyser *stringAnalyser = new StringBasedAnalyser();
        if (perChar)
            stringAnalyser->mode = STR_ANALYSE_CHAR;
        else if (perLine)
            stringAnalyser->mode = STR_ANALYSE_LINE;
        else
            stringAnalyser->mode = STR_ANALYSE_LINE;
        analyser = stringAnalyser;
    }
    else
    {
        auto tokenAnalyser = new TokenBasedAnalyser();
        if(tokenOnly)
            tokenAnalyser->tokenOnly = true;
        else
            tokenAnalyser->tokenOnly = false;
        analyser = tokenAnalyser;
    }
    
    auto result = analyser->calcSimilarity(source, sample);
    delete analyser;
    cout << result << endl;
    exit(0);
}

int main(int argc, char** argv)
{

    try
    {
        p.ParseCLI(argc, argv);

        if(sim)
        {
            similarity();
        }
    }
    catch (args::Help)
    {
        std::cout << p;
    }
    catch (args::Error& e)
    {
        std::cerr << e.what() << std::endl << p;
        return 1;
    }
    return 0;
}