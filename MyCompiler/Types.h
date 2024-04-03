#pragma once
#include <string>
#include <iostream>

using namespace std;
enum class CharType
{
    Unknown,
    WhiteSpace,
    NumberLiteral, // 일이삼사오육칠팔구십백천만억조점
    StringLiteral, // " 으로 시작 " 으로 끝.
    Identifier, // ' 으로 시작 ' 으로 끝
    Korean, // 0xAC00 <= c && c <= 0xD7A3
    //Operator, // 더하기, 빼기, 곱하기, 나누기, 증가, 감소, 반전
    Punctuator, //(), {},[]
    //PostPosition,//조사 //은 는 / 이 가 / 을 를 /와 과/ 보다 / 고 거나
};
enum class TokenKind
{
    Unknown, EndOfToken,

    NullLiteral,
    TrueLiteral, FalseLiteral,
    NumberLiteral, StringLiteral,
    Identifier, Static,

    Function, Return, 
    NumberVariable, StringVariable,
    Repetition, Break, Continue,
    If, Then,
    Print,

    Or, // ~거나
    And, // ~고
    Assignment,// 은 는
    Subject, // 이 가
    Object,// 을 를
    With, //와 과
    Than, //~보다

    Add, Subtract, Multiply, Divide,
    Increase, Decrease,
    Reverse,
    Equal, NotEqual,
    Smaller, Greater,

    Comma, Colon, Period,
    LeftParen, RightParen,
    LeftBrace, RightBrace,
    LeftBraket, RightBraket,
};



TokenKind StrToType(wstring string);
wstring TypeToStr(TokenKind type);