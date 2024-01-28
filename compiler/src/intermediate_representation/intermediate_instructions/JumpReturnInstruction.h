#pragma once
#include "Instruction.h"
#include "../assembly_instructions/JumpInstruction.h"

class JumpReturnInstruction : public Instruction
{
public:
    JumpReturnInstruction(const std::string &jumpblockLabel) : blockLabel(jumpblockLabel)
    {
    }

    void generateAssembly()
    {
        assemblyInstructions.push_back(new JumpInstruction(std::string("jmp"), blockLabel));
    }

private:
    const string blockLabel;
};
