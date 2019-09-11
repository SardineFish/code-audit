#pragma once

typedef struct
{
    const char *name;
    const char *attribute;
    const int pos;
} token_t;

void skip();

typedef void (*token_callback_t)(token_t, void*);

void set_token_callback(token_callback_t callback, void* state);

void lexer(const char *text);
