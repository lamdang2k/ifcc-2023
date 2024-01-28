#pragma once
#include <iostream>
#include <Recognizer.h>
#include <BaseErrorListener.h>
#include <Token.h>
#include <string>

class SyntaxFeedbackListener : public antlr4::BaseErrorListener
{
public:
    SyntaxFeedbackListener(const std::string & filepath, std::stringstream & content) : filepath(filepath), fileContent(content)
    {
        error = false;
    }

    bool Error()
    {
        return error;
    }

    virtual void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine,
                             const std::string &msg, std::exception_ptr e) override;

protected:
    const std::string & filepath;
    std::stringstream & fileContent;
    bool error;
};