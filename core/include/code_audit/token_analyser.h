#include "analyser_base.h"

namespace CodeAudit
{

class TokenBasedAnalyser : public CodeAnanyser
{
  public:
      bool tokenOnly = false;

      double calcSimilarity(string source, string sample) override;
};

}