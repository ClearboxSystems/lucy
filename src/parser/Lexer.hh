#pragma once

#if !defined (yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL int Lexer::yylex()

#include "BisonParser.hh"

class Lexer : public yyFlexLexer {
	int yylex();
	lucy::Parser::semantic_type *yylval;

public:
	Lexer();
	void setInput(std::istream *in);
	int yylex(lucy::Parser::semantic_type *l_val);
};

