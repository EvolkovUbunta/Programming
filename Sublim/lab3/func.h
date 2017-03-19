#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <list>

using namespace std;

class Huffman{
	uint32_t mass[256];
public:
	Huffman();
	int makeFile(ifstream &fin);
};

class List{
	unsigned char pstr;
public:
	List(unsigned char i, uint32_t mass);
	List();
};