#pragma once

#include "string_analyser.h"
#include "token_analyser.h"
#include "syntax_analyser.h"

namespace CodeAudit
{
enum AnalyserType
{
    ANALYSE_STRING_LINE = 0,
    ANALYSE_STRING_CHAR = 1,
    ANALYSE_TOKEN = 2,
    ANALYSE_SYNTAX = 3,
};
}