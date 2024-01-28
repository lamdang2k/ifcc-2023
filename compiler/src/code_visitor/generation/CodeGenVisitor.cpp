#include "CodeGenVisitor.h"
#include "../../intermediate_representation/intermediate_instructions/AssignConstToVariableInstruction.h"
#include "../../intermediate_representation/intermediate_instructions/AssignVariableToVariableInstruction.h"
#include "../../intermediate_representation/intermediate_instructions/ReturnVariableInstruction.h"
#include "../../intermediate_representation/intermediate_instructions/JumpReturnInstruction.h"
#include "../../intermediate_representation/intermediate_instructions/EpilogueInstruction.h"
#include "../../intermediate_representation/ControlFlowGraph.h"
#include <string>
#include <iostream>
#include <exception>

using namespace std;

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitBlock(ifccParser::BlockContext *ctx)
{
	/*switches context when visiting a new block of the function,
	but not the blocks of if-else-while
	*/
	SymbolTable *parentContext = intermediateRepresentator.getCurrentControlFlowGraph()->getSymbolTable();
	SymbolTable *childContext = new SymbolTable(parentContext);
	childContext->synchronize(parentContext);
	ControlFlowGraph *currentCfg = intermediateRepresentator.getCurrentControlFlowGraph();
	BasicBlock *currentBB = currentCfg->getCurrentBasicBlock();
	// if(currentBB->getLabel().substr(0,2)!=".L"){
	intermediateRepresentator.getCurrentControlFlowGraph()->addContext(childContext);
	intermediateRepresentator.getCurrentControlFlowGraph()->switchContext(childContext);
	visitChildren(ctx);
	intermediateRepresentator.getCurrentControlFlowGraph()->switchContext(parentContext);
	parentContext->synchronize(childContext);
	return defaultResult();
	//} else return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitNestedBlock_(ifccParser::NestedBlock_Context *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitInstruction_(ifccParser::Instruction_Context *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitSingleAssignment_(ifccParser::SingleAssignment_Context *ctx)
{
	visitChildren(ctx);
	if (intermediateRepresentator.getCurrentControlFlowGraph() != nullptr)
	{
		const std::string variableType = intermediateRepresentator.getCurrentType();
		const std::string variableName = ctx->VAR()->getText();
		intermediateRepresentator.addVariableToSymbolTable(variableType, variableName, true);
		intermediateRepresentator.checkFeedbackSymbolTable(variableName, ctx->getStart());
		ifccParser::ExpressionContext *expressionContext = ctx->expression();
		if (expressionContext != nullptr)
		{
			std::string tempVariable = intermediateRepresentator.popTemporaryVariable();
			intermediateRepresentator.addInstruction(new AssignVariableToVariableInstruction(intermediateRepresentator.getVariableFromSymbolTable(tempVariable, true), intermediateRepresentator.getVariableFromSymbolTable(variableName)));
		}
	}
	return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitSimpleDeclaration_(ifccParser::SimpleDeclaration_Context *ctx)
{
	std::string type = ctx->type()->getText();
	intermediateRepresentator.setCurrentType(type);
	return visitChildren(ctx);
}
antlrcpp::Any CodeGenVisitor::visitReturnInstruction_(ifccParser::ReturnInstruction_Context *ctx)
{
	/*Saves the return value in a specific variable !retval
	The fact of having more than 1 basic block justifies that there are if/else instructions
	Then one is allowed to create a new basic block to close the CFG
	Copies the return value to the %eax register
	and then jumps to this new block dedicated to return
	finally raises flag returnFound to block adding instructions
	*/
	visitChildren(ctx);
	std::string tempVar = intermediateRepresentator.popTemporaryVariable();
	ControlFlowGraph *cfg = intermediateRepresentator.getCurrentControlFlowGraph();
	BasicBlock *currentBB = cfg->getCurrentBasicBlock();
	intermediateRepresentator.addInstruction(new ReturnVariableInstruction(intermediateRepresentator.getVariableFromSymbolTable(tempVar, true)));
	int nbNextBB = cfg->getNextBasicBlockNumber();
	if (nbNextBB > 1)
	{
		// intermediateRepresentator.addInstruction(new AssignVariableToVariableInstruction(tempVar,"!retvalue"));
		BasicBlock *returnBB = cfg->getReturnBasicBlock();
		if (returnBB == nullptr)
		{
			string label;
			int nbBB = cfg->getNextBasicBlockNumber();
			++nbBB;
			label = ".L" + to_string(nbBB);
			returnBB = new BasicBlock(cfg, label);
			cfg->increaseBBNumber();
			cfg->setReturnBasicBlock(returnBB);
			// Instruction for return Basic Block
			cfg->modifyCurrentBasicBlock(returnBB);
			intermediateRepresentator.addInstruction(new EpilogueInstruction());
			cfg->modifyCurrentBasicBlock(currentBB);
		}
		intermediateRepresentator.addInstruction(new JumpReturnInstruction(returnBB->getLabel()));
	}
	currentBB->returnFound();
	return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitAssignmentExpression_(ifccParser::AssignmentExpression_Context *ctx)
{
	visitChildren(ctx);
	const string variableName = ctx->VAR()->getText();
	Parameters variable = *intermediateRepresentator.getVariableFromSymbolTable(variableName, true);
	intermediateRepresentator.checkFeedbackSymbolTable(variableName, ctx->getStart());
	std::string type = variable.type;
	intermediateRepresentator.setCurrentType(type);
	std::string tempVariable = intermediateRepresentator.popTemporaryVariable();
	intermediateRepresentator.addInstruction(new AssignVariableToVariableInstruction(intermediateRepresentator.getVariableFromSymbolTable(tempVariable, true), intermediateRepresentator.getVariableFromSymbolTable(variableName)));
	std::string newTempVariable = intermediateRepresentator.createTemporaryVariable(type);
	intermediateRepresentator.addInstruction(new AssignVariableToVariableInstruction(intermediateRepresentator.getVariableFromSymbolTable(variableName), intermediateRepresentator.getVariableFromSymbolTable(newTempVariable)));

	intermediateRepresentator.setCurrentBinaryOperator("");
	return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitTypeInt_(ifccParser::TypeInt_Context *ctx)
{
	intermediateRepresentator.setCurrentType("int");
	return defaultResult();
}
antlrcpp::Any CodeGenVisitor::visitTypeChar_(ifccParser::TypeChar_Context *ctx)
{
	intermediateRepresentator.setCurrentType("char");
	return defaultResult();
}
