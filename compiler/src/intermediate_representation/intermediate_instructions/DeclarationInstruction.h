#include "Instruction.h"

class DeclarationInstruction : public Instruction
{
public:
    DeclarationInstruction(const std::string &variableType, const std::string &variableName) : variableType(variableType), variableName(variableName)
    {
    }

    std::string toAssembly()
    {
        return "";
    }

private:
    const std::string variableName;
    const std::string variableType;
};