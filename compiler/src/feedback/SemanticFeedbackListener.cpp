#include "SemanticFeedbackListener.h"
#include "FeedbackOutputFormat.h"
#include <string>

void SemanticFeedbackListener::semanticFeedback(const std::string &functionName, const std::string &offendingSymbol, size_t line, size_t charPositionInLine,
                                             const std::string &msg, const std::string &feedbackType)
{
    // FIXME : find a way of getting the function label.
    if(functionName != "")
    {
        FeedbackOutputFormat::positionFeedbackOutput(filepath, functionName);
    }

    FeedbackOutputFormat::descriptionFeedbackOutput(line, charPositionInLine, filepath, feedbackType, msg);
    FeedbackOutputFormat::ilustrateFeedbackOutput(line, charPositionInLine, fileContent, offendingSymbol, feedbackType);
    if (feedbackType == "error")
    {
        error = true;
    }
}