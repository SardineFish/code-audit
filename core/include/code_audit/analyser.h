#pragma once

#include "string_analyser.h"
#include "token_analyser.h"
#include "syntax_analyser.h"

namespace CodeAudit
{
enum AnalyserType
{
    ANALYSE_STRING_CHAR,
    ANALYSE_STRING_LINE,
    ANALYSE_TOKEN,
    ANALYSE_SYNTAX,
};
}