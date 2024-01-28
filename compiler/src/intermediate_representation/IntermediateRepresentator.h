#pragma once
#include <Token.h>
#include <map>
#include <string>
#include <unordered_map>
#include <stack>
#include "ControlFlowGraph.h"
#include "FunctionDefinition.h"
#include "intermediate_instructions/Instruction.h"
#include "../symbol_table/SymbolTable.h"
#include "../feedback/SemanticFeedbackListenable.h"
#include "../feedback/FeedbackState.h"

class IntermediateRepresentator : public SemanticFeedbackListenable
{
public:
    IntermediateRepresentator()
    {
    }
    void addControlFlowGraph (const string& functionName, ControlFlowGraph* cfg);
    void addFunctionDefinition (const string& functionName, FunctionDefinition* funcDef);
    void addInstruction(Instruction *instruction);
    std::string createTemporaryVariable(const std::string &variableType);
    void createArray(const std::string &variableType, const std::string &variableName, int size);
    std::string popTemporaryVariable();
    void addTempVariable(const std::string &variableName);
    void addVariableToSymbolTable(const std::string &variableType, const std::string &variableName, bool isTraceable = false);
    void addBasicBlock(BasicBlock *basicBlock);

    // getters and setters
    void setCurrentFunctionName(std::string &functionName);
    void setCurrentType(std::string type);
    void setCurrentBinaryOperator(std::string binaryOperator);
    void setCurrentControlFlowGraph(ControlFlowGraph *cfg);
    void setCurrentConst(std::string constValue);
    std::string getCurrentFunctionName();
    std::string getCurrentType();
    std::string getCurrentBinaryOperator();
    ControlFlowGraph *getControlFlowGraph(const string &functionName);
    const std::unordered_map<string, ControlFlowGraph *> &getMapControlFlowGraph();
    ControlFlowGraph *getCurrentControlFlowGraph();
    FunctionDefinition* getFunctionDefinition (const string& functionName);
    Parameters *getVariableFromSymbolTable(const std::string &variableName, bool isTracking = false);
    Parameters *getVariableArrayFromSymbolTable(const std::string &variableName, int index);
    std::string getArrayVariableName(const std::string &variableName, int index);
    std::string getCurrentConst();

    // Output functions
    void toAssembly(ostream &o);

    // feedback functions
    void checkFeedbackSymbolTable(std::string variableName, antlr4::Token *token);
    void checkAlreadyDefinedFunction(std::string variableName, antlr4::Token *token);
    void checkVariableInsideSymbolTable(const std::string &variableName);
    bool checkFunctionDefinitionCoherence(const std::string& functionName,FunctionDefinition* d1, FunctionDefinition* d2,antlr4::Token * token);
    bool checkFunctionCallDefinitionCoherence(const std::string& functionName,FunctionDefinition* d1, FunctionDefinition* d2,antlr4::Token * token);
    bool checkFunctionExistence(const std::string& functionName,antlr4::Token * token);
    bool isVariableUnused(const std::string &variableName);

    int getStackSize()
    {
        return temporaryVariables.size();
    }

    ~IntermediateRepresentator()
    {
        for (auto &cfg : mapControlFlowGraph)
        {
            delete (cfg.second);
        }
    }

private:
    std::unordered_map<string, ControlFlowGraph *> mapControlFlowGraph;   
    ControlFlowGraph *currentControlFlowGraph;
    std::unordered_map<string,FunctionDefinition*> mapFunctionDefinition;
    std::string currentFunctionName;
    std:: string currentType;
    std:: string currentConst;
    std::string currentBinaryOperator = "";
    std::stack<std::string> temporaryVariables;
    int indexTemporaryVariables = 0;
};