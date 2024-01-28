#pragma once
#include "Instruction.h"
#include "../assembly_instructions/MovInstruction.h"
#include "../assembly_instructions/OrInstruction.h"
#include "../assembly_instructions/AndInstruction.h"
#include "../assembly_instructions/XorInstruction.h"

enum bitSigns
{
    AND = 0,
    OR = 1,
    XOR = 2
};

class BitToBitInstruction : public Instruction
{
public:
    BitToBitInstruction(bitSigns s, Parameters *left, Parameters *right, Parameters *stockResult) : leftExpr(left), rightExpr(right), bitSign(s), stockResult(stockResult)
    {
    }

    void generateAssembly()
    {
        std::string leftValue;
        leftValue += std::to_string(leftExpr->position);
        leftValue += "(%rbp)";

        std::string rightValue;
        rightValue += "%eax";

        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));

        leftValue = std::to_string(rightExpr->position);
        leftValue += "(%rbp)";
        rightValue = "%eax";
        if (bitSign == OR)
        {
            assemblyInstructions.push_back(new OrInstruction(leftValue, rightValue, ByteType::L));
        }
        else if (bitSign == AND)
        {
            assemblyInstructions.push_back(new AndInstruction(leftValue, rightValue, ByteType::L));
        }
        else if (bitSign == XOR)
        {
            assemblyInstructions.push_back(new XorInstruction(leftValue, rightValue, ByteType::L));
        }

        leftValue = "%eax";
        rightValue = std::to_string(stockResult->position);
        rightValue += "(%rbp)";
        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));
    }

private:
    const Parameters *leftExpr;
    const Parameters *rightExpr;
    const bitSigns bitSign;
    const Parameters *stockResult;
};
