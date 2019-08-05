/*! This file holds definitions for the network protocol */

enum opcode {
	ERR,
	SET,
	GET,
	DEL
};

enum subSpecifier {
	nID,
	gID,
	tID,
	pID
};

enum detail {
	empty,
	input,
	output,
	inout,
	state,
	nID,
	pID,
	gID
};

