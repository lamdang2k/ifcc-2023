#pragma once
#include "Instruction.h"
#include "../assembly_instructions/MovInstruction.h"
#include "CopyRegisterToVariableInstruction.h"

class CopyParamsToRegistersInstruction : public Instruction
{
    // TODO: Raise error when nb of args >6
public:
    CopyParamsToRegistersInstruction(const std::deque<Parameters *> &params) : params(params)
    {
    }

    void generateAssembly()
    {
        std::string assembly;
        for (int i = 0; i < params.size(); i++)
        {
            std::string leftValue;
            leftValue += std::to_string(params[i]->position);
            leftValue += "(%rbp)";

            std::string rightValue;
            rightValue += availableRegisters[i];
            assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));
        }
    }

private:
    std::deque<Parameters *> params;
};
