/*
	 работает с популярным строчным 
	символом 'o', считая его наиболее встречаемым в файле.
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "table.h"
#define CP1251 1
#define CP866 2
#define KOI8R 3

using namespace std;
/**
	Класс Stirlitz. 
	---
	Class Stirlitz.
*/
class Stirlitz{
	int mass[128];
	int encoding;
	unsigned char popular;
	int one,two,three;
public:
	/**
	Конструктор по уиолчанию.
	---
	Constructor for uiolchaniyu.
	*/
	Stirlitz() {
		for(int i=0; i<128;++i){
			mass[i]=0;
		}
		encoding = 0;
		popular = 0;
		one=two=three=-1;
	}
	/**
	Функция, осуществляющая посимвольное чтение из файла.
	Встречаемость символов. Популярный символ.
	---
	The function carries out character by character read from the file.
	Occurrence characters. The popular character.
	*/
	int open_file(char* name_file){
		char str;
		unsigned char kstr;
		bool system = false;
		ifstream fin_i(name_file);
		if(!fin_i){
			cout << "A file with that name does not exist." << endl;
			return 1;
		}
		while(true){
			fin_i.get(str);
			if(fin_i.eof()){
				break;
			}
			kstr = (unsigned char)str;
			if (kstr >=128){
				mass[kstr-128]++;
			}
		}
		for (int i=0;i < 128; ++i){
			if(mass[i]!=0){
				system = true;
			} 
		}
		if(system == false) { 
			return 1;
		}
		else{
			for(int i=0;i<128;++i){
				if(mass[i]>mass[popular]){
					popular = i;
				}
				
			}
		}
		cout <<(unsigned int) popular << endl;
		fin_i.close();
	}
	/**
	Функция, определяющая кодировку.
	---
	Function that determines the character encoding encoding.
	*/
	int charset_definition(unsigned char ent){
		if( ent == 0xee ){
			return encoding=CP1251;
		}
	    if( ent == 0xae ){
            return encoding=CP866;
        }
        if( ent == 0xcf ){
            return encoding=KOI8R;
        }
        return 0;	
	}
	/**
	Функция, определяющая кодировку шести производных символов
	в соответствии с шестью заданными таблицами перекодировок.
	---
	The function that determines the encoding of the six derivatives characters
	in accordance with the six specified a lookup tables.
	*/
	void recoding(unsigned char ent, unsigned char (&array)[6]){
		int i=-1;
		array[++i]=Cp1251ToCp866[ent & 0x7f];
		array[++i]=Cp1251ToKoi8R[ent & 0x7f];
		array[++i]=Cp866ToCp1251[ent & 0x7f];
		array[++i]=Cp866ToKoi8R [ent & 0x7f];
		array[++i]=Koi8RToCp1251[ent & 0x7f];
		array[++i]=Koi8RToCp866 [ent & 0x7f];
	}
	/**
	Функция, определяющая, как был преобразован файл, если его 
	кто-то намеренно попортил. На выходе будем иметь либо то,
	что файл корректен, либо то, какой таблице соответствует 
	преобразоание(я).
	---
	The function that determines how the file has been converted, 
	if someone deliberately spoiled. The output will be either that
	that the file is valid, or that which corresponds to the table
	preobrazoanie(I).
	*/
	int possible_transformations(){
		cout << endl << ">>>Work_possible_transformations<<<" << endl;
		unsigned char r=popular;
		unsigned char array[6];
		unsigned char array1[6][6];
		cout << charset_definition(r|0x80) << endl;
		if(charset_definition(r|0x80)!=0) {
			cout << "\t\t\t\t\tFile correct." << endl;
			file_encoding(); 
			return 0;
		}
		recoding(r,array);
		for(int i=0; i<6;i++){
			if(charset_definition(array[i])) 
			{
				one = i; 
				return 0;
			}
		}
		for(int i=0; i<6;i++)
		recoding(array[i],array1[i]);
		for(int i=0; i<6;i++){
			for(int j=0; j<6;j++){
				if (charset_definition(array1[i][j])) 
				{
					one = i;
					two = j; 
					return 0;
				}
			}
		}
		for(int i=0;i<6;i++){
			for(int j=0;j<6;j++){
				recoding(array1[i][j],array);
				for(int l=0;l<6;l++){
					if(charset_definition(array[l])){
						one = i;
						two = j;
						three =l;
						return 0;
					}
				}
			}
		}
		return 0;
	}
	/**
	Функция, определяющая, как был перекодирован текст.
	В соответствии с какой таблицей. 
	---
	The function that determines how the text was perekozhirovan.
	In accordance with a table.
	*/
	unsigned char conversion_definition(int ent,unsigned char kstr){
		int i=0;
		if (ent==0) return Cp1251ToCp866[kstr&0x7f];
		if (ent==1) return Cp1251ToKoi8R[kstr&0x7f];
		if (ent==2) return Cp866ToCp1251[kstr&0x7f];
		if (ent==3) return Cp866ToKoi8R [kstr&0x7f];
		if (ent==4) return Koi8RToCp1251[kstr&0x7f];
		if (ent==5) return Koi8RToCp866 [kstr&0x7f];	
	}
	/**
	Функция, осуществляющая перезапись файла в первоначальную(верную)
	кодировку.
	---
	Function undertaking overwrite the file in the original(true)
	encoding
	*/
	int file_overwrite(char* name_file){
		cout << endl << "    >>>Work_file_overwrite<<<" << endl;
		char str;
		unsigned char kstr;
		unsigned char p[128];
		for(int i=0; i<128; i++){
			p[i]=i | 0x80;
			if(one!=-1) p[i]=conversion_definition(one,p[i]);
			if (two!=-1) p[i]=conversion_definition(two,p[i]);
			if (three!=-1) p[i]=conversion_definition(three,p[i]);
		}
		ifstream fin_i(name_file);
		ofstream fin_o("resault.txt");
		while(true){
			fin_i.get(str);
			if(fin_i.eof()){
				break;
			}
			if(str & 0x80) fin_o << (char) (p[str & 0x7f]);
				else fin_o << str;
		}
		cout << endl<<"\t\t\t\t\tMAX:"<< (unsigned int)popular << endl;
		fin_i.close();
		fin_o.close();
		file_encoding();
	}
	/**
	Функция, определяющая кодировку.
	Она необходима, чтобы визуализировать работу алгоритма(не более того).
	---
	The function that determines the encoding.
	It is necessary to visualize the algorithm.
	*/
	int file_encoding(){
		if (encoding == 1){ 
			cout << "\t\t\t\t\tFILE:cp1251" <<endl; 
		return 0;
		}
		if(encoding == 2) {
			cout << "\t\t\t\t\tFILE:cp866" <<endl;
		return 0;
		}
		if(encoding == 3) {
			cout << "\t\t\t\t\tFILE:Koi8-r" << endl;
		return 0;
		}
	}
	/**
	Функция, осуществляющая перекодировку файла, если она необходима,
	или же нет. В обоих случаях определяется в какой кодировке данный файл есть,
	или в какой файл будет преобразован, ведь он был испорчер и показывает нам
	кракозябры.
	--- 
	The function carries out re-encoding the file, if required,
	or not. In both cases determined what encoding the file is,
	or a file is converted, because he was isporcher and shows us
	gibberish.
	*/
	int transcoder(char* name_file){
		cout << "\t   ____________"  << "\t\t\t" << " __________"  << endl;
		cout << "\t  |WORK DEKODER|" << "\t\t" << "|CONCLUSION|" << endl;
		cout << "\t  ''''''''''''''" << "\t\t" << "''''''''''''" << endl;
		if(open_file(name_file)==0) {
			return 0;
		}
		if(popular!=0){
			possible_transformations();
			cout << ">>>Table1= " << one << "; "<< "Table2= " << two <<"; "<< "Table3= " << three << endl;
			if(one == -1 && two == -1 && three == -1){
				cout << "\t\t\t\t\tThe file is invalid and can not be overwritten,"<< endl;
				cout << "\t\t\t\t\tbecause file CORRECT." << endl << endl;
			}
			else {
				file_overwrite(name_file); 
				cout << "\t\t\t\t\tThe file was overwriten" << endl << endl;
			}
		}
	}
};
/**
	Функция main()
	---
	Function main()
*/
int main(int argc, char *argv[1]){
	Stirlitz dkod;
	if(argc!=2){
			cout << "At the command prompt, you must enter the file name." << endl;
		return 1;
	}
	dkod.transcoder(argv[1]);
	return 0;
}