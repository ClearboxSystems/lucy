#include "Lexer.hh"

namespace lucy {
using namespace std;

Lexer::Lexer() : yyFlexLexer(), yylval(nullptr) {}

void Lexer::setInput(istream *in) {
	switch_streams(in);
}

int Lexer::yylex(BisonParser::semantic_type *l_val) {
	yylval = l_val;
	return yylex();
}

}