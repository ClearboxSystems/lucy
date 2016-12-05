%skeleton "lalr1.cc"
%require "3.0.2"

%verbose

%defines
%define parser_class_name {Parser}
%define api.namespace {bison}

%code requires{
    #include "tree.hpp"

    class STree;
}

%code provides{
    # define YY_DECL \
        bison::Parser::token yylex(STree &tree)

    YY_DECL;
}

%parse-param { STree &tree }


%union {
    ASTNode *node;
    int num;
    char *symbol;
    std::vector<ASTNode*> *nodes;
}

%destructor {
    if ($$)  { delete ($$); ($$) = nullptr; }
} <node>

%define api.token.prefix {}

%token <num> NUMBER 
%token <symbol> IDENT
%token ASSIGN
%token ADD SUB MUL DIV EQUAL
%token OP CP OL CL LS
%token SEMICOLON
%token LET
%token END

%type <node> exp
%type <nodes> list

%left ADD SUB
%left MUL DIV
%nonassoc UMINUS

%%
%start calclist;

calclist: /* nothing */ 
  exp END { tree.set_root($1); printf("Hello\n"); }
 ;

list: { $$ = new std::vector<ASTNode *>(); }
 | exp { $$ = new std::vector<ASTNode *>(); $$->push_back($1); }
 | list LS exp { $$ = $1; $$->push_back($3); }
 ;

exp: exp ADD exp        { $$ = new BinaryNode('+', $1, $3); }
 | exp SUB exp          { $$ = new BinaryNode('-', $1, $3); }
 | exp MUL exp          { $$ = new BinaryNode('*', $1, $3); }
 | exp DIV exp          { $$ = new BinaryNode('/', $1, $3); }
 | OP exp CP            { $$ = $2; }
 | OL list CL           { $$ = new ListNode($2); } 
 | SUB exp %prec UMINUS { $$ = new UnaryNode('M', $2); }
 | NUMBER               { $$ = new NumberNode($1); }
 ;


%%

void
bison::Parser::error( const std::string &err_message )
{
   std::cerr << "Error: " << err_message << "\n";
}
