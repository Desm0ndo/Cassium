#include "stdafx.h"
#include "Scanner.h"
#include <list>
#include <iostream>
#include <sstream>

using namespace std;

#define CanAdvance(pos, count, src)  (pos + count < (int)src.length ())
#define Peek(pos, count, src)  (CanAdvance (pos, count, src) ? src [pos + count] : '\0')
#define Read(pos, src)  (src [++pos])

Scanner::Scanner () {
	tokens = list<Token> ();
	pos = -1;
	linenum = 0;
	linepos = 0;
}

list<Token> Scanner::Scan (string src) {
	source = src;

	cout << "Started scanning the source." << endl;
	while (CanAdvance (pos, 1, source)) {
		while (CanAdvance (pos, 1, source) && isspace (Peek (pos, 1, source)))
			++pos;
		if (!CanAdvance (pos, 1, source))
			break;
		if (isalpha (Peek (pos, 1, source)) || isdigit (Peek (pos, 1, source))) {
			tokens.push_back (ScanIdentifier ());
			continue;
		}
		switch (Peek (pos, 1, source)) {
			case '\'':
			case '"':
				cout << "Scanning string." << endl;
				tokens.push_back (ScanString ());
				break;
			case '$':
				cout << "Scanning comment." << endl;
				++pos;
				while (CanAdvance (pos, 1, source) && Peek (pos, 1, source) != '$')
					++pos;
				++pos;
				break;
			case ';':
				cout << "Scanning expression terminator (semicolon)." << endl;
				tokens.push_back (Token (TokenType::LineTerminator, string (&Read (pos, source))));
				break;
			case '(':
				cout << "Scanning opening parenthesis." << endl;
				tokens.push_back (Token (TokenType::OpeningParen, string (&Read (pos, source))));
				break;
			case ')':
				cout << "Scanning closing parenthesis." << endl;
				tokens.push_back (Token (TokenType::ClosingParen, string (&Read (pos, source))));
				break;
			case '{':
				cout << "Scanning opening bracket." << endl;
				tokens.push_back (Token (TokenType::OpeningBracket, string (&Read (pos, source))));
				break;
			case '}':
				cout << "Scanning closing bracket." << endl;
				tokens.push_back (Token (TokenType::ClosingBracket, string (&Read (pos, source))));
				break;
			case '[':
				cout << "Scanning opening square bracket." << endl;
				tokens.push_back (Token (TokenType::OpeningSquareBracket, string (&Read (pos, source))));
				break;
			case ']':
				cout << "Scanning closing square bracket." << endl;
				tokens.push_back (Token (TokenType::ClosingSquareBracket, string (&Read (pos, source))));
				break;
			case ',':
				tokens.push_back (Token (TokenType::Comma, string (&Read (pos, source))));
				break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
				cout << "Scanning binary operation." << endl;
				tokens.push_back (Token (TokenType::BinOp, string (&Read (pos, source))));
				break;
			case '<':
			case '>':
			case '=':
				cout << "Scanning comparation." << endl;
				tokens.push_back (Token (TokenType::CompOp, string (&Read (pos, source))));
				break;
			case '!':
				if (Peek (pos, 2, source) == '=') {
					cout << "Scanning comparation." << endl;
					pos += 2;
					tokens.push_back (Token (TokenType::CompOp, "!="));
					break;
				} else
					tokens.push_back (Token (TokenType::UnOp, string (&Read (pos, source))));
				break;
			case ':':
				if (Peek (pos, 2, source) == '=') {
					cout << "Scanning assignment." << endl;
					pos += 2;
					tokens.push_back (Token (TokenType::AssignOp, ":="));
					break;
				} else
					throw exception ("Expected '=' character.");
			default:
				cout << "Unexpected: " << Peek (pos, 1, source) << endl;
				throw exception ("Invalid token!");
		}
	}
	cout << "Stopped scanning the source." << endl;

	return tokens;
}

Token Scanner::ScanIdentifier () {
	stringstream accum;
	cout << "Scanning identifier." << endl;
	while (CanAdvance (pos, 1, source) && (isalnum (Peek (pos, 1, source)) || Peek (pos, 1, source) == '.'))
		accum << Read (pos, source);
	double dbl;
	accum >> noskipws >> dbl;
	bool is_double = accum.eof () && !accum.fail ();
	cout << "Identifier: " << accum.str () << endl;
	if (is_double)
		return Token (TokenType::Double, accum.str ());
	return Token (TokenType::Identifier, accum.str ());
}

Token Scanner::ScanString () {
	stringstream accum;
	char opening_char = Read (pos, source);
	while (CanAdvance (pos, 1, source)) {
		char current = Peek (pos, 1, source);
		if (current == opening_char) {
			++pos;
			break;
		} else if (current == '\'' || current == '"') {
			accum << Read (pos, source);
		} else
			accum << Read (pos, source);
	}
	cout << "String: " << accum.str () << endl;
	return Token (TokenType::String, accum.str ());
}

Scanner::~Scanner () {
}
