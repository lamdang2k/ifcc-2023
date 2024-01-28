#pragma once

#include "antlr4-runtime.h"
#include "../../grammar_generated_files/ifccBaseVisitor.h"
#include "../../intermediate_representation/IntermediateRepresentator.h"

using namespace std;

class CodeFeedbackVisitor : public ifccBaseVisitor, public SemanticFeedbackListenable
{
public:
	CodeFeedbackVisitor(IntermediateRepresentator &intermediateRepresentator) : intermediateRepresentator(intermediateRepresentator)
	{
	}

	virtual antlrcpp::Any visitSingleAssignment_(ifccParser::SingleAssignment_Context *ctx);
	virtual antlrcpp::Any visitFunctionDefinition_(ifccParser::FunctionDefinition_Context *ctx) override;
	virtual antlrcpp::Any visitFunctionPrototype_(ifccParser::FunctionPrototype_Context *ctx) override;
private:
	IntermediateRepresentator &intermediateRepresentator;
};