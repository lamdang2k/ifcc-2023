#include "Instruction.h"

class CallInstruction : public Instruction
{
public:
    CallInstruction(const std::string &functionName) : functionName(functionName)
    {
    }

    std::string toAssembly()
    {
        std::string assembly;
        assembly += "call " + functionName + " \n";
        return assembly;
    }

private:
    const std::string functionName;
};