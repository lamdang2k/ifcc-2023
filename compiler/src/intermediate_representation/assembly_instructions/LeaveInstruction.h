#pragma once
#include "AssemblyInstruction.h"
class LeaveInstruction : public AssemblyInstruction
{

public :
    LeaveInstruction() : AssemblyInstruction()
    {
    }
    
    std::string toString()
    {
        std::string assembly;
        assembly += "   leave";
        assembly += "\n";
        return assembly;
    }

};
