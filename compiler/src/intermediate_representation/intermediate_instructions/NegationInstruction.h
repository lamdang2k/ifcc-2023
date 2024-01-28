#pragma once
#include "Instruction.h"
#include "../assembly_instructions/MovInstruction.h"
#include "../assembly_instructions/CmpInstruction.h"
#include "../assembly_instructions/SetInstruction.h"
#include "../assembly_instructions/MovzInstruction.h"

class NegationInstruction : public Instruction
{
public:
    NegationInstruction(Parameters* stockVariable, Parameters* rightVar, std::string rightConst, bool isConst) : stockVariable(stockVariable), rightVar(rightVar), rightConst(rightConst), isConst(isConst)
    {
    }

    void generateAssembly()
    {
        std::string leftValue = "$0";
        std::string rightValue;
        if (isConst)
        {
            rightValue += "$";
            rightValue += rightConst;
        }
        else
        {
            rightValue += std::to_string(rightVar->position);
            rightValue += "(%rbp)";
        }
        assemblyInstructions.push_back(new CmpInstruction(leftValue, rightValue, ByteType::L));
        assemblyInstructions.push_back(new SetInstruction(std::string("e"), std::string("%al")));
        assemblyInstructions.push_back(new MovzInstruction(std::string("%al"), std::string("%eax"), ByteType::B, ByteType::L));

        leftValue = "%eax";
        rightValue = std::to_string(stockVariable->position);
        rightValue += "(%rbp)";
        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));
    }

private:
    const Parameters* stockVariable;
    const Parameters* rightVar;
    const std::string rightConst;
    const bool isConst;
};