
#include "Parser.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include "Token.h"
#include "Node.h"
using namespace std;

static vector<Token>::iterator current;

void Parser::PrintSyntaxTree(Program* program)
{
    wcout << program->ToString(0);
}

Program* Parser::Parse(vector<Token> tokens)
{
    Program* result = new Program();
    current = tokens.begin();
    while (current->type != TokenKind::EndOfToken)
    {
        switch (current->type)
        {
        case TokenKind::Function:
            result->functions.push_back(ParseFunction());
            break;
        case TokenKind::Static:
            result->staticVariables.push_back(ParseStaticVariable());
            break;
        case TokenKind::NumberVariable:
            result->staticVariables.push_back(ParseNumberVariable());
			break;
        case TokenKind::StringVariable:
            result->staticVariables.push_back(ParseStringVariable());
            break;
        default:
            wcout << current->string << " 잘못된 구문입니다." << endl;
            exit(1);
        }
    }
    return result;
}



Function* Parser::ParseFunction()
{
    Function* result = new Function();
    SkipCurrent(TokenKind::Function);
    result->name = current->string;
    SkipCurrent(TokenKind::Identifier);
    SkipCurrent(TokenKind::LeftParen);
    if (current->type != TokenKind::RightParen)
    {
        do
        {
            Parameter* variable = PareseParameter();
			result->parameters.push_back(variable);
        } while (SkipCurrentIf(TokenKind::Comma));
    }
    SkipCurrent(TokenKind::RightParen);
    SkipCurrent(TokenKind::LeftBrace);
    result->block = ParseBlock(); 
    SkipCurrent(TokenKind::RightBrace);
    return result;
}

Parameter* Parser::PareseParameter()
{
    Parameter* result = new Parameter();
    if (current->type == TokenKind::NumberVariable)
    {
        result->isNumber = true;
        SkipCurrent(TokenKind::NumberVariable);
    }
    else if (current->type == TokenKind::StringVariable)
    {
        result->isNumber = false;
        SkipCurrent(TokenKind::StringVariable);
    }
    else
    {
        wcout << "잘못된 매개변수 선언입니다." << endl;
        exit(1);
    }

    result->name = current->string;
    SkipCurrent(TokenKind::Identifier);
    return result;
}

vector<Statement*> Parser::ParseBlock()
{
    vector<Statement*> result;
    while (current->type != TokenKind::RightBrace)
    {
        switch (current->type)
        {
        default:
            result.push_back(ParseExpressionStatement());
            break;
        case TokenKind::Static:
			result.push_back(ParseStaticVariable());
			break;
        case TokenKind::NumberVariable:
            result.push_back(ParseNumberVariable());
            break;
        case TokenKind::StringVariable:
            result.push_back(ParseStringVariable());
			break;
        case TokenKind::If:
            result.push_back(ParseIf());
            break;
        case TokenKind::Repetition:
            result.push_back(ParseWhile());
            break;
        case TokenKind::Break:
            result.push_back(ParseBreak());
             break;
        case TokenKind::Continue:
            result.push_back(ParseContinue());
            break;
        case TokenKind::Return:
            result.push_back(ParseExpressionStatement());
            break;
        case TokenKind::EndOfToken:
            wcout << TypeToStr(current->type) << " 잘못된 구문입니다.";
            exit(1);
  
        }
    }
    return result;
}

