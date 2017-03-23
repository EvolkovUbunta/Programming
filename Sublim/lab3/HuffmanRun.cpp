#include "func.h"

void Huffman::run(ifstream & finI, ofstream & finO){
	
	Entering(finI);
	Tree();
	big->recursiveCodingFunction(Code(0,0),CodeBit,k);
	finI.clear();

	writeFile(finI,finO);

}