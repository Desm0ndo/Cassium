#pragma once
#include "TokenType.h"
#include <string>

using namespace std;

class Token {
	public:
	string value;
	TokenType type;
	Token (TokenType tktype, string val);
	~Token ();
};

