#pragma once
#include "Instruction.h"
#include "../assembly_instructions/MovInstruction.h"
class AssignVariableToVariableInstruction : public Instruction
{
public:
    AssignVariableToVariableInstruction(const Parameters *fromVariable, const Parameters *toVariable) : fromVariable(fromVariable), toVariable(toVariable)
    {
    }

    void generateAssembly()
    {
        std::string leftValue;
        leftValue += std::to_string(fromVariable->position);
        leftValue += "(%rbp)";

        std::string rightValue;
        rightValue += "%eax";

        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));

        leftValue = "%eax";
        rightValue = std::to_string(toVariable->position);
        rightValue += "(%rbp)";
        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));
    }

private:
    const Parameters *fromVariable;
    const Parameters *toVariable;
};