Variable* Parser::ParseStaticVariable()
{
    Variable* result;
    SkipCurrent(TokenKind::Static);

    switch (current->type)
    {
    case TokenKind::NumberVariable:
		result = ParseNumberVariable();
		break;
    case TokenKind::StringVariable:
        result = ParseStringVariable();
        break;
    default:
        cout << "잘못된 변수 선언입니다." << endl;
        exit(1);
        break;
    }
    result->isStatic = true;
    return result;
}
Variable* Parser::ParseNumberVariable()
{
    Variable* result = new Variable();

    result->isNumber = true;
    SkipCurrent(TokenKind::NumberVariable);

    result->name = current->string;
    SkipCurrent(TokenKind::Identifier);

    if (SkipCurrentIf(TokenKind::Assignment) == true)
    {
        result->expression = ParseExpression();
    }
    SkipCurrent(TokenKind::Period);
    return result;
}
Variable* Parser::ParseStringVariable()
{
    Variable* result = new Variable();
    result->name = current->string;
    SkipCurrent(TokenKind::StringVariable);
    SkipCurrent(TokenKind::Identifier);
    if (SkipCurrentIf(TokenKind::Assignment) == true)
    {
        result->expression = ParseExpression();
    }
    SkipCurrent(TokenKind::Period);
    return result;
}
If* Parser::ParseIf()
{
    auto result = new If();
    SkipCurrent(TokenKind::If);

    auto condition = ParseInnerExpression();
    if (condition == nullptr)
    {
        wcout << "조건문에 조건식이 없습니다." << endl;
        exit(1);
    }
    result->condition = condition;
    SkipCurrent(TokenKind::Then);
    SkipCurrent(TokenKind::LeftBrace);
    result->block = ParseBlock();
    SkipCurrent(TokenKind::RightBrace);
 
    if (current->type == TokenKind::Else)
    {
        SkipCurrent(TokenKind::Else);
        SkipCurrent(TokenKind::LeftBrace);
        result->elseblock = ParseBlock();
        SkipCurrent(TokenKind::RightBrace);
    }
    
    return result;
}
While* Parser::ParseWhile()
{
    auto result = new While();
    SkipCurrent(TokenKind::Repetition);

    auto condition = ParseInnerExpression();
    if (condition == nullptr)
    {
        wcout << "반복문에 조건식이 없습니다." << endl;
        exit(1);
    }
    result->condition = condition;
    SkipCurrent(TokenKind::Ing);
    SkipCurrent(TokenKind::LeftBrace);
    result->block = ParseBlock();
    SkipCurrent(TokenKind::RightBrace);


    return result;
}
Break* Parser::ParseBreak()
{
    Break* result = new Break();
    SkipCurrent(TokenKind::Break);
    SkipCurrent(TokenKind::Period);
    return result;
}
Continue* Parser::ParseContinue()
{
    Continue* result = new Continue();
    SkipCurrent(TokenKind::Continue);
    SkipCurrent(TokenKind::Period);
    return result;
}
Return* Parser::ParseReturn()
{
    auto result = new Return();
    SkipCurrent(TokenKind::Return);
    result->expression = ParseExpression();
    if (result->expression == nullptr) {
        cout << "return문에 식이 없습니다.";
        exit(1);
    }
    SkipCurrent(TokenKind::Period);
    return result;
}
Print* Parser::ParsePrint()
{
    Print* result = new Print();
    SkipCurrent(TokenKind::Print);
    SkipCurrent(TokenKind::LeftParen);
    if (current->type != TokenKind::RightParen)
    {
        do
        {
            result->expressions.push_back(ParseExpression());
        } while (SkipCurrentIf(TokenKind::Comma));
    }
    SkipCurrent(TokenKind::RightParen);
    SkipCurrent(TokenKind::Period);
    return result;
}
ExpressionStatement* Parser::ParseExpressionStatement()
{
    ExpressionStatement* result = new ExpressionStatement();
    result->expression = ParseExpression();
    SkipCurrent(TokenKind::Period);
    return result;
}

Expression* Parser::ParseExpression()
{
    return ParseAssignment();
}

//A가 B보다 크거나 A가 C보다 작다
//A가 B보다 크거나 A가 C보다 작고 A가 D와 같다
//는
//거나
//고
//
Expression* Parser::ParseAssignment()
{
    Expression* result = ParseOr();
    if (current->type != TokenKind::Assignment)
    {
        return result;
    }

    SkipCurrent(TokenKind::Assignment);
    if (GetVariable* getVariable = dynamic_cast<GetVariable*>(result))
    {
        SetVariable* result = new SetVariable();
        result->name = getVariable->name;
        result->value = ParseAssignment();
        return result;
    }

    wcout << "잘못된 대입 연산자.";
    exit(1);
} 

Expression* Parser::ParseOr()
{
    Expression* result = ParseAnd();
    while (SkipCurrentIf(TokenKind::Or))
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
    SkipCurrentIf(TokenKind::Terminal);
    while (SkipCurrentIf(TokenKind::And))
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
    if (SkipCurrentIf(TokenKind::Subject))
    {
        Relational* tmp = new Relational();
        tmp->lhs = result;
        tmp->rhs = ParsePlusMinus();
        TokenKind type;
        if (SkipCurrentIf(TokenKind::Than))
        {
            type = current->type;
            if(SkipCurrentIf(TokenKind::Smaller) ||
                SkipCurrentIf(TokenKind::Greater))
            {
                tmp->type = type;
            }
            else
            {
                wcout << TypeToStr(TokenKind::Smaller) << " 혹은 " << TypeToStr(TokenKind::Greater) << " 가 와야합니다." << endl;
                exit(1);
            }
        }
        else if (SkipCurrentIf(TokenKind::With))
        {
            type = current->type;
            if(SkipCurrentIf(TokenKind::Equal) ||
                SkipCurrentIf(TokenKind::NotEqual))
            {
                tmp->type = type;
            }
            else
            {
                wcout << TypeToStr(TokenKind::Equal) << " 혹은 " << TypeToStr(TokenKind::NotEqual) << " 가 와야합니다." << endl;
                exit(1);
            }
        }
        else
        {
            wcout << TypeToStr(TokenKind::Than) << " 혹은 " << TypeToStr(TokenKind::With) << " 가 와야합니다." << endl;
            exit(1);
        }
        
        

        result = tmp;
    }

	return result;
}

