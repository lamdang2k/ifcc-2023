#pragma once
#include "AssemblyInstruction.h"
class MovzInstruction : public AssemblyInstruction
{

public:
    MovzInstruction(std::string leftValue, std::string rightValue, ByteType fromByteType, ByteType byteType) : AssemblyInstruction(leftValue, rightValue, byteType), fromType(fromByteType)
    {
    }

    std::string toString()
    {
        std::string assembly;
        assembly += "   movz";
        assembly += getByteTypeTermination(fromType);
        assembly += getByteTypeTermination();
        assembly += " ";
        assembly += leftValue;
        assembly += ", ";
        assembly += rightValue;
        assembly += "\n";
        return assembly;
    }

private:
    ByteType fromType;
};
