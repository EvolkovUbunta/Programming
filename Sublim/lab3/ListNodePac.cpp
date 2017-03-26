#include "HUFF.h"
int Huffman::unpac(ifstream & fin_I, ofstream & fin_O){
	fin_I.unsetf(std::ios::skipws);
	unsigned short i;
 	unsigned char way;
	char mass[4];
	for (i = 0; i < 4;++i) {
		fin_I >> mass[i];
	}
	for(i = 0; i < 256 ; i++){ // in BIG ENDIAN
		for(char j = 3; j!=-1; j--){
			fin_I >> enteringByte[4*i+j];
		}
	}
	Tree();
	ListNode * b = big;
	fin_I >> way;
	while(!fin_I.eof()){
		for(unsigned char i = 0; i < 8; i++){
			if(way & (0x80 >> i)) b = b->rigth;
			else b = b->left;
			if(b->rigth == NULL && b->left == NULL) {
				fin_O << b->pstr;
				--entering[b->pstr];
				if(entering[b->pstr] == -1) return 0;
				b = big;
			}
		}
	fin_I >> way;
	}
}