#pragma once
#include <map>
#include <string>
#include <vector>
#include "intermediate_instructions/Instruction.h"
#include "../symbol_table/SymbolTable.h"

class ControlFlowGraph;

class BasicBlock
{
public:
	BasicBlock(ControlFlowGraph *controlFlowGraph, string &entry_label) : controlFlowGraph(controlFlowGraph), entry_label(entry_label)
	{
	}
	
	void generateAssembly(); /**< x86 assembly code generation for this basic block (very simple) */
	void addAssemblyInstruction(AssemblyInstruction * instruction);
	std::string assemblyToString();
	void addInstruction(Instruction *instruction);
	void modifyExitTrueBlock(BasicBlock *bb);
	void modifyExitFalseBlock(BasicBlock *bb);
	BasicBlock *getExitTrueBlock();
	BasicBlock *getExitFalseBlock();
	std::string getLabel();
	void optimize();

	~BasicBlock()
	{
		for (auto i : instructionSequence)
		{
			delete i;
		}
	}
	void returnFound(){
		hasReturn = true;
	}

private:
	//nullptr is necessary, otherwise, bad_alloc.
	BasicBlock *exit_true = nullptr;	/**< pointer to the next basic block, true branch. If nullptr, return from procedure */
	BasicBlock *exit_false = nullptr;	/**< pointer to the next basic block, false branch. If null_ptr, the basic block ends with an unconditional jump */
	string entry_label;					/**< label of the BB, also will be the label in the generated code */
	string test_var_name;				/** < when generating IR code for an if(expr) or while(expr) etc,
										  store here the name of the variable that holds the value of expr */
	ControlFlowGraph *controlFlowGraph; /** < the ControlFlowGraph where this block belongs */
	bool hasReturn = false;
	std::vector<Instruction *> instructionSequence;
	std::vector<AssemblyInstruction *> assemblyInstructionsSequence;
};
