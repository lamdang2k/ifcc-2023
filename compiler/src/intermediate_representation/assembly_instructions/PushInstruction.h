#pragma once
#include "AssemblyInstruction.h"
class PushInstruction : public AssemblyInstruction
{

public :
    PushInstruction(std::string leftValue, ByteType byteType) : AssemblyInstruction(leftValue, "", byteType)
    {
    }
    
    std::string toString()
    {
        std::string assembly;
        assembly += "   push";
        assembly += getByteTypeTermination();
        assembly += " ";
        assembly += leftValue;
        assembly += "\n";
        return assembly;
    }
};