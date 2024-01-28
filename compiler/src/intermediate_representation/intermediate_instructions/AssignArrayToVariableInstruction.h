#pragma once
#include "Instruction.h"
#include "../assembly_instructions/MovInstruction.h"
#include "../assembly_instructions/CltdInstruction.h"


class AssignArrayToVariableInstruction : public Instruction
{
public:
    AssignArrayToVariableInstruction(Parameters* currentArray, Parameters* indexVariable, Parameters* toVariable) : currentArray(currentArray), indexVariable(indexVariable), toVariable(toVariable)
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

        leftValue = std::to_string(currentArray->position);
        leftValue += "(%rbp, %rax, ";
        //TODO : ArrayType
        leftValue += "4";
        leftValue += ")";

        rightValue = "%edx";
        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));

        
        leftValue = "%edx";
        rightValue = std::to_string(toVariable->position);
        rightValue +="(%rbp)";
        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));
    }

private:
    const Parameters* currentArray;
    const Parameters* indexVariable;
    const Parameters* toVariable;
};