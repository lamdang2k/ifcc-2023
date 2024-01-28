#pragma once
#include "AssemblyInstruction.h"
class LabelInstruction : public AssemblyInstruction
{

public:
    LabelInstruction(std::string leftValue) : AssemblyInstruction(leftValue, "", ByteType::NONE)
    {
    }
    
    std::string toString()
    {
        std::string assembly;
        assembly += leftValue;
        assembly += ":";
        assembly += "\n";
        return assembly;
    }

};
