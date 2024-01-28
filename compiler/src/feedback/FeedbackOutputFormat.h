#pragma once
#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

enum Style
{
    MAJENTA,
    RED,
    BOLD,
    RESET,
};

class StyleOutput
{
public:
    std::string getCode(Style style)
    {
        std::string output;
        std::streambuf const *osbuf = std::cout.rdbuf();
        if (isTerminal(osbuf))
        {
            if (style == Style::MAJENTA)
            {
                output += "\033[1;35m";
            }
            else if (style == Style::RED)
            {
                output += "\033[1;31m";
            }
            else if (style == Style::RESET)
            {
                output += "\033[0m";
            }
            else if (style == Style::BOLD)
            {
                output += "\033[1m";
            }
        }
        return output;
    }

    bool isTerminal(const std::streambuf *osbuf)
    {
        FILE *currentStream = nullptr;
        if (osbuf == coutbuf)
        {
            currentStream = stdout;
        }
        else if (osbuf == cerrbuf || osbuf == clogbuf)
        {
            currentStream = stderr;
        }
        else
        {
            return false;
        }
        return isatty(fileno(currentStream));
    }

private:
    std::streambuf const *coutbuf = std::cout.rdbuf();
    std::streambuf const *cerrbuf = std::cerr.rdbuf();
    std::streambuf const *clogbuf = std::clog.rdbuf();
};

class FeedbackOutputFormat
{
public:
    static void positionFeedbackOutput(const std::string &filepath, const std::string &functionName)
    {
        StyleOutput style;
        std::cerr << style.getCode(Style::BOLD) << filepath << style.getCode(Style::RESET) + ": ";
        std::cerr << "In function ‘" << functionName << "’:" << std::endl;
    }

    static void descriptionFeedbackOutput(size_t line, size_t charPositionInLine, const std::string &filepath, const std::string &feedbackType, const std::string &message)
    {
        StyleOutput style;
        std::cerr << style.getCode(Style::BOLD) << filepath << style.getCode(Style::RESET) + ": ";
        std::cerr << line << ":" << (charPositionInLine + 1) << ": ";

        if (feedbackType == "error")
        {
            std::cerr << style.getCode(Style::RED) + style.getCode(Style::BOLD);
        }
        else if (feedbackType == "warning")
        {
            std::cerr << style.getCode(Style::MAJENTA) + style.getCode(Style::BOLD);
        }

        std::cerr << feedbackType << ": "
                  << style.getCode(Style::RESET);

        std::cerr << message;
        std::cerr << std::endl;
    }

    static void ilustrateFeedbackOutput(size_t line, size_t charPositionInLine, std::stringstream &fileContent, const std::string &selectedCharacter, const std::string &feedbackType)
    {
        StyleOutput style;
        fileContent.seekg(0);
        int maxLineCharacters = 128;
        char buffer[maxLineCharacters];
        for (int i = 0; i < line; i++)
        {
            fileContent.getline(buffer, maxLineCharacters);
        }
        std::string lineContent = buffer;

        std::cerr << "    " << line << " |";

        for (int i = 0; i < lineContent.size(); i++)
        {
            if (i == charPositionInLine)
            {
                if (feedbackType == "error")
                {
                    std::cerr << style.getCode(Style::RED) + style.getCode(Style::BOLD);
                }
                else if (feedbackType == "warning")
                {
                    std::cerr << style.getCode(Style::MAJENTA) + style.getCode(Style::BOLD);
                }

                std::cerr << selectedCharacter << style.getCode(Style::RESET);
                i += selectedCharacter.size() - 1;
            }
            else
            {
                std::cerr << lineContent[i];
            }
        }

        std::cerr << std::endl;
        std::cerr << "      |";
        for (int i = 0; i < charPositionInLine; i++)
        {
            std::cerr << " ";
        }

        if (feedbackType == "error")
        {
            std::cerr << style.getCode(Style::RED) + style.getCode(Style::BOLD);
        }
        else if (feedbackType == "warning")
        {
            std::cerr << style.getCode(Style::MAJENTA) + style.getCode(Style::BOLD);
        }
        std::cerr << "^";
        for (int i = 0; i < selectedCharacter.size() - 1; i++)
        {
            std::cerr << "~";
        }
        std::cerr << style.getCode(Style::RESET) << std::endl;
    }
};