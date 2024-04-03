// MyCompiler.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <fstream> 
#include <cstdlib>

#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"


wstring ReadSourceFile(wstring fileName)
{
 
    locale::global(locale(".UTF-8"));

    wifstream fIn;
    fIn.open(fileName);
    if (!fIn.is_open()) {
        wcout << L"파일열기 실패" << endl;
        exit(1);
    }

    fIn.seekg(0, std::ios::end);
    streampos len = fIn.tellg();
    wchar_t* buf = new wchar_t[len];
    fIn.seekg(0, ios::beg);

    fIn.read(buf, len);

    wstring source(buf);   

    fIn.close();
    wcout << L"파일에서 와이드 문자열 읽기 완료" << endl;
    return source;
}

int main()
{
    wstring source = ReadSourceFile(L"./Source.txt");
    Scanner scanner;
    //Parser parser;
    //Interpreter interpreter;

    auto tokenList = scanner.Scan(source);
    scanner.PrintTokenList(tokenList);
    cout << "Scan Complete=======================================" << endl;
  /*  auto syntaxTree = parser.Parse(tokenList);
    parser.PrintSyntaxTree(syntaxTree);
    cout <<"Parse Complete=======================================" << endl;
    interpreter.Interpret(syntaxTree);
    cout << "Interpret Complete=======================================" << endl;*/
}

