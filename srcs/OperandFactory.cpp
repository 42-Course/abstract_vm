#include "OperandFactory.hpp"
#include "Int8.hpp"
#include "Int16.hpp"
#include "Int32.hpp"
#include "Float.hpp"
#include "Double.hpp"
#include "AbstractVMException.hpp"

const std::array<OperandFactory::CreateFn, 5> OperandFactory::_createFunctions = {
    &OperandFactory::createInt8,
    &OperandFactory::createInt16,
    &OperandFactory::createInt32,
    &OperandFactory::createFloat,
    &OperandFactory::createDouble
};

const IOperand* OperandFactory::createOperand(eOperandType type, const std::string& value) const {
    // Cast enum to size_t to use as array index
    size_t index = static_cast<int>(type);

    // Bounds check (should never fail if eOperandType is valid, just in case design changes later)
    if (index >= _createFunctions.size()) {
        throw std::invalid_argument("Invalid operand type");
    }

    // Call the appropriate creation method using the static array
    // Syntax: (this->*functionPointer)(arguments)
    return (this->*_createFunctions[index])(value);
}

const IOperand* OperandFactory::createInt8(const std::string& value) const {
    return new Int8(value);
}

const IOperand* OperandFactory::createInt16(const std::string& value) const {
    return new Int16(value);
}

const IOperand* OperandFactory::createInt32(const std::string& value) const {
    return new Int32(value);
}

const IOperand* OperandFactory::createFloat(const std::string& value) const {
    return new Float(value);
}

const IOperand* OperandFactory::createDouble(const std::string& value) const {
    return new Double(value);
}
