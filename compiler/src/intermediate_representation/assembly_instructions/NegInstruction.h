#pragma once
#include "AssemblyInstruction.h"
class NegInstruction : public AssemblyInstruction
{

public :
    NegInstruction(std::string leftValue, ByteType byteType) : AssemblyInstruction(leftValue, "", byteType)
    {
    }

    std::string toString()
    {
        std::string assembly;
        assembly += "   neg";
        assembly += getByteTypeTermination();
        assembly += " ";
        assembly += leftValue;
        assembly += "\n";
        return assembly;
    }
};
