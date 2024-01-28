#pragma once
#include "AssemblyInstruction.h"
class AddInstruction : public AssemblyInstruction
{

public:
    AddInstruction(std::string leftValue, std::string rightValue, ByteType byteType) : AssemblyInstruction(leftValue, rightValue, byteType)
    {
    }
    std::string toString()
    {
        std::string assembly;
        assembly += "   add";
        assembly += getByteTypeTermination();
        assembly += " ";
        assembly += leftValue;
        assembly += ", ";
        assembly += rightValue;
        assembly += "\n";
        return assembly;
    }
};