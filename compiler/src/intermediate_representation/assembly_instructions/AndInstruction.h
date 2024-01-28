#pragma once
#include "AssemblyInstruction.h"
class AndInstruction : public AssemblyInstruction
{

public:
    AndInstruction(std::string leftValue, std::string rightValue, ByteType byteType) : AssemblyInstruction(leftValue, rightValue, byteType)
    {
    }
    
    std::string toString()
    {
        std::string assembly;
        assembly += "   and";
        assembly += getByteTypeTermination();
        assembly += " ";
        assembly += leftValue;
        assembly += ", ";
        assembly += rightValue;
        assembly += "\n";
        return assembly;
    }
};