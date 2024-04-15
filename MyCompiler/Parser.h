#pragma once
#include "Node.h"
#include "Token.h"
#include <vector>

class Parser
{
public: 
	Program* Parse(vector<Token> tokens);
	void PrintSyntaxTree(Program* program);

private:
	Function* ParseFunction();
	Parameter* PareseParameter();
	vector<Statement*> ParseBlock();
	ExpressionStatement* ParseExpressionStatement();
	Variable* ParseStaticVariable();
	Variable* ParseNumberVariable();
	Variable* ParseStringVariable();
	If* ParseIf();
	While* ParseWhile();
	Break* ParseBreak();
	Continue* ParseContinue();
	Return* ParseReturn();
	Print* ParsePrint();
	Expression* ParseExpression();
	Expression* ParseAssignment();//은 는1
	Expression* ParseOr();//거나 2
	Expression* ParseAnd();//보다 3
	Expression* ParseRelational(); //관계연산4
	Expression* ParsePlusMinus();//산술 +- 5
	Expression* ParseMulDiv();//산술 */
	Expression* ParseUnary();
	Expression* ParseOperand();
	Expression* ParseNullLiteral();
	Expression* ParseBooleanLiteral();
	Expression* ParseNumberLiteral();
	Expression* ParseStringLiteral();
	Expression* ParseIdentifier();
	Expression* ParseInnerExpression();
	Expression* ParsePostfix(Expression* sub);
	Expression* ParseCall();
	Expression* ParseElement(Expression* sub);

	void SkipCurrent(TokenKind type);
	bool SkipCurrentIf(TokenKind type);
};

