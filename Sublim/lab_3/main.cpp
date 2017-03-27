#include "HUFF.h"

using namespace std;

int main(int argc, char *argv[]){
	Huffman stream;
	ifstream finI("file.txt");
	finI.unsetf (std::ios::skipws);
	ofstream finO("result.txt");
	if (!finI){
		return 1;
	}
	cout << "WORK: func/run      >>>>>>>><<<<<<<" << endl;
	stream.run(finI,finO);	
	finI.close();
	finO.close();
	ifstream fin_I("result.txt");
	fin_I.unsetf (std::ios::skipws);
	ofstream fin_O("final_file.txt");
	cout << "WORK: func/UnPac    >>>>>>>><<<<<<<" << endl;
	stream.unPac(fin_I,fin_O);
	fin_I.close();
	fin_O.close();
	cout << "WORK: FINISH/FILE   >>>>>>>><<<<<<<" << endl;
	cout << "                    *file.txt" << endl;
	cout << "                    *result.txt" << endl;
	cout << "                    *final_file.txt" << endl; 
	return 0;
}