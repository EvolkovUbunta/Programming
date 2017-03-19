#include "func.h"

Huffman::Huffman(){
	for(int i = 0; i < 256; i++){
		mass[i] = 0;
	}
}

List::List(){
	pstr = 0;
}

List::List(unsigned char i, uint32_t mass){
	i = i;
	mass = mass;
}

int Huffman::makeFile(ifstream &fin){
	unsigned char pstr;
	//необходимо, чтобы видеть пробелы при считывании
	fin.unsetf(ios::skipws);
	//производим посимвольное считывание из файла 
	while(true){
		fin >> pstr;
		if(fin.eof()){
			break;
		}
		mass[pstr]++;
	}
	//помещем массив в list
	list <List> human;
	for(int i = 0; i < 256 ; i++){
		human.push_back(List(i,mass[i]));
	}
	//Посмотрим, что list
	list <List>::iterator ch = human.begin();
	while(ch != human.end()){
		cout << *ch;
		ch++;
	}
	return 0;
}
