#include <cctype>
#include <cstdint>
#include <cstdio>
#include "token.hpp"

static std::string identifierStr; // Filled in if tok_identifier
static double numVal;             // Filled in if tok_number

int getToken() {
	static int lastChar = ' ';

	// Skip any whitespace.
  	while (isspace(LastChar))
    	lastChar = getchar();

    if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
	    identifierStr = lastChar;
    	while (isalnum((lastChar = getchar())))
      		identifierStr += lastChar;

    	if (identifierStr == "extern")
      		return tok_extern;

    	return tok_identifier;
  	}

  	if (isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+
    	std::string numStr;
    	do {
 	    	numStr += lastChar;
      		lastChar = getchar();
    	} while (isdigit(lastChar) || lastChar == '.');

    	numVal = strtod(numStr.c_str(), nullptr);
    	return tok_number;
  	}

  	if (lastChar == '#') {
    	// Comment until end of line.
    	do
      		lastChar = getchar();
    	while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

    	if (lastChar != EOF)
      		return getToken();
  	}

  	// Check for end of file.  Don't eat the EOF.
  	if (LastChar == EOF)
    	return tok_eof;

  	// Otherwise, just return the character as its ascii value.
  	int thisChar = lastChar;
  	lastChar = getchar();
  	return thisChar;
}
