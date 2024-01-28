/* apparently unused */

#include "Instruction.h"

class AssignVariableToRegisterInstruction : public Instruction
{
public:
    AssignVariableToRegisterInstruction(Parameters* variableParams, std::string registerName) : variableParams(variableParams), registerName(registerName)
    {

    }

    std::string toAssembly()
    {
        std::string assembly;
        assembly += "movl ";
        assembly += std::to_string(variableParams->position);
        assembly += "(%rbp)";
        assembly += ", ";
        assembly += "%";
        assembly += registerName;
        assembly += "\n";
        return assembly;
    }

private:
    const Parameters* variableParams;
    const std::string registerName;
};