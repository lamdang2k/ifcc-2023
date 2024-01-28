#pragma once
#include "AssemblyInstruction.h"
class PopInstruction : public AssemblyInstruction
{

public:
    PopInstruction(std::string leftValue, ByteType byteType = ByteType::NONE) : AssemblyInstruction(leftValue, "", byteType)
    {
    }

    std::string toString()
    {
        std::string assembly;
        assembly += "   pop";
        assembly += getByteTypeTermination();
        assembly += " ";
        assembly += leftValue;
        assembly += "\n";
        return assembly;
    }
};
