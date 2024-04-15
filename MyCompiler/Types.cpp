#include "Types.h"
#include <map>
#include <set>

static map<wstring, TokenKind> StringToTokenType =
{
    {L"#unknown", TokenKind::Unknown},
    {L"#EndOfToken", TokenKind::EndOfToken},

    {L"����", TokenKind::NullLiteral},
    {L"��", TokenKind::TrueLiteral},
    {L"����", TokenKind::FalseLiteral},

    {L"��", TokenKind::NumberLiteral},
    {L"��", TokenKind::NumberLiteral},
    {L"��", TokenKind::NumberLiteral},
    {L"��", TokenKind::NumberLiteral},
    {L"��", TokenKind::NumberLiteral},
    {L"��", TokenKind::NumberLiteral},
    {L"��", TokenKind::NumberLiteral},
    {L"ĥ", TokenKind::NumberLiteral},
    {L"��", TokenKind::NumberLiteral},
    {L"��", TokenKind::NumberLiteral},
    {L"��", TokenKind::NumberLiteral},
    {L"��", TokenKind::NumberLiteral},
    {L"õ", TokenKind::NumberLiteral},
    {L"��", TokenKind::NumberLiteral},
    {L"��", TokenKind::NumberLiteral},
    {L"��", TokenKind::NumberLiteral},
    {L"��", TokenKind::NumberLiteral},

    {L"#String", TokenKind::StringLiteral},
    {L"#Identifier", TokenKind::Identifier},
    {L"�Լ�", TokenKind::Function},
    {L"��ȯ", TokenKind::Return},
    {L"����", TokenKind::NumberVariable},
    {L"���ڿ�", TokenKind::StringVariable},
    {L"����", TokenKind::BooleanVariable},
    {L"����", TokenKind::Static},
    {L"�ݺ�", TokenKind::Repetition},
    {L"Ż��", TokenKind::Break},
    {L"���", TokenKind::Continue},
    {L"Ȥ��", TokenKind::If},
    {L"�ƴϸ�", TokenKind::Else},
    {L"���", TokenKind::Print},

    {L"�׸���", TokenKind::And},
    {L"��", TokenKind::And},
    {L"�Ǵ�", TokenKind::Or},
    {L"�ų�", TokenKind::Or},


    {L"��", TokenKind::Assignment},
    {L"��", TokenKind::Assignment},
    {L"��", TokenKind::Subject},
    {L"��", TokenKind::Subject},
    {L"��", TokenKind::Object},
    {L"��", TokenKind::Object},
    {L"��", TokenKind::With},
    {L"��", TokenKind::With},
    {L"��", TokenKind::Then},
    {L"����", TokenKind::Ing},
    {L"����", TokenKind::Than},

    {L"���ϱ�", TokenKind::Add},
    {L"����", TokenKind::Subtract},
    {L"���ϱ�", TokenKind::Multiply},
    {L"������", TokenKind::Divide},
    {L"����", TokenKind::Increase},
    {L"����", TokenKind::Decrease},
    {L"����", TokenKind::Reverse},

    {L"��", TokenKind::Equal},
    {L"������", TokenKind::NotEqual},
    {L"��", TokenKind::Smaller},
    {L"ũ", TokenKind::Greater},
    {L"��", TokenKind::Terminal},

    {L",", TokenKind::Comma},
    {L":", TokenKind::Colon},
    {L".", TokenKind::Period},
    {L"(", TokenKind::LeftParen},
    {L")", TokenKind::RightParen},
    {L"{", TokenKind::LeftBrace},
    {L"}", TokenKind::RightBrace},
    {L"[", TokenKind::LeftBraket},
    {L"]", TokenKind::RightBraket}

};

set<wchar_t> NumberLiteralSet =
{
    L'��',
    L'��',
    L'��',
    L'��',
    L'��',
    L'��',
    L'��',
    L'ĥ',
    L'��',
    L'��',
    L'��',
    L'��',
    L'õ',
    L'��',
    L'��',
    L'��',
    L'��',
};
map<wchar_t, long long> UnitsMap =
{
    {L'��',10},
    {L'��',100},
    {L'õ',1000},
    {L'��',10000},
    {L'��',100000000},
    {L'��',1000000000000},
};
map<wchar_t, int> DigitsMap =
{
    {L'��',0},
    {L'��',1},
    {L'��',2},
    {L'��',3},
    {L'��',4},
    {L'��',5},
    {L'��',6},
    {L'ĥ',7},
    {L'��',8},
    {L'��',9},
};
set<wchar_t> PunctuatorSet =
{
   L',',
   L':',
   L'.',
   L'(',
   L')',
   L'{',
   L'}',
   L'[',
   L']',
};
set<wstring> PostPositionSet =
{
     L"��",
     L"��",
     L"��",
     L"��",
     L"��",
     L"��",
     L"��",
     L"��",
     L"��",
     L"����",
     L"����",
};
static auto TypeToString = [] {
    map<TokenKind, wstring> result;
    for (auto& item : StringToTokenType)
        result[item.second] = item.first;
    return result;
}();


TokenKind StrToType(wstring string) {
    if (StringToTokenType.count(string))
        return StringToTokenType.at(string);
    return TokenKind::Unknown;
}

wstring TypeToStr(TokenKind type) {
    if (TypeToString.count(type))
        return TypeToString.at(type);
    return L"";
}

bool IsValidNumber(wstring string)
{
    if (*string.begin() == L'��')
    {
        if (*(string.begin() + 1) != L'��')
        {
            return false;
        }
    }

    return true;
}
//�� /�� �� �� �� �� �� ĥ �� �� /�� �� õ �� �� �� ��
double StrToNumber(wstring string)
{
    int digit  = 0;
    long long unit = 1;
    double underDotMultiplier = 10;
    double result =0;

    auto cur = string.begin();
    while (cur != string.end())
    {
        if (DigitsMap.find(*cur) != DigitsMap.end())
        {
            digit = DigitsMap[*cur];
            cur++;
            continue;
        }
        if (UnitsMap.find(*cur) != UnitsMap.end())
        {
            unit = UnitsMap[*cur];
            cur++;
            if (cur != string.end())
            {
                if (UnitsMap.find(*(cur)) != UnitsMap.end())
                {
                    unit *= UnitsMap[*(cur)];
                    cur++;
                }
            }
            result += digit * unit; 
            digit = 0;
            continue;
        }
        if(*(string.begin() + 1) != L'��')
        {
            cur++;
           
            break;
        }
        
        unit = 1;
    }
    result += digit;

    //�Ҽ��� �Ʒ� 
    while (cur != string.end())
    {
        if (DigitsMap.find(*cur) != DigitsMap.end())
        {
            digit = DigitsMap[*cur];
            cur++;
            result += digit / underDotMultiplier;
            underDotMultiplier *= 10;
        }
        
    }
    return result;
}

