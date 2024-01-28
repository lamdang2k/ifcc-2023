#pragma once
#include "AssemblyInstruction.h"
class RetInstruction : public AssemblyInstruction
{

public:
    RetInstruction(ByteType type = ByteType::NONE) : AssemblyInstruction("", "", type)
    {
    }

    std::string toString()
    {
        std::string assembly;
        assembly += "   ret";
        assembly += getByteTypeTermination();
        assembly += "\n";
        return assembly;
    }
};