#pragma once


class Token {
public:
    enum Type {
        Identifier,
        Number,
        Keyword,
        EndOfFile
    };
    
    Type type;
    
    
};



/*
emum Token {
	tok_eof = -1,

  	// keywords
	tok_extern = -2,

  	// primary
  	tok_identifier = -4,
  	tok_number = -5
}
 * 
 * */