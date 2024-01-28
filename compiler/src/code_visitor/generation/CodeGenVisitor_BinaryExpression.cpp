#include "CodeGenVisitor.h"
#include "../../intermediate_representation/intermediate_instructions/ArithmeticInstruction.h"
#include "../../intermediate_representation/intermediate_instructions/ComparisonInstruction.h"
#include "../../intermediate_representation/intermediate_instructions/BitToBitInstruction.h"

antlrcpp::Any CodeGenVisitor::visitBinaryComparatorExpression_(ifccParser::BinaryComparatorExpression_Context *ctx)
{
	visit(ctx->expression(0));
	std::string leftValue = intermediateRepresentator.popTemporaryVariable();
	visit(ctx->expression(1));
	std::string rightValue = intermediateRepresentator.popTemporaryVariable();

	ifccParser::ComparisonOperatorContext *biOp = ctx->comparisonOperator();

	createBinaryComparatorInstruction(biOp, leftValue, rightValue);

	return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitBinaryBitExpression_(ifccParser::BinaryBitExpression_Context *ctx)
{
	visit(ctx->expression(0));
	std::string leftValue = intermediateRepresentator.popTemporaryVariable();
	visit(ctx->expression(1));
	std::string rightValue = intermediateRepresentator.popTemporaryVariable();

	ifccParser::BitOperatorContext *biOp = ctx->bitOperator();

	createBinaryBitInstruction(biOp, leftValue, rightValue);

	return defaultResult();
}

void CodeGenVisitor::createBinaryComparatorInstruction(ifccParser::ComparisonOperatorContext *op, std::string leftValue, std::string rightValue)
{
	compSigns sign;
	if (instanceof <ifccParser::Equal_Context>(op))
	{
		sign = EQUAL;
		intermediateRepresentator.setCurrentBinaryOperator("==");
	}
	else if (instanceof <ifccParser::Nequal_Context>(op))
	{
		sign = NEQUAL;
		intermediateRepresentator.setCurrentBinaryOperator("!=");
	}
	else if (instanceof <ifccParser::Less_Context>(op))
	{
		sign = LESS;
		intermediateRepresentator.setCurrentBinaryOperator("<");
	}
	else if (instanceof <ifccParser::Greater_Context>(op))
	{
		sign = GREATER;
		intermediateRepresentator.setCurrentBinaryOperator(">");
	}
	else if (instanceof <ifccParser::LessOrEqual_Context>(op))
	{
		sign = LESS_OR_EQUAL;
		intermediateRepresentator.setCurrentBinaryOperator("<=");
	}
	else if (instanceof <ifccParser::GreaterOrEqual_Context>(op))
	{
		sign = GREATER_OR_EQUAL;
		intermediateRepresentator.setCurrentBinaryOperator(">=");
	}

	std::string stockResultVariable = intermediateRepresentator.createTemporaryVariable("int");
	intermediateRepresentator.addInstruction(new ComparisonInstruction(sign,
																	   intermediateRepresentator.getVariableFromSymbolTable(leftValue, true),
																	   intermediateRepresentator.getVariableFromSymbolTable(rightValue, true),
																	   intermediateRepresentator.getVariableFromSymbolTable(stockResultVariable)));
}

void CodeGenVisitor::createBinaryBitInstruction(ifccParser::BitOperatorContext *op, std::string leftValue, std::string rightValue)
{
	bitSigns sign;
	if (instanceof <ifccParser::Or_Context>(op))
	{
		sign = OR;
		intermediateRepresentator.setCurrentBinaryOperator("|");
	}
	else if (instanceof <ifccParser::And_Context>(op))
	{
		sign = AND;
		intermediateRepresentator.setCurrentBinaryOperator("&");
	}
	else if (instanceof <ifccParser::Xor_Context>(op))
	{
		sign = XOR;
		intermediateRepresentator.setCurrentBinaryOperator("^");
	}

	std::string stockResultVariable = intermediateRepresentator.createTemporaryVariable("int");
	intermediateRepresentator.addInstruction(new BitToBitInstruction(sign,
																	 intermediateRepresentator.getVariableFromSymbolTable(leftValue, true),
																	 intermediateRepresentator.getVariableFromSymbolTable(rightValue, true),
																	 intermediateRepresentator.getVariableFromSymbolTable(stockResultVariable)));
}

antlrcpp::Any CodeGenVisitor::visitPlusMinusExpression_(ifccParser::PlusMinusExpression_Context *ctx)
{
	visit(ctx->expression(0));
	std::string leftValue = intermediateRepresentator.popTemporaryVariable();
	visit(ctx->expression(1));
	std::string rightValue = intermediateRepresentator.popTemporaryVariable();

	ifccParser::PlusMinusOperatorContext *biOp = ctx->plusMinusOperator();

	arithSigns sign;
	if (instanceof <ifccParser::PlusBinary_Context>(biOp))
	{
		sign = PLUS;
		intermediateRepresentator.setCurrentBinaryOperator("+");
	}
	else if (instanceof <ifccParser::MinusBinary_Context>(biOp))
	{
		sign = MINUS;
		intermediateRepresentator.setCurrentBinaryOperator("-");
	}

	std::string stockResultVariable = intermediateRepresentator.createTemporaryVariable("int");
	intermediateRepresentator.addInstruction(new ArithmeticInstruction(sign,
																	   intermediateRepresentator.getVariableFromSymbolTable(leftValue, true),
																	   intermediateRepresentator.getVariableFromSymbolTable(rightValue, true),
																	   intermediateRepresentator.getVariableFromSymbolTable(stockResultVariable)));

	intermediateRepresentator.setCurrentBinaryOperator("");
	return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitMultDivExpression_(ifccParser::MultDivExpression_Context *ctx)
{
	visit(ctx->expression(0));
	std::string leftValue = intermediateRepresentator.popTemporaryVariable();
	visit(ctx->expression(1));
	std::string rightValue = intermediateRepresentator.popTemporaryVariable();

	ifccParser::MultDivisionOperatorContext *operatorContext = ctx->multDivisionOperator();
	arithSigns binaryOperator;
	if (instanceof <ifccParser::MultOperator_Context>(operatorContext))
	{
		binaryOperator = MULT;
		intermediateRepresentator.setCurrentBinaryOperator("*");
	}
	else if (instanceof <ifccParser::ModulusOperator_Context>(operatorContext))
	{
		binaryOperator = MODULUS;
		intermediateRepresentator.setCurrentBinaryOperator("%");
	}
	else if (instanceof <ifccParser::DivisionOperator_Context>(operatorContext))
	{
		binaryOperator = DIVISION;
		intermediateRepresentator.setCurrentBinaryOperator("/");
	}

	std::string stockResultVariable = intermediateRepresentator.createTemporaryVariable("int");
	intermediateRepresentator.addInstruction(new ArithmeticInstruction(binaryOperator,
																	   intermediateRepresentator.getVariableFromSymbolTable(leftValue, true),
																	   intermediateRepresentator.getVariableFromSymbolTable(rightValue, true),
																	   intermediateRepresentator.getVariableFromSymbolTable(stockResultVariable)));

	intermediateRepresentator.setCurrentBinaryOperator("");
	return defaultResult();
}