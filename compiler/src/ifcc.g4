grammar ifcc;

axiom : prog;
prog : globalInstruction+ ;

globalInstruction :	function				# functionDeclarationOrDefinition_
	| declaration							# globalDeclarationInstruction_
;

function : returnType functionSignature (',' functionSignature)* ';'										# functionDeclaration_
	| returnType functionSignature OPENCONTEXT blockOrInstructionOrDeclaration* CLOSECONTEXT (';')*			# functionDefinition_
;

functionSignature : VAR '(' args? ')'	# functionPrototype_
;

args : type VAR (',' type VAR)*	# functionArgs_
;

block : OPENCONTEXT blockOrInstructionOrDeclaration* CLOSECONTEXT;

blockOrInstructionOrDeclaration: declaration    # declarationInstruction_
|  blockOrInstruction # nestedBlockInstruction_	
  
;

blockOrInstruction: block	# nestedBlock_
	| instruction			# instruction_
;

declaration : type assignment (',' assignment)* ';' #simpleDeclaration_
 | type arrayAssignment # arrayDeclaration_
; 

instruction :	expression ';'		# expressionInstruction_
	| RETURN expression ';'	# returnInstruction_
	| ';' 					# nullInstruction_
  | ifBlock elseifBlock* elseBlock? # ifElseInstruction_
  | whileBlock	# whileInstruction_
;

ifBlock: 'if' '(' expression ')' blockOrInstruction;

elseifBlock: 'else' 'if' '(' expression ')' blockOrInstruction; 

elseBlock: 'else' blockOrInstruction; 

whileBlock: 'while' '(' expression ')' blockOrInstruction;

assignment : VAR ('=' expression)?	# singleAssignment_
;

arrayAssignment :  VAR '[' expression ']' ('=' '{'(expression (',' expression)* ','?)* '}')? #singleArrayAssignement_
;

expression: expression multDivisionOperator expression	# multDivExpression_
	| expression plusMinusOperator expression			# plusMinusExpression_
	| expression comparisonOperator expression			# binaryComparatorExpression_
	| expression bitOperator expression					# binaryBitExpression_
	| VAR '=' expression								# assignmentExpression_
	| VAR '[' expression ']' '=' expression				# arrayAssignmentExpression_
	| VAR '[' expression ']'							# dereferenceExpression_
	| '(' expression ')'								# expressionBetweenParentheses_				
	| literalExpression									# literalExpression_
	| unaryOperator expression							# unaryExpression_
    | VAR '(' valuedArgs? ')'							# functionCall_
;

valuedArgs : expression (',' expression)*  # functionCallArgs_
;

literalExpression : VAR	# var_
	| CONST				# const_
	| CONST_CHAR		# constChar_
;

unaryOperator: '-'	# minus_
	| '!'			# negation_
	| '+'			# plus_
; 
comparisonOperator : '=='	# equal_
	| '!='					# nequal_
	| '<'					# less_
	| '>'					# greater_
	| '<='					# lessOrEqual_
	| '>='					# greaterOrEqual_
;

multDivisionOperator : '*' 		# multOperator_
	|	'/'						# divisionOperator_
	|	'%'						# modulusOperator_
;

plusMinusOperator : '+'	# plusBinary_
	| '-'				# minusBinary_
;

bitOperator : '|'	# or_
	| '&'			# and_ 
	| '^'			# xor_
;

type : 'int'	#typeInt_	
	| 'char' 	#typeChar_
;

returnType : type | 'void' ; 

OPENCONTEXT : '{' ;
CLOSECONTEXT : '}' ;
RETURN : 'return' ;
VAR : [a-zA-Z_]+[a-zA-Z0-9]*;
CONST : [0-9]+ ;
CONST_CHAR : '\''[ -~]'\'' ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
