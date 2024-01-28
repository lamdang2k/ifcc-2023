#pragma once
#include <map>
#include <string>
#include <vector>
#include "intermediate_instructions/Instruction.h"
#include "../symbol_table/SymbolTable.h"
#include "BasicBlock.h"

class ControlFlowGraph {
public:

	ControlFlowGraph(string functionName) : functionName(functionName)
	{
		symbolTable = new SymbolTable();
		symbolTables.push_back(symbolTable);
	}

	~ControlFlowGraph(){
		for (auto currentBasicBlock : listBasicBlocks)
	 	{
	 		delete currentBasicBlock;
		}
		for (auto currentContext : symbolTables)
	 	{
	 		delete currentContext;
		}
	 }

	void addVariableToSymbolTable(const std::string &variableType, const std::string &variableName,bool isTraceable = false);
	void addReturnVariable();
	void addBasicBlock(BasicBlock* basicBlock);
	void prologueToAssembly(BasicBlock *basicBlock);
	void epilogueToAssembly(BasicBlock *basicBlock);
	const string& getFunctionName() {return functionName;}

	const int getNextBasicBlockNumber(){return nextBasicBlockNumber;}
	void increaseBBNumber();
	void decreaseBBNumber();
	BasicBlock* getCurrentBasicBlock(){
		return currentBasicBlock;
	}
    SymbolTable* getSymbolTable();
    void addInstruction(Instruction *instruction);
	bool hasBasicBlock();
	void functionCallsFound(){
		hasFunctionCalls = true;
	}
	void removeFromTable(std::string variable);
	BasicBlock* modifyCurrentBasicBlock(BasicBlock* bb);
	void setReturnBasicBlock(BasicBlock* bb);
	BasicBlock* getReturnBasicBlock();

	void generateAssembly();
	std::string assemblyToString();
	void calculateSymbolsPositions();	
	void switchContext(SymbolTable* context);
	void addContext(SymbolTable* context);

	std::string toString();
	void optimize();

private:
	SymbolTable* symbolTable;
	std::vector <SymbolTable*> symbolTables;
	std::vector <BasicBlock*> listBasicBlocks; /**< all the basic blocks of this CFG*/
	BasicBlock* currentBasicBlock;
	int nextBasicBlockNumber = 0;
  	string functionName;
	bool hasFunctionCalls = false;
	BasicBlock* returnBasicBlock = nullptr;
};