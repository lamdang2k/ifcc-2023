#include "CodeGenVisitor.h"
#include "../../intermediate_representation/ControlFlowGraph.h"
#include "../../intermediate_representation/intermediate_instructions/CopyParamsToRegistersInstruction.h"
#include "../../intermediate_representation/intermediate_instructions/CopyRegisterToVariableInstruction.h"
#include "../../intermediate_representation/intermediate_instructions/FunctionCallInstruction.h"

antlrcpp::Any CodeGenVisitor::visitFunctionDefinition_(ifccParser::FunctionDefinition_Context *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitFunctionDeclaration_(ifccParser::FunctionDeclaration_Context *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitReturnType(ifccParser::ReturnTypeContext *ctx)
{
	visitChildren(ctx);

	string returnType;
	if (ctx->type() != nullptr)
	{
		returnType = ctx->type()->getText();
	}
	else
	{
		returnType = "void";
	}
	// cout<<"RETURN: "<<returnType<<endl;
	intermediateRepresentator.setCurrentType(returnType);
	return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitFunctionPrototype_(ifccParser::FunctionPrototype_Context *ctx)
{
	/*visit function prototype
	if the parent is functionDeclaration, add a new CFG named the declared function
	if functionDefintion, setCurrentCfg and add arguments to the symbol table
	*/
	string functionName = ctx->VAR()->getText();
	intermediateRepresentator.setCurrentFunctionName(functionName);
	if (intermediateRepresentator.getControlFlowGraph(functionName) == nullptr)
	{
		ControlFlowGraph *newCfg = new ControlFlowGraph(functionName);
		intermediateRepresentator.addControlFlowGraph(functionName, newCfg);
	}
	if (instanceof <ifccParser::FunctionDefinition_Context>(ctx->parent))
	{
		ControlFlowGraph *currentCfg = intermediateRepresentator.getControlFlowGraph(functionName);
		intermediateRepresentator.setCurrentControlFlowGraph(currentCfg);
		intermediateRepresentator.checkAlreadyDefinedFunction(functionName, ctx->getStart());
		string label = functionName + '0';
		BasicBlock *newBlock = new BasicBlock(currentCfg, label);
		currentCfg->addBasicBlock(newBlock);
		currentCfg->modifyCurrentBasicBlock(newBlock);
	}
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitFunctionArgs_(ifccParser::FunctionArgs_Context *ctx)
{
	/* Adding function definition to the mapFunctionDefinition
	If the function has been declared, one verifies the coherence of declaration and definition
	Once a new BasicBlock has been created and the coherence is satisfied, add new instructions to the block
	One also adds instructions when there is no declaration
	*/
	string functionName = intermediateRepresentator.getCurrentFunctionName();
	FunctionDefinition *existingFuncDef = intermediateRepresentator.getFunctionDefinition(functionName);
	string returnType = intermediateRepresentator.getCurrentType();
	visitChildren(ctx);
	std::vector<antlr4::tree::TerminalNode *> listArgs = ctx->VAR();
	std::vector<ifccParser::TypeContext *> listTypes = ctx->type();
	std::deque<string> types, vars;
	for (int i = 0; i < listArgs.size(); i++)
	{
		string var = listArgs[i]->getText();
		string type = listTypes[i]->getText();
		types.push_back(type);
		vars.push_back(var);
	}
	FunctionDefinition *newFunctionDef = new FunctionDefinition(listTypes.size(), types, returnType);
	if (existingFuncDef == nullptr)
	{
		intermediateRepresentator.addFunctionDefinition(functionName, newFunctionDef);
	}
	ControlFlowGraph *currentCfg = intermediateRepresentator.getControlFlowGraph(functionName);
	if (currentCfg->hasBasicBlock())
	{
		bool isCoherent = intermediateRepresentator.checkFunctionDefinitionCoherence(functionName, existingFuncDef, newFunctionDef, ctx->getStart());
		if (isCoherent)
		{
			for (int i = 0; i < types.size(); i++)
			{
				string var = vars[i];
				string type = types[i];
				intermediateRepresentator.addVariableToSymbolTable(type, var, true);
				intermediateRepresentator.addInstruction(new CopyRegisterToVariableInstruction(intermediateRepresentator.getVariableFromSymbolTable(var, true), i));
			}
		}
	}
	return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitFunctionCall_(ifccParser::FunctionCall_Context *ctx)
{
	/* FunctionCall with (return int or char) and without assignment(return void)
	 */
	ControlFlowGraph *currentCFG = intermediateRepresentator.getCurrentControlFlowGraph();
	currentCFG->functionCallsFound();
	string functionName = ctx->VAR()->getText();
	intermediateRepresentator.setCurrentFunctionName(functionName);
	bool isDefined = intermediateRepresentator.checkFunctionExistence(functionName, ctx->getStart());
	string returnType;
	if (isDefined)
	{
		FunctionDefinition *existingFuncDef = intermediateRepresentator.getFunctionDefinition(functionName);
		if (instanceof <ifccParser::ExpressionInstruction_Context>(ctx->parent) || instanceof <ifccParser::ReturnInstruction_Context>(ctx->parent))
		{
			// the case of no assignment
			if (existingFuncDef != nullptr)
			{
				returnType = existingFuncDef->getReturnType();
			}
			else
			{
				returnType = "void";
			}
			intermediateRepresentator.setCurrentType(returnType);
		}
		else
		{
			// function call and assignment
			returnType = intermediateRepresentator.getCurrentType();
		}
		visitChildren(ctx);
		std::string stockResultVariable = intermediateRepresentator.createTemporaryVariable(returnType);
		intermediateRepresentator.addInstruction(new FunctionCallInstruction(functionName, intermediateRepresentator.getVariableFromSymbolTable(stockResultVariable)));
		intermediateRepresentator.setCurrentBinaryOperator("");
	}
	return defaultResult();
}

antlrcpp::Any CodeGenVisitor::visitFunctionCallArgs_(ifccParser::FunctionCallArgs_Context *ctx)
{
	ControlFlowGraph *currentCFG = intermediateRepresentator.getCurrentControlFlowGraph();
	string functionName = intermediateRepresentator.getCurrentFunctionName();
	string returnType = intermediateRepresentator.getCurrentType();
	FunctionDefinition *existingFuncDef = intermediateRepresentator.getFunctionDefinition(functionName);
	// cout<<"return: "<<returnType<<"function: "<<functionName;
	visitChildren(ctx);
	std::string tempVariable;
	std::vector<ifccParser::ExpressionContext *> listArgs = ctx->expression();
	std::deque<Parameters *> listVarName;
	std::deque<string> varTypes;
	for (int i = 0; i < listArgs.size(); i++)
	{
		tempVariable = intermediateRepresentator.popTemporaryVariable();
		Parameters *varParam = intermediateRepresentator.getVariableFromSymbolTable(tempVariable, true);
		string type = varParam->type;
		varTypes.push_front(type);
		listVarName.push_front(varParam);
	}
	FunctionDefinition *currentFuncCall = new FunctionDefinition(varTypes.size(), varTypes, returnType);
	bool isCoherent = intermediateRepresentator.checkFunctionCallDefinitionCoherence(functionName, existingFuncDef, currentFuncCall, ctx->getStart());
	if (isCoherent && listVarName.size() < 7)
	{
		currentCFG->addInstruction(new CopyParamsToRegistersInstruction(listVarName));
	}
	return defaultResult();
}
