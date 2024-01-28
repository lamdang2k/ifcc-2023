#include "Instruction.h"
static const size_t number = 6;
std::string availableRegisters[number]={"%edi","%esi","%edx","%ecx","%r8d","%r9d"};

class CopyRegistersToVariablesInstruction : public Instruction
{
    //TODO: Raise error when nb of args >6
public:
    CopyRegistersToVariablesInstruction(const Parameters* variableParameters, const int index): variableParameters(variableParameters), index(index)
    {
    }

    std::string toAssembly()
    {
        std::string assembly;
        assembly += "movl ";
        assembly += availableRegisters[index];
        assembly += ", ";
        assembly += std::to_string(variableParameters->position);
        assembly += "(%rbp) \n";
        return assembly;
    }

private:
    const Parameters* variableParameters;
    const int index;
};