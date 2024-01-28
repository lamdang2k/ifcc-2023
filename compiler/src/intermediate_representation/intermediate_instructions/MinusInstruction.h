#pragma once
#include "Instruction.h"
#include "../assembly_instructions/MovInstruction.h"
#include "../assembly_instructions/NegInstruction.h"

class MinusInstruction : public Instruction
{
public:
    MinusInstruction(Parameters* stockVar, Parameters* rightVar, std::string rightConst, bool isConst) : stockVar(stockVar), rightVar(rightVar), rightConst(rightConst), isConst(isConst)
    {
    }

    void generateAssembly()
    {
        std::string leftValue;
        if (isConst)
        {
            leftValue += "$";
            leftValue += rightConst;
        }
        else
        {
            
            leftValue += std::to_string(rightVar->position);
            leftValue += "(%rbp)";
        }
        std::string rightValue = "%eax";
        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));

        leftValue = "%eax";
        assemblyInstructions.push_back(new NegInstruction(leftValue, ByteType::L));

        leftValue = "%eax";
        rightValue = std::to_string(stockVar->position);
        rightValue += "(%rbp)\n";
        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));
    }

private:
    const Parameters* stockVar;
    const Parameters* rightVar;
    const std::string rightConst;
    const bool isConst;
};