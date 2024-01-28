#pragma once
#include "Instruction.h"
#include "../assembly_instructions/MovInstruction.h"
#include "../assembly_instructions/PopInstruction.h"
#include "../assembly_instructions/RetInstruction.h"

class EpilogueInstruction : public Instruction
{
public:
    EpilogueInstruction()
    {
    }

    void generateAssembly()
    {
        assemblyInstructions.push_back(new MovInstruction(std::string("%rbp"), std::string("%rsp"), ByteType::Q));
        assemblyInstructions.push_back(new PopInstruction(std::string("%rbp")));
        assemblyInstructions.push_back(new RetInstruction(ByteType::Q));
    }
};
