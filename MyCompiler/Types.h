#pragma once
#include <string>
#include <iostream>

using namespace std;
enum class CharType
{
    Unknown,
    WhiteSpace,
    NumberLiteral, // ���̻�����ĥ�ȱ��ʹ�õ��������
    StringLiteral, // " ���� ���� " ���� ��.
    Identifier, // ' ���� ���� ' ���� ��
    Korean, // 0xAC00 <= c && c <= 0xD7A3
    //Operator, // ���ϱ�, ����, ���ϱ�, ������, ����, ����, ����
    Punctuator, //(), {},[]
    //PostPosition,//���� //�� �� / �� �� / �� �� /�� ��/ ���� / �� �ų�
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

    Or, // ~�ų�
    And, // ~��
    Assignment,// �� ��
    Subject, // �� ��
    Object,// �� ��
    With, //�� ��
    Than, //~����

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