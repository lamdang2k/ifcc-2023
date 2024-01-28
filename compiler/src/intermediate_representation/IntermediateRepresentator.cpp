#include "IntermediateRepresentator.h"
#include "../symbol_table/SymbolTable.h"
#include <iostream>
using namespace std;

void IntermediateRepresentator::addControlFlowGraph(const string &functionName, ControlFlowGraph *cfg)
{
    std::pair<string, ControlFlowGraph *> newGraph(functionName, cfg);
    mapControlFlowGraph.insert(newGraph);
}

void IntermediateRepresentator::addFunctionDefinition(const string &functionName, FunctionDefinition *funcDef)
{
    std::pair<string, FunctionDefinition *> newFunctionDef(functionName, funcDef);
    mapFunctionDefinition.insert(newFunctionDef);
}

ControlFlowGraph *IntermediateRepresentator::getControlFlowGraph(const string &functionName)
{
    std::unordered_map<string, ControlFlowGraph *>::iterator cfgToFind = mapControlFlowGraph.find(functionName);
    if (cfgToFind == mapControlFlowGraph.end())
    {
        return nullptr;
    }
    else
    {
        return cfgToFind->second;
    }
}

FunctionDefinition *IntermediateRepresentator::getFunctionDefinition(const string &functionName)
{
    std::unordered_map<string, FunctionDefinition *>::iterator funcDefToFind = mapFunctionDefinition.find(functionName);
    if (funcDefToFind == mapFunctionDefinition.end())
    {
        return nullptr;
    }
    else
    {
        return funcDefToFind->second;
    }
}

const std::unordered_map<string, ControlFlowGraph *> &IntermediateRepresentator::getMapControlFlowGraph()
{
    return mapControlFlowGraph;
}

void IntermediateRepresentator::setCurrentControlFlowGraph(ControlFlowGraph *cfg)
{
    currentControlFlowGraph = cfg;
}

ControlFlowGraph *IntermediateRepresentator::getCurrentControlFlowGraph()
{
    return currentControlFlowGraph;
}

void IntermediateRepresentator::addInstruction(Instruction *instruction)
{
    currentControlFlowGraph->addInstruction(instruction);
}

void IntermediateRepresentator::addBasicBlock(BasicBlock *bb)
{
    currentControlFlowGraph->addBasicBlock(bb);
}
void IntermediateRepresentator::addVariableToSymbolTable(const std::string &variableType, const std::string &variableName, bool isTraceable)
{
    currentControlFlowGraph->addVariableToSymbolTable(variableType, variableName, isTraceable);
}
void IntermediateRepresentator::addTempVariable(const std::string &variableName)
{
    temporaryVariables.push(variableName);
}

void IntermediateRepresentator::toAssembly(ostream &o)
{

    for (auto &iteratorControlFlowGraph : mapControlFlowGraph)
    {
        iteratorControlFlowGraph.second->calculateSymbolsPositions();
        // std::cerr << iteratorControlFlowGraph.second->toString() << std::endl;
    }

    for (auto &cfg : mapControlFlowGraph)
    {
        cfg.second->generateAssembly();
    }

    std::string output = "";
    for (auto &iteratorControlFlowGraph : mapControlFlowGraph)
    {
        output += iteratorControlFlowGraph.second->assemblyToString();
    }

    o << output;
}

void IntermediateRepresentator::setCurrentType(std::string type)
{
    currentType = type;
}

std::string IntermediateRepresentator::getCurrentType()
{
    return currentType;
}

void IntermediateRepresentator::setCurrentFunctionName(std::string &functionName)
{
    currentFunctionName = functionName;
}

std::string IntermediateRepresentator::getCurrentFunctionName()
{
    return currentFunctionName;
}

std::string IntermediateRepresentator::getCurrentBinaryOperator()
{
    return currentBinaryOperator;
}

void IntermediateRepresentator::setCurrentBinaryOperator(std::string binaryOperator)
{
    currentBinaryOperator = binaryOperator;
}

std::string IntermediateRepresentator::createTemporaryVariable(const std::string &variableType)
{
    std::string variableName = "!tempVariable_";
    variableName += std::to_string(indexTemporaryVariables);
    indexTemporaryVariables++;
    addVariableToSymbolTable(variableType, variableName);
    temporaryVariables.push(variableName);
    return variableName;
}

std::string IntermediateRepresentator::popTemporaryVariable()
{
    std::string variableName = temporaryVariables.top();
    temporaryVariables.pop();
    return variableName;
}

void IntermediateRepresentator::createArray(const std::string &variableType, const std::string &variableName, int size)
{
    for (int currentVariableIndex = 0; currentVariableIndex < size; currentVariableIndex++)
    {
        bool isTraceable = false;
        if (currentVariableIndex == 0)
        {
            isTraceable = true;
        }

        std::string formatArrayVariableName = getArrayVariableName(variableName, currentVariableIndex);
        addVariableToSymbolTable(variableType, formatArrayVariableName, isTraceable);
    }
}

void IntermediateRepresentator::setCurrentConst(std::string constValue)
{
    currentConst = constValue;
}

std::string IntermediateRepresentator::getCurrentConst()
{
    return currentConst;
}

Parameters *IntermediateRepresentator::getVariableArrayFromSymbolTable(const std::string &variableName, int index)
{
    std::string formatArrayVariableName = getArrayVariableName(variableName, index);
    Parameters *firstArrayParameters = currentControlFlowGraph->getSymbolTable()->getSymbol(formatArrayVariableName);
    if (firstArrayParameters != nullptr)
    {
        firstArrayParameters->numberOfUtilisation++;
    }

    Parameters *variableParameters = currentControlFlowGraph->getSymbolTable()->getSymbol(formatArrayVariableName);

    return variableParameters;
}

