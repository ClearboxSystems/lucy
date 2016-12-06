#pragma once

#if !defined (yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL int lucy::Lexer::yylex()

#include "BisonParser.hh"
namespace lucy {
using namespace std;

class Lexer : public yyFlexLexer {
	int yylex();
	BisonParser::semantic_type *yylval;

public:
	Lexer();
	void setInput(istream *in);
	int yylex(BisonParser::semantic_type *l_val);
};

}
