#pragma once
#include "AssemblyInstruction.h"
class XorInstruction : public AssemblyInstruction
{

public :
    XorInstruction(std::string leftValue, std::string rightValue, ByteType byteType) : AssemblyInstruction(leftValue, rightValue, byteType)
    {
    }
    
    std::string toString()
    {
        std::string assembly;
        assembly += "   xor";
        assembly += getByteTypeTermination();
        assembly += " ";
        assembly += leftValue;
        assembly += ", ";
        assembly += rightValue;
        assembly += "\n";
        return assembly;
    }
};
