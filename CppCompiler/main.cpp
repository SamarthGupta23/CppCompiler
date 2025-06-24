// main.cpp - Comprehensive test for the bytecode system
#include "common.hpp"
#include "chunk.hpp"
#include "debug.hpp"
#include "value.hpp"

int main() {
    std::cout << "=== BYTECODE VM TEST SUITE ===" << std::endl << std::endl;

    // Test 1: Simple constant loading
    std::cout << "TEST 1: Simple constant loading" << std::endl;
    Chunk simpleChunk;
    simpleChunk.initChunk();

    Value val1(42.0);
    int index1 = simpleChunk.addConstant(val1);
    simpleChunk.writeChunk(Opcode::OP_CONSTANT);
    simpleChunk.writeChunk(static_cast<Opcode>(index1));
    simpleChunk.writeChunk(Opcode::OP_RETURN);

    disassembleChunk(simpleChunk, "Simple Test");
    simpleChunk.freeChunk();

    std::cout << std::endl << "Expected: Load constant 42, then return" << std::endl;
    std::cout << std::string(50, '-') << std::endl << std::endl;

    // Test 2: Multiple constants (simulating arithmetic expression like: 1.2 + 3.4)
    std::cout << "TEST 2: Multiple constants (simulating: 1.2 + 3.4)" << std::endl;
    Chunk mathChunk;
    mathChunk.initChunk();

    // Load first operand
    Value operand1(1.2);
    int idx1 = mathChunk.addConstant(operand1);
    mathChunk.writeChunk(Opcode::OP_CONSTANT);
    mathChunk.writeChunk(static_cast<Opcode>(idx1));

    // Load second operand  
    Value operand2(3.4);
    int idx2 = mathChunk.addConstant(operand2);
    mathChunk.writeChunk(Opcode::OP_CONSTANT);
    mathChunk.writeChunk(static_cast<Opcode>(idx2));

    // Note: We don't have OP_ADD yet, but this shows the pattern
    // mathChunk.writeChunk(Opcode::OP_ADD); // Future opcode

    mathChunk.writeChunk(Opcode::OP_RETURN);

    disassembleChunk(mathChunk, "Math Expression");
    mathChunk.freeChunk();

    std::cout << std::endl << "Expected: Load 1.2, load 3.4, return (ADD would go between)" << std::endl;
    std::cout << std::string(50, '-') << std::endl << std::endl;

    // Test 3: Complex expression with many constants (simulating: (1.0 + 2.0) * (3.0 - 4.0))
    std::cout << "TEST 3: Complex expression simulation" << std::endl;
    Chunk complexChunk;
    complexChunk.initChunk();

    // Left side: 1.0 + 2.0
    Value c1(1.0);
    Value c2(2.0);
    int i1 = complexChunk.addConstant(c1);
    int i2 = complexChunk.addConstant(c2);

    complexChunk.writeChunk(Opcode::OP_CONSTANT);
    complexChunk.writeChunk(static_cast<Opcode>(i1));
    complexChunk.writeChunk(Opcode::OP_CONSTANT);
    complexChunk.writeChunk(static_cast<Opcode>(i2));
    // complexChunk.writeChunk(Opcode::OP_ADD); // Future

    // Right side: 3.0 - 4.0
    Value c3(3.0);
    Value c4(4.0);
    int i3 = complexChunk.addConstant(c3);
    int i4 = complexChunk.addConstant(c4);

    complexChunk.writeChunk(Opcode::OP_CONSTANT);
    complexChunk.writeChunk(static_cast<Opcode>(i3));
    complexChunk.writeChunk(Opcode::OP_CONSTANT);
    complexChunk.writeChunk(static_cast<Opcode>(i4));
    // complexChunk.writeChunk(Opcode::OP_SUBTRACT); // Future

    // Multiply results
    // complexChunk.writeChunk(Opcode::OP_MULTIPLY); // Future

    complexChunk.writeChunk(Opcode::OP_RETURN);

    disassembleChunk(complexChunk, "Complex Expression");
    complexChunk.freeChunk();

    std::cout << std::endl << "Expected: Four constants loaded in sequence, then return" << std::endl;
    std::cout << std::string(50, '-') << std::endl << std::endl;

    // Test 4: Edge cases - duplicate constants
    std::cout << "TEST 4: Duplicate constants test" << std::endl;
    Chunk duplicateChunk;
    duplicateChunk.initChunk();

    Value same1(99.9);
    Value same2(99.9);  // Same value
    Value different(88.8);

    int idx_a = duplicateChunk.addConstant(same1);
    int idx_b = duplicateChunk.addConstant(same2);  // Will be stored separately
    int idx_c = duplicateChunk.addConstant(different);

    duplicateChunk.writeChunk(Opcode::OP_CONSTANT);
    duplicateChunk.writeChunk(static_cast<Opcode>(idx_a));
    duplicateChunk.writeChunk(Opcode::OP_CONSTANT);
    duplicateChunk.writeChunk(static_cast<Opcode>(idx_b));
    duplicateChunk.writeChunk(Opcode::OP_CONSTANT);
    duplicateChunk.writeChunk(static_cast<Opcode>(idx_c));
    duplicateChunk.writeChunk(Opcode::OP_RETURN);

    disassembleChunk(duplicateChunk, "Duplicate Constants");
    duplicateChunk.freeChunk();

    std::cout << std::endl << "Expected: 99.9, 99.9, 88.8 (duplicates stored separately)" << std::endl;
    std::cout << std::string(50, '-') << std::endl << std::endl;

    // Test 5: Large constant pool
    std::cout << "TEST 5: Large constant pool stress test" << std::endl;
    Chunk largeChunk;
    largeChunk.initChunk();

    // Add many constants
    for (int i = 0; i < 10; i++) {
        Value val(i * 1.1 + 0.5);  // Creates: 0.5, 1.6, 2.7, 3.8, etc.
        int idx = largeChunk.addConstant(val);
        largeChunk.writeChunk(Opcode::OP_CONSTANT);
        largeChunk.writeChunk(static_cast<Opcode>(idx));
    }
    largeChunk.writeChunk(Opcode::OP_RETURN);

    disassembleChunk(largeChunk, "Large Constant Pool");
    largeChunk.freeChunk();

    std::cout << std::endl << "Expected: 10 constants from 0.5 to 10.4, then return" << std::endl;
    std::cout << std::string(50, '-') << std::endl << std::endl;

    std::cout << "=== ALL TESTS COMPLETED ===" << std::endl;

    return 0;
}