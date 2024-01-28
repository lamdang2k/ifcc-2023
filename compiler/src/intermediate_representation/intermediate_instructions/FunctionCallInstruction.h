#pragma once
#include "Instruction.h"
#include "../assembly_instructions/CallInstruction.h"

class FunctionCallInstruction : public Instruction
{
public:
    FunctionCallInstruction(const std::string &functionName, const Parameters * stockResultVariable) : functionName(functionName), stockResultVariable(stockResultVariable)
    {
    }

    void generateAssembly()
    {
        assemblyInstructions.push_back(new CallInstruction(functionName));
        
        std::string leftValue = "%eax";
        std::string rightValue;
        rightValue += to_string(stockResultVariable->position);
        rightValue += "(%rbp)";
        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));
    }

private:
    const std::string functionName;
    const Parameters * stockResultVariable;
};