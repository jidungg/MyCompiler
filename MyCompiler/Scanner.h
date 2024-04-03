#pragma once
#include "Token.h"
#include <vector>

//1. 한 글자씩 읽음.
//2. 읽은 글자가 CharType중 어떤 단어의 첫 글자에 해당하는지 판별.
//3. 판별 결과에 따라 단어가 어떤 단어인지 판별함.
//4. 예를 들어 검사한 글자가 Operator 타입이었다면, 
//      단어가 끝날 때까지 읽어들이고,
//      그 단어가 Operator 중 어떤 Operator였는지 판별.
//5. 판별한 단어와 타입을 Token으로 묶어 리스트에 저장.
//6. Token 리스트 반환
class Scanner
{
public:
	vector<Token> Scan(wstring source);
    void PrintTokenList(vector<Token> tokens);
private:
	CharType GetCharType(wchar_t c);
    bool IsCharType(wchar_t _c, CharType _type);
    Token ScanNumberLiteral();
    Token ScanStringLiteral();
    Token ScanIdentifier();
    Token ScanKorean();
    Token ScanPunctuator();
};

