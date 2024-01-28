#include "CodeFeedbackVisitor.h"

antlrcpp::Any CodeFeedbackVisitor::visitSingleAssignment_(ifccParser::SingleAssignment_Context *ctx)
{
    std::string variableName = ctx->VAR()->getText();
    if(intermediateRepresentator.isVariableUnused(variableName))
    {
        std::string functionName = intermediateRepresentator.getCurrentFunctionName();
        size_t charPositionInLine = ctx->getStart()->getCharPositionInLine();
        size_t line = ctx->getStart()->getLine();
        std::string errorMessage = "unused variable ‘";
        errorMessage += variableName;
        errorMessage += "’";
        notifyFeedbackListeners(functionName, variableName, line, charPositionInLine, errorMessage, "warning");
    }
    return visitChildren(ctx);
}

antlrcpp::Any CodeFeedbackVisitor::visitFunctionDefinition_(ifccParser::FunctionDefinition_Context *ctx)
{
    std::string functionName = intermediateRepresentator.getCurrentFunctionName();
    /*
    string functionName = visit(ctx->functionSignature()).as<std::string>();
	ControlFlowGraph *currentCfg = intermediateRepresentator.getCfg(functionName);
	intermediateRepresentator.setCurrentCfg(currentCfg);
    */
    return visitChildren(ctx);
}

antlrcpp::Any CodeFeedbackVisitor::visitFunctionPrototype_(ifccParser::FunctionPrototype_Context *ctx)
{
	visitChildren(ctx);

	string functionName = ctx->VAR()->getText();
	intermediateRepresentator.setCurrentFunctionName(functionName);

	return defaultResult();
}