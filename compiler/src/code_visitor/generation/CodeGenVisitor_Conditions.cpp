#include <string>
#include "CodeGenVisitor.h"
#include "../../intermediate_representation/intermediate_instructions/ConditionInstruction.h"
#include "../../intermediate_representation/intermediate_instructions/WhileInstruction.h"

antlrcpp::Any CodeGenVisitor::visitIfBlock(ifccParser::IfBlockContext *ctx)
{
	visit(ctx->expression());

	ControlFlowGraph *currentCFG = intermediateRepresentator.getCurrentControlFlowGraph();
	std::string binaryOperator = intermediateRepresentator.getCurrentBinaryOperator();
	BasicBlock *currentBB = currentCFG->getCurrentBasicBlock();

	std::string tempVar = intermediateRepresentator.popTemporaryVariable();

	std::string labelFalseBB = currentBB->getExitFalseBlock()->getLabel();
	intermediateRepresentator.addInstruction(new ConditionInstruction(binaryOperator, labelFalseBB, intermediateRepresentator.getVariableFromSymbolTable(tempVar, true), TRUE));

	if (currentBB->getExitTrueBlock() != nullptr)
	{
		std::string labelTrueBB = currentBB->getExitTrueBlock()->getLabel();
		visit(ctx->blockOrInstruction());
		// cout<<"label true"<<labelTrueBB<<endl;
		intermediateRepresentator.addInstruction(new ConditionInstruction(binaryOperator, labelTrueBB, intermediateRepresentator.getVariableFromSymbolTable(tempVar, true), FALSE));
	}
	else
	{
		visit(ctx->blockOrInstruction());
	}
	currentCFG->modifyCurrentBasicBlock(currentBB->getExitFalseBlock());
	return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitElseifBlock(ifccParser::ElseifBlockContext *ctx)
{
	visit(ctx->expression());

	std::string binaryOperator = intermediateRepresentator.getCurrentBinaryOperator();
	ControlFlowGraph *currentCFG = intermediateRepresentator.getCurrentControlFlowGraph();
	BasicBlock *currentBB = currentCFG->getCurrentBasicBlock();

	std::string tempVar = intermediateRepresentator.popTemporaryVariable();

	std::string labelFalseBB = currentBB->getExitFalseBlock()->getLabel();
	intermediateRepresentator.addInstruction(new ConditionInstruction(binaryOperator, labelFalseBB, intermediateRepresentator.getVariableFromSymbolTable(tempVar, true), TRUE));

	if (currentBB->getExitTrueBlock() != nullptr)
	{
		std::string labelTrueBB = currentBB->getExitTrueBlock()->getLabel();
		visit(ctx->blockOrInstruction());
		intermediateRepresentator.addInstruction(new ConditionInstruction(binaryOperator, labelTrueBB, intermediateRepresentator.getVariableFromSymbolTable(tempVar, true), FALSE));
	}
	else
	{
		visit(ctx->blockOrInstruction());
	}

	return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitIfElseInstruction_(ifccParser::IfElseInstruction_Context *ctx)
{
	/*Cases to handle: no else, no else if and all
	Labels basic block by using tampon variable nbBB
	This variable has to be updated for each visit, since there will be a return at the end of the block
	Otherwise, label collision will happen between conditional and return block
	*/
	ControlFlowGraph *cfg = intermediateRepresentator.getCurrentControlFlowGraph();
	BasicBlock *currentBB = cfg->getCurrentBasicBlock();
	ifccParser::IfBlockContext *ifBlockContext = ctx->ifBlock();
	ifccParser::ElseBlockContext *elseBlockContext = ctx->elseBlock();
	vector<ifccParser::ElseifBlockContext *> elseIfBlockVector = ctx->elseifBlock();

	// get number of BB created in the CFG
	std::string label;
	int nbBB = cfg->getNextBasicBlockNumber();

	// currentBB->exit_false
	++nbBB;
	label = ".L" + to_string(nbBB);
	BasicBlock *bbIfFalse = new BasicBlock(cfg, label);
	currentBB->modifyExitFalseBlock(bbIfFalse); // L2
	cfg->addBasicBlock(bbIfFalse);

	// we have only if() {}
	if (elseIfBlockVector.size() == 0 && elseBlockContext == nullptr)
	{
		return visit(ifBlockContext);
	}
	// We have if() {} else {}
	++nbBB;
	label = ".L" + to_string(nbBB);					   // L3
	BasicBlock *bbIfTrue = new BasicBlock(cfg, label); // L3
	currentBB->modifyExitTrueBlock(bbIfTrue);
	cfg->increaseBBNumber();
	visit(ifBlockContext);

	nbBB = cfg->getNextBasicBlockNumber();
	currentBB = cfg->modifyCurrentBasicBlock(bbIfFalse);
	std::vector<BasicBlock *> bbElseIfVector;
	if (elseIfBlockVector.size() == 0)
	{
		// we are in the case if() {} else{}
		bbIfFalse->modifyExitTrueBlock(bbIfTrue);
		cfg->decreaseBBNumber();
		cfg->addBasicBlock(bbIfTrue);
		visit(elseBlockContext);
		currentBB = cfg->modifyCurrentBasicBlock(currentBB->getExitTrueBlock());
		return defaultResult();
	}
	else
	// we have if() {} else if () {} ... else {}
	{
		// nbBB = cfg->getNextBasicBlockNumber();//bb:4
		bbIfFalse->modifyExitFalseBlock(bbIfTrue);
		bbElseIfVector.push_back(bbIfFalse);
		for (int i = 1; i < elseIfBlockVector.size(); ++i)
		{
			++nbBB; // 4, currentNbBB 3 or 4
			label = ".L" + to_string(nbBB);
			BasicBlock *newElseIfBB = new BasicBlock(cfg, label); // L4 or L5
			newElseIfBB->modifyExitFalseBlock(bbIfTrue);
			cfg->increaseBBNumber(); // bb:5/6
			bbElseIfVector[i - 1]->modifyExitTrueBlock(bbIfTrue);
			bbElseIfVector[i - 1]->modifyExitFalseBlock(newElseIfBB);
			visit(elseIfBlockVector[i - 1]);

			nbBB = cfg->getNextBasicBlockNumber();

			currentBB = cfg->modifyCurrentBasicBlock(newElseIfBB);
			bbElseIfVector.push_back(newElseIfBB);
			cfg->decreaseBBNumber(); // bb:4/5
			cfg->addBasicBlock(newElseIfBB);
		}

		if (elseBlockContext != nullptr)
		{
			++nbBB;
			label = ".L" + to_string(nbBB);
			BasicBlock *elseBB = new BasicBlock(cfg, label);
			cfg->increaseBBNumber();

			bbElseIfVector[elseIfBlockVector.size() - 1]->modifyExitTrueBlock(bbIfTrue);
			bbElseIfVector[elseIfBlockVector.size() - 1]->modifyExitFalseBlock(elseBB);
			visit(elseIfBlockVector[elseIfBlockVector.size() - 1]);

			currentBB = cfg->modifyCurrentBasicBlock(elseBB);
			elseBB->modifyExitTrueBlock(bbIfTrue);
			elseBB->modifyExitFalseBlock(bbIfTrue);

			cfg->decreaseBBNumber();
			cfg->addBasicBlock(elseBB);
			visit(elseBlockContext);
			currentBB = cfg->modifyCurrentBasicBlock(currentBB->getExitTrueBlock());
		}
		else
		{
			visit(elseIfBlockVector[elseIfBlockVector.size() - 1]);
			currentBB = cfg->modifyCurrentBasicBlock(currentBB->getExitFalseBlock());
		}

		cfg->decreaseBBNumber();
		cfg->addBasicBlock(bbIfTrue);
	}

	return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitWhileBlock(ifccParser::WhileBlockContext *ctx)
{
	ControlFlowGraph *cfg = intermediateRepresentator.getCurrentControlFlowGraph();
	BasicBlock *currentBB = cfg->getCurrentBasicBlock();

	// get number of BB created in the CFG
	std::string label;
	int nbBB = cfg->getNextBasicBlockNumber();

	// currentBB->exit_false
	++nbBB;
	label = ".L" + to_string(nbBB);
	BasicBlock *bbExitFalse = new BasicBlock(cfg, label);
	currentBB->modifyExitFalseBlock(bbExitFalse);
	cfg->increaseBBNumber();

	std::string binaryOperator = "";
	std::string labelFalseBB = bbExitFalse->getLabel();
	intermediateRepresentator.addInstruction(new WhileInstruction(binaryOperator, labelFalseBB, nullptr, FALSE));

	// currentBB->exit_true
	++nbBB;
	label = ".L" + to_string(nbBB);
	BasicBlock *bbwhileBody = new BasicBlock(cfg, label);
	currentBB->modifyExitTrueBlock(bbwhileBody);
	cfg->addBasicBlock(bbwhileBody);

	cfg->modifyCurrentBasicBlock(bbwhileBody);

	visit(ctx->blockOrInstruction());

	cfg->modifyCurrentBasicBlock(bbExitFalse);

	visit(ctx->expression());
	string tempVar = intermediateRepresentator.popTemporaryVariable();
	binaryOperator = intermediateRepresentator.getCurrentBinaryOperator();

	labelFalseBB = bbwhileBody->getLabel();
	intermediateRepresentator.addInstruction(new WhileInstruction(binaryOperator, labelFalseBB, intermediateRepresentator.getVariableFromSymbolTable(tempVar, true), TRUE));

	cfg->decreaseBBNumber();
	cfg->addBasicBlock(bbExitFalse);

	return defaultResult();
}
