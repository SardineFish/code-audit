#pragma once

typedef struct
{
    const char* name;
    const char* attribute;
} token_t;

typedef void (*token_callback_t)(token_t);

void set_token_callback(token_callback_t callback);

void lexer(const char *text);