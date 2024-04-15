
#include "Node.h"


wstring Indent(int depth)
{
    return wstring(static_cast<size_t>(depth * 2), ' ');
}

wstring Function::ToString(int depth)
{
    wstring str;
    str += Indent(depth) + L"FUNCTION : " + name + L'\n';
    if (parameters.size() > 0)
    {
        str += Indent(depth + 1) + L"PARAMETERS :\n";
        for (auto item : parameters)
        {
            str += item->ToString(depth + 2);
        }
    }
    str += Indent(depth + 1) + L"BLOCK :\n";
    for (auto item : block)
    {
        str += item->ToString(depth + 2);
    }
    return str;
}

wstring Return::ToString(int depth)
{
    wstring str = Indent(depth) + L"RETURN :\n";
    str += Indent(depth + 1) + L"EXPRESSION :\n";
    str += expression->ToString(depth + 2);
    return str;
}

wstring Variable::ToString(int depth)
{
    wstring str = Indent(depth) + L"VAR : " + name + L'\n';
    str += Indent(depth + 1) + L"EXPRESSION :\n";
    str += expression->ToString(depth + 2);
    return str;
}

wstring While::ToString(int depth)
{
    wstring str;
    str = Indent(depth) + L"WHILE :\n";

    if (condition)
    {
        str += Indent(depth + 1) + L"CONDITION : \n";
        str += condition->ToString(depth + 2);
    }
    str += Indent(depth + 1) + L"BLOCK : \n";
    for (auto& item : block)
    {
        str += item->ToString(depth + 2);
    }
    return str;
}

wstring If::ToString(int depth)
{
    wstring str;
    str = Indent(depth) + L"IF :\n";
    if (condition)
    {
        str += Indent(depth + 1) + L"CONDITION : \n";
        str += condition->ToString(depth + 2);
    }

    str += Indent(depth + 1) + L"IF_BLOCK : \n";
    for (auto& item : block)
    {
        str += item->ToString(depth + 2);
    }
  
    str += Indent(depth + 1) + L"ELSE_BLOCK : \n";
    for (auto& item : elseblock)
    {
        str+= item->ToString(depth + 2);
    }

    return str;
}

wstring Print::ToString(int depth)
{
    wstring str = Indent(depth) + L"PRINT : LINE_FEED(" + (lineFeed ? L"TRUE" : L"FALSE") + L")\n";
    if (expressions.size() > 0)
    {
        str += Indent(depth + 1) + L"EXPRESSION: \n";
        for (auto& i : expressions)
        {
            str += i->ToString(depth + 2);
        }
    }
    
    return str;
}

wstring Break::ToString(int depth)
{
    wstring str = Indent(depth)+ L"BREAK :\n";
    return str;
}

wstring Continue::ToString(int depth)
{
    wstring str = Indent(depth) + L"CONTINUE :\n";
    return str;
}

wstring ExpressionStatement::ToString(int depth)
{
    wstring str = Indent(depth) + L"EXPRESSION_STATEMENT :\n ";
    str += Indent(depth + 1) + L"EXPRESSION :\n";
    str += expression->ToString(depth + 2);
    return str;
}

wstring Or::ToString(int depth)
{
    wstring str = Indent(depth) + L"OR : \n";
    str += Indent(depth+1) + L"LHS : \n";
    str += lhs->ToString(depth + 2);
    str += Indent(depth+1) + L"RHS : \n";
    str += rhs->ToString(depth + 2);
    return str;
}

wstring And::ToString(int depth)
{
    wstring str = Indent(depth) + L"AND : \n";
    str += Indent(depth + 1) + L"LHS : \n";
    str += lhs->ToString(depth + 2);
    str += Indent(depth + 1) + L"RHS : \n";
    str += rhs->ToString(depth + 2);
    return str;
}

wstring Relational::ToString(int depth)
{
    wstring str = Indent(depth) + TypeToStr(type) + L":\n";
    str += Indent(depth + 1) + L"LHS : \n";
    str += lhs->ToString(depth + 2);
    str += Indent(depth + 1) + L"RHS : \n";
    str += rhs->ToString(depth + 2);
    return str;
}

