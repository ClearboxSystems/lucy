#include "parser.hpp"

#include <iostream>
#include <sstream>
#include <string>


Parser::Parser ()
  : trace_scanning (false), trace_parsing (false)
{
  variables["one"] = 1;
  variables["two"] = 2;
}

Parser::~Parser () {
}

int Parser::parse (const std::string &f) {
  file = f;
  scan_begin ();
  yy::BisonParser parser (*this);
  parser.set_debug_level (trace_parsing);
  int res = parser.parse ();
  scan_end ();
  return res;
}

int Parser::parse (std::istringstream &iss) {
  this->iss = &iss;
  scan_begin ();
  yy::BisonParser parser (*this);
  parser.set_debug_level (trace_parsing);
  int res = parser.parse ();
  scan_end ();
  return res;
}


void Parser::error (const yy::location& l, const std::string& m) {
  std::cerr << l << ": " << m << std::endl;
}

void Parser::error (const std::string& m) {
  std::cerr << m << std::endl;
}

int main (int argc, char *argv[]) {
  int res = 0;
  int parsed = 0;
  Parser parser;
  for (int i = 1; i < argc; ++i)
    if (argv[i] == std::string ("-p"))
      parser.trace_parsing = true;
    else if (argv[i] == std::string ("-s"))
      parser.trace_scanning = true;
    else if (!parser.parse(argv[i])) {
      std::cout << parser.result << std::endl;      
      parsed = 1;
    }
    else
      res = 1;

  if (!parsed) {
    std::string input;
    fprintf(stderr, "ready> ");
    while (std::getline(std::cin, input)) {
      std::istringstream iss(input);

      parser.parse(iss);
      fprintf(stderr, "ready> ");
    }
  }
  return res;
}


// int main (int argc, char *argv[]) {
//   std::string input;
//   Parser parser;

//   for (int i = 1; i < argc; ++i) {
//     if (argv[i] == std::string ("-p"))
//       parser.trace_parsing = true;
//     else if (argv[i] == std::string ("-s"))
//       parser.trace_scanning = true;
//   }

//   fprintf(stderr, "ready> ");
//   while (std::getline(std::cin, input)) {
//     std::istringstream iss(input);

//     parser.parse("-");
//     fprintf(stderr, "ready> ");
//   }
// }

