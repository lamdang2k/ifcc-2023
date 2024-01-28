#pragma once
#include "AssemblyInstruction.h"
class OrInstruction : public AssemblyInstruction
{

public :
    OrInstruction(std::string leftValue, std::string rightValue, ByteType byteType) : AssemblyInstruction(leftValue, rightValue, byteType)
    {
    }
    
    std::string toString()
    {
        std::string assembly;
        assembly += "   or";
        assembly += getByteTypeTermination();
        assembly += " ";
        assembly += leftValue;
        assembly += ", ";
        assembly += rightValue;
        assembly += "\n";
        return assembly;
    }

private:
};
