#include "pch.h"
#include "Parser.h"

static vector<Token>::iterator current;

void Parser::PrintSyntaxTree(Program* program)
{
    cout << program->ToString(0);
}

Program* Parser::Parse(vector<Token> tokens)
{
    Program* result = new Program();
    current = tokens.begin();
    while (current->type != WordType::EndOfToken)
    {
        switch (current->type)
        {
        case WordType::Function:
            result->functions.push_back(ParseFunction());
            break;
        default:
            cout << current->string << " 잘못된 구문입니다." << endl;
            exit(1);
        }
    }
    return result;
}



Function* Parser::ParseFunction()
{
    Function* result = new Function();
    SkipCurrent(WordType::Function);
    result->name = current->string;
    SkipCurrent(WordType::Identifier);
    SkipCurrent(WordType::LeftParen);
    if (current->type != WordType::RightParen)
    {
        do
        {
            result->parameters.push_back(current->string);
            SkipCurrent(WordType::Identifier);
        } while (SkipCurrentIf(WordType::Comma));
    }
    SkipCurrent(WordType::RightParen);
    SkipCurrent(WordType::LeftBrace);
    result->block = ParseBlock(); 
    SkipCurrent(WordType::RightBrace);
    return result;
}

vector<Statement*> Parser::ParseBlock()
{
    vector<Statement*> result;
    while (current->type != WordType::RightBrace)
    {
        switch (current->type)
        {
        default:
            result.push_back(ParseExpressionStatement());
            break;
        case WordType::Variable:
            result.push_back(ParseVariable());
            break;
        case WordType::If:
            result.push_back(ParseIf());
            break;
        case WordType::For:
            result.push_back(ParseFor());
            break;
        case WordType::Break:
            result.push_back(ParseBreak());
             break;
        case WordType::Continue:
            result.push_back(ParseContinue());
            break;
        case WordType::Print:
        case WordType::PrintLine:
            result.push_back(ParsePrint());
            break;
        case WordType::EndOfToken:
            cout << WordTypeToString[current->type] << " 잘못된 구문입니다.";
            exit(1);
  
        }
    }
    return result;
}

Variable* Parser::ParseVariable()
{
    Variable* result = new Variable();
    SkipCurrent(WordType::Variable);
    result->name = current->string;
    SkipCurrent(WordType::Identifier);
    if (SkipCurrentIf(WordType::Assignment) == true)
    {
        result->expression = ParseExpression();
    }
    SkipCurrent(WordType::Semicolon);
    return result;
}
If* Parser::ParseIf()
{
    auto result = new If();
    SkipCurrent(WordType::If);
    do
    {
        auto condition = ParseInnerExpression();
        if (condition == nullptr)
        {
            cout << "if문에 조건식이 없습니다." << endl;
            exit(1);
        }
        result->conditions.push_back(condition);
        SkipCurrent(WordType::LeftBrace);
        result->blocks.push_back(ParseBlock());
        SkipCurrent(WordType::RightBrace);
    } while (SkipCurrentIf(WordType::Elif));
    if (current->type == WordType::Else)
    {
        SkipCurrent(WordType::LeftBrace);
        result->elseblock = ParseBlock();
        SkipCurrent(WordType::RightBrace);
    }
    
    return result;
}
For* Parser::ParseFor()
{
    auto result = new For();
    SkipCurrent(WordType::For);

    SkipCurrent(WordType::LeftParen);
    if (current->type != WordType::Semicolon)
    {
        do
        {
            Variable* variable = new Variable();
            if (current->type == WordType::Variable)
                SkipCurrent(WordType::Variable);
            variable->name = current->string;
            SkipCurrent(WordType::Identifier);
            SkipCurrent(WordType::Assignment);
            variable->expression = ParseExpression();
            result->variables.push_back(variable);
        } while (SkipCurrentIf(WordType::Comma));
    }
    SkipCurrent(WordType::Semicolon);
    if (current->type != WordType::Semicolon)
    {
        result->condition = ParseExpression();
    }
    SkipCurrent(WordType::Semicolon);
    if (current->type != WordType::RightParen)
    {
        do
        {
            result->expressions.push_back(ParseExpression());
        } while (SkipCurrentIf(WordType::Comma));
    }
    SkipCurrent(WordType::RightParen);

    SkipCurrent(WordType::LeftBrace);
    result->block = ParseBlock();
    SkipCurrent(WordType::RightBrace);

    return result;
}
Break* Parser::ParseBreak()
{
    Break* result = new Break();
    SkipCurrent(WordType::Break);
    return result;
}
Continue* Parser::ParseContinue()
{
    Continue* result = new Continue();
    SkipCurrent(WordType::Continue);
    return result;
}
Print* Parser::ParsePrint()
{
    Print* result = new Print();
    result->lineFeed = current->type == WordType::PrintLine;
    current++;
    SkipCurrent(WordType::LeftParen);
    if (current->type != WordType::RightParen)
    {
        do
        {
            result->expressions.push_back(ParseExpression());
        } while (SkipCurrentIf(WordType::Comma));
    }
    SkipCurrent(WordType::RightParen);
    SkipCurrent(WordType::Semicolon);
    return result;
}
ExpressionStatement* Parser::ParseExpressionStatement()
{
    ExpressionStatement* result = new ExpressionStatement();
    result->expression = ParseExpression();
    SkipCurrent(WordType::Semicolon);
    return result;
}

