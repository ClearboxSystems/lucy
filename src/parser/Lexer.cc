#include "Lexer.hh"

Lexer::Lexer() : yyFlexLexer(), yylval(nullptr) {}

void Lexer::setInput(std::istream *in) {
	switch_streams(in);
}

int Lexer::yylex(lucy::Parser::semantic_type *l_val) {
	yylval = l_val;
	return yylex();
}

