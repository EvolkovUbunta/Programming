#include "HUFF.h"

void Huffman::run(ifstream & finI, ofstream & finO){
	Entering(finI);
	Tree();
	big->recursiveCodingFunction(Code(0,0),CodeBit,k);
	finI.clear();
	finI.seekg (0, std::ios::beg);
	writeFile(finI,finO);
}