%{
    #include "code_audit/parser.h"

    #include <map>

    using namespace std;
    #define YYSTYPE ASTNode*
    #define EXTRACT_TOKEN(NAME, TARGET)     \
        TokenNode* __temp = (TokenNode*)TARGET;   \
        Token NAME = __temp->token;         \
        delete __temp;                   

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
%right ASSIGN OP_ASSIGN //'=' "+=" "-=" "*=" "/=" "%=" "<<=" ">>=" "&=" "^=" "|="
%left OR
%left AND
%left '|'
%left '^'
%left '&'
%left EQ //"==" "!="
%left CMPR //'<' '>' "<=" ">="
%left SHIFT //"<<" ">>"
%left '+' '-'
%left '*' '/' '%'
%left '.' PTR_MBR
%right '!' '~'

%token ID
%token TYPE
%token NUMBER
%token UNSIGNED
%token IF "if"
%token ELSEIF "else if"
%token ELSE "else"
%token FOR "for"
%token WHILE "while"
%token ASSIGN // '=' "+=" "-=" "*=" "/=" "%=" "<<=" ">>=" "&=" "^=" "|="
%token OP_ASSIGN // "+=" "-=" "*=" "/=" "%=" "<<=" ">>=" "&=" "^=" "|="
%token EQ // "==" "!="
%token CMPR // '<' '>' "<=" ">="
%token SHIFT // "<<" ">>"
%token OR "||"
%token AND "&&"
%token INC "++"
%token DEC "--"
%token PTR_MBR "->"
%token STRING;
%token PREPROC;
%token RETURN;
//%token INFIX_OP '=' "+=" "-=" "*=" "/=" "%=" "<<=" ">>=" "&=" "^=" "|=" "==" "!="

%%

input:  /* empty */ { 
        auto ast = new ASTTree;
        ASTCallback(ast);
        $$ = ast;
    }
        | input global_def {
                ASTTree* root = (ASTTree*)$1;
                root->globals->push_back((FunctionDefine*)$2);
                $$ = root;
            }
;

global_def: func_def { $$ = $1; }
    | var_def ';' { $$ = $1; }
    | preprocessor { $$ = $1; }
;

/* TokenNode */
preprocessor: PREPROC { $$ = $1; }
;

func_def: type id '(' args_declare ')' block { 
    auto f = new FunctionDefine;
    ListNode<VariableDefine>* args = (ListNode<VariableDefine>*)$4;
    f->name = ((TokenNode*)$2)->token.name;
    f->type = (TypeNode*)$1;
    f->id = (TokenNode*)$2;
    f->args = args->list;
    f->body = (BlockNode*)$6;
    delete args;
    $$ = f;
 }
;

type: pointer_type     { 
        TypeNode* type = (TypeNode*)$1;
        type->sign = true;
        $$ = type;
    }
    | UNSIGNED pointer_type {
        TypeNode* type = (TypeNode*)$2;
        type->sign = false;
        $$ = type;
    }
;

pointer_type: type_name { 
        EXTRACT_TOKEN(type, $1)
        $$ = new TypeNode(true, type);
    }
    | pointer_type '*' {
        TypeNode* type = (TypeNode*)$1;
        type->pointerLevel++;
        $$ = type;
    }
;

type_name: TYPE { $$ = $1; }
    | ID { $$ = $1; }
;

id: ID { $$ = $1; }
;

args_declare: /* empty */ { $$ = new ListNode<VariableDefine>; }
    | args_declare_element {
        auto list = new ListNode<VariableDefine>;
        list->list->push_back((VariableDefine*)$1);
        $$ = list;
    }
    | args_declare ',' args_declare_element {
        ListNode<VariableDefine>* list = (ListNode<VariableDefine>*)$1;
        list->list->push_back((VariableDefine*)$3);
        $$ = list;
    }
;

/* VariableDefine */
args_declare_element: type id array_dimensions {
        auto arg = new VariableDefine((TypeNode*)$1, (TokenNode*)$2, nullptr);
        ListNode<Expression>* arr = (ListNode<Expression>*)$3;
        arg->arrayDimensions = arr->list;
        delete arr;
        $$ = arg;
    }
;

/* ListNode<Expression> */
array_dimensions: /* empty */ {
        auto node = new ListNode<Expression>;
        $$ = node;
    }
    | array_dimensions '['']' {
        ListNode<Expression>* node = (ListNode<Expression>*)$1;
        node->list->push_back(nullptr);
        $$ = node;
    }
    | array_dimensions '[' expr ']' {
        ListNode<Expression>* node = (ListNode<Expression>*)$1;
        node->list->push_back((Expression*)$3);
        $$ = node;
    }
;

/* BlockNode */
block: '{' statement_sequence '}' { 
        auto block = new BlockNode; 
        block->statements = ((ListNode<Statement>*)$2)->list;
        delete $2;
        $$ = block;
    }
;

statement_sequence: /* empty */ { $$ = new ListNode<Statement>; }
    | statement_sequence statement {
        auto list = (ListNode<Statement>*) $1;
        list->list->push_back((Statement*)$2);
        $$ = list;
    }
;

statement: expr ';' { 
        auto s = new ExpressionStatement;
        s->expression = (Expression*)$1;
        $$ = s;
    }
    | var_def ';' { $$ = $1; }
    | if_struct { $$ = $1; }
    | for_struct { $$ = $1; }
    | while_struct { $$ = $1; }
    | RETURN expr ';' { $$ = new ReturnStatement((Expression*)$2); }
;



expr: ID { 
            EXTRACT_TOKEN(token, $1)
            $$ = new Variable(token);
        }
    | constant { $$ = $1; }
    | '(' expr ')' { $$ = (Expression*)$2; }
    | prefix_expr { $$ = $1; }
    | subfix_expr { $$ = $1; }
    | array_subscript { $$ = $1; }
    | type_cast { $$ = $1; }
    | expr '+' expr { $$ = new InfixExpr("+", (Expression*)$1, (Expression*)$3); }
    | expr '-' expr { $$ = new InfixExpr("-", (Expression*)$1, (Expression*)$3); }
    | expr '*' expr { $$ = new InfixExpr("*", (Expression*)$1, (Expression*)$3); }
    | expr '/' expr { $$ = new InfixExpr("/", (Expression*)$1, (Expression*)$3); }
    | expr '%' expr { $$ = new InfixExpr("%", (Expression*)$1, (Expression*)$3); }
    | expr SHIFT expr {
        EXTRACT_TOKEN(op, $2)
        $$ = new InfixExpr(op.name, (Expression*)$1, (Expression*)$3);
    }
    | expr CMPR expr {
        EXTRACT_TOKEN(op, $2)
        $$ = new InfixExpr(op.name, (Expression*)$1, (Expression*)$3);
    }
    | expr OP_ASSIGN expr {
        EXTRACT_TOKEN(op, $2)
        $$ = new InfixExpr(op.name, (Expression*)$1, (Expression*)$3);
    }
    | expr ASSIGN expr {
        EXTRACT_TOKEN(op, $2)
        $$ = new InfixExpr(op.name, (Expression*)$1, (Expression*)$3);
    }
    | expr EQ expr {
        EXTRACT_TOKEN(op, $2)
        $$ = new InfixExpr(op.name, (Expression*)$1, (Expression*)$3);
    }
    | expr OR expr {
        EXTRACT_TOKEN(op, $2)
        $$ = new InfixExpr(op.name, (Expression*)$1, (Expression*)$3);
    }
    | expr AND expr {
        EXTRACT_TOKEN(op, $2)
        $$ = new InfixExpr(op.name, (Expression*)$1, (Expression*)$3);
    }
    | expr '&' expr {
        $$ = new InfixExpr("&", (Expression*)$1, (Expression*)$3);
    }
    | expr '|' expr {
        $$ = new InfixExpr("|", (Expression*)$1, (Expression*)$3);
    }
    | expr '^' expr {
        $$ = new InfixExpr("^", (Expression*)$1, (Expression*)$3);
    }
    | expr '.' expr {
        $$ = new InfixExpr(".", (Expression*)$1, (Expression*)$3);
    }
    | expr PTR_MBR expr {
        EXTRACT_TOKEN(op, $2)
        $$ = new InfixExpr(op.name, (Expression*)$1, (Expression*)$3);
    }
    | func_call { $$ = $1; }
;

constant: NUMBER {
        EXTRACT_TOKEN(num, $1)
        $$ = new Constant(num);
    }
    | STRING {
        EXTRACT_TOKEN(str, $1)
        $$ = new Constant(str);
    }

array_subscript: expr '[' expr ']' {
        $$ =  new ArraySubscript((Expression*)$1, (Expression*)$3);
    }

/* TypeCast */
type_cast: '(' type ')' expr {
    $$ = new TypeCast((TypeNode*)$2, (Expression*)$4);
}
;

prefix_expr: INC expr {
        EXTRACT_TOKEN(op, $1)
        $$ = new PrefixExpr(op, (Expression*) $2);
    }
    | DEC expr {
        EXTRACT_TOKEN(op, $1)
        $$ = new PrefixExpr(op, (Expression*) $2);
    }
    | '+' expr {
        Token op = {"+", "+"};
        $$ = new PrefixExpr(op, (Expression*) $2);
    }
    | '-' expr {
        Token op = {"-", "-"};
        $$ = new PrefixExpr(op, (Expression*) $2);
    }
    | '!' expr {
        Token op = {"!", "!"};
        $$ = new PrefixExpr(op, (Expression*) $2);
    }
    | '~' expr {
        Token op = {"~", "~"};
        $$ = new PrefixExpr(op, (Expression*) $2);
    }
    | '*' expr {
        Token op = {"*", "*"};
        $$ = new PrefixExpr(op, (Expression*) $2);
    }
    | '&' expr {
        Token op = {"&", "&"};
        $$ = new PrefixExpr(op, (Expression*) $2);
    }

;
subfix_expr: expr INC {
        EXTRACT_TOKEN(op, $2)
        $$ = new SubfixExpr((Expression*)$1, op);
    }
    | expr DEC {
        EXTRACT_TOKEN(op, $2)
        $$ = new SubfixExpr((Expression*)$1, op);
    }
;
/* FunctionInvokeNode */
func_call: ID '(' args_sequence ')' { 
        EXTRACT_TOKEN(id, $1)
        $$ = new FunctionInvokeNode(id, (ListNode<Expression>*)$3);
    }
;
/* ListNode<Expression> */
args_sequence: /* empty */ { $$ = new ListNode<Expression>; }
    | expr {
        auto list = new ListNode<Expression>;
        list->list->push_back((Expression*) $1);
        $$ = list;
    }
    | args_sequence ',' expr {
        ListNode<Expression>* list = (ListNode<Expression>*)$1;
        list->list->push_back((Expression*) $3);
        $$ = list;
    }
;
/* If */
if_struct: "if" '(' expr ')' block_or_line else_if_seq else_body {
        auto if_struct = new If((Expression*)$3, (BlockNode*)$5);
        if_struct->elseif = ((ListNode<ConditionStructure>*)$6)->list;
        delete $6;
        if_struct->elseBody = (BlockNode*)$7;
        $$ = if_struct;
    }
;
/* ListNode<ConditionStructure> */
else_if_seq: /* empty */ { $$ = new ListNode<ConditionStructure>; }
    | else_if_seq "else if" '(' expr ')' block_or_line {
        ListNode<ConditionStructure>* node = (ListNode<ConditionStructure>*)$1;
        node->list->push_back(new ConditionStructure((Expression*)$4, (BlockNode*)$6));
        $$ = node;
    }
;
/* BlockNode */
else_body: /* empty */ { $$ = nullptr; }
    | "else" block_or_line { $$ = $2; }
;

/* ForLoop */
while_struct: "while" '(' expr ')' block_or_line {
        auto loop = new ForLoop;
        loop->s2 = (Expression*)$3;
        loop->body = (BlockNode*)$5;
        $$ = loop;
    }
;

/* Expression? */
empty_or_expr: /* empty */ { $$ = nullptr; }
    | expr { $$ = $1; }
;

/* Expression? | VariableDefStatement? */
for_statement_1: /* empty */ { $$ = nullptr; }
    | expr { $$ = $1; }
    | var_def { $$ = $1; }
;

/* ForLoop */
for_struct: "for" '(' for_statement_1 ';' empty_or_expr ';' empty_or_expr ')' block_or_line {
        auto loop = new ForLoop;
        loop->s1 = (Expression*)$3;
        loop->s2 = (Expression*)$5;
        loop->s3 = (Expression*)$7;
        loop->body = (BlockNode*)$9;
        $$ = loop;
    }
;

/* VariableDefStatement */
var_def: type var_def_seq {
        auto def = new VariableDefStatement;
        def->vars = ((ListNode<VariableDefine>*)$2)->list;
        delete $2;
        for(auto & var : *(def->vars))
        {
            var->type = (TypeNode*)$1;
        }
        $$ = def;
    }
;

/* ListNode<VariableDefine> */
var_def_seq: var_def_element { 
        auto seq = new ListNode<VariableDefine>;
        seq->list->push_back((VariableDefine*)$1);
        $$ =  seq;
    }
    | var_def_seq ',' var_def_element {
        ListNode<VariableDefine>* seq = (ListNode<VariableDefine>*)$1;
        seq->list->push_back((VariableDefine*)$3);
        $$ = seq;
    }
;

/* VariableDefine*/
var_def_element: id array_dimensions var_def_init { 
        auto var = new VariableDefine(nullptr, (TokenNode*)$1, (Expression*)$3); 
        ListNode<Expression>* arr = (ListNode<Expression>*)$2;
        var->arrayDimensions = arr->list;
        delete arr;
        $$ = var;
    }
;

/* Expression */
var_def_init: /* empty */ { $$ = nullptr; }
    | ASSIGN expr { $$ = $2; }
    | ASSIGN struct_init { $$ = $2; }
;

/* StructInit */
struct_init: '{' struct_elements '}' {
        auto init = new StructInit;
        ListNode<Expression>* elements = (ListNode<Expression>*)$2;
        init->elements = elements->list;
        delete elements;
        $$ = init;
    }
;

/* ListNode<Expression> */
struct_elements: /* empty */ { $$ = new ListNode<Expression>; }
    | expr {
        auto elements = new ListNode<Expression>;
        elements->list->push_back((Expression*)$1);
        $$ = elements;
    }
    | struct_elements ',' expr {
        ListNode<Expression>* elements = (ListNode<Expression>*)$1;
        elements->list->push_back((Expression*)$3);
        $$ = elements;
    }
;

/* BlockNode */
block_or_line: statement { 
        auto block = new BlockNode;
        block->statements->push_back((Statement*)$1);
        $$ = block;
    }
    | block { $$ = $1; }
;

%%

enum LexerState
{
    LEX_NEXT,
    LEX_OUTPUT,
};

map<string, int> TokenMap;
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
    TokenMap["id"] = ID;
    TokenMap["number"] = NUMBER;
    TokenMap["bool"] = TYPE;
    TokenMap["char"] = TYPE;
    TokenMap["byte"] = TYPE;
    TokenMap["short"] = TYPE;
    TokenMap["int"] = TYPE;
    TokenMap["long"] = TYPE;
    TokenMap["long long"] = TYPE;
    TokenMap["float"] = TYPE;
    TokenMap["double"] = TYPE;
    TokenMap["void"] = TYPE;
    TokenMap["unsigned"] = UNSIGNED;
    TokenMap["if"] = IF;
    TokenMap["else if"] = ELSEIF;
    TokenMap["else"] = ELSE;
    TokenMap["for"] = FOR;
    TokenMap["while"] = WHILE;
    TokenMap["||"] = OR;
    TokenMap["&&"] = AND;
    TokenMap["<"] = TokenMap[">"] = TokenMap["<="] = TokenMap[">="] = CMPR;
    TokenMap["<<"] = TokenMap[">>"] = SHIFT;
    TokenMap["=="] = TokenMap["!="] = EQ;
    TokenMap["="] = ASSIGN;
    TokenMap["+="]
        =TokenMap["-="]
        =TokenMap["*="]
        =TokenMap["/="]
        =TokenMap["%="]
        =TokenMap["<<="]
        =TokenMap[">>="]
        =TokenMap["&="]
        =TokenMap["^="]
        =TokenMap["|="] = OP_ASSIGN;
    TokenMap["++"] = INC;
    TokenMap["--"] = DEC;
    TokenMap["->"] = PTR_MBR;
    TokenMap["string"] = STRING;
    TokenMap["preprocessor"] = PREPROC;
    TokenMap["return"] = RETURN;
}

int yylex()
{
    auto t = (int)idx >= (int)(TokenList->size());
    if(t)
        return 0;

    if(subIdx < 0)
    {
        if(TokenMap.find(TokenList->at(idx).name) != TokenMap.end())
        {
            auto node = new TokenNode;
            node->token = TokenList->at(idx);
            idx++;
            subIdx = -1;
            yylval = node;
            return TokenMap[node->token.name];
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