#pragma once
#include "Instruction.h"
#include "../assembly_instructions/MovInstruction.h"

class AssignConstToVariableInstruction : public Instruction
{
public:
    AssignConstToVariableInstruction(std::string currentConstValue, Parameters* parameters) : constValue(currentConstValue), parameters(parameters)
    {
    }

    void generateAssembly()
    {
        std::string leftValue;
        leftValue += "$";
        if(parameters->type == "char")
        {
            leftValue += std::to_string(int(constValue.at(0)));
        }
        else if(parameters->type == "int")
        {
            leftValue += constValue;
        }

        std::string rightValue;
        rightValue += std::to_string(parameters->position);
        rightValue += "(%rbp)";

        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));
    }

private:
    const Parameters* parameters;
    const std::string constValue;
};