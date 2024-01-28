#pragma once
#include <unordered_map>
#include <string>
#include "../feedback/FeedbackState.h"
using namespace std;

struct Parameters
{
    std::string type = "";
    int position = -1;
    int numberOfUtilisation = 0;
    bool isTraceable = false;
    int id = -1;
};

class SymbolTable
{
public:
    SymbolTable(): parentContext(nullptr) {}
    SymbolTable(SymbolTable* parentContext): parentContext(parentContext) {}

    void addSymbol(std::string variableType, std::string variableName, bool isTraceable = false);

    string addTempSymbol(string variableType);

    Parameters * getSymbol(std::string variableName, bool withFeedback = true);
    
    FeedbackState getFeedback();

    SymbolTable* getParentContext();

    int getRSPFunctionOffset();

    void remove(std::string variable);

    int getSymbolCount()
    {
        return symbolCount;
    };

    void calculateSymbolsPositions();

    std::string toString();

    int getInputParamsCount() {
        return inputParamsCount;
    };

    void synchronize(SymbolTable* context) {
        symbolCount = context->getSymbolCount();
        inputParamsCount = context->getInputParamsCount();
    }

private:
    std::unordered_map<std::string, Parameters> symbolTable;
    FeedbackState feedbackState = FeedbackState::OK;
    int symbolCount = 0;
    int inputParamsCount = 0;
    int closetNumberDivisibleBy16 (int input);
    SymbolTable* parentContext;
};