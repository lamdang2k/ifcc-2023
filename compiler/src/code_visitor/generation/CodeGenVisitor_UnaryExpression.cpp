#include "CodeGenVisitor.h"
#include "../../intermediate_representation/intermediate_instructions/MinusInstruction.h"
#include "../../intermediate_representation/intermediate_instructions/NegationInstruction.h"
using namespace std;

antlrcpp::Any CodeGenVisitor::visitUnaryExpression_(ifccParser::UnaryExpression_Context *ctx)
{
    visitChildren(ctx);
    string unaryOperator = ctx->unaryOperator()->getText();
    std::string variableName = intermediateRepresentator.popTemporaryVariable();
    Parameters * variable = intermediateRepresentator.getVariableFromSymbolTable(variableName, true);

    const string variableType = variable->type;
    std::string tempVariable = intermediateRepresentator.createTemporaryVariable(variableType);

    if (unaryOperator.compare("-") == 0)
    {
        intermediateRepresentator.addInstruction(new MinusInstruction(intermediateRepresentator.getVariableFromSymbolTable(tempVariable), variable, "", false));
    }
    else if (unaryOperator.compare("!") == 0)
    {
        intermediateRepresentator.addInstruction(new NegationInstruction(intermediateRepresentator.getVariableFromSymbolTable(tempVariable), variable, "", false));
    }

    intermediateRepresentator.setCurrentBinaryOperator("");

    return defaultResult();
}
