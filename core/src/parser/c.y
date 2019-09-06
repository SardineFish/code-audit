%{
    #include "code_audit/parser.h"
    #define YYSTYPE ASTNode*

namespace CodeAudit
{
namespace SyntaxParser
{
    void yyerror (char *s)
    {
        printf ("%s\n", s);
    }
    int yylex();
    
    void (*ASTCallback)(ASTTree*);
%}

%left ','
%token ID
%token TYPE
%%

input:  /* empty */ { 
        auto ast = new ASTTree;
        ASTCallback(ast);
        $$ = ast;
    }
        | input global_def {
                ASTTree* root = (ASTTree*)$1;
                root->globalDefinitions->push_back((FunctionDefine*)$2);
                $$ = root;
            }
;

global_def: func_def { $$ = $1; }
;

func_def: type id '(' args_declare ')' block { 
    auto f = new FunctionDefine;
    f->name = ((TokenNode*)$2)->token.name;
    f->type = (TokenNode*)$1;
    f->id = (TokenNode*)$2;
    f->args = (ListNode<ParameterNode>*)$4;
    f->body = (BlockNode*)$6;
    $$ = f;
 }
;

type: TYPE     { $$ = $1; }
;

id: ID { $$ = $1; }
;

args_declare: /* empty */ { $$ = nullptr; }
    | args_declare ',' type id {
        ListNode<ParameterNode>* list = (ListNode<ParameterNode>*)$1;
        auto p = new ParameterNode;
        p->type = (TokenNode*)$3;
        p->id = (TokenNode*)$4;
        list->list->push_back(p);
        $$ = list;
    }
    | type id {
        auto p = new ParameterNode;
        p->type = (TokenNode*)$1;
        p->id = (TokenNode*)$2;
        $$ = p;
    }
;
block: '{' '}' {$$ = new BlockNode; }

%%

enum LexerState
{
    LEX_NEXT,
    LEX_OUTPUT,
};

vector<Token>* TokenList;
int idx = 0;
int subIdx = -1;

void set_tokens(vector<Token>* tokens)
{
    TokenList = tokens;
}

void set_ast_callback(void (*callback)(ASTTree*))
{
    ASTCallback = callback;
}
void reset_parser()
{
    TokenList = nullptr;
    idx = 0;
    subIdx = -1;
}

int yylex()
{
    auto t = (int)idx >= (int)(TokenList->size());
    if(t)
        return 0;

    if(subIdx < 0)
    {
        if(TokenList->at(idx).name == "id")
        {
            auto node = new TokenNode;
            node->token = TokenList->at(idx);
            idx++;
            subIdx = -1;
            yylval = node;
            return ID;
        }
        else if(TokenList->at(idx).name == "int" | TokenList->at(idx).name == "void")
        {
            auto node = new TokenNode;
            node->token = TokenList->at(idx);
            idx++;
            subIdx = -1;
            yylval = node;
            return TYPE;
        }
        else
        {
            subIdx = 0;
        }
    }
    
    char chr = TokenList->at(idx).name[subIdx++];
    if(subIdx >= TokenList->at(idx).name.size())
    {
        idx++;
        subIdx = -1;
    }
    return chr;
}
}
}