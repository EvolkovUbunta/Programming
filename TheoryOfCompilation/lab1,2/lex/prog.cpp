#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
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

int file(char * namefile){
	char str;
	int line=0;
	int column =0;
	int poz=0;
	ifstream fin(namefile);
	if(!fin){
		cout << "A file with that name does not exist." << endl;
		return 1;
	}
	while(!fin.eof()){
		if((str=fin.get())=='\n'){
			++line;
			column = 0;
		} else ++column;
		++poz;
		if(isLetter(str)){
		
			return 1;
		}
		if(fin.eof()){
			break;
		}
	cout << str;
	} 
	cout << endl;
}
int main(int argc, char *argv[1]){
	if(argc!=2){
			cout << "At the command prompt, you must enter the file name." << endl;
		return 1;
	}
	file(argv[1]);
	return 0;
}