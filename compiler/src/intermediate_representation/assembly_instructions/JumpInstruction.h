#pragma once
#include "AssemblyInstruction.h"
class JumpInstruction : public AssemblyInstruction
{

public:
    JumpInstruction(std::string jmpType, std::string rightValue) : AssemblyInstruction(jmpType, rightValue, ByteType::NONE)
    {
    }

    std::string toString()
    {
        std::string assembly;
        assembly += "   ";
        assembly += leftValue;
        assembly += " ";
        assembly += rightValue;
        assembly += "\n";
        return assembly;
    }

};
