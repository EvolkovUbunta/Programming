#include <iostream>
#include <fstream>
#include "func.h"

using namespace std;

int main(int argc, char * argv[]){
	Huffman huff;
	ifstream fin("file.txt");
	if (!fin){
		return 1;
	}
	huff.makeFile(fin);
	return 0;
}