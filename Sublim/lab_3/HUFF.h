#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <iomanip>
#include <list>
#include <vector>
#include <map>

using namespace std;

class Huffman;

class Code{
public:
	uint64_t code; 
	unsigned char size;
	Code(uint64_t cod, unsigned char siz){
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
	ListNode& operator = (ListNode& ob);
	int operator > (ListNode ob);
	int reCodFunc(Code bit, vector<Code> &CodeBit,unsigned char (&k)[256]);
	friend Huffman;
};

class Huffman{
	vector<Code> CodeBit;
	unsigned char k[256];
	union{
		uint32_t entering[256];
		unsigned char enteringByte[1024];
	};
	unsigned short pstr;
	ListNode *big;
public:
	Huffman();
	void enteriing(ifstream & fin);
	void tree();
	void pac(ifstream & finI, ofstream & finO);
	int unPac(ifstream & fin_I, ofstream & fin_O);
	list <ListNode>::iterator min (std::list <ListNode> &list);
	void run(ifstream & finI, ofstream & finO);
};

