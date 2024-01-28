#pragma once
#include <string>
#include "../../symbol_table/SymbolTable.h"
#include "../assembly_instructions/AssemblyInstruction.h"

class ControlFlowGraph;

class Instruction
{
public:
    virtual void generateAssembly() = 0;
    virtual void verifyContext(ControlFlowGraph *controlFlowGraph) {}
    vector<AssemblyInstruction *> & getAssemblyInstructions()
    {
        return assemblyInstructions;
    }

protected:
    vector<AssemblyInstruction *> assemblyInstructions;
};
