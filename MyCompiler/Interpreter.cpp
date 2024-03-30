#include "pch.h"
#include "Interpreter.h"
#include "Node.h"

static map<string, Function*> functionTable;
static list<list<map<string, any>>> localVariables;
static map<string, any> globalVariables;

bool IsAnyString(any value)
{
	return value.type() == typeid(string);
}
bool IsAnyNumber(any value)
{
	return value.type() == typeid(double);
}
string AnyToString(any value)
{
	return any_cast<string>(value);
}
double AnyToNumber(any value)
{
	return any_cast<double>(value);
}
ostream& operator<<(ostream& os, any& value)
{
	if (IsAnyString(value))
		os << AnyToString(value);
	if(IsAnyNumber(value))
		os << AnyToNumber(value);
	return os;
}
void Program::Interpret()
{
	for (auto& i : this->functions)
	{
		functionTable[i->name] = i;
	}
	localVariables.emplace_back().emplace_front();
	functionTable["main"]->Interpret();

}

void Function::Interpret()
{
	for (auto& i : block)
	{
		i->Interpret();
	}
}
void Return::Interpret()
{
}
void Variable::Interpret()
{
	localVariables.back().front()[name] = expression->Interpret();
}
void For::Interpret()
{
}
void If::Interpret()
{
}
void Print::Interpret()
{
	for (auto& i : expressions)
	{
		any value = i->Interpret();
		cout << value;
	}
	if (lineFeed)
		cout << endl;
}
	
void Break::Interpret()
{
}
void Continue::Interpret()
{
}
void ExpressionStatement::Interpret()
{
	expression->Interpret();
}
any Or::Interpret()
{
	return any();
}
any And::Interpret()
{
	return any();
}
any Relational::Interpret()
{
	return any();
}
any Arithmetic::Interpret()
{
	auto lhsValue = lhs->Interpret();
	auto rhsValue = rhs->Interpret();
	if (IsAnyNumber(lhsValue) && IsAnyNumber(rhsValue))
	{
		auto lhsNumber = AnyToNumber(lhsValue);
		auto rhsNumber = AnyToNumber(rhsValue);
		switch (type)
		{
		case WordType::Add:
			return lhsNumber + rhsNumber;
		case WordType::Subtract:
			return lhsNumber - rhsNumber;
		case WordType::Multiply:
			return lhsNumber * rhsNumber;
		case WordType::Divide:
			return rhsNumber == 0 ? 0.0  : lhsNumber / rhsNumber;
		case WordType::Modulo:
			return rhsNumber == 0? 0.0 : fmod(lhsNumber , rhsNumber);
		default:
			break;
		}
	}
	if (IsAnyString(lhsValue) && IsAnyString(rhsValue))
	{
		auto lhsString = AnyToString(lhsValue);
		auto rhsString = AnyToString(rhsValue);
		switch (type)
		{
		case WordType::Add:
			return lhsString + rhsString;
		default:
			break;
		}
	}
	return 0.0;
}
any Unary::Interpret()
{
	auto value = sub->Interpret();
	if (IsAnyNumber(value))
	{
		auto number = AnyToNumber(value);
		switch (type)
		{
		case WordType::Increase:
			return number + 1;
		case WordType::Decrease:
			return number - 1;
		case WordType::Subtract:
			return -number;
		case WordType::Add:
			return number;
		default:
			break;
		}
	}
	return any();
}

any Call::Interpret()
{
	return any();
}
any GetElement::Interpret()
{
	return any();
}
any SetElement::Interpret()
{
	return any();
}
any GetVariable::Interpret()
{
	for (auto& i : localVariables.back())
	{
		if (i.count(name))
			return i[name];
	}
	if (globalVariables.count(name))
		return globalVariables[name];
	if (functionTable.count(name))
		return functionTable[name];
	return nullptr;
}

any SetVariable::Interpret()
{
	for (auto& i : localVariables.back())
	{
		if(i.count(name))
			return i[name] = value->Interpret();
	}
	return globalVariables[name] = value->Interpret();
}
any NullLiteral::Interpret()
{
	return NULL;
}
any BooleanLiteral::Interpret()
{
	return value;
}
any NumberLiteral::Interpret()
{
	return value;
}
any StringLiteral::Interpret()
{
	return value;
}
any ArrayLiteral::Interpret()
{
	return values;
}
any MapLiteral::Interpret()
{
	return values;
}


void Interpreter::Interpret(Program* program)
{
	program->Interpret();
}
