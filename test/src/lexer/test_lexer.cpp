#include <cstdio>
#include <iostream>
#include "code_audit/lexer.h"

using namespace std;

void callback(token_t t)
{
    printf("<%s %s>\n", t.name, t.attribute);
}

int main(int argc, char** argv)
{
    char buffer[8192];
    cin.get(buffer, 8192, EOF);
    
    set_token_callback(callback);
    lexer(buffer);
    return 0;
}