#pragma once
#include "Instruction.h"
#include "../assembly_instructions/MovInstruction.h"
#include "../assembly_instructions/TestInstruction.h"
#include "../assembly_instructions/JumpInstruction.h"

enum withConditionIfElseWhile
{
    FALSE = 0,
    TRUE = 1
};

class ConditionInstruction : public Instruction
{
public:
    ConditionInstruction(const std::string &op, const std::string &jumpblockLabel, const Parameters *tempVar, const withConditionIfElseWhile &hasCondition) : op(op), blockLabel(jumpblockLabel), tempVar(tempVar), hasCondition(hasCondition)
    {
    }

    void generateAssembly()
    {
        if (hasCondition == TRUE)
        {
            std::string leftValue;
            leftValue += std::to_string(tempVar->position);
            leftValue += "(%rbp)";
            std::string rightValue = "%eax";

            assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));

            if (op == ">")
            {
                assemblyInstructions.push_back(new JumpInstruction(std::string("jle"), blockLabel));
            }
            else if (op == "<")
            {
                assemblyInstructions.push_back(new JumpInstruction(std::string("jge"), blockLabel));
            }
            else if (op == "==")
            {
                assemblyInstructions.push_back(new JumpInstruction(std::string("jne"), blockLabel));
            }
            else if (op == "!=")
            {
                assemblyInstructions.push_back(new JumpInstruction(std::string("je"), blockLabel));
            }
            else if (op == ">=")
            {
                assemblyInstructions.push_back(new JumpInstruction(std::string("jl"), blockLabel));
            }
            else if (op == "<=")
            {
                assemblyInstructions.push_back(new JumpInstruction(std::string("jg"), blockLabel));
            }
            else
            {
                assemblyInstructions.push_back(new JumpInstruction(std::string("je"), blockLabel));
            }
        }
        else
        {
            assemblyInstructions.push_back(new JumpInstruction(std::string("jmp"), blockLabel));
        }
    }

private:
    const std::string op;
    const std::string blockLabel;
    const Parameters *tempVar;
    const withConditionIfElseWhile hasCondition;
};