std::string IntermediateRepresentator::getArrayVariableName(const std::string &variableName, int index)
{
    if (index == 0)
    {
        return variableName;
    }

    std::string formatArrayVariableName = "!";
    formatArrayVariableName += variableName;
    formatArrayVariableName += to_string(index);
    return formatArrayVariableName;
}

Parameters *IntermediateRepresentator::getVariableFromSymbolTable(const std::string &variableName, bool isTracking)
{
    Parameters *variableParameters = currentControlFlowGraph->getSymbolTable()->getSymbol(variableName);
    if (variableParameters != nullptr && variableParameters->isTraceable && isTracking)
    {
        variableParameters->numberOfUtilisation++;
    }

    return variableParameters;
}

bool IntermediateRepresentator::isVariableUnused(const std::string &variableName)
{
    Parameters *variableParameters = currentControlFlowGraph->getSymbolTable()->getSymbol(variableName);
    if (variableParameters == nullptr)
    {
        return false;
    }

    return (variableParameters->numberOfUtilisation == 0) && (variableParameters->isTraceable);
}

void IntermediateRepresentator::checkVariableInsideSymbolTable(const std::string &variableName)
{
    currentControlFlowGraph->getSymbolTable()->getSymbol(variableName);
}

void IntermediateRepresentator::checkFeedbackSymbolTable(std::string variableName, antlr4::Token *token)
{
    getVariableFromSymbolTable(variableName);

    FeedbackState feedbackSymbolTableState = currentControlFlowGraph->getSymbolTable()->getFeedback();
    std::string functionName = currentFunctionName;

    if (feedbackSymbolTableState == FeedbackState::VARIABLE_ALREADY_DECLARED)
    {
        currentFunctionName = "";
        size_t charPositionInLine = token->getCharPositionInLine();
        size_t line = token->getLine();
        std::string errorMessage = "redeclaration of ‘";
        errorMessage += variableName;
        errorMessage += "’ with no linkage";
        notifyFeedbackListeners(functionName, variableName, line, charPositionInLine, errorMessage, "error");
    }
    else if (feedbackSymbolTableState == FeedbackState::VARIABLE_NOT_DECLARED)
    {
        currentFunctionName = "";
        size_t charPositionInLine = token->getCharPositionInLine();
        size_t line = token->getLine();
        std::string errorMessage = "‘";
        errorMessage += variableName;
        errorMessage += "’ undeclared (first use in this function)";
        notifyFeedbackListeners(functionName, variableName, line, charPositionInLine, errorMessage, "error");
    }
}

void IntermediateRepresentator::checkAlreadyDefinedFunction(std::string variableName, antlr4::Token *token)
{
    if (currentControlFlowGraph->hasBasicBlock())
    {
        size_t charPositionInLine = token->getCharPositionInLine();
        size_t line = token->getLine();
        std::string errorMessage = "redefinition of ‘";
        errorMessage += variableName;
        errorMessage += "’";
        notifyFeedbackListeners("", variableName, line, charPositionInLine, errorMessage, "error");
    }
}

bool IntermediateRepresentator::checkFunctionDefinitionCoherence(const string &functionName, FunctionDefinition *d1, FunctionDefinition *d2, antlr4::Token *token)
{
    /*Verifies the coherence of function definition and declaration
    If d1 is null, i.e, there is no declaration, returns true
    */
    if (d1 != nullptr && !d1->isEqual(d2))
    {
        size_t charPositionInLine = token->getCharPositionInLine();
        size_t line = token->getLine();
        std::string errorMessage = "Incoherent definition of function ‘";
        errorMessage += functionName;
        errorMessage += "’";
        notifyFeedbackListeners("", functionName, line, charPositionInLine, errorMessage, "error");
        return false;
    }
    else
        return true;
}
bool IntermediateRepresentator::checkFunctionExistence(const string &functionName, antlr4::Token *token)
{
    /*Verifies also the existence of function definition, i.e, CFG
    always returns true if standard functions like putchar and getchar*/
    size_t charPositionInLine = token->getCharPositionInLine();
    size_t line = token->getLine();
    if (functionName != "getchar" && functionName != "putchar")
    {
        if (this->getControlFlowGraph(functionName) == nullptr)
        {
            std::string errorMessage = "Undefined reference to function ‘";
            errorMessage += functionName;
            errorMessage += "’";
            notifyFeedbackListeners("", functionName, line, charPositionInLine, errorMessage, "error");
            return false;
        }
    }
    return true;
}

bool IntermediateRepresentator::checkFunctionCallDefinitionCoherence(const string &functionName, FunctionDefinition *d1, FunctionDefinition *d2, antlr4::Token *token)
{
    /*Verifies the coherence of function definition and call
     */
    size_t charPositionInLine = token->getCharPositionInLine();
    size_t line = token->getLine();
    if (functionName != "getchar" && functionName != "putchar")
    {
        std::string errorMessage;
        if (d1 != nullptr && !d1->isEqual(d2))
        {
            errorMessage = "Incoherent call of function ‘";
            errorMessage += functionName;
            errorMessage += "’";
            if (d1->getNbParams() != d2->getNbParams())
            {
                errorMessage += ". " + to_string(d2->getNbParams()) + " argument(s) entered, while " + to_string(d1->getNbParams()) + " expected.";
            }
            notifyFeedbackListeners("", functionName, line, charPositionInLine, errorMessage, "error");
            return false;
        }
    }
    return true;
}