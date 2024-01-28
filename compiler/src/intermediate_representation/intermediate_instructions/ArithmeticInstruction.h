#pragma once
#include "Instruction.h"
#include "../assembly_instructions/MovInstruction.h"
#include "../assembly_instructions/AddInstruction.h"
#include "../assembly_instructions/ImulInstruction.h"
#include "../assembly_instructions/SubInstruction.h"
#include "../assembly_instructions/CltdInstruction.h"
#include "../assembly_instructions/IdivInstruction.h"

enum arithSigns
{
  PLUS = 0,
  MINUS = 1,
  MULT = 2,
  MODULUS = 3,
  DIVISION = 4,
};

class ArithmeticInstruction : public Instruction
{
public:
  ArithmeticInstruction(arithSigns sign, Parameters *left, Parameters *right, Parameters *stockResult) : leftExpr(left), rightExpr(right), arithSign(sign), stockResult(stockResult)
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

    if (arithSign == PLUS)
    {
      std::string leftValue;
      leftValue += std::to_string(rightExpr->position);
      leftValue += "(%rbp)";

      std::string rightValue;
      rightValue += "%eax";

      assemblyInstructions.push_back(new AddInstruction(leftValue, rightValue, ByteType::L));
    }
    else if (arithSign == MULT)
    {
      std::string leftValue;
      leftValue += std::to_string(rightExpr->position);
      leftValue += "(%rbp)";

      std::string rightValue;
      rightValue += "%eax";

      assemblyInstructions.push_back(new ImulInstruction(leftValue, rightValue, ByteType::L));
    }
    else if (arithSign == MINUS)
    {
      std::string leftValue;
      leftValue += std::to_string(rightExpr->position);
      leftValue += "(%rbp)";

      std::string rightValue;
      rightValue += "%eax";

      assemblyInstructions.push_back(new SubInstruction(leftValue, rightValue, ByteType::L));
    }
    else if (arithSign == MODULUS)
    {
      assemblyInstructions.push_back(new CltdInstruction());

      std::string leftValue;
      leftValue += std::to_string(rightExpr->position);
      leftValue += "(%rbp)";
      assemblyInstructions.push_back(new IdivInstruction(leftValue, ByteType::L));

      assemblyInstructions.push_back(new MovInstruction(std::string("%edx"), std::string("%eax"), ByteType::L));
    }
    else if (arithSign == DIVISION)
    {
      assemblyInstructions.push_back(new CltdInstruction());

      std::string leftValue;
      leftValue += std::to_string(rightExpr->position);
      leftValue += "(%rbp)";

      assemblyInstructions.push_back(new IdivInstruction(leftValue, ByteType::L));
    }

    leftValue = "%eax";
    rightValue = std::to_string(stockResult->position);
    rightValue += "(%rbp)";
    assemblyInstructions.push_back(new MovInstruction(leftValue, rightValue, ByteType::L));
  }

private:
  const Parameters *leftExpr;
  const Parameters *rightExpr;
  const arithSigns arithSign;
  const Parameters *stockResult;
};
