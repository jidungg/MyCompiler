#pragma once



class Scanner
{
public:
	vector<Token> Scan(string source);
    void PrintTokenList(vector<Token> tokens);
private:
	CharType GetCharType(char c);
    bool IsCharType(char _c, CharType _type);
    WordType ToWordType(string str);
	Token ScanNumLiteral();
    Token ScanStringLiteral();
    Token ScanIdenltifierAndKeyword();
    Token ScanOperatorAndPunctuator();
};

