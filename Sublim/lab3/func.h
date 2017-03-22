#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <iomanip>
#include <math.h>
#include <list>

using namespace std;

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
};

class Huffman{
	uint32_t entering[256];
	unsigned short pstr;
	ListNode *big;
public:
	Huffman();
	std::list <ListNode>::iterator min (std::list <ListNode> &list);
	void run(ifstream & finI, ofstream & finO);
	void Entering(ifstream & fin);
	void Tree();
};
