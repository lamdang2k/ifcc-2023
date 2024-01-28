#pragma once
#include "Instruction.h"
#include "ConditionInstruction.h"
#include "../assembly_instructions/MovInstruction.h"
#include "../assembly_instructions/TestInstruction.h"
#include "../assembly_instructions/JumpInstruction.h"

class WhileInstruction : public Instruction
{
public:
    WhileInstruction(const string &op, const string &jumpblockLabel, const Parameters *tempVar, const withConditionIfElseWhile &hasCondition) : op(op), blockLabel(jumpblockLabel), tempVar(tempVar), hasCondition(hasCondition)
    {
    }

    void generateAssembly()
    {
        if (hasCondition == TRUE)
        {
            if (op == "")
            {
                std::string leftValue;
                leftValue += std::to_string(tempVar->position);
                leftValue += "(%rbp)";
                std::string rightValue = "%eax";

                assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));

                assemblyInstructions.push_back(new TestInstruction(std::string("%eax"), std::string("%eax"), ByteType::L));

                assemblyInstructions.push_back(new JumpInstruction(std::string("jne"), blockLabel));
            }
            if (op == ">")
            {
                assemblyInstructions.push_back(new JumpInstruction(std::string("jg"), blockLabel));
            }
            else if (op == "<")
            {
                assemblyInstructions.push_back(new JumpInstruction(std::string("jl"), blockLabel));
            }
            else if (op == "==")
            {
                assemblyInstructions.push_back(new JumpInstruction(std::string("je"), blockLabel));
            }
            else if (op == "!=")
            {
                assemblyInstructions.push_back(new JumpInstruction(std::string("jne"), blockLabel));
            }
            else if (op == ">=")
            {
                assemblyInstructions.push_back(new JumpInstruction(std::string("jge"), blockLabel));
            }
            else if (op == "<=")
            {
                assemblyInstructions.push_back(new JumpInstruction(std::string("jle"), blockLabel));
            }
        }
        else
        {
                assemblyInstructions.push_back(new JumpInstruction(std::string("jmp"), blockLabel));
        }
    }

private:
    const string op;
    const string blockLabel;
    const Parameters *tempVar;
    const withConditionIfElseWhile hasCondition;
};
