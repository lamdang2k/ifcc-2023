#pragma once
#include "AssemblyInstruction.h"
class MovInstruction : public AssemblyInstruction
{

public :
    MovInstruction(std::string leftValue, std::string rightValue, ByteType byteType) : AssemblyInstruction(leftValue, rightValue, byteType)
    {
    }
    
    std::string toString()
    {
        std::string assembly;
        assembly += "   mov";
        assembly += getByteTypeTermination();
        assembly += " ";
        assembly += leftValue;
        assembly += ", ";
        assembly += rightValue;
        assembly += "\n";
        return assembly;
    }
};
