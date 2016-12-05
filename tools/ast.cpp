#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ast.h>

extern int yyparse();

struct ast *newast(int nodetype, struct ast *left, struct ast *right) {
	struct ast *a = (struct ast *)malloc(sizeof(struct ast));

	if (!a) {
		yyerror("out of memory");
		exit(0);
	}

	a->nodetype = nodetype;
	a->left = left;
	a->right = right;
	return a;
}

struct ast *newnum(int num) {
	struct numval *a = (struct numval *)malloc(sizeof(struct numval));

	if (!a) {
		yyerror("out of memory");
		exit(0);
	}

	a->nodetype = 'K';
	a->number = num;	
	return (struct ast *)a;
}

struct list *newlist() {
	struct list *l = (struct list *)malloc(sizeof(struct list));

	if (!l) {
		yyerror("out of memory");
		exit(0);
	}

	l->val = NULL;
	l->next = NULL;
	return l;
}

struct list *newlist(struct ast *val) {
	struct list *l = (struct list *)malloc(sizeof(struct list));

	if (!l) {
		yyerror("out of memory");
		exit(0);
	}

	l->val = val;
	l->next = NULL;
	return l;	
}

struct list *growlist(struct ast *val, struct list *next) {
		struct list *l = (struct list *)malloc(sizeof(struct list));

	if (!l) {
		yyerror("out of memory");
		exit(0);
	}

	l->val = val;
	l->next = next;
	return l;
}

void printlist(struct list *l) {
	if (l->val) {
		printAst(l->val);
	}

	if (l->next) {
		printf(", ");
		printlist(l->next);
	}
}

void freelist(struct list *l) {
	if (l->val)
		freeAst(l->val);
	if (l->next)
		freelist(l->next);	

	free(l);
}

int evalList(struct list *l) {
	return 1;
}

int evalAst(struct ast *a) {
	int v;

	switch(a->nodetype) {
		case 'K': v = ((struct numval *)a)->number; break;
		case '+': v = evalAst(a->left) + evalAst(a->right); break;
		case '-': v = evalAst(a->left) - evalAst(a->right); break;
		case '*': v = evalAst(a->left) * evalAst(a->right); break;
		case '/': v = evalAst(a->left) / evalAst(a->right); break;
		case 'M': v = - evalAst(a->right); break;
		case 'L': v = evalList((struct list *)a->right); break;
		default: printf("eval internal error: bad node %c\n", a->nodetype);
	}

	return v;
}

void printAst(struct ast* a) {	
	switch(a->nodetype) {
		case 'K': printf("%d", ((struct numval *)a)->number); break;
		case '+': printf("("); printAst(a->left); printf(" + "); printAst(a->right); printf(")"); break;
		case '-': printf("("); printAst(a->left); printf(" - "); printAst(a->right); printf(")"); break;
		case '*': printf("("); printAst(a->left); printf(" * "); printAst(a->right); printf(")"); break;
		case '/': printf("("); printAst(a->left); printf(" / "); printAst(a->right); printf(")"); break;
		case 'M': printf("("); printf(" -"); printAst(a->right); printf(")"); break;
		case 'L': printf("["); printlist((struct list *)a->right); printf("]"); break;
		default: printf("print internal error: bad node %c\n", a->nodetype);
	}
}

void freeAst(struct ast* a) {
	switch(a->nodetype) {
		case '+':
		case '-':
		case '*':
		case '/':
			freeAst(a->left);

		case 'M':
			freeAst(a->right);

		case 'K':
			free(a);
			break;

		case 'L':
			freelist((struct list *)a->right);
			free(a);
			break;

		default: printf("free internal error: bad node %c\n", a->nodetype);
	}
}

void yyerror(const char *s, ...) {
	va_list ap;
	va_start(ap, s);

	fprintf(stderr, "%d: error: ", yylineno);
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}

int main() {
	printf("> ");
	return yyparse();
}
