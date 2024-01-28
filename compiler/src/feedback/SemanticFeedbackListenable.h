#pragma once
#include <string>
#include <vector>
#include "./SemanticFeedbackListener.h"

class SemanticFeedbackListenable
{

public:
    void addFeedbackListener(SemanticFeedbackListener *feedback)
    {
        feedbackListeners.push_back(feedback);
    }

protected:
    void notifyFeedbackListeners(const std::string &functionName, const std::string &offendingSymbol, size_t line, size_t charPositionInLine,
                                 const std::string &msg, const std::string &feedbackType)
    {
        for (auto currentListener : feedbackListeners)
        {
            currentListener->semanticFeedback(functionName, offendingSymbol, line, charPositionInLine, msg, feedbackType);
        }
    }
    vector<SemanticFeedbackListener *> feedbackListeners;
};