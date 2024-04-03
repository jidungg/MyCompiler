#pragma once
#include "Token.h"
#include <vector>

//1. �� ���ھ� ����.
//2. ���� ���ڰ� CharType�� � �ܾ��� ù ���ڿ� �ش��ϴ��� �Ǻ�.
//3. �Ǻ� ����� ���� �ܾ � �ܾ����� �Ǻ���.
//4. ���� ��� �˻��� ���ڰ� Operator Ÿ���̾��ٸ�, 
//      �ܾ ���� ������ �о���̰�,
//      �� �ܾ Operator �� � Operator������ �Ǻ�.
//5. �Ǻ��� �ܾ�� Ÿ���� Token���� ���� ����Ʈ�� ����.
//6. Token ����Ʈ ��ȯ
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

