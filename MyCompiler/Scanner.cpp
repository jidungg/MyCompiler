
#include "Scanner.h"
#include <string>
#include <iostream>
#include <set>

static wstring::iterator current ;
extern set<wchar_t> NumberLiteralSet;
extern set<wchar_t> PunctuatorSet;

vector<Token> Scanner::Scan(wstring source)
{
	vector<Token> result;
	source += L'\0';
	current = source.begin();
	while (*current != '\0')
	{
		switch (GetCharType(*current))
		{
		case CharType::WhiteSpace:
			current++;
			break;
		case CharType::NumberLiteral:
			result.push_back(ScanNumberLiteral());
			break;
		case CharType::StringLiteral:
			result.push_back(ScanStringLiteral());
			break;
		case CharType::Identifier:
			result.push_back(ScanIdentifier());
			break;
		case CharType::Korean:
			result.push_back(ScanKorean());
			break;
		case CharType::Punctuator:
			result.push_back(ScanPunctuator());
			break;
		case CharType::Unknown:
		default:
			cout << "모르는 글자" << endl;
			exit(1);
			break;
		}
	}
	
	result.push_back({ TokenKind::EndOfToken });
    return result;
}
CharType Scanner::GetCharType(wchar_t c)
{
	if (' ' == c || '\t' == c || '\n' == c || '\r' == c)
		return CharType::WhiteSpace;

	if (NumberLiteralSet.count(c))
		return CharType::NumberLiteral;

	if (PunctuatorSet.count(c))
		return CharType::Punctuator;

	if (L'\"' == c)
		return CharType::StringLiteral;

	if (L'\'' == c)
		return CharType::Identifier;

	if (0xAC00 <= c && c <= 0xD7A3)
		return CharType::Korean;

	return CharType::Unknown;
}
Token Scanner::ScanNumberLiteral()
{
	wstring string;
	while (IsCharType(*current,CharType::NumberLiteral))
	{
		string += *current++;
	}
	return Token{ TokenKind::NumberLiteral, string };
}
Token Scanner::ScanStringLiteral()
{
	wstring string;
	current++;
	while (IsCharType(*current, CharType::StringLiteral))
	{
		string += *current++;
	}
	if (L'\"' != *current)
	{
		cout << "문자열 끝에 \" 가 없습니다." << endl;
		exit(1);
	}
	current++; 
	return Token{ TokenKind::StringLiteral , string };
}
Token Scanner::ScanIdentifier()
{
	wstring string;
	current++;
	while (IsCharType(*current, CharType::Identifier))
	{
		string += *current++;
	}
	if (L'\'' != *current)
	{
		cout << "문자열 끝에 \" 가 없습니다." << endl;
		exit(1);
	}
	current++;
	return Token{ TokenKind::Identifier , string };
}
Token Scanner::ScanKorean()
{
	wstring string;
	TokenKind type;
	while (IsCharType(*current, CharType::Korean))
	{
		string += *current++;
		type = StrToType(string);
		if (type != TokenKind::Unknown)
		{
			return Token{ type, string };
		}
	}

	type = StrToType(string);
	if (type == TokenKind::Unknown)
	{
		wcout << string << L" 을 알 수 없습니다." << endl;
		exit(1);
	}
		
	return Token{ type, string };
	
}

Token Scanner::ScanPunctuator()
{
	wstring string;
	while (IsCharType(*current, CharType::Punctuator))
		string += *current++;
	while (string.empty() == false && StrToType(string) == TokenKind::Unknown) {
		string.pop_back();
		current--;
	}
	if (string.empty()) {
		cout << *current << " 사용할 수 없는 문자입니다.";
		exit(1);
	}
	return Token{ StrToType(string), string };
}
bool Scanner::IsCharType(wchar_t c, CharType type)
{
	switch (type)
	{
	case CharType::Unknown:
		break;
	case CharType::WhiteSpace:
		return (L' ' == c || L'\t' == c || L'\n' == c || L'\r' == c);
	case CharType::NumberLiteral:
		return (NumberLiteralSet.count(c));
	case CharType::StringLiteral:
		return ((0xAC00 <= c && c <= 0xD7A3) || (32 <= c && c <= 126)) && c != L'\"';
	case CharType::Identifier:
		return (0xAC00 <= c && c <= 0xD7A3);
	case CharType::Korean:
		return (0xAC00 <= c && c <= 0xD7A3);
	case CharType::Punctuator:
		return (PunctuatorSet.count(c));
	default:
		return false;
	}
	return false;
}

void Scanner::PrintTokenList(vector<Token> tokens)
{
	for (auto iter = tokens.begin(); iter != tokens.end(); iter++)
	{
		wcout.width(20);
		wcout << left << TypeToStr(iter->type);
		wcout << L"\t" << iter->string << endl;
	}
}