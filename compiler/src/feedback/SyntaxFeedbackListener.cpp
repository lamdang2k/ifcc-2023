#include "SyntaxFeedbackListener.h"
#include "FeedbackOutputFormat.h"
#include <iostream>
#include <vector>

void SyntaxFeedbackListener::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine,
                                         const std::string &msg, std::exception_ptr e)
{
    // TODO: Find a way for recovering the name of the function, expected characters.
    std::string functionName = "???";
    std::vector<std::string> expectedCharacters = {"?", "??", "???"};
    std::string direction = "before";

    std::string selectedCharacter = offendingSymbol->getText();

    std::string expectedCharactersMessage;

    if (expectedCharacters.size() > 0)
    {
        expectedCharactersMessage += "expected ";

        for (int i = 0; i < expectedCharacters.size() - 2; i++)
        {
            expectedCharactersMessage += "‘";
            expectedCharactersMessage += expectedCharacters[i];
            expectedCharactersMessage += "’, ";
        }

        if (expectedCharacters.size() == 1)
        {
            expectedCharactersMessage += "‘";
            expectedCharactersMessage += expectedCharacters[0];
            expectedCharactersMessage += "’ ";
        }
        else
        {
            expectedCharactersMessage += "‘";
            expectedCharactersMessage += expectedCharacters[expectedCharacters.size() - 2];
            expectedCharactersMessage += "’ or ‘";
            expectedCharactersMessage += expectedCharacters[expectedCharacters.size() - 1];
            expectedCharactersMessage += "’ ";
        }
        expectedCharactersMessage += direction;
        expectedCharactersMessage += " ";
        expectedCharactersMessage += "‘";
        expectedCharactersMessage += selectedCharacter;
        expectedCharactersMessage += "’";
    }

    FeedbackOutputFormat::positionFeedbackOutput(filepath, functionName);
    FeedbackOutputFormat::descriptionFeedbackOutput(line, charPositionInLine, filepath, "error", expectedCharactersMessage);
    FeedbackOutputFormat::ilustrateFeedbackOutput(line, charPositionInLine, fileContent, selectedCharacter, "error");

    error = true;
}