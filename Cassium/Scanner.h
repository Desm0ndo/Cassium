#pragma once

#include <list>
#include "Token.h"

using namespace std;

class Scanner {
	public:
	Scanner ();
	~Scanner ();
	list<Token> Scan (string src);

	private:
	string source;
	list<Token> tokens;
	int pos;
	int linenum;
	int linepos;
	Token ScanIdentifier ();
	Token ScanString ();
};

