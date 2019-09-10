#include "analyser_base.h"
namespace CodeAudit
{

class SyntaxBasedAnalyser:public CodeAnanyser
{
  public:
      virtual double calcSimilarity(string source, string sample) override;
};

}