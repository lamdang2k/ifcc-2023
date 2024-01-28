#include "Instruction.h"

class AssignRegisterToVariableInstruction : public Instruction
{
public:
    AssignRegisterToVariableInstruction(Parameters* currentVariable) : variableParams(currentVariable)
    {

    }

    std::string toAssembly()
    {
        std::string assembly;
        assembly += "movl ";
        assembly += "%eax";
        assembly += ", ";
        assembly += std::to_string(variableParams->position);
        assembly += "(%rbp) \n";
        return assembly;
    }

private:
    const Parameters* variableParams;
};