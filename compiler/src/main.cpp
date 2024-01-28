#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <antlr4-runtime.h>
#include <vector>
#include "grammar_generated_files/ifccLexer.h"
#include "grammar_generated_files/ifccParser.h"
#include "grammar_generated_files/ifccBaseVisitor.h"
#include "code_visitor/generation/CodeGenVisitor.h"
#include "code_visitor/feedback/CodeFeedbackVisitor.h"
#include "feedback/SemanticFeedbackListener.h"
#include "feedback/SyntaxFeedbackListener.h"
#include "intermediate_representation/IntermediateRepresentator.h"
#include "symbol_table/SymbolTable.h"

using namespace antlr4;
using namespace std;

int main(int argn, const char **argv)
{

#ifdef _DEBUG
  std::cerr << "== Debug mode" << std::endl;
#endif

  stringstream in;
  string filepath;
  if (argn == 2)
  {
    filepath = argv[1];
    ifstream lecture(filepath);
    in << lecture.rdbuf();
  }
  else
  {
    cerr << "usage: ifcc path/to/file.c" << endl;
    return 1;
  }

  ANTLRInputStream input(in.str());
  ifccLexer lexer(&input);

  SyntaxFeedbackListener syntaxFeedbackListener(filepath, in);
  lexer.removeErrorListeners();
 
  CommonTokenStream tokens(&lexer);
  tokens.fill();

  ifccParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(&syntaxFeedbackListener);
 
  tree::ParseTree *tree = parser.axiom();

  if (syntaxFeedbackListener.Error())
  {
    return 1;
  }

  IntermediateRepresentator intermediateRepresentator;
  CodeGenVisitor visitor(intermediateRepresentator);

  SemanticFeedbackListener semanticFeedback(filepath, in);
  visitor.addFeedbackListener(&semanticFeedback);
  intermediateRepresentator.addFeedbackListener(&semanticFeedback);

  CodeFeedbackVisitor feedbackVisitor(intermediateRepresentator);
  feedbackVisitor.addFeedbackListener(&semanticFeedback);

  try
  {
    visitor.visit(tree);
    feedbackVisitor.visit(tree);
  }
  catch (std::invalid_argument &e)
  {
    return 1;
  }

  if (semanticFeedback.Error())
  {
    return 1;
  }

  intermediateRepresentator.toAssembly(cout);

  return 0;
}
