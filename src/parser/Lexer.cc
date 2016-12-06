#include "Lexer.hh"

Lexer::Lexer(std::istream *in) : yyFlexLexer(in), yylval(nullptr) {}

int Lexer::yylex(lucy::Parser::semantic_type *l_val) {
	yylval = l_val;
	return yylex();
}

