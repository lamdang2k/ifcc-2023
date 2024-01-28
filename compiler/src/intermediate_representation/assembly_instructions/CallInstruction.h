#pragma once
#include "AssemblyInstruction.h"
class CallInstruction : public AssemblyInstruction
{

public:
    CallInstruction(std::string leftValue) : AssemblyInstruction(leftValue)
    {
    }

    std::string toString()
    {
        std::string assembly;
        assembly += "   call ";
        assembly += leftValue;
        assembly += "\n";
        return assembly;
    }
};