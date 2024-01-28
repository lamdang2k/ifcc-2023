#pragma once
#include "AssemblyInstruction.h"
class CltdInstruction : public AssemblyInstruction
{

public :
    CltdInstruction() : AssemblyInstruction()
    {
    }

    std::string toString()
    {
        std::string assembly;
        assembly += "   cltd\n";
        return assembly;
    }
};