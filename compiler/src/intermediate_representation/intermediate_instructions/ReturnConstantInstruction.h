#include "Instruction.h"

class ReturnConstantInstruction : public Instruction
{
public:
    ReturnConstantInstruction(std::string constValue) : constValue(constValue)
    {
    }

    std::string toAssembly()
    {
        std::string assembly;
        assembly += "movl $";
        assembly += constValue;
        assembly += ", %eax \n";
        return assembly;
    }

private:
    const std::string constValue;
};