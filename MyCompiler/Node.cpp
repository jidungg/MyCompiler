#include "pch.h"
#include "Node.h"

string Indent(int depth)
{
    return string(static_cast<size_t>(depth * 2), ' ');
}

string Function::ToString(int depth)
{

    string str;
    str += Indent(depth) + "FUNCTION : " + name + '\n';
    if (parameters.size() > 0)
    {
        str += Indent(depth + 1) + "PARAMETERS :\n";
        for (auto item : parameters)
        {
            str += Indent(depth+2) +item + '\n';
        }
    }
    str += Indent(depth + 1) + "BLOCK :\n";
    for (auto item : block)
    {
        str += item->ToString(depth + 2);
    }
    return str;
}

string Return::ToString(int depth)
{
    string str = Indent(depth) + "RETURN :\n";
    str += Indent(depth + 1) + "EXPRESSION :\n";
    str += expression->ToString(depth + 2);
    return str;
}

string Variable::ToString(int depth)
{
    string str = Indent(depth) + "VAR : " + name + '\n';
    str += Indent(depth + 1) + "EXPRESSION :\n";
    str += expression->ToString(depth + 2);
    return str;
}

string For::ToString(int depth)
{
    string str;
    str = Indent(depth) + "For :\n"; 
    if (variables.size() > 0)
    {
        str += Indent(depth + 1) + "VARIABLES : \n";
        for (auto& i : variables)
        {
            str += i->ToString(depth+2);
        }
    }
    if (condition)
    {
        str += Indent(depth + 1) + "CONDITION : \n";
        str += condition->ToString(depth + 2);
    }
    if (expressions.size() > 0)
    {
        str += Indent(depth + 1) + "EXPRESSIONS : \n";
        for (auto& i : expressions)
        {
            str += i->ToString(depth + 2);
        }
    }


    str += Indent(depth + 1) + "BLOCK : \n";
    for (auto& item : block)
    {
        str += item->ToString(depth + 2);
    }
    return str;
}

string If::ToString(int depth)
{
    string str;
    str = Indent(depth) + "IF :\n";
    if (conditions.size() > 0)
    {
        str += Indent(depth + 1) + "CONDITIONS : \n";
        for (auto& i : conditions)
        {
            str += i->ToString(depth + 2);
        }
    }

    if (blocks.size() > 0)
    {
        str += Indent(depth + 1) + "BLOCKS : \n";
        for (auto& item : blocks)
        {
            for (auto& i : item)
            {
                str += i->ToString(depth + 2);
            }
        }
    }
  
    str += Indent(depth + 1) + "ELSE_BLOCK : \n";
    for (auto& item : elseblock)
    {
        str+= item->ToString(depth + 2);
    }

    return str;
}

string Print::ToString(int depth)
{
    string str = Indent(depth) + "PRINT : LINE_FEED(" + (lineFeed ? "TRUE" : "FALSE") + ")\n";
    if (expressions.size() > 0)
    {
        str += Indent(depth + 1) + "EXPRESSION: \n";
        for (auto& i : expressions)
        {
            str += i->ToString(depth + 2);
        }
    }
    
    return str;
}

string Break::ToString(int depth)
{
    string str = Indent(depth)+ "BREAK :\n";
    return str;
}

string Continue::ToString(int depth)
{
    string str = Indent(depth) + "CONTINUE :\n";
    return str;
}

string ExpressionStatement::ToString(int depth)
{
    string str = Indent(depth) + "EXPRESSION_STATEMENT :\n ";
    str += Indent(depth + 1) + "EXPRESSION :\n";
    str += expression->ToString(depth + 2);
    return str;
}

string Or::ToString(int depth)
{
    string str = Indent(depth) + "OR : \n";
    str += Indent(depth+1) + "LHS : \n";
    str += lhs->ToString(depth + 2);
    str += Indent(depth+1) + "RHS : \n";
    str += rhs->ToString(depth + 2);
    return str;
}

string And::ToString(int depth)
{
    string str = Indent(depth) + "AND : \n";
    str += Indent(depth + 1) + "LHS : \n";
    str += lhs->ToString(depth + 2);
    str += Indent(depth + 1) + "RHS : \n";
    str += rhs->ToString(depth + 2);
    return str;
}

