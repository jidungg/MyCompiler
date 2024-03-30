#pragma once
#include "Node.h"

class Parser
{
public: 
	Program* Parse(vector<Token> tokens);
	void PrintSyntaxTree(Program* program);

private:
	Function* ParseFunction();
	vector<Statement*> ParseBlock();
	ExpressionStatement* ParseExpressionStatement();
	Variable* ParseVariable();
	If* ParseIf();
	For* ParseFor();
	Break* ParseBreak();
	Continue* ParseContinue();
	Print* ParsePrint();
	Expression* ParseExpression();
	Expression* ParseAssignment();//1
	Expression* ParseOr();//2
	Expression* ParseAnd();//3
	Expression* ParseRelational(); //관계연산4
	Expression* ParsePlusMinus();//산술 +- 5
	Expression* ParseMulDivMod();//산술 */% 
	Expression* ParseUnary();
	Expression* ParsePreUnary();//단항연산자
	Expression* ParsePostUnary(Expression* preUnary);//단항연산자
	Expression* ParseOperand();
	Expression* ParseNullLiteral();
	Expression* ParseBooleanLiteral();
	Expression* ParseNumberLiteral();
	Expression* ParseStringLiteral();
	Expression* ParseListLiteral();
	Expression* ParseMapLiteral();
	Expression* ParseIdentifier();
	Expression* ParseInnerExpression();
	Expression* ParsePostfix(Expression* sub);
	Expression* ParseCall(Expression* sub);
	Expression* ParseElement(Expression* sub);

	void SkipCurrent(WordType type);
	bool SkipCurrentIf(WordType type);
};

