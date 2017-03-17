//---------------------------------------------------------------------------
#include <fstream>
#include <conio.h>

#pragma hdrstop

#include "Lexer.h"
#include "Utils.h"
using namespace ESL;
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{


    CLexer Lexer;

    string data[]={"bool","int","string","end","if","else","while","for","break",
                   "+", "-", "=", "/", "*", ">", "<", "~", "!", "|", "&",
                   "Randomize","Write","Random","Char","StrToInt","ReadString",
                   " ", ";", "(", ")", ",", "{", "}", "\n", "\t", "\r", "%"};

    Lexer.Init(data,9,11,6,11);

    FILE *f = fopen("test.txt","rt");

    fseek(f, 0, SEEK_END); long len = ftell(f); fseek(f, 0, SEEK_SET);

    string str;
    str.resize(len);
    fread(&str[0],1,len,f);

    Lexer.Lex(str);

    Lexer.SaveTokens(ESLLog.LogFile());

    fclose(f);

    getch();

    return 0;
}
//---------------------------------------------------------------------------

