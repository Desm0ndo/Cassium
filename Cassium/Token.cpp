#include "stdafx.h"
#include "Token.h"
#include <string>

using namespace std;

Token::Token (TokenType tktype, string val) {
	type = tktype;
	value = val;
}

Token::~Token () {
}
