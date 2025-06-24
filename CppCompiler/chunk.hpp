#pragma once
#include "common.hpp"
enum class Opcode: uint8_t {
	OP_RETURN,
};

class Chunk {
	std::vector <Opcode> code; //vector of bytecode

public:
	void initChunk();
	void writeChunk(Opcode byte);
	void freeChunk();

	//getters
	std::vector <Opcode> getCode();
};