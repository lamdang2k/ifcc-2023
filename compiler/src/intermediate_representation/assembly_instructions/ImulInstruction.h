#pragma once
#include "AssemblyInstruction.h"
class ImulInstruction : public AssemblyInstruction
{

public :
    ImulInstruction(std::string leftValue, std::string rightValue, ByteType byteType) : AssemblyInstruction(leftValue, rightValue, byteType)
    {
    }

    std::string toString()
    {
        std::string assembly;
        assembly += "   imul";
        assembly += getByteTypeTermination(); 
        assembly += " ";
        assembly += leftValue;
        assembly += ", ";
        assembly += rightValue;
        assembly += "\n";
        return assembly;
    }
};
