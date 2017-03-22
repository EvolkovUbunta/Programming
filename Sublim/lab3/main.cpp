#include <iostream>
#include <fstream>
#include "func.h"

using namespace std;

int main(int argc, char *argv[]){
	Huffman stream;
	ifstream finI("file.txt");
	ofstream finO("result.txt");
	if (!finI){
		return 1;
	}
	stream.run(finI,finO);
	finI.close();
	finO.close();
	return 0;
}