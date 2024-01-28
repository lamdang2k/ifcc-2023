#pragma once
#include "AssemblyInstruction.h"
class SubInstruction : public AssemblyInstruction
{

public:
    SubInstruction(std::string leftValue, std::string rightValue, ByteType byteType) : AssemblyInstruction(leftValue, rightValue, byteType)
    {
    }
    
    std::string toString()
    {
        std::string assembly;
        assembly += "   sub";
        assembly += getByteTypeTermination();
        assembly += " ";
        assembly += leftValue;
        assembly += ", ";
        assembly += rightValue;
        assembly += "\n";
        return assembly;
    }
};
