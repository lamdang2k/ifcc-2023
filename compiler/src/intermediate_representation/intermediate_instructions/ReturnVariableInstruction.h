#pragma once
#include "Instruction.h"
#include "../assembly_instructions/MovInstruction.h"

class ReturnVariableInstruction : public Instruction
{
public:
    ReturnVariableInstruction(Parameters *variableParams) : variableParams(variableParams)
    {
    }

    void generateAssembly()
    {
        std::string leftValue;
        leftValue += std::to_string(variableParams->position);
        leftValue += "(%rbp)";

        std::string rightValue;
        rightValue += "%eax";
        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));
    }

private:
    const Parameters *variableParams;
};
