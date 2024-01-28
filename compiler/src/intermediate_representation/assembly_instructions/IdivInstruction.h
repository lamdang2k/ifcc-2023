#pragma once
#include "AssemblyInstruction.h"
class IdivInstruction : public AssemblyInstruction
{

public:
    IdivInstruction(std::string leftValue, ByteType byteType) : AssemblyInstruction(leftValue, "", byteType)
    {
    }

    std::string toString()
    {
        std::string assembly;
        assembly += "   idiv";
        assembly += getByteTypeTermination();
        assembly += " ";
        assembly += leftValue;
        assembly += "\n";
        return assembly;
    }
};