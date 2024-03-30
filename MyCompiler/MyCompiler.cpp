// MyCompiler.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"



int main()
{
    //string source = R"(
    //function foo(value)
    //{
    //    print(value);
    //}
    //function main() 
    //{
    //    var a = 1;
    //    for(var i = 0, a = 1; i < a; i++, a++)
    //    {
    //        if(a > 10)
    //        {
    //            foo(a);
    //        }
    //    } 
    //}
    //)";
    string source = R"(
    function foo(value)
    {
        print(value);
    }
    function main() 
    {
        var a = 1;
        a = 2;
        printLine (a);
    }
    )";
    Scanner scanner;
    Parser parser;
    Interpreter interpreter;

    auto tokenList = scanner.Scan(source);
    scanner.PrintTokenList(tokenList);
    cout << "Scan Complete=======================================" << endl;
    auto syntaxTree = parser.Parse(tokenList);
    parser.PrintSyntaxTree(syntaxTree);
    cout <<"Parse Complete=======================================" << endl;
    interpreter.Interpret(syntaxTree);
    cout << "Interpret Complete=======================================" << endl;
}

