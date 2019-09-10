%{
#include "code_audit/c_lexer.h"
#include <stdio.h>

void token(const char* name, const char* attribute);

// Avoid undecleare error from gcc in Windows.
%}

DIGIT   [0-9]
ID      [a-zA-Z_][a-zA-Z0-9_]*
SPACE   [ \t]
WS      [ \t\r\n\f]
CHR     [^ \t\r\n\f]
NL      (\r\n|\n|\r)
ANY     (.|{NL})

%%

{WS}    
((\/\*([^*]|\*[^/])*\*\/)|(\/\/.*{NL}))
'(\\({CHR}|{DIGIT}+)|.)'                token("char", yytext);
(\"([^\\"]|\\{CHR}|\\\")*\")            token("string", yytext);
(else{SPACE}if)                         token("else if", yytext);
(long{SPACE}long)                       token("long long", yytext);
(void|char|short|int|long|unsigned|double|float|if|else|for|while|do|break|continue|return|switch|case|default)    token(yytext, yytext);
{ID}                                    token("id", yytext);
(0x[0-9A-Fa-f]+L?)|({DIGIT}+L?)((\.({DIGIT}+))?)((e(\+|-)?({DIGIT}+))?f?)           token("number", yytext);
((->)|(\+\+|--)|(\|\||&&)|((\+|-|\*|\/|%|=|&|\||\^|<<|>>|<|>|=|!|~)=?)|(\?|:|,|\.|;)) token(yytext, yytext);
\(|\)|\[|\]|\{|\}|<|>                   token(yytext, yytext);
(#.*(\\{NL}.*)*)                          token("preprocessor", yytext);
.                                       token("unknown", yytext);


%%

int yywrap(){ return 1; }

token_callback_t TokenCallback;
void* CallbackState;

void token(const char* name, const char* attribute)
{
    token_t t = {name, attribute};
    TokenCallback(t, CallbackState);
}

void set_token_callback(token_callback_t callback, void* state)
{
    TokenCallback = callback;
    CallbackState = state;
}

void lexer(const char *text)
{
    YY_BUFFER_STATE buffer = yy_scan_string(text);
    yy_switch_to_buffer(buffer);
    yylex();
}