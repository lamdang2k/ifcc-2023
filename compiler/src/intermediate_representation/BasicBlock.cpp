#include <iostream>
#include "assembly_instructions/LabelInstruction.h"
#include "assembly_instructions/MovInstruction.h"
#include "BasicBlock.h"
#include "ControlFlowGraph.h"

void BasicBlock::addInstruction(Instruction *instruction)
{
#ifdef _DEBUG
    std::cerr << "== Adding Instruction to basic block " << std::endl;
#endif
    if (!hasReturn)
    {
        instructionSequence.push_back(instruction);
    }
}

void BasicBlock::generateAssembly()
{
    
    assemblyInstructionsSequence.push_back(new LabelInstruction(this->entry_label));
    for (Instruction *currentInstruction : instructionSequence)
    {
        
        currentInstruction->generateAssembly();
        std::vector<AssemblyInstruction *> & assemblyInstructions = currentInstruction->getAssemblyInstructions();
        assemblyInstructionsSequence.insert(assemblyInstructionsSequence.end(), assemblyInstructions.begin(), assemblyInstructions.end());
    }
    
    if (!hasReturn && entry_label.substr(0, 4) == "main")
    {
        assemblyInstructionsSequence.push_back(new MovInstruction(std::string("$0"), std::string("%eax"), ByteType::L));
    }
}

std::string BasicBlock::assemblyToString()
{
    std::string output = "";
    for (AssemblyInstruction *currentInstruction : assemblyInstructionsSequence)
    {
       output += currentInstruction->toString();
    }
    return output;
}

void BasicBlock::addAssemblyInstruction(AssemblyInstruction * instruction)
{
    assemblyInstructionsSequence.push_back(instruction);
}

void BasicBlock::modifyExitTrueBlock(BasicBlock *bb)
{
    this->exit_true = bb;
}

void BasicBlock::modifyExitFalseBlock(BasicBlock *bb)
{
    this->exit_false = bb;
}

BasicBlock *BasicBlock::getExitTrueBlock()
{
    return this->exit_true;
}

BasicBlock *BasicBlock::getExitFalseBlock()
{
    return this->exit_false;
}

std::string BasicBlock::getLabel()
{
    return this->entry_label;
}

void BasicBlock::optimize()
{
}
