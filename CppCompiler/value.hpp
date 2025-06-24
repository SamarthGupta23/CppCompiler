#pragma once
#include "common.hpp"
#include <variant>

enum class valueType {
    NUMBER, //the 'double' datatype
};



class Value {
public:
    valueType type;
    union {
        double number;
    }data;

    Value(double input) {     //constructor for double datatype
        type = valueType::NUMBER;  // FIX: Set the type!
        data.number = input;
    }

    double getDouble();
};

class valueArray {
public:
    std::vector <Value> ValueVector;
    void initValueVector();
    void writeValueVector(Value value);
    void freeValueVector();
};