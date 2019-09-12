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

{WS}                                    skip();
((\/\*([^*]|\*[^/])*\*\/)|(\/\/.*{NL})) skip();
'(\\({CHR}|{DIGIT}+)|.)'                token("const-char", yytext);
(\"([^\\"]|\\{CHR}|\\\")*\")            token("const-string", yytext);
(else{SPACE}if)                         token("else if", yytext);
(long{SPACE}long|long{SPACE}long{SPACE}int)                       token("long long", yytext);
(void|char|short|int|long|unsigned|double|float|if|else|for|while|do|break|continue|return|switch|case|default|sizeof)    token(yytext, yytext);
(NULL)                                  token("null", yytext);
{ID}                                    token("id", yytext);
(0x[0-9A-Fa-f]+L?)|({DIGIT}+L?)((\.({DIGIT}+))?)((e(\+|-)?({DIGIT}+))?f?)           token("number", yytext);
((->)|(\+\+|--)|(\|\||&&)|((\+|-|\*|\/|%|=|&|\||\^|<<|>>|<|>|=|!|~)=?)|(\?|:|,|\.|;)) token(yytext, yytext);
\(|\)|\[|\]|\{|\}|<|>                   token(yytext, yytext);
(#.*(\\{NL}.*)*)                        token("preprocessor", yytext);
.                                       token("unknown", yytext);


%%

int yywrap(){ return 1; }

token_callback_t TokenCallback;
void* CallbackState;

int input_pos = 0;

void skip()
{
    input_pos += yyleng;
}

void token(const char* name, const char* attribute)
{
    token_t t = {name, attribute, input_pos};
    skip();
    TokenCallback(t, CallbackState);
}

void set_token_callback(token_callback_t callback, void* state)
{
    TokenCallback = callback;
    CallbackState = state;
}

void lexer(const char *text)
{
    input_pos = 0;
    YY_BUFFER_STATE buffer = yy_scan_string(text);
    yy_switch_to_buffer(buffer);
    yylex();
}