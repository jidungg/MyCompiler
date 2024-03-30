#pragma once
#include <any>

struct Statement
{
	virtual string ToString(int depth) abstract;
	virtual void Interpret() abstract;
};
struct Expression
{
	virtual string ToString(int depth) abstract;
	virtual any Interpret()	abstract;
};
struct Function : Statement
{
	virtual string ToString(int depth);
	virtual void Interpret();

	string name;
	vector<string> parameters;
	vector<Statement*> block;
};
struct Return :Statement
{
	virtual string ToString(int depth);
	virtual void Interpret();

	Expression* expression;
};
struct Variable : Statement
{
	virtual string ToString(int depth);
	virtual void Interpret();

	string name;
	Expression* expression;
};
struct For : Statement
{
	virtual string ToString(int depth);
	virtual void Interpret();

	vector<Variable*> variables;
	Expression* condition;
	vector<Expression*> expressions;
	vector<Statement*> block;
};
struct If : Statement
{
	virtual string ToString(int depth);
	virtual void Interpret();

	vector<Expression*> conditions;
	vector<vector<Statement*>> blocks;
	vector<Statement*> elseblock;
};
struct Print : Statement
{
	virtual string ToString(int depth);
	virtual void Interpret();

	bool lineFeed = false;
	vector<Expression*> expressions;
};
struct Break : Statement
{
	virtual string ToString(int depth);
	virtual void Interpret();

};
struct Continue : Statement
{
	virtual string ToString(int depth);
	virtual void Interpret();
};
struct ExpressionStatement : Statement
{
	virtual string ToString(int depth);
	virtual void Interpret();

	Expression* expression;
};
struct Or : Expression
{
	virtual string ToString(int depth);
	virtual any Interpret();

	Expression* lhs;
	Expression* rhs;
};
struct And : Expression
{
	virtual string ToString(int depth);
	virtual any Interpret();

	Expression* lhs;
	Expression* rhs;
};
struct Relational : Expression
{
	virtual string ToString(int depth);
	virtual any Interpret();

	WordType type;
	Expression* lhs;
	Expression* rhs;
};
struct Arithmetic : Expression
{
	virtual string ToString(int depth);
	virtual any Interpret();

	WordType type;
	Expression* lhs;
	Expression* rhs;
};
struct Unary : Expression
{
	virtual string ToString(int depth);
	virtual any Interpret();

	WordType type;
	Expression* sub;
};
struct Call : Expression
{
	virtual string ToString(int depth);
	virtual any Interpret();

	Expression* sub;
	vector<Expression*> arguments;
};
struct GetElement : Expression
{
	virtual string ToString(int depth);
	virtual any Interpret();

	Expression* sub;
	Expression* index;
};
struct SetElement : Expression
{
	virtual string ToString(int depth);
	virtual any Interpret();

	Expression* sub;
	Expression* index;
	Expression* value;
};
struct GetVariable : Expression
{
	virtual string ToString(int depth);
	virtual any Interpret();

	string name;
};
struct SetVariable : Expression
{
	virtual string ToString(int depth);
	virtual any Interpret();

	string name;
	Expression* value;
};
struct NullLiteral : Expression 
{
	virtual string ToString(int depth);
	virtual any Interpret();
};
struct BooleanLiteral : Expression {
	virtual string ToString(int depth);
	virtual any Interpret();

	bool value = false;
};
struct NumberLiteral : Expression
{
	virtual string ToString(int depth);
	virtual any Interpret();

	double  value = 0.0;
};
struct StringLiteral : Expression
{
	virtual string ToString(int depth);
	virtual any Interpret();

	string value;
};
struct ArrayLiteral : Expression
{
	virtual string ToString(int depth);
	virtual any Interpret();

	vector<Expression*> values;
};
struct MapLiteral : Expression
{
	virtual string ToString(int depth);
	virtual any Interpret();

	map<string, Expression*> values;
};
struct Program
{
	virtual string ToString(int depth);
	virtual void Interpret();

	vector<Function*> functions;
};

class Node
{
};

