#pragma once
#include "Instruction.h"
#include "../assembly_instructions/MovInstruction.h"
#include "../assembly_instructions/CltdInstruction.h"
class AssignVariableToArrayInstruction : public Instruction
{
public:
    AssignVariableToArrayInstruction(Parameters* fromVariable, Parameters* currentArray, Parameters* indexVariable) : currentArray(currentArray), indexVariable(indexVariable), fromVariable(fromVariable)
    {
    }

    void generateAssembly()
    {
        std::string leftValue;
        leftValue += std::to_string(indexVariable->position);
        leftValue += "(%rbp)";

        std::string rightValue;
        rightValue += "%eax";

        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));
        assemblyInstructions.push_back(new CltdInstruction());

        leftValue = std::to_string(fromVariable->position);
        leftValue += "(%rbp)";
        rightValue = "%edx";

        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));

        leftValue = "%edx";
        rightValue = std::to_string(currentArray->position);
        rightValue += "(%rbp, %rax, ";
        rightValue += "4"; //FIXME: Different size array
        rightValue += ")";

        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));
    }

private:
    const Parameters* currentArray;
    const Parameters* indexVariable;
    const Parameters* fromVariable;
};