wstring Arithmetic::ToString(int depth)
{
    wstring str = Indent(depth) + TypeToStr(type) + L":\n";
    str += Indent(depth + 1) + L"LHS : \n";
    str += lhs->ToString(depth + 2);
    str += Indent(depth + 1) + L"RHS : \n";
    str += rhs->ToString(depth + 2);
    return str;
}

wstring Unary::ToString(int depth)
{
    wstring str = Indent(depth) + TypeToStr(type) + L":\n";
    str += Indent(depth + 1) + L"SUB : \n";
    str += sub->ToString(depth + 2);
    return str;
}

wstring Call::ToString(int depth)
{
    wstring str = Indent(depth) + L"CALL :\n ";
    str += Indent(depth + 1) + L"SUB : \n";
    str += sub->ToString(depth + 2);
    if (arguments.size() > 0)
    {
        str += Indent(depth + 1) + L"ARGUMENTS : \n";
        for (auto& i : arguments)
        {
            str += i->ToString(depth + 2);
        }
    }
    return str;
}


wstring GetElement::ToString(int depth)
{
    wstring str = Indent(depth) + L"GET_ELEM :\n";
    str += Indent(depth + 1) + L"SUB : \n";
    str += sub->ToString(depth + 2);
    str += Indent(depth + 1) + L"INDEX : \n";
    str += index->ToString(depth + 2);

    return str;
}

wstring SetElement::ToString(int depth)
{
    wstring str = Indent(depth) + L"GET_ELEM :\n";
    str += Indent(depth + 1) + L"SUB : \n";
    str += sub->ToString(depth + 2);
    str += Indent(depth + 1) + L"INDEX : \n";
    str += index->ToString(depth + 2);
    str += Indent(depth + 1) + L"VALUE : \n";
    str += value->ToString(depth + 2);
    return str;
}

wstring GetVariable::ToString(int depth)
{
    wstring str = Indent(depth) + L"GET_VAR :" + name + L'\n';
    return str;
}

wstring SetVariable::ToString(int depth)
{
    wstring str = Indent(depth) + L"SET_VAR :" + name + L'\n';
    str += Indent(depth + 1) + L"VALUE : \n";
    str += value->ToString(depth + 2);
    return str;
}

wstring NullLiteral::ToString(int depth)
{
    wstring str = Indent(depth) + L"NULL :\n";
    return str;
}

wstring BooleanLiteral::ToString(int depth)
{
    wstring str = Indent(depth) + L"BOOLEAN :";
    str += value ? L"TRUE" : L"FALSE";
    str += '\n';
    return str;
}

wstring NumberLiteral::ToString(int depth)
{
    wstring str = Indent(depth) + L"NUMBER :";
    str += to_wstring(value);
    str += '\n';
    return str;
}

wstring StringLiteral::ToString(int depth)
{
    wstring str = Indent(depth) + L"STRING :" +value;
    str += '\n';
    return str;
}

//wstring ArrayLiteral::ToString(int depth)
//{
//    wstring str = Indent(depth)+ L"ARRAY :\n";
//    if (values.size() > 0)
//    {
//        str += Indent(depth + 1) + L"VALUES :\n";
//        for (auto& i : values)
//        {
//            str += i->ToString(depth + 2);
//        }
//    }
//    return str;
//}
//
//wstring MapLiteral::ToString(int depth)
//{
//    wstring str = Indent(depth) + L"MAP :\n";
//    if (values.size() > 0)
//    {
//        str += Indent(depth + 1) + L"VALUES :\n";
//        for (auto& i : values)
//        {
//            str += L"{";
//            str += i.first + L", " + i.second->ToString(depth + 1);
//            str += L"}, ";
//        }
//    }
//
//    str += L"}";
//    str += '\n';
//    return str;
//}

wstring Program::ToString(int depth)
{
    wstring str= Indent(depth) + L"PROGRAM\n";
    str += Indent(depth+1) + L"FUNCTIONS\n";
    for (auto& i : functions)
    {
        str += i->ToString(depth+2);
    }
    str += '\n';
    return str;
}

wstring Parameter::ToString(int depth)
{
    wstring str = Indent(depth) + L"PARAMETER\n";
    str += Indent(depth + 1) + (isNumber? L"NUMBER " : L"STRING ");
    str += name + L'\n';

    return wstring();
}
