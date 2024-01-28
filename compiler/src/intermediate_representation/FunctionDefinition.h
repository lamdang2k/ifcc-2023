#pragma once
#include <string>
#include <deque>
#include "intermediate_instructions/Instruction.h"
#include "ControlFlowGraph.h"
#include "../symbol_table/SymbolTable.h"

class FunctionDefinition {
public:

	FunctionDefinition(int nbParams, deque<string> paramTypes, string returnType):nbParams(nbParams),paramTypes(paramTypes),returnType(returnType)
	{}
	~FunctionDefinition()
    {}
    int getNbParams (){return nbParams;}
    bool isEqual (FunctionDefinition* d){
        if (d->nbParams == nbParams && d->paramTypes == paramTypes && d->returnType==returnType){
            return true;
        } else return false;
    }
    string getReturnType (){return returnType;}
private:
	int nbParams;
    deque<string> paramTypes;
    string returnType;
};