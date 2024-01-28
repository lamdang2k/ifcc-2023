#pragma once
#include "Instruction.h"

static const size_t number = 6;
std::string availableRegisters[number] = {"%edi", "%esi", "%edx", "%ecx", "%r8d", "%r9d"};

class CopyRegisterToVariableInstruction : public Instruction
{
    // TODO: Raise error when nb of args >6
public:
    CopyRegisterToVariableInstruction(const Parameters *variableParameters, const int index) : variableParameters(variableParameters), index(index)
    {
    }

    void generateAssembly()
    {
        std::string leftValue;
        leftValue += availableRegisters[index];
        std::string rightValue;
        rightValue += std::to_string(variableParameters->position);
        rightValue += "(%rbp)";
        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));
    }

private:
    const Parameters *variableParameters;
    const int index;
};