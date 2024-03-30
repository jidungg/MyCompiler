#pragma once

#include <string>
#include <iostream>
#include <any>
#include "map"
#include "vector"
#include "set"
#include "list"

using namespace std;
enum class CharType
{
    Unknown,
    WhiteSpace,
    NumberLiteral,
    StringLiteral,
    IdentifierAndKeyword,
    OperatorAndPunctuator,
};
enum class WordType
{
    Unknown, EndOfToken,
    NullLiteral,
    TrueLiteral, FalseLiteral,
    NumberLiteral, StringLiteral,
    Identifier,

    Function, Return, Variable,
    For, Break, Continue,
    If, Else, Elif,
    Print, PrintLine,

    LogicalAnd, LogicalOr,
    Assignment,
    Add, Subtract,
    Multiply, Divide, Modulo,
    Increase, Decrease,
    Equal, NotEqual,
    LessThan, GreaterThan,
    LessOrEqual, GreaterOrEqual,

    Comma, Colon, Semicolon,
    LeftParen, RightParen,
    LeftBrace, RightBrace,
    LeftBraket, RightBraket
};

static map<string, WordType> StringToWordType =
{
    {"#unknown", WordType::Unknown},
    {"#EndOfToken", WordType::EndOfToken},

    {"null", WordType::NullLiteral},
    {"true", WordType::TrueLiteral},
    {"false", WordType::FalseLiteral},
    {"#Number", WordType::NumberLiteral},
    {"#String", WordType::StringLiteral},
    {"#Identifier", WordType::Identifier},
    {"function", WordType::Function},
    {"return", WordType::Return},
    {"var", WordType::Variable},
    {"for", WordType::For},
    {"break", WordType::Break},
    {"continue", WordType::Continue},
    {"if", WordType::If},
    {"elif", WordType::Elif},
    {"else", WordType::Else},
    {"print", WordType::Print},
    {"printLine", WordType::PrintLine},

    {"and", WordType::LogicalAnd},
    {"or", WordType::LogicalOr},

    {"=", WordType::Assignment},
    {"+", WordType::Add},
    {"-", WordType::Subtract},
    {"*", WordType::Multiply},
    {"/", WordType::Divide},
    {"%", WordType::Modulo},
    {"++", WordType::Increase},
	{"--", WordType::Decrease},

    {"==", WordType::Equal},
    {"!=", WordType::NotEqual},
    {"<", WordType::LessThan},
    {">", WordType::GreaterThan},
    {"<=", WordType::LessOrEqual},
    {">=", WordType::GreaterOrEqual},


    {",", WordType::Comma},
    {":", WordType::Colon},
    {";", WordType::Semicolon},
    {"(", WordType::LeftParen},
    {")", WordType::RightParen},
    {"{", WordType::LeftBrace},
    {"}", WordType::RightBrace},
    {"[", WordType::LeftBraket},
    {"]", WordType::RightBraket}

};
static map<WordType, string> WordTypeToString =
{
    {WordType::Unknown, "WordType::Unknown"},
    {WordType::EndOfToken ,"WordType::EndOfToken"},

    {WordType::NullLiteral, "WordType::NullLiteral"},
    {WordType::TrueLiteral, "WordType::TrueLiteral"},
    {WordType::FalseLiteral,"WordType::FalseLiteral"},
    {WordType::NumberLiteral, "WordType::NumberLiteral"},
    {WordType::StringLiteral, "WordType::StringLiteral"},
    {WordType::Identifier, "WordType::Identifier"},
    {WordType::Function, "WordType::Function"},
    {WordType::Return, "WordType::Return"},
    {WordType::Variable, "WordType::Variable"},
    {WordType::For, "WordType::For"},
    {WordType::Break, "WordType::Break"},
    {WordType::Continue, "WordType::Continue"},
    {WordType::If, "WordType::If"},
    {WordType::Elif, "WordType::Elif"},
    {WordType::Else, "WordType::Else"},
    {WordType::Print, "WordType::Print"},
    {WordType::PrintLine, "WordType::PrintLine"},

    {WordType::LogicalAnd, "WordType::LogicalAnd"},
    {WordType::LogicalOr, "WordType::LogicalOr"},

    {WordType::Assignment, "WordType::Assignment"},
    {WordType::Add, "WordType::Add"},
    {WordType::Subtract, "WordType::Subtract"},
    {WordType::Multiply, "WordType::Multiply"},
    {WordType::Divide, "WordType::Divide"},
    {WordType::Modulo, "WordType::Modulo"},
    {WordType::Increase, "WordType::Increase"},
    {WordType::Decrease, "WordType::Decrease"},

    {WordType::Equal, "WordType::Equal"},
    {WordType::NotEqual, "WordType::NotEqual"},
    {WordType::LessThan, "WordType::LessThan"},
    {WordType::GreaterThan, "WordType::GreaterThan"},
    {WordType::LessOrEqual, "WordType::LessOrEqual"},
    {WordType::GreaterOrEqual, "WordType::GreaterOrEqual"},

    {WordType::Comma, "WordType::Comma"},
    {WordType::Colon, "WordType::Colon"},
    {WordType::Semicolon, "WordType::Semicolon"},
    {WordType::LeftParen, "WordType::LeftParen"},
    {WordType::RightParen, "WordType::RightParen"},
    {WordType::LeftBrace, "WordType::LeftBrace"},
    {WordType::RightBrace, "WordType::RightBrace"},
    {WordType::LeftBraket, "WordType::LeftBraket"},
    {WordType::RightBraket, "WordType::RightBraket"}
};


struct Token
{
    WordType type = WordType::Unknown;
    string string;
};

class pch
{
};

