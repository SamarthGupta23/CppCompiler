#include "value.hpp"

void valueArray::initValueVector()
{
    this->ValueVector = {};
}

void valueArray::writeValueVector(Value value)
{
    this->ValueVector.push_back(value);
}

void valueArray::freeValueVector()
{
    this->ValueVector.clear();
}

double Value::getDouble()
{
    if (this->type == valueType::NUMBER)
    {
        return this->data.number;
    }
    else
    {
        throw std::runtime_error("NOT A DOUBLE");
    }
}
