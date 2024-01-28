#pragma once
#include "AssemblyInstruction.h"
class TestInstruction : public AssemblyInstruction
{

public:
    TestInstruction(std::string leftValue, std::string rightValue, ByteType byteType) : AssemblyInstruction(leftValue, rightValue, byteType)
    {
    }

    std::string toString()
    {
        std::string assembly;
        assembly += "   test";
        assembly += getByteTypeTermination();
        assembly += " ";
        assembly += leftValue;
        assembly += ", ";
        assembly += rightValue;
        assembly += "\n";
        return assembly;
    }
};
