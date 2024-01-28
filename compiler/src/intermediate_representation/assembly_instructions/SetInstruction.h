#pragma once
#include "AssemblyInstruction.h"
class SetInstruction : public AssemblyInstruction
{

public :
    SetInstruction(std::string setType, std::string rightValue) : AssemblyInstruction(setType, rightValue)
    {
    }

    std::string toString()
    {
        std::string assembly;
        assembly += "   set";
        assembly += leftValue;
        assembly += " ";
        assembly += rightValue;
        assembly += "\n";
        return assembly;
    }
};