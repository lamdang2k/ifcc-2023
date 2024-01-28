#include <vector>
#include "CodeGenVisitor.h"
#include "../../intermediate_representation/intermediate_instructions/AssignVariableToVariableInstruction.h"
#include "../../intermediate_representation/intermediate_instructions/AssignArrayToVariableInstruction.h"
#include "../../intermediate_representation/intermediate_instructions/AssignVariableToArrayInstruction.h"

antlrcpp::Any CodeGenVisitor::visitArrayDeclaration_(ifccParser::ArrayDeclaration_Context *ctx)
{
    return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitSingleArrayAssignement_(ifccParser::SingleArrayAssignement_Context *ctx)
{
    std::string variableName = ctx->VAR()->getText();
    std::string variableType = intermediateRepresentator.getCurrentType();
    std::vector<ifccParser::ExpressionContext *> expressions = ctx->expression();
    int arraySizeRightAssignment = expressions.size() - 1;
    std::vector<ifccParser::ExpressionContext *>::iterator currentExpression = expressions.begin();

    visit(*currentExpression);
    if (arraySizeRightAssignment == 0)
    {
        //std::string arraySizeVariableName = intermediateRepresentator.popTemporaryVariable();
        arraySizeRightAssignment = stoi(intermediateRepresentator.getCurrentConst());
        intermediateRepresentator.createArray(variableType, variableName, arraySizeRightAssignment);
    }
    else
    {
        intermediateRepresentator.createArray(variableType, variableName, arraySizeRightAssignment);
        ++currentExpression;
        int currentArrayIndex = 0;
        while (currentExpression != expressions.end())
        {
            visit(*currentExpression);
            std::string currentExpressionName = intermediateRepresentator.popTemporaryVariable();
            std::string currentVariableArrayName = intermediateRepresentator.getArrayVariableName(variableName, currentArrayIndex);
            intermediateRepresentator.addInstruction(new AssignVariableToVariableInstruction(intermediateRepresentator.getVariableFromSymbolTable(currentExpressionName,true), intermediateRepresentator.getVariableFromSymbolTable(currentVariableArrayName)));

            ++currentArrayIndex;
            ++currentExpression;
        }
    }
    return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitDereferenceExpression_(ifccParser::DereferenceExpression_Context *ctx)
{
    visit(ctx->expression());
    std::string sizeVariableName = intermediateRepresentator.popTemporaryVariable();
    std::string variableArrayName = ctx->VAR()->getText();

    Parameters *firstElementParameters = intermediateRepresentator.getVariableArrayFromSymbolTable(variableArrayName, 0);

    std::string temporaryVariable = intermediateRepresentator.createTemporaryVariable(firstElementParameters->type);
    intermediateRepresentator.addInstruction(new AssignArrayToVariableInstruction(firstElementParameters, intermediateRepresentator.getVariableArrayFromSymbolTable(sizeVariableName, 0), intermediateRepresentator.getVariableArrayFromSymbolTable(temporaryVariable, 0)));

    intermediateRepresentator.setCurrentBinaryOperator("");

    return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitArrayAssignmentExpression_(ifccParser::ArrayAssignmentExpression_Context *ctx)
{
    visit(ctx->expression(0));
    std::string sizeVariableName = intermediateRepresentator.popTemporaryVariable();
    std::string variableArrayName = ctx->VAR()->getText();

    visit(ctx->expression(1));
    std::string expressionVariableName = intermediateRepresentator.popTemporaryVariable();

    intermediateRepresentator.addInstruction(new AssignVariableToArrayInstruction(intermediateRepresentator.getVariableFromSymbolTable(expressionVariableName, true), intermediateRepresentator.getVariableFromSymbolTable(variableArrayName), intermediateRepresentator.getVariableFromSymbolTable(sizeVariableName)));

    Parameters *firstElementParameters = intermediateRepresentator.getVariableArrayFromSymbolTable(variableArrayName, 0);
    std::string temporaryVariable = intermediateRepresentator.createTemporaryVariable(firstElementParameters->type);
    intermediateRepresentator.addInstruction(new AssignVariableToVariableInstruction(intermediateRepresentator.getVariableFromSymbolTable(expressionVariableName, true), intermediateRepresentator.getVariableFromSymbolTable(temporaryVariable)));

    intermediateRepresentator.setCurrentBinaryOperator("");
    return defaultResult();
}
