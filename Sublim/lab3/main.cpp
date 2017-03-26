#include "HUFF.h"

using namespace std;

int main(int argc, char *argv[]){
	Huffman stream;
	ifstream finI("file1.txt");
	ofstream finO("result.txt");
	if (!finI){
		return 1;
	}
	stream.run(finI,finO);	
	finI.close();
	finO.close();
	ifstream fin_I("result.txt");
	ofstream fin_O("final1.txt");
	stream.unpac(fin_I,fin_O);
	fin_I.close();
	fin_O.close();
	return 0;
}