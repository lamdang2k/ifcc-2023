#pragma once
#include <string>

enum ByteType
{
    NONE,
    B, // Byte 8-bit
    S, // Single 32-bit
    W, // Word 16-bit
    L, // Long 32-bit or 64-bit
    Q, // Quad 64-bit
};

class AssemblyInstruction
{
public:
    AssemblyInstruction(std::string leftValue = "", std::string rightValue = "", ByteType byteType = ByteType::NONE) : leftValue(leftValue), rightValue(rightValue), byteType(byteType)
    {
    }

    std::string getLeftValue()
    {
        return leftValue;
    }

    std::string getRightValue()
    {
        return rightValue;
    }

    bool isLeftConstant()
    {
        bool isConstant = false;
        if (leftValue.size() != 0 && leftValue.at(0) == '$')
        {
            isConstant = true;
        }
        return isConstant;
    }

    std::string getByteTypeTermination()
    {
        return getByteTypeTermination(byteType);
    }

    std::string getByteTypeTermination(ByteType type)
    {
        std::string termination;
        if (type == ByteType::Q)
        {
            termination += 'q';
        }
        else if (type == ByteType::B)
        {
            termination += 'b';
        }
        else if (type == ByteType::S)
        {
            termination += 's';
        }
        else if (type == ByteType::W)
        {
            termination += 'w';
        }
        else if (type == ByteType::L)
        {
            termination += 'l';
        }

        return termination;
    }

    virtual std::string toString()
    {
        return leftValue + "\n";
    }

protected:
    std::string leftValue;
    std::string rightValue;
    ByteType byteType;
};