Expression* Parser::ParsePlusMinus()
{
	Expression* result = ParseMulDiv();
    TokenKind type = current->type;
    while (SkipCurrentIf(TokenKind::Add) || SkipCurrentIf(TokenKind::Subtract))
    {
		Arithmetic* tmp = new Arithmetic();
        tmp->type = type;
		tmp->lhs = result;
		tmp->rhs = ParseMulDiv();
		result = tmp;
        type = current->type;
	}
	return result;
}

Expression* Parser::ParseMulDiv()
{
	Expression* result = ParseUnary();
	TokenKind type = current->type;
    while (SkipCurrentIf(TokenKind::Multiply) || SkipCurrentIf(TokenKind::Divide) )
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
    Expression* result = ParseOperand();
    TokenKind type = current->type;
    Unary* unary;
    while (SkipCurrentIf(TokenKind::Increase) || SkipCurrentIf(TokenKind::Decrease) ||
        SkipCurrentIf(TokenKind::Reverse))
    {
        unary = new Unary();
        unary->type = type;
        unary->sub = result;
        type = current->type;
        result = unary;
    }
    return result;
}

Expression* Parser::ParseOperand()
{
    Expression* result = nullptr;
    switch (current->type) {
    case TokenKind::NullLiteral:   result = ParseNullLiteral();      break;
    case TokenKind::TrueLiteral:
    case TokenKind::FalseLiteral:  result = ParseBooleanLiteral();   break;
    case TokenKind::NumberLiteral: result = ParseNumberLiteral();    break;
    case TokenKind::StringLiteral: result = ParseStringLiteral();    break;
    case TokenKind::LeftBraket:    result = ParseCall();             break;
    case TokenKind::Identifier:    result = ParseIdentifier();       break;
    case TokenKind::LeftParen:     result = ParseInnerExpression();  break;
    default: wcout << "잘못된 식입니다.";       exit(1);
    }
    return ParsePostfix(result);
}

Expression* Parser::ParseNullLiteral()
{
    SkipCurrent(TokenKind::NullLiteral);
    Expression* result = new NullLiteral();
    return result;
}

Expression* Parser::ParseBooleanLiteral()
{
    BooleanLiteral* result = new BooleanLiteral();
    result->value = current->type == TokenKind::TrueLiteral;
    if (SkipCurrentIf(TokenKind::TrueLiteral))
        SkipCurrent(TokenKind::FalseLiteral);
    return result;
}

Expression* Parser::ParseNumberLiteral()
{
    NumberLiteral* result = new NumberLiteral();
    result->value = StrToNumber(current->string);
    SkipCurrent(TokenKind::NumberLiteral);
    return result;
}

Expression* Parser::ParseStringLiteral()
{
    StringLiteral* result = new StringLiteral();
    result->value = current->string;
    SkipCurrent(TokenKind::StringLiteral);
    return result;
}

Expression* Parser::ParseIdentifier()
{
    GetVariable* result = new GetVariable();
    result->name = current->string;
    SkipCurrent(TokenKind::Identifier);
    return result;
}

Expression* Parser::ParseInnerExpression()
{
    Expression* result;
    SkipCurrent(TokenKind::LeftParen);
    result = ParseExpression(); 
    SkipCurrent(TokenKind::RightParen);
    return result;
}

Expression* Parser::ParsePostfix(Expression* sub)
{
    while (true)
    {
        switch (current->type)
        {
 /*       case TokenKind::LeftBraket:
            sub = ParseElement(sub); break;*/
        default:
            return sub;
        }

    }
    
}

Expression* Parser::ParseCall()
{
    auto result = new Call();

    SkipCurrent(TokenKind::LeftBraket);
    if (current->type != TokenKind::RightBraket)
    {
        do
        {
            result->arguments.push_back(ParseExpression());
        } while (SkipCurrentIf(TokenKind::Comma));

    }
    SkipCurrent(TokenKind::RightBraket);

    SkipCurrent(TokenKind::Object);
    
    result->sub = ParseIdentifier();
    
    return result;
}

Expression* Parser::ParseElement(Expression* sub)
{
    auto result = new GetElement();
    result->sub = sub;
    SkipCurrent(TokenKind::LeftBraket);
    result->index = ParseExpression();
    SkipCurrent(TokenKind::RightBraket);

    return result;
}

void Parser::SkipCurrent(TokenKind type)
{
    if (current->type != type)
    {
        wcout << TypeToStr(type) + L" 토큰이 필요합니다." << endl;
        exit(1);
    }
    current++;
}

bool Parser::SkipCurrentIf(TokenKind type)
{
    if (current->type != type)
        return false;
    else
        current++;

    return true;
}
