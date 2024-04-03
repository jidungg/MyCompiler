
//#include "Parser.h"
//
//static vector<Token>::iterator current;
//
//void Parser::PrintSyntaxTree(Program* program)
//{
//    cout << program->ToString(0);
//}
//
//Program* Parser::Parse(vector<Token> tokens)
//{
//    Program* result = new Program();
//    current = tokens.begin();
//    while (current->type != TokenType::EndOfToken)
//    {
//        switch (current->type)
//        {
//        case TokenType::Function:
//            result->functions.push_back(ParseFunction());
//            break;
//        default:
//            cout << current->string << " 잘못된 구문입니다." << endl;
//            exit(1);
//        }
//    }
//    return result;
//}
//
//
//
//Function* Parser::ParseFunction()
//{
//    Function* result = new Function();
//    SkipCurrent(TokenType::Function);
//    result->name = current->string;
//    SkipCurrent(TokenType::Identifier);
//    SkipCurrent(TokenType::LeftParen);
//    if (current->type != TokenType::RightParen)
//    {
//        do
//        {
//            result->parameters.push_back(current->string);
//            SkipCurrent(TokenType::Identifier);
//        } while (SkipCurrentIf(TokenType::Comma));
//    }
//    SkipCurrent(TokenType::RightParen);
//    SkipCurrent(TokenType::LeftBrace);
//    result->block = ParseBlock(); 
//    SkipCurrent(TokenType::RightBrace);
//    return result;
//}
//
//vector<Statement*> Parser::ParseBlock()
//{
//    vector<Statement*> result;
//    while (current->type != TokenType::RightBrace)
//    {
//        switch (current->type)
//        {
//        default:
//            result.push_back(ParseExpressionStatement());
//            break;
//        case TokenType::Variable:
//            result.push_back(ParseVariable());
//            break;
//        case TokenType::If:
//            result.push_back(ParseIf());
//            break;
//        case TokenType::For:
//            result.push_back(ParseFor());
//            break;
//        case TokenType::Break:
//            result.push_back(ParseBreak());
//             break;
//        case TokenType::Continue:
//            result.push_back(ParseContinue());
//            break;
//        case TokenType::Print:
//        case TokenType::PrintLine:
//            result.push_back(ParsePrint());
//            break;
//        case TokenType::EndOfToken:
//            cout << WordTypeToString[current->type] << " 잘못된 구문입니다.";
//            exit(1);
//  
//        }
//    }
//    return result;
//}
//
//Variable* Parser::ParseVariable()
//{
//    Variable* result = new Variable();
//    SkipCurrent(TokenType::Variable);
//    result->name = current->string;
//    SkipCurrent(TokenType::Identifier);
//    if (SkipCurrentIf(TokenType::Assignment) == true)
//    {
//        result->expression = ParseExpression();
//    }
//    SkipCurrent(TokenType::Period);
//    return result;
//}
//If* Parser::ParseIf()
//{
//    auto result = new If();
//    SkipCurrent(TokenType::If);
//    do
//    {
//        auto condition = ParseInnerExpression();
//        if (condition == nullptr)
//        {
//            cout << "if문에 조건식이 없습니다." << endl;
//            exit(1);
//        }
//        result->conditions.push_back(condition);
//        SkipCurrent(TokenType::LeftBrace);
//        result->blocks.push_back(ParseBlock());
//        SkipCurrent(TokenType::RightBrace);
//    } while (SkipCurrentIf(TokenType::Elif));
//    if (current->type == TokenType::Else)
//    {
//        SkipCurrent(TokenType::LeftBrace);
//        result->elseblock = ParseBlock();
//        SkipCurrent(TokenType::RightBrace);
//    }
//    
//    return result;
//}
//For* Parser::ParseFor()
//{
//    auto result = new For();
//    SkipCurrent(TokenType::For);
//
//    SkipCurrent(TokenType::LeftParen);
//    if (current->type != TokenType::Period)
//    {
//        do
//        {
//            Variable* variable = new Variable();
//            if (current->type == TokenType::Variable)
//                SkipCurrent(TokenType::Variable);
//            variable->name = current->string;
//            SkipCurrent(TokenType::Identifier);
//            SkipCurrent(TokenType::Assignment);
//            variable->expression = ParseExpression();
//            result->variables.push_back(variable);
//        } while (SkipCurrentIf(TokenType::Comma));
//    }
//    SkipCurrent(TokenType::Period);
//    if (current->type != TokenType::Period)
//    {
//        result->condition = ParseExpression();
//    }
//    SkipCurrent(TokenType::Period);
//    if (current->type != TokenType::RightParen)
//    {
//        do
//        {
//            result->expressions.push_back(ParseExpression());
//        } while (SkipCurrentIf(TokenType::Comma));
//    }
//    SkipCurrent(TokenType::RightParen);
//
//    SkipCurrent(TokenType::LeftBrace);
//    result->block = ParseBlock();
//    SkipCurrent(TokenType::RightBrace);
//
//    return result;
//}
//Break* Parser::ParseBreak()
//{
//    Break* result = new Break();
//    SkipCurrent(TokenType::Break);
//    return result;
//}
//Continue* Parser::ParseContinue()
//{
//    Continue* result = new Continue();
//    SkipCurrent(TokenType::Continue);
//    return result;
//}
//Print* Parser::ParsePrint()
//{
//    Print* result = new Print();
//    result->lineFeed = current->type == TokenType::PrintLine;
//    current++;
//    SkipCurrent(TokenType::LeftParen);
//    if (current->type != TokenType::RightParen)
//    {
//        do
//        {
//            result->expressions.push_back(ParseExpression());
//        } while (SkipCurrentIf(TokenType::Comma));
//    }
//    SkipCurrent(TokenType::RightParen);
//    SkipCurrent(TokenType::Period);
//    return result;
//}
//ExpressionStatement* Parser::ParseExpressionStatement()
//{
//    ExpressionStatement* result = new ExpressionStatement();
//    result->expression = ParseExpression();
//    SkipCurrent(TokenType::Period);
//    return result;
//}
//
//Expression* Parser::ParseExpression()
//{
//    return ParseAssignment();
//}
//
//
//Expression* Parser::ParseAssignment()
//{
//    Expression* result = ParseOr();
//    if (current->type != TokenType::Assignment)
//    {
//        return result;
//    }
//
//    SkipCurrent(TokenType::Assignment);
//    if (GetVariable* getVariable = dynamic_cast<GetVariable*>(result))
//    {
//        SetVariable* result = new SetVariable();
//        result->name = getVariable->name;
//        result->value = ParseAssignment();
//        return result;
//    }
//    if (GetElement* getElement = dynamic_cast<GetElement*>(result))
//    {
//        SetElement* result = new SetElement();
//        result->sub = getElement->sub;
//        result->index = getElement->index;
//        result->value = ParseAssignment();
//        return result;
//    }
//    cout << "잘못된 대입 연산자.";
//    exit(1);
//} 
//
//Expression* Parser::ParseOr()
//{
//    Expression* result = ParseAnd();
//    while (SkipCurrentIf(TokenType::LogicalOr))
//    {
//        Or* tmp = new Or();
//        tmp->lhs = result;
//        tmp->rhs = ParseAnd();
//        result = tmp;
//    }
//    return result;
//}
//
//Expression* Parser::ParseAnd()
//{
//    Expression* result = ParseRelational();
//    while (SkipCurrentIf(TokenType::LogicalAnd))
//    {
//        And* tmp = new And();
//        tmp->lhs = result;
//        tmp->rhs = ParseRelational();
//        result = tmp;
//    }
//    return result;
//}
//
//Expression* Parser::ParseRelational()
//{
//	Expression* result = ParsePlusMinus();
//    TokenType type = current->type;
//    while (SkipCurrentIf(TokenType::LessOrEqual) || SkipCurrentIf(TokenType::LessThan)
//        || SkipCurrentIf(TokenType::GreaterOrEqual) || SkipCurrentIf(TokenType::GreaterThan))
//    {
//		Relational* tmp = new Relational();
//        tmp->type = type;
//		tmp->lhs = result;
//		tmp->rhs = ParsePlusMinus();
//		result = tmp;
//        type = current->type;
//	}
//	return result;
//}
//
//Expression* Parser::ParsePlusMinus()
//{
//	Expression* result = ParseMulDivMod();
//    TokenType type = current->type;
//    while (SkipCurrentIf(TokenType::Add) || SkipCurrentIf(TokenType::Subtract))
//    {
//		Arithmetic* tmp = new Arithmetic();
//        tmp->type = type;
//		tmp->lhs = result;
//		tmp->rhs = ParseMulDivMod();
//		result = tmp;
//        type = current->type;
//	}
//	return result;
//}
//
//Expression* Parser::ParseMulDivMod()
//{
//	Expression* result = ParseUnary();
//	TokenType type = current->type;
//    while (SkipCurrentIf(TokenType::Multiply) || SkipCurrentIf(TokenType::Divide) || SkipCurrentIf(TokenType::Modulo))
//    {
//		Arithmetic* tmp = new Arithmetic();
//        tmp->type = type;
//		tmp->lhs = result;
//		tmp->rhs = ParseUnary();
//		result = tmp;
//        type = current->type;
//	}
//	return result;
//}
//
//Expression* Parser::ParseUnary()
//{
//    return ParsePostUnary(ParsePreUnary());
//}
//
//Expression* Parser::ParsePreUnary()
//{
//
//    TokenType type = current->type;
//    while (SkipCurrentIf(TokenType::Increase) || SkipCurrentIf(TokenType::Decrease)
//        || SkipCurrentIf(TokenType::Subtract) || SkipCurrentIf(TokenType::Add))
//    {
//        Unary* result = new Unary();
//		result->type = type;
//		result->sub = ParsePreUnary();
//        type = current->type;
//        return result;
//	}      
//
//    return ParseOperand();
//}
//
//Expression* Parser::ParsePostUnary(Expression* preUnary)
//{
//    TokenType type = current->type;
//    if (SkipCurrentIf(TokenType::Increase) || SkipCurrentIf(TokenType::Decrease) )
//    {
//        Unary* result = new Unary();
//        result->type = type;
//        result->sub = ParsePostUnary(preUnary);
//        type = current->type;
//        return result;
//    }
//    return preUnary;
//}
//
//Expression* Parser::ParseOperand()
//{
//    Expression* result = nullptr;
//    switch (current->type) {
//    case TokenType::NullLiteral:   result = ParseNullLiteral();      break;
//    case TokenType::TrueLiteral:
//    case TokenType::FalseLiteral:  result = ParseBooleanLiteral();   break;
//    case TokenType::NumberLiteral: result = ParseNumberLiteral();    break;
//    case TokenType::StringLiteral: result = ParseStringLiteral();    break;
//    case TokenType::LeftBraket:    result = ParseListLiteral();      break;
//    case TokenType::LeftBrace:     result = ParseMapLiteral();       break;
//    case TokenType::Identifier:    result = ParseIdentifier();       break;
//    case TokenType::LeftParen:     result = ParseInnerExpression();  break;
//    default: cout << "잘못된 식입니다.";       exit(1);
//    }
//    return ParsePostfix(result);
//}
//
//Expression* Parser::ParseNullLiteral()
//{
//    SkipCurrent(TokenType::NullLiteral);
//    Expression* result = new NullLiteral();
//    return result;
//}
//
//Expression* Parser::ParseBooleanLiteral()
//{
//    BooleanLiteral* result = new BooleanLiteral();
//    result->value = current->type == TokenType::TrueLiteral;
//    if (SkipCurrentIf(TokenType::TrueLiteral))
//        SkipCurrent(TokenType::FalseLiteral);
//    return result;
//}
//
//Expression* Parser::ParseNumberLiteral()
//{
//    NumberLiteral* result = new NumberLiteral();
//    result->value = stod(current->string);
//    SkipCurrent(TokenType::NumberLiteral);
//    return result;
//}
//
//Expression* Parser::ParseStringLiteral()
//{
//    StringLiteral* result = new StringLiteral();
//    result->value = current->string;
//    SkipCurrent(TokenType::StringLiteral);
//    return result;
//}
//
//Expression* Parser::ParseListLiteral()
//{
//    ArrayLiteral* result = new ArrayLiteral();
//    SkipCurrent(TokenType::LeftBrace);
//
//    if (current->type != TokenType::RightBrace)
//    {
//        do
//        {
//            result->values.push_back(ParseExpression());
//        } while (SkipCurrentIf(TokenType::Comma));
//    }
//    SkipCurrent(TokenType::RightBrace);
//    return result;
//}
//
//Expression* Parser::ParseMapLiteral()
//{
//    MapLiteral* result = new MapLiteral();
//    SkipCurrent(TokenType::LeftBrace);
//    if (current->type != TokenType::RightBrace)
//    {
//        do
//        {
//            SkipCurrent(TokenType::LeftBrace);
//            string key = current->string;
//            SkipCurrent(TokenType::Comma);
//            result->values[key] = ParseExpression();
//            
//        } while (SkipCurrentIf(TokenType::Comma));
//    }
//    SkipCurrent(TokenType::RightBrace);
//    return result;
//}
//
//Expression* Parser::ParseIdentifier()
//{
//    GetVariable* result = new GetVariable();
//    result->name = current->string;
//    SkipCurrent(TokenType::Identifier);
//    return result;
//}
//
//Expression* Parser::ParseInnerExpression()
//{
//    SkipCurrent(TokenType::LeftParen);
//    Expression* result = ParseExpression();
//    SkipCurrent(TokenType::RightParen);
//    return result;
//}
//
//Expression* Parser::ParsePostfix(Expression* sub)
//{
//    while (true)
//    {
//        switch (current->type)
//        {
//        case TokenType::LeftParen:
//            sub = ParseCall(sub); break;
//        case TokenType::LeftBraket:
//            sub = ParseElement(sub); break;
//        default:
//            return sub;
//        }
//
//    }
//    
//}
//
//Expression* Parser::ParseCall(Expression* sub)
//{
//    auto result = new Call();
//    result->sub = sub;
//    SkipCurrent(TokenType::LeftParen);
//
//    if (current->type != TokenType::RightParen)
//    {
//        do
//        {
//            result->arguments.push_back(ParseExpression());
//        } while (SkipCurrentIf(TokenType::Comma));
//
//    }
//    
//    SkipCurrent(TokenType::RightParen);
//    return result;
//}
//
//Expression* Parser::ParseElement(Expression* sub)
//{
//    auto result = new GetElement();
//    result->sub = sub;
//    SkipCurrent(TokenType::LeftBraket);
//    result->index = ParseExpression();
//    SkipCurrent(TokenType::RightBraket);
//
//    return result;
//}
//
//void Parser::SkipCurrent(TokenType type)
//{
//    if (current->type != type)
//    {
//        cout << WordTypeToString[type] + " 토큰이 필요합니다." << endl;
//        exit(1);
//    }
//    current++;
//}
//
//bool Parser::SkipCurrentIf(TokenType type)
//{
//    if (current->type != type)
//        return false;
//    else
//        current++;
//
//    return true;
//}
