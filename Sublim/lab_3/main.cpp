#include "HUFF.h"

using namespace std;

int main(int argc, char *argv[]){
	if (argc < 4) {
		cout << " Too few arguments!!!" << endl;
		return 1;
	}
	Huffman stream;
	ifstream finI(argv[1]);
	finI.unsetf (std::ios::skipws);
	ofstream finO(argv[2]);
	if (!finI){
		return 1;
	}
	if (argv[3][0] != '-') {
		cout << "Invalid input" << endl;
		return 1;
	}
	if (argv[3][1] == 'p') {
		cout << "WORK: func/run   | " << argv[1] << " -> " << argv[2]<< endl;
		stream.run(finI,finO);	
	}

	if (argv[3][1] == 'u') {
		cout << "WORK: func/UnPac | "<< argv[1] << " -> " << argv[2] << endl;
		stream.unPac(finI,finO);
	}
	finI.close();
	finO.close();
	return 0;
}