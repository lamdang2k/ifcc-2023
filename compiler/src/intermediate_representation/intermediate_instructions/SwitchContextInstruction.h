#pragma once
#include "Instruction.h"

class SwitchContextInstruction : public Instruction
{
public:
    SwitchContextInstruction(SymbolTable* context) : context(context)
    {
    }

    void generateAssembly()
    {

    }
    
    void verifyContext(ControlFlowGraph *controlFlowGraph)
    {
        controlFlowGraph->switchContext(context);
    }

private:
    SymbolTable* context;
};