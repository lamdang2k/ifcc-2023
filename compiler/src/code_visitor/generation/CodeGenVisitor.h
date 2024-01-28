#pragma once

#include <string>
#include <map>
#include "antlr4-runtime.h"
#include "../../grammar_generated_files/ifccBaseVisitor.h"
#include "../../intermediate_representation/IntermediateRepresentator.h"
#include "../../feedback/SemanticFeedbackListenable.h"

using namespace std;

template <typename Base, typename T>
inline bool instanceof (const T *ptr)
{
	return dynamic_cast<const Base *>(ptr) != nullptr;
}

class CodeGenVisitor : public ifccBaseVisitor, public SemanticFeedbackListenable
{
public:
	CodeGenVisitor(IntermediateRepresentator &intermediateRepresentator) : intermediateRepresentator(intermediateRepresentator)
	{
	}
	virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;
	virtual antlrcpp::Any visitFunctionPrototype_(ifccParser::FunctionPrototype_Context *ctx) override;
	virtual antlrcpp::Any visitFunctionDefinition_(ifccParser::FunctionDefinition_Context *ctx) override;
	virtual antlrcpp::Any visitFunctionDeclaration_(ifccParser::FunctionDeclaration_Context *ctx) override;
	virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx) override;
	virtual antlrcpp::Any visitNestedBlock_(ifccParser::NestedBlock_Context *ctx) override;
	virtual antlrcpp::Any visitInstruction_(ifccParser::Instruction_Context *ctx) override;
	virtual antlrcpp::Any visitAssignmentExpression_(ifccParser::AssignmentExpression_Context *ctx) override;
	virtual antlrcpp::Any visitReturnInstruction_(ifccParser::ReturnInstruction_Context *ctx) override;
	virtual antlrcpp::Any visitSingleAssignment_(ifccParser::SingleAssignment_Context *ctx) override;
	virtual antlrcpp::Any visitUnaryExpression_(ifccParser::UnaryExpression_Context *ctx) override;
  	virtual antlrcpp::Any visitBinaryComparatorExpression_(ifccParser::BinaryComparatorExpression_Context *ctx) override;
	virtual antlrcpp::Any visitBinaryBitExpression_(ifccParser::BinaryBitExpression_Context *ctx) override;
	virtual antlrcpp::Any visitMultDivExpression_(ifccParser::MultDivExpression_Context *ctx) override;
	virtual antlrcpp::Any visitPlusMinusExpression_(ifccParser::PlusMinusExpression_Context *ctx) override;
	virtual antlrcpp::Any visitConst_(ifccParser::Const_Context *ctx) override;
	virtual antlrcpp::Any visitConstChar_(ifccParser::ConstChar_Context *ctx) override;
	virtual antlrcpp::Any visitVar_(ifccParser::Var_Context *ctx) override;
	virtual antlrcpp::Any visitFunctionArgs_ (ifccParser::FunctionArgs_Context* ctx) override;
	virtual antlrcpp::Any visitFunctionCall_ (ifccParser::FunctionCall_Context* ctx) override;
	virtual antlrcpp::Any visitFunctionCallArgs_ (ifccParser::FunctionCallArgs_Context* ctx) override;
	virtual antlrcpp::Any visitTypeInt_(ifccParser::TypeInt_Context *ctx) override;
  	virtual antlrcpp::Any visitTypeChar_(ifccParser::TypeChar_Context *ctx) override;
	virtual antlrcpp::Any visitIfElseInstruction_(ifccParser::IfElseInstruction_Context *ctx) override;
	virtual antlrcpp::Any visitElseifBlock(ifccParser::ElseifBlockContext *ctx) override;
	virtual antlrcpp::Any visitIfBlock(ifccParser::IfBlockContext *ctx) override;
	virtual antlrcpp::Any visitArrayDeclaration_(ifccParser::ArrayDeclaration_Context *ctx) override;
	virtual antlrcpp::Any visitSingleArrayAssignement_(ifccParser::SingleArrayAssignement_Context *ctx) override;
	virtual antlrcpp::Any visitDereferenceExpression_(ifccParser::DereferenceExpression_Context *ctx) override;
	virtual antlrcpp::Any visitArrayAssignmentExpression_(ifccParser::ArrayAssignmentExpression_Context *ctx) override;
	virtual antlrcpp::Any visitReturnType(ifccParser::ReturnTypeContext *ctx) override;
	virtual antlrcpp::Any visitSimpleDeclaration_(ifccParser::SimpleDeclaration_Context *ctx) override;
	virtual antlrcpp::Any visitWhileBlock(ifccParser::WhileBlockContext *ctx) override;

private:
	IntermediateRepresentator &intermediateRepresentator;
	void createBinaryComparatorInstruction(ifccParser::ComparisonOperatorContext *op, std::string leftValue, std::string rightValue);
	void createBinaryBitInstruction(ifccParser::BitOperatorContext *op, std::string leftValue, std::string rightValue);
	std::string getBinaryValues(ifccParser::ExpressionContext *expressionContext);
};
