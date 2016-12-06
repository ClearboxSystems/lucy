#pragma once

#include <sstream>
#include <string>
#include <map>
#include "bison_parser.hpp"

// Tell Flex the lexer's prototype ...
# define YY_DECL yy::BisonParser::symbol_type yylex (Parser& parser)
// ... and declare it for the parser's sake.
YY_DECL;


// Conducting the whole scanning and parsing of Calc++.
class Parser {
public:
  Parser ();
  virtual ~Parser ();

  std::map<std::string, int> variables;

  int result;

  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;

  // Run the parser on file F.
  // Return 0 on success.
  int parse (const std::string& f);
  int parse (std::istringstream& iss);
  // The name of the file being parsed.
  // Used later to pass the file name to the location tracker.
  std::string file;
  std::istringstream *iss;

  // Whether parser traces should be generated.
  bool trace_parsing;

  // Error handling.
  void error (const yy::location& l, const std::string& m);
  void error (const std::string& m);
};