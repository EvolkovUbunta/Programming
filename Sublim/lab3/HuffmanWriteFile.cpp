#include "func.h"

void Huffman::writeFile(ifstream & finI, ofstream & finO){
	
	finO << 'H' << 'U' << 'F' << 'F';//Записываем HUFF
	for(unsigned short i = 0; i < 256 ; i++){ // in BIG ENDIAN
		for(char j = 3; j!=-1; j--){
			finO << enteringByte[4*i+j];//Делаем перевертыш 
		}
	}
	//Необходимо записать закодированное сообщение

}