#include <iostream>
#include <fstream>

using namespace std;


class La{
  char si;
  int poz,line,column;
public:
  La(){
    si=0;
    poz=line=column=0;
  }
// Функции транслитератора, используемые для определения класса лексем
//
// Определяет принадлежность символа к классу букв
bool inline isLetter(int ch) {
  if((ch>='A' && ch<='Z') || (ch>='a' && ch<='z'))
    return true;
  else
    return false;
}
//
// Определяет принадлежность символа к классу двоичных цифр
bool inline isBin(int ch) {
  if((ch=='0' || ch=='1'))
    return true;
  else
    return false;
}
//
// Определяет принадлежность символа к классу восьмеричных цифр
bool inline isOctal(int ch) {
  if((ch >= '0' && ch <= '7'))
    return true;
  else
    return false;
}
//
// Определяет принадлежность символа к классу десятичных цифр
bool inline isDigit(int ch) {
  if((ch >= '0' && ch <= '9'))
    return true;
  else
    return false;
}
//
// Определяет принадлежность символа к классу шестнадцатеричных цифр
bool inline isHex(int ch) {
  if((ch >= '0' && ch <= '9') ||
     (ch >= 'A' && ch <= 'F') || 
     (ch >= 'a' && ch <= 'f'))
    return true;
  else
    return false;
}
//
// Определяет принадлежность символа к классу пропусков
bool inline isSkip(int ch) {
  if(ch == ' ' || ch == '\t' || ch == '\n' || ch == '\f')
    return true;
  else
    return false;
}
//
// Определяет принадлежность к классу игнорируемых символов
bool inline isIgnore(int ch) {
  if(ch>0 && ch<' ' && ch!='\t' && ch!='\n' && ch!='\f')
    return true;
  else
    return false;
}

//
// Читает следующий символ из входного потока
/*atic void nxsi() {
  if((si = getc(infil)) == '\n') {
    ++line; column = 0;
  }
  else ++column;
    ++poz; // Переход к следующей позиции в файле
}
*/
};

int main(int argc, char *argv[1]){
  return 0;
}
