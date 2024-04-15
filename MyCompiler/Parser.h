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
	Expression* ParseAssignment();//�� ��1
	Expression* ParseOr();//�ų� 2
	Expression* ParseAnd();//���� 3
	Expression* ParseRelational(); //���迬��4
	Expression* ParsePlusMinus();//��� +- 5
	Expression* ParseMulDiv();//��� */
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

