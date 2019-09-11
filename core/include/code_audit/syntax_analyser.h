#pragma once
#include "analyser_base.h"
#include "compare_tree.h"
#include "parser.h"

using namespace CodeAudit::SyntaxParser;

namespace CodeAudit
{

class SyntaxBasedAnalyser:public CodeAnanyser
{
  public:
      int level = 0;
      virtual double calcSimilarity(string source, string sample) override;
};

ComparableTree<string>* createDiffTree(ASTTree* ast);

}