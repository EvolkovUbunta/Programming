#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <iomanip>
#include <math.h>
#include <list>
#include <vector>
#include <map>

using namespace std;

class Code{
public:
	uint32_t code;
	unsigned char size;
	Code(uint32_t cod, unsigned char siz){
		code = cod;
		size = siz;
	}
};

class ListNode{
	unsigned char pstr;
	uint32_t entering;
	ListNode *left,*rigth;
public:
	ListNode(unsigned char P, uint32_t E);
	ListNode(ListNode* lef, ListNode* rig);
	ListNode(const ListNode &ob);
	ListNode();
	int operator > (ListNode ob);
	ListNode& operator = (ListNode& ob);
	int recursiveCodingFunction(Code bit, std::vector<Code> &CodeBit,unsigned char (&k)[256]);
};

class Huffman{
	std::vector<Code> CodeBit;
	unsigned char k[256];
	union{
		uint32_t entering[256];
		unsigned char enteringByte[1024];
	};
	unsigned short pstr;
	ListNode *big;
public:
	Huffman();
	std::list <ListNode>::iterator min (std::list <ListNode> &list);
	void run(ifstream & finI, ofstream & finO);
	void Entering(ifstream & fin);
	void Tree();
	void writeFile(ifstream & finI, ofstream & finO);
};

