#pragma once

// Interface to flex
extern int yylineno;
void yyerror(const char *s, ...);

// Nodes in the AST
struct ast {
	int nodetype;
	struct ast *left;
	struct ast *right;
};

struct numval {
	int nodetype;
	int number;
};

struct list {
	struct ast *val;
	struct list *next;
};

// AST Helper functions
struct ast *newast(int nodetype, struct ast *left, struct ast *right);
struct ast *newnum(int num);

struct list *newlist();
struct list *newlist(struct ast *);
struct list *growlist(struct ast *, struct list *);
void freelist(struct list *);
void printlist(struct list *);

int evalAst(struct ast *);
void printAst(struct ast* a);
void freeAst(struct ast *);

class Node {
public:
	virtual ~Node() { }
};

class NExpression : public Node {
};
