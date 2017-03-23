#include "func.h"

void Huffman::Entering(ifstream & fin){
	
	unsigned char pstr;
	fin.unsetf(std::ios::skipws);
	fin >> pstr;
	while (!fin.eof()) {
		entering[pstr]++;
		fin >> pstr;
	}

}