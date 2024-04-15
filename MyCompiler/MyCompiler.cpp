// MyCompiler.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <fstream> 
#include <cstdlib>
#include <cstdio>

#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"


wstring ReadSourceFile(wstring fileName)
{
    FILE* f;
    
    auto isOpen = _wfopen_s(&f, fileName.c_str(), L"rt+,ccs=UNICODE");
    if (isOpen != 0)
    {
        cout << "파일 열기 실패";
        exit(1);
    }


    wchar_t* buf;
    fseek(f,0,SEEK_END);
    int len = ftell(f);
    fseek(f, 2, SEEK_SET);
    buf = new wchar_t[(len +1) / sizeof(wchar_t)];
    memset(buf, 0, len + 1);
    fread_s(buf,len,sizeof(wchar_t), len / sizeof(wchar_t), f);
    //fgetws(buf,len,f);
    wstring str(buf);
    return str;
}

int main()
{
    wcout.imbue(locale("kor"));
    wstring source = ReadSourceFile((L"./Source.txt"));
    Scanner scanner;
    Parser parser;
    //Interpreter interpreter;

    auto tokenList = scanner.Scan(source);
    scanner.PrintTokenList(tokenList);
    cout << "Scan Complete=======================================" << endl;
    auto syntaxTree = parser.Parse(tokenList);
    parser.PrintSyntaxTree(syntaxTree);
    cout <<"Parse Complete=======================================" << endl;
   // interpreter.Interpret(syntaxTree);
    //cout << "Interpret Complete=======================================" << endl;
}

