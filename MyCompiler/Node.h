#pragma once
#include <any>
#include <map>
#include <vector>
#include <list>
#include <string>
#include "Types.h"

using namespace std;
struct Statement
{
	virtual wstring ToString(int depth) abstract;
	//virtual void Interpret() abstract;
};
struct Expression
{
	virtual wstring ToString(int depth) abstract;
	//virtual any Interpret()	abstract;
};
struct Parameter : Statement
{
	virtual wstring ToString(int depth);
	bool isNumber = false;
	wstring name;
};
struct Function : Statement
{
	virtual wstring ToString(int depth);
	//virtual void Interpret();

	wstring name;
	vector<Parameter*> parameters;
	vector<Statement*> block;
};
struct Return :Statement
{
	virtual wstring ToString(int depth);
	//virtual void Interpret();

	Expression* expression;
};
struct Variable : Statement
{
	virtual wstring ToString(int depth);
	//virtual void Interpret();

	bool isStatic = false;
	bool isNumber = false;
	wstring name;
	Expression* expression;
};
struct While : Statement
{
	virtual wstring ToString(int depth);
	//virtual void Interpret();

	Expression* condition;
	vector<Statement*> block;
};
struct If : Statement
{
	virtual wstring ToString(int depth);
	//virtual void Interpret();

	Expression* condition;
	vector<Statement*> block;
	vector<Statement*> elseblock;
};
struct Print : Statement
{
	virtual wstring ToString(int depth);
	//virtual void Interpret();

	bool lineFeed = false;
	vector<Expression*> expressions;
};
struct Break : Statement
{
	virtual wstring ToString(int depth);
	//virtual void Interpret();

};
struct Continue : Statement
{
	virtual wstring ToString(int depth);
	//virtual void Interpret();
};
struct ExpressionStatement : Statement
{
	virtual wstring ToString(int depth);
	//virtual void Interpret();

	Expression* expression;
};
struct Or : Expression
{
	virtual wstring ToString(int depth);
	//virtual any Interpret();

	Expression* lhs;
	Expression* rhs;
};
struct And : Expression
{
	virtual wstring ToString(int depth);
	//virtual any Interpret();

	Expression* lhs;
	Expression* rhs;
};
struct Relational : Expression
{
	virtual wstring ToString(int depth);
	//virtual any Interpret();

	TokenKind type;
	Expression* lhs;
	Expression* rhs;
};
struct Arithmetic : Expression
{
	virtual wstring ToString(int depth);
	//virtual any Interpret();

	TokenKind type;
	Expression* lhs;
	Expression* rhs;
};
struct Unary : Expression
{
	virtual wstring ToString(int depth);
	//virtual any Interpret();

	TokenKind type;
	Expression* sub;
};
struct Call : Expression
{
	virtual wstring ToString(int depth);
	//virtual any Interpret();

	Expression* sub;
	vector<Expression*> arguments;
};
struct GetElement : Expression
{
	virtual wstring ToString(int depth);
	//virtual any Interpret();

	Expression* sub;
	Expression* index;
};
struct SetElement : Expression
{
	virtual wstring ToString(int depth);
	//virtual any Interpret();

	Expression* sub;
	Expression* index;
	Expression* value;
};
struct GetVariable : Expression
{
	virtual wstring ToString(int depth);
	//virtual any Interpret();

	wstring name;
};
struct SetVariable : Expression
{
	virtual wstring ToString(int depth);
	//virtual any Interpret();

	wstring name;
	Expression* value;
};
struct NullLiteral : Expression 
{
	virtual wstring ToString(int depth);
	//virtual any Interpret();
};
struct BooleanLiteral : Expression {
	virtual wstring ToString(int depth);
	//virtual any Interpret();

	bool value = false;
};
struct NumberLiteral : Expression
{
	virtual wstring ToString(int depth);
	//virtual any Interpret();

	double  value = 0.0;
};
struct StringLiteral : Expression
{
	virtual wstring ToString(int depth);
	//virtual any Interpret();

	wstring value;
};

struct Program
{
	virtual wstring ToString(int depth);
	//virtual void Interpret();

	vector<Function*> functions;
	vector<Variable*> staticVariables;
};

class Node
{
};

