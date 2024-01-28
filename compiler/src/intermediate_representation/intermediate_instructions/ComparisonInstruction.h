#pragma once
#include "Instruction.h"
#include "../assembly_instructions/MovInstruction.h"
#include "../assembly_instructions/CmpInstruction.h"
#include "../assembly_instructions/SetInstruction.h"
#include "../assembly_instructions/MovzInstruction.h"

using namespace std;
enum compSigns
{
    EQUAL = 0,
    NEQUAL = 1,
    GREATER = 2,
    LESS = 3,
    GREATER_OR_EQUAL = 4,
    LESS_OR_EQUAL = 5
};

class ComparisonInstruction : public Instruction
{
public:
    ComparisonInstruction(compSigns sign, Parameters* left, Parameters* right, Parameters* stockVariable) :leftExpr(left), rightExpr(right), compSign(sign), stockVariable(stockVariable)
    {
    }

    void generateAssembly()
    {
        /* Adding movl and cmpl instructions and then raising flags*/
        std::string leftValue;
        leftValue += std::to_string(leftExpr->position);
        leftValue += "(%rbp)";

        std::string rightValue;
        rightValue += "%eax";

        assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));

        leftValue = std::to_string(rightExpr->position);
        leftValue += "(%rbp)";
        rightValue = "%eax";

        assemblyInstructions.push_back(new CmpInstruction(leftValue, rightValue, ByteType::L));

        if (compSign == EQUAL)
        {
            assemblyInstructions.push_back(new SetInstruction(std::string("e"), std::string("%al")));
        }
        else if (compSign == NEQUAL)
        {
            assemblyInstructions.push_back(new SetInstruction(std::string("ne"), std::string("%al")));
        }
        else if (compSign == LESS)
        {
            assemblyInstructions.push_back(new SetInstruction(std::string("l"), std::string("%al")));
        }
        else if (compSign == GREATER)
        {
            assemblyInstructions.push_back(new SetInstruction(std::string("g"), std::string("%al")));
        }
        else if (compSign == LESS_OR_EQUAL)
        {
            assemblyInstructions.push_back(new SetInstruction(std::string("le"), std::string("%al")));
        }
        else if (compSign == GREATER_OR_EQUAL)
        {
            assemblyInstructions.push_back(new SetInstruction(std::string("ge"), std::string("%al")));
        }
        
        assemblyInstructions.push_back(new MovzInstruction(std::string("%al"), std::string("%eax"), ByteType::B, ByteType::L));

        leftValue = "%eax";
        rightValue = std::to_string(stockVariable->position);
        rightValue += "(%rbp)";
		assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));
    }

private:
    const Parameters* leftExpr;
    const Parameters* rightExpr;
    const Parameters* stockVariable;
    const compSigns compSign;
};