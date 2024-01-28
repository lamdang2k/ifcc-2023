#pragma once
#include <string>

class SemanticFeedbackListener
{
public:
    SemanticFeedbackListener(const std::string &filepath, std::stringstream &content) : filepath(filepath), fileContent(content)
    {
        error = false;
    }

    bool Error()
    {
        return error;
    }

    virtual void semanticFeedback(const std::string &functionName, const std::string &offendingSymbol, size_t line, size_t charPositionInLine,
                               const std::string &msg, const std::string & feedbackType);

protected:
    const std::string &filepath;
    std::stringstream &fileContent;
    bool error;
};