Expression* Parser::ParseExpression()
{
    return ParseAssignment();
}


Expression* Parser::ParseAssignment()
{
    Expression* result = ParseOr();
    if (current->type != WordType::Assignment)
    {
        return result;
    }

    SkipCurrent(WordType::Assignment);
    if (GetVariable* getVariable = dynamic_cast<GetVariable*>(result))
    {
        SetVariable* result = new SetVariable();
        result->name = getVariable->name;
        result->value = ParseAssignment();
        return result;
    }
    if (GetElement* getElement = dynamic_cast<GetElement*>(result))
    {
        SetElement* result = new SetElement();
        result->sub = getElement->sub;
        result->index = getElement->index;
        result->value = ParseAssignment();
        return result;
    }
    cout << "잘못된 대입 연산자.";
    exit(1);
} 

Expression* Parser::ParseOr()
{
    Expression* result = ParseAnd();
    while (SkipCurrentIf(WordType::LogicalOr))
    {
        Or* tmp = new Or();
        tmp->lhs = result;
        tmp->rhs = ParseAnd();
        result = tmp;
    }
    return result;
}

Expression* Parser::ParseAnd()
{
    Expression* result = ParseRelational();
    while (SkipCurrentIf(WordType::LogicalAnd))
    {
        And* tmp = new And();
        tmp->lhs = result;
        tmp->rhs = ParseRelational();
        result = tmp;
    }
    return result;
}

Expression* Parser::ParseRelational()
{
	Expression* result = ParsePlusMinus();
    WordType type = current->type;
    while (SkipCurrentIf(WordType::LessOrEqual) || SkipCurrentIf(WordType::LessThan)
        || SkipCurrentIf(WordType::GreaterOrEqual) || SkipCurrentIf(WordType::GreaterThan))
    {
		Relational* tmp = new Relational();
        tmp->type = type;
		tmp->lhs = result;
		tmp->rhs = ParsePlusMinus();
		result = tmp;
        type = current->type;
	}
	return result;
}

Expression* Parser::ParsePlusMinus()
{
	Expression* result = ParseMulDivMod();
    WordType type = current->type;
    while (SkipCurrentIf(WordType::Add) || SkipCurrentIf(WordType::Subtract))
    {
		Arithmetic* tmp = new Arithmetic();
        tmp->type = type;
		tmp->lhs = result;
		tmp->rhs = ParseMulDivMod();
		result = tmp;
        type = current->type;
	}
	return result;
}

Expression* Parser::ParseMulDivMod()
{
	Expression* result = ParseUnary();
	WordType type = current->type;
    while (SkipCurrentIf(WordType::Multiply) || SkipCurrentIf(WordType::Divide) || SkipCurrentIf(WordType::Modulo))
    {
		Arithmetic* tmp = new Arithmetic();
        tmp->type = type;
		tmp->lhs = result;
		tmp->rhs = ParseUnary();
		result = tmp;
        type = current->type;
	}
	return result;
}

Expression* Parser::ParseUnary()
{
    return ParsePostUnary(ParsePreUnary());
}

Expression* Parser::ParsePreUnary()
{

    WordType type = current->type;
    while (SkipCurrentIf(WordType::Increase) || SkipCurrentIf(WordType::Decrease)
        || SkipCurrentIf(WordType::Subtract) || SkipCurrentIf(WordType::Add))
    {
        Unary* result = new Unary();
		result->type = type;
		result->sub = ParsePreUnary();
        type = current->type;
        return result;
	}      

    return ParseOperand();
}

Expression* Parser::ParsePostUnary(Expression* preUnary)
{
    WordType type = current->type;
    if (SkipCurrentIf(WordType::Increase) || SkipCurrentIf(WordType::Decrease) )
    {
        Unary* result = new Unary();
        result->type = type;
        result->sub = ParsePostUnary(preUnary);
        type = current->type;
        return result;
    }
    return preUnary;
}

