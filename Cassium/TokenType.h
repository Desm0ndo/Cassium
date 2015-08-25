#pragma once

enum TokenType {
	Identifier,
	Double,
	String,
	LineTerminator,
	OpeningBracket,
	ClosingBracket,
	OpeningSquareBracket,
	ClosingSquareBracket,
	OpeningParen,
	ClosingParen,
	BinOp,
	UnOp,
	CompOp,
	AssignOp,
	Comma,
};