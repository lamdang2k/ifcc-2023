#include "CodeGenVisitor.h"
#include "../../intermediate_representation/intermediate_instructions/AssignConstToVariableInstruction.h"

antlrcpp::Any CodeGenVisitor::visitConst_(ifccParser::Const_Context *ctx)
{
	std::string var = intermediateRepresentator.createTemporaryVariable("int");
	std::string value = ctx->CONST()->getText();
	intermediateRepresentator.setCurrentConst(value);
	intermediateRepresentator.setCurrentBinaryOperator("");
	intermediateRepresentator.addInstruction(new AssignConstToVariableInstruction(value, intermediateRepresentator.getVariableFromSymbolTable(var)));
	return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitVar_(ifccParser::Var_Context *ctx)
{
	string variableName = ctx->VAR()->getText();
	intermediateRepresentator.checkFeedbackSymbolTable(variableName, ctx->getStart());
	intermediateRepresentator.setCurrentConst("");
	intermediateRepresentator.setCurrentBinaryOperator("");
	intermediateRepresentator.addTempVariable(variableName);
	return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitConstChar_(ifccParser::ConstChar_Context *ctx)
{
	std::string var = intermediateRepresentator.createTemporaryVariable("char");
	std::string value = ctx->CONST_CHAR()->getText().substr(1, 1);
	int c = value[0];
	intermediateRepresentator.setCurrentConst(std::to_string(c));
	intermediateRepresentator.setCurrentBinaryOperator("");
	intermediateRepresentator.addInstruction(new AssignConstToVariableInstruction(value, intermediateRepresentator.getVariableFromSymbolTable(var)));
	return defaultResult();
}
