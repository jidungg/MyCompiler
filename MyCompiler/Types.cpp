#include "Types.h"
#include <map>
#include <set>

static map<wstring, TokenKind> StringToTokenType =
{
    {L"#unknown", TokenKind::Unknown},
    {L"#EndOfToken", TokenKind::EndOfToken},

    {L"없음", TokenKind::NullLiteral},
    {L"참", TokenKind::TrueLiteral},
    {L"거짓", TokenKind::FalseLiteral},

    {L"영", TokenKind::NumberLiteral},
    {L"일", TokenKind::NumberLiteral},
    {L"둘", TokenKind::NumberLiteral},
    {L"삼", TokenKind::NumberLiteral},
    {L"사", TokenKind::NumberLiteral},
    {L"오", TokenKind::NumberLiteral},
    {L"육", TokenKind::NumberLiteral},
    {L"칠", TokenKind::NumberLiteral},
    {L"팔", TokenKind::NumberLiteral},
    {L"구", TokenKind::NumberLiteral},
    {L"십", TokenKind::NumberLiteral},
    {L"백", TokenKind::NumberLiteral},
    {L"천", TokenKind::NumberLiteral},
    {L"만", TokenKind::NumberLiteral},
    {L"억", TokenKind::NumberLiteral},
    {L"조", TokenKind::NumberLiteral},
    {L"점", TokenKind::NumberLiteral},

    {L"#String", TokenKind::StringLiteral},
    {L"#Identifier", TokenKind::Identifier},
    {L"함수", TokenKind::Function},
    {L"반환", TokenKind::Return},
    {L"숫자", TokenKind::NumberVariable},
    {L"문자열", TokenKind::StringVariable},
    {L"전역", TokenKind::Static},
    {L"반복", TokenKind::Repetition},
    {L"탈출", TokenKind::Break},
    {L"건너뛰기", TokenKind::Continue},
    {L"혹시", TokenKind::If},
    {L"출력", TokenKind::Print},

    {L"그리고", TokenKind::And},
    {L"고", TokenKind::And},
    {L"또는", TokenKind::Or},
    {L"거나", TokenKind::Or},


    {L"은", TokenKind::Assignment},
    {L"는", TokenKind::Assignment},
    {L"이", TokenKind::Subject},
    {L"가", TokenKind::Subject},
    {L"을", TokenKind::Object},
    {L"를", TokenKind::Object},
    {L"와", TokenKind::With},
    {L"과", TokenKind::With},
    {L"면", TokenKind::Then},
    {L"동안", TokenKind::Then},
    {L"보다", TokenKind::Than},

    {L"더하기", TokenKind::Add},
    {L"빼기", TokenKind::Subtract},
    {L"곱하기", TokenKind::Multiply},
    {L"나누기", TokenKind::Divide},
    {L"증가", TokenKind::Increase},
    {L"감소", TokenKind::Decrease},
    {L"반전", TokenKind::Reverse},

    {L"같다", TokenKind::Equal},
    {L"다르다", TokenKind::NotEqual},
    {L"작다", TokenKind::Smaller},
    {L"크다", TokenKind::Greater},

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
    L'영',
    L'일',
    L'둘',
    L'삼',
    L'사',
    L'오',
    L'육',
    L'칠',
    L'팔',
    L'구',
    L'십',
    L'백',
    L'천',
    L'만',
    L'억',
    L'조',
    L'점',
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
     L"은",
     L"는",
     L"이",
     L"가",
     L"을",
     L"를",
     L"와",
     L"과",
     L"면",
     L"동안",
     L"보다",
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

