#include <iostream>
#include "ControlFlowGraph.h"
#include "../symbol_table/SymbolTable.h"
#include "assembly_instructions/LabelInstruction.h"
#include "assembly_instructions/PushInstruction.h"
#include "assembly_instructions/MovInstruction.h"
#include "assembly_instructions/SubInstruction.h"
#include "assembly_instructions/LeaveInstruction.h"
#include "assembly_instructions/PopInstruction.h"
#include "assembly_instructions/RetInstruction.h"

void ControlFlowGraph::addVariableToSymbolTable(const std::string &variableType, const std::string &variableName, bool isTraceable)
{
#ifdef _DEBUG
    std::cerr << "== Adding variable to symbolTable: " << variableType << "|" << variableName << std::endl;
#endif
    symbolTable->addSymbol(variableType, variableName, isTraceable);
}

void ControlFlowGraph::addReturnVariable()
{
    Parameters *param = symbolTable->getSymbol("!retvalue", false);
    if (param == nullptr)
    {
        symbolTable->addSymbol("int", "!retvalue");
    }
}

void ControlFlowGraph::addBasicBlock(BasicBlock *basicBlock)
{
    listBasicBlocks.push_back(basicBlock);
    ++nextBasicBlockNumber;
}

void ControlFlowGraph::prologueToAssembly(BasicBlock *basicBlock)
{
    std::string note;
    note += "   .globl ";
    note += functionName;
    basicBlock->addAssemblyInstruction(new AssemblyInstruction(note));

    basicBlock->addAssemblyInstruction(new LabelInstruction(functionName));
    basicBlock->addAssemblyInstruction(new PushInstruction(std::string("%rbp"), ByteType::Q));
    basicBlock->addAssemblyInstruction(new MovInstruction(std::string("%rsp"), std::string("%rbp"), ByteType::Q));

    if (hasFunctionCalls)
    {
        int offset = symbolTable->getRSPFunctionOffset();
        if (returnBasicBlock != nullptr)
        {
            offset += 8;
        }

        std::string leftValue;
        leftValue += "$";
        leftValue += to_string(offset);

        basicBlock->addAssemblyInstruction(new SubInstruction(leftValue, std::string("%rsp"), ByteType::Q));
    }
}

void ControlFlowGraph::epilogueToAssembly(BasicBlock *basicBlock)
{
    if (hasFunctionCalls)
    {
        basicBlock->addAssemblyInstruction(new LeaveInstruction());
    }
    else
    {
        basicBlock->addAssemblyInstruction(new PopInstruction(std::string("%rbp"), ByteType::Q));
    }
    basicBlock->addAssemblyInstruction(new RetInstruction(ByteType::Q));
}

void ControlFlowGraph::generateAssembly()
{
    if (listBasicBlocks.size() != 0)
    {
        /*Produces assembly instructions
        if there is no return, adds a return 0 by default
        */
        BasicBlock *firstBlock = listBasicBlocks.front();
        prologueToAssembly(firstBlock);

        for (BasicBlock *basicBlock : listBasicBlocks)
        {
            basicBlock->generateAssembly();
        }

        if (returnBasicBlock != nullptr)
        {
            returnBasicBlock->generateAssembly();
            listBasicBlocks.push_back(returnBasicBlock);
        }
        else
        {
            BasicBlock *lastBlock = listBasicBlocks.back();
            epilogueToAssembly(lastBlock);
        }
    }
}

void ControlFlowGraph::optimize()
{
    for (BasicBlock *basicBlock : listBasicBlocks)
    {
        basicBlock->optimize();
    }
}

SymbolTable *ControlFlowGraph::getSymbolTable()
{
    return symbolTable;
}

void ControlFlowGraph::addInstruction(Instruction *instruction)
{
    currentBasicBlock->addInstruction(instruction);
}

bool ControlFlowGraph::hasBasicBlock()
{
    return listBasicBlocks.size() != 0;
}

void ControlFlowGraph::increaseBBNumber()
{
    ++nextBasicBlockNumber;
}

void ControlFlowGraph::decreaseBBNumber()
{
    --nextBasicBlockNumber;
}

BasicBlock *ControlFlowGraph::modifyCurrentBasicBlock(BasicBlock *bb)
{
    this->currentBasicBlock = bb;
    return bb;
}

void ControlFlowGraph::setReturnBasicBlock(BasicBlock *bb)
{
    this->returnBasicBlock = bb;
}

BasicBlock *ControlFlowGraph::getReturnBasicBlock()
{
    return this->returnBasicBlock;
}

void ControlFlowGraph::calculateSymbolsPositions()
{
    for (SymbolTable *currentSymbolTable : symbolTables)
    {
        currentSymbolTable->calculateSymbolsPositions();
    }
}

std::string ControlFlowGraph::assemblyToString()
{
    std::string output = "";
    for (BasicBlock *basicBlock : listBasicBlocks)
    {
        output += basicBlock->assemblyToString();
    }
    return output;
}

void ControlFlowGraph::switchContext(SymbolTable *context)
{
    symbolTable = context;
}

void ControlFlowGraph::addContext(SymbolTable *context)
{
    symbolTables.push_back(context);
}

std::string ControlFlowGraph::toString()
{
    std::string message;
    message += functionName;
    message += ": \n";
    for (SymbolTable *currentSymbolTable : symbolTables)
    {
        message += currentSymbolTable->toString();
    }
    return message;
}