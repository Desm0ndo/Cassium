// Cassium.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Token.h"
#include "Scanner.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int _tmain(int argc, char *argv []) {
	string input = \
		"$ THIS IS A COMMENT $\n" \
		"variable := 123;\n" \
		"print (variable);\n";
	/*
	vector<string> args;
	args.assign (argv, argv + argc);
	for (string &str : args) {
		cout << "Argument: " << str << endl;
		if (str == "-i" || str == "--input")
			input = str;
		else
			cout << "Invalid argument: " << str << endl;
	}
	if (input == "") {
		cout << "No source was passed to the interpreter." << endl;
		return 1;
	}
	*/
	Scanner scanner = Scanner ();
	list<Token> tokens;
	try {
		tokens = scanner.Scan (input);
	} catch (exception e) {
		cout << "Scanning the source failed: " << e.what () << endl;
		return 1;
	}
	return 0;
}

