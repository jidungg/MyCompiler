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
    {L"����", TokenKind::Static},
    {L"�ݺ�", TokenKind::Repetition},
    {L"Ż��", TokenKind::Break},
    {L"�ǳʶٱ�", TokenKind::Continue},
    {L"Ȥ��", TokenKind::If},
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
    {L"����", TokenKind::Then},
    {L"����", TokenKind::Than},

    {L"���ϱ�", TokenKind::Add},
    {L"����", TokenKind::Subtract},
    {L"���ϱ�", TokenKind::Multiply},
    {L"������", TokenKind::Divide},
    {L"����", TokenKind::Increase},
    {L"����", TokenKind::Decrease},
    {L"����", TokenKind::Reverse},

    {L"����", TokenKind::Equal},
    {L"�ٸ���", TokenKind::NotEqual},
    {L"�۴�", TokenKind::Smaller},
    {L"ũ��", TokenKind::Greater},

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

