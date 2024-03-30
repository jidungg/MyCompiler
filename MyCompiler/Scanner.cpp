#include "pch.h"
#include "Scanner.h"


static string::iterator current ;

vector<Token> Scanner::Scan(string source)
{
	vector<Token> result;
	source += '\0';
	current = source.begin();
	while (*current != '\0')
	{
		switch (GetCharType(*current))
		{
		case CharType::WhiteSpace:
			current++;
			break;
		case CharType::NumberLiteral:
			result.push_back(ScanNumLiteral());
			break;
		case CharType::StringLiteral:
			result.push_back(ScanStringLiteral());
			break;
		case CharType::IdentifierAndKeyword:
			result.push_back(ScanIdenltifierAndKeyword());
			break;
		case CharType::OperatorAndPunctuator:
			result.push_back(ScanOperatorAndPunctuator());
			break;

		case CharType::Unknown:
		default:
			cout << "모르는 글자" << endl;
			exit(1);
			break;
		}
	}
	
	result.push_back({ WordType::EndOfToken });
    return result;
}
void Scanner::PrintTokenList(vector<Token> tokens)
{
	for (auto iter = tokens.begin(); iter != tokens.end(); iter++)
	{
		cout.width(20);
		cout << left<< WordTypeToString[iter->type];
		cout << "\t" << iter->string << endl;

	}
}
CharType Scanner::GetCharType(char c)
{
	if (' ' == c || '\t' == c || '\n' == c || '\r' == c)
		return CharType::WhiteSpace;
	           
	if ('0' <= c && '9' >= c)
		return CharType::NumberLiteral;

	if ('\'' == c)
		return CharType::StringLiteral;

	if ('a' <= c && 'z' >= c||
		'A' <= c && 'Z' >= c)
		return CharType::IdentifierAndKeyword;

	if (('!' <= c && '/' >= c) ||
		(':' <= c && '@' >= c) ||
		('[' <= c && '`' >= c) ||
		('{' <= c && '}' >= c))
		return CharType::OperatorAndPunctuator;

	return CharType::Unknown;
}

Token Scanner::ScanNumLiteral()
{
	string string;
	while (IsCharType(*current, CharType::NumberLiteral) || *current == '.')
	{
		string += *current++;
	}

	return Token{ WordType::NumberLiteral , string};
}
Token Scanner::ScanStringLiteral()
{
	string string;
	current++;
	while (IsCharType(*current, CharType::StringLiteral))
	{
		string += *current++;
	}
	if ('\'' != *current)
	{
		cout << "문자열 끝에 \' 가 없습니다." << endl;
		exit(1);
	}
	current++; 
	return Token{ WordType::StringLiteral , string };
}
Token Scanner::ScanIdenltifierAndKeyword()
{
	string string;
	while (IsCharType(*current, CharType::IdentifierAndKeyword))
	{
		string += *current++;
	}
	WordType type = ToWordType(string);
	if (type == WordType::Unknown)
		type = WordType::Identifier;
	return Token{ type, string };
	
}
Token Scanner::ScanOperatorAndPunctuator()
{
	string string;
	while (IsCharType(*current, CharType::OperatorAndPunctuator))
	{
		string += *current++;
	}
	WordType type = WordType::Unknown;
	while (string.empty() == false && (type = ToWordType(string)) == WordType::Unknown)
	{
		string.pop_back();
		current--;
	}
	if (string.empty() || type == WordType::Unknown)
	{
		cout << *current << " : 잘못된 연산자입니다." << endl;
		exit(1);
	}
	return Token{ type, string };
}
bool Scanner::IsCharType(char c, CharType type)
{
	switch (type)
	{
	case CharType::Unknown:
		break;
	case CharType::WhiteSpace:
		return (' ' == c || '\t' == c || '\n' == c || '\r' == c);
	case CharType::NumberLiteral:
		return ('0' <= c && '9' >= c);
	case CharType::StringLiteral:
		return (' ' <= c && '~' >= c && '\'' != c);
	case CharType::IdentifierAndKeyword:
		return ('O' <= c && c <= '9' ||
			'a' <= c && c <= 'z' ||
			'A' <= c && c <= 'Z');
	case CharType::OperatorAndPunctuator:
		return ('!' <= c && '/' >= c) ||
			(':' <= c && '@' >= c) ||
			('[' <= c && '`' >= c) ||
			('{' <= c && '}' >= c);
	default:
		return false;
	}


	return false;
}
WordType Scanner::ToWordType(string str)
{
	if (StringToWordType.count(str))
	{
		return StringToWordType[str];
	}
	return WordType::Unknown;
}