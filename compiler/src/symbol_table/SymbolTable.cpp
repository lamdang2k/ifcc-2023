#include "SymbolTable.h"
#include <iostream>
using namespace std;

void SymbolTable::addSymbol(std::string variableType, std::string variableName, bool isTraceable)
{
    std::unordered_map<std::string, Parameters>::iterator variable = symbolTable.find(variableName);

    if (variable != symbolTable.end())
    {
        if (isTraceable)
        {
            feedbackState = FeedbackState::VARIABLE_ALREADY_DECLARED;
        }
    }
    else
    {
        int id = symbolCount;
        symbolTable[variableName] = Parameters{variableType, -1, 0, isTraceable, id};
        ++symbolCount;
    }
}

string SymbolTable::addTempSymbol(string variableType)
{
    string variableName = "!tmp";
    int id = symbolCount;
    variableName += to_string(id);
    symbolTable[variableName] = Parameters{variableType, id, -1, 0, false};

    ++symbolCount;
    return variableName;
}

Parameters *SymbolTable::getSymbol(std::string variableName, bool withFeedback)
{
    Parameters *variableParameters;
    std::unordered_map<std::string, Parameters>::iterator variable = symbolTable.find(variableName);

    if (variable == symbolTable.end())
    {
        if (parentContext != nullptr)
        {
            variableParameters = parentContext->getSymbol(variableName, withFeedback);
            if (variableParameters == nullptr && withFeedback)
            {
                feedbackState = FeedbackState::VARIABLE_NOT_DECLARED;
            }
        }
        else
        {
            if (withFeedback)
            {
                feedbackState = FeedbackState::VARIABLE_NOT_DECLARED;
            }
            variableParameters = nullptr;
        }
    }
    else
    {
        variableParameters = &(variable->second);
    }

    return variableParameters;
}

void SymbolTable::remove(std::string var)
{
    symbolTable.erase(var);
    --symbolCount;
}

FeedbackState SymbolTable::getFeedback()
{
    return feedbackState;
}

SymbolTable *SymbolTable::getParentContext()
{
    return parentContext;
}

void SymbolTable::calculateSymbolsPositions()
{
    for (auto &currentSymbol : symbolTable)
    {
        int id = currentSymbol.second.id;

        int address = -4 * (symbolCount - id);

        currentSymbol.second.position = address;
    }
}

int SymbolTable::getRSPFunctionOffset()
{
    int min = 0;
    // Max position
    for (auto &currentSymbol : symbolTable)
    {
        if (min > currentSymbol.second.position)
        {
            min = currentSymbol.second.position;
        }
    }
    return closetNumberDivisibleBy16(-min);
}

int SymbolTable::closetNumberDivisibleBy16(int input)
{
    if (input % 16 == 0)
        return input;
    else
    {
        int quotient = (int)input / 16;
        return (quotient + 1) * 16;
    }
}

std::string SymbolTable::toString()
{
    std::string message;
    for (auto &currentSymbol : symbolTable)
    {
        message += "{";
        message += "[type : ";
        message += currentSymbol.second.type;
        message += "][position : ";
        message += to_string(currentSymbol.second.position);
        message += "]} - ";
        message += currentSymbol.first;
        message += "\n";
    }
    return message;
}