Expression* Parser::ParseOperand()
{
    Expression* result = nullptr;
    switch (current->type) {
    case WordType::NullLiteral:   result = ParseNullLiteral();      break;
    case WordType::TrueLiteral:
    case WordType::FalseLiteral:  result = ParseBooleanLiteral();   break;
    case WordType::NumberLiteral: result = ParseNumberLiteral();    break;
    case WordType::StringLiteral: result = ParseStringLiteral();    break;
    case WordType::LeftBraket:    result = ParseListLiteral();      break;
    case WordType::LeftBrace:     result = ParseMapLiteral();       break;
    case WordType::Identifier:    result = ParseIdentifier();       break;
    case WordType::LeftParen:     result = ParseInnerExpression();  break;
    default: cout << "잘못된 식입니다.";       exit(1);
    }
    return ParsePostfix(result);
}

Expression* Parser::ParseNullLiteral()
{
    SkipCurrent(WordType::NullLiteral);
    Expression* result = new NullLiteral();
    return result;
}

Expression* Parser::ParseBooleanLiteral()
{
    BooleanLiteral* result = new BooleanLiteral();
    result->value = current->type == WordType::TrueLiteral;
    if (SkipCurrentIf(WordType::TrueLiteral))
        SkipCurrent(WordType::FalseLiteral);
    return result;
}

Expression* Parser::ParseNumberLiteral()
{
    NumberLiteral* result = new NumberLiteral();
    result->value = stod(current->string);
    SkipCurrent(WordType::NumberLiteral);
    return result;
}

Expression* Parser::ParseStringLiteral()
{
    StringLiteral* result = new StringLiteral();
    result->value = current->string;
    SkipCurrent(WordType::StringLiteral);
    return result;
}

Expression* Parser::ParseListLiteral()
{
    ArrayLiteral* result = new ArrayLiteral();
    SkipCurrent(WordType::LeftBrace);

    if (current->type != WordType::RightBrace)
    {
        do
        {
            result->values.push_back(ParseExpression());
        } while (SkipCurrentIf(WordType::Comma));
    }
    SkipCurrent(WordType::RightBrace);
    return result;
}

Expression* Parser::ParseMapLiteral()
{
    MapLiteral* result = new MapLiteral();
    SkipCurrent(WordType::LeftBrace);
    if (current->type != WordType::RightBrace)
    {
        do
        {
            SkipCurrent(WordType::LeftBrace);
            string key = current->string;
            SkipCurrent(WordType::Comma);
            result->values[key] = ParseExpression();
            
        } while (SkipCurrentIf(WordType::Comma));
    }
    SkipCurrent(WordType::RightBrace);
    return result;
}

Expression* Parser::ParseIdentifier()
{
    GetVariable* result = new GetVariable();
    result->name = current->string;
    SkipCurrent(WordType::Identifier);
    return result;
}

Expression* Parser::ParseInnerExpression()
{
    SkipCurrent(WordType::LeftParen);
    Expression* result = ParseExpression();
    SkipCurrent(WordType::RightParen);
    return result;
}

Expression* Parser::ParsePostfix(Expression* sub)
{
    while (true)
    {
        switch (current->type)
        {
        case WordType::LeftParen:
            sub = ParseCall(sub); break;
        case WordType::LeftBraket:
            sub = ParseElement(sub); break;
        default:
            return sub;
        }

    }
    
}

Expression* Parser::ParseCall(Expression* sub)
{
    auto result = new Call();
    result->sub = sub;
    SkipCurrent(WordType::LeftParen);

    if (current->type != WordType::RightParen)
    {
        do
        {
            result->arguments.push_back(ParseExpression());
        } while (SkipCurrentIf(WordType::Comma));

    }
    
    SkipCurrent(WordType::RightParen);
    return result;
}

Expression* Parser::ParseElement(Expression* sub)
{
    auto result = new GetElement();
    result->sub = sub;
    SkipCurrent(WordType::LeftBraket);
    result->index = ParseExpression();
    SkipCurrent(WordType::RightBraket);

    return result;
}

void Parser::SkipCurrent(WordType type)
{
    if (current->type != type)
    {
        cout << WordTypeToString[type] + " 토큰이 필요합니다." << endl;
        exit(1);
    }
    current++;
}

bool Parser::SkipCurrentIf(WordType type)
{
    if (current->type != type)
        return false;
    else
        current++;

    return true;
}