string Relational::ToString(int depth)
{
    string str = Indent(depth) + WordTypeToString[type] + ":\n";
    str += Indent(depth + 1) + "LHS : \n";
    str += lhs->ToString(depth + 2);
    str += Indent(depth + 1) + "RHS : \n";
    str += rhs->ToString(depth + 2);
    return str;
}

string Arithmetic::ToString(int depth)
{
    string str = Indent(depth) + WordTypeToString[type] + ":\n";
    str += Indent(depth + 1) + "LHS : \n";
    str += lhs->ToString(depth + 2);
    str += Indent(depth + 1) + "RHS : \n";
    str += rhs->ToString(depth + 2);
    return str;
}

string Unary::ToString(int depth)
{
    string str = Indent(depth) + WordTypeToString[type] + ":\n";
    str += Indent(depth + 1) + "SUB : \n";
    str += sub->ToString(depth + 2);
    return str;
}

string Call::ToString(int depth)
{
    string str = Indent(depth) + "CALL :\n ";
    str += Indent(depth + 1) + "SUB : \n";
    str += sub->ToString(depth + 2);
    if (arguments.size() > 0)
    {
        str += Indent(depth + 1) + "ARGUMENTS : \n";
        for (auto& i : arguments)
        {
            str += i->ToString(depth + 2);
        }
    }
    return str;
}


string GetElement::ToString(int depth)
{
    string str = Indent(depth) + "GET_ELEM :\n";
    str += Indent(depth + 1) + "SUB : \n";
    str += sub->ToString(depth + 2);
    str += Indent(depth + 1) + "INDEX : \n";
    str += index->ToString(depth + 2);

    return str;
}

string SetElement::ToString(int depth)
{
    string str = Indent(depth) + "GET_ELEM :\n";
    str += Indent(depth + 1) + "SUB : \n";
    str += sub->ToString(depth + 2);
    str += Indent(depth + 1) + "INDEX : \n";
    str += index->ToString(depth + 2);
    str += Indent(depth + 1) + "VALUE : \n";
    str += value->ToString(depth + 2);
    return str;
}

string GetVariable::ToString(int depth)
{
    string str = Indent(depth) + "GET_VAR :" + name +'\n';
    return str;
}

string SetVariable::ToString(int depth)
{
    string str = Indent(depth) + "SET_VAR :" + name + '\n';
    str += Indent(depth + 1) + "VALUE : \n";
    str += value->ToString(depth + 2);
    return str;
}

string NullLiteral::ToString(int depth)
{
    string str = Indent(depth) + "NULL :\n";
    return str;
}

string BooleanLiteral::ToString(int depth)
{
    string str = Indent(depth) + "BOOLEAN :";
    str += value ? "TRUE" : "FALSE";
    str += '\n';
    return str;
}

string NumberLiteral::ToString(int depth)
{
    string str = Indent(depth) + "NUMBER :";
    str += to_string(value);
    str += '\n';
    return str;
}

string StringLiteral::ToString(int depth)
{
    string str = Indent(depth) + "STRING :" +value;
    str += '\n';
    return str;
}

string ArrayLiteral::ToString(int depth)
{
    string str = Indent(depth)+ "ARRAY :\n";
    if (values.size() > 0)
    {
        str += Indent(depth + 1) + "VALUES :\n";
        for (auto& i : values)
        {
            str += i->ToString(depth + 2);
        }
    }
    return str;
}

string MapLiteral::ToString(int depth)
{
    string str = Indent(depth) + "MAP :\n";
    if (values.size() > 0)
    {
        str += Indent(depth + 1) + "VALUES :\n";
        for (auto& i : values)
        {
            str += "{";
            str += i.first + ", " + i.second->ToString(depth + 1);
            str += "}, ";
        }
    }

    str += "}";
    str += '\n';
    return str;
}

string Program::ToString(int depth)
{
    string str= Indent(depth) + "PROGRAM\n";
    str += Indent(depth+1) + "FUNCTIONS\n";
    for (auto& i : functions)
    {
        str += i->ToString(depth+2);
    }
    str += '\n';
    return str;
}


