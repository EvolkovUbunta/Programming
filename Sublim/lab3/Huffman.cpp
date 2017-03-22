#include "func.h"

Huffman::Huffman(){
	for (int i = 0 ; i < 256; ++i){
			entering[i] = 0;
	}
	pstr = 0;
}
void Huffman::Entering(ifstream & fin){
	unsigned char pstr;
	fin.unsetf(std::ios::skipws);
	fin >> pstr;
	while (!fin.eof()) {
		entering[pstr]++;
		fin >> pstr;
	}
}
void Huffman::Tree(){
	list <ListNode> les;
	ListNode ob;
	unsigned short k;
	pstr = 0;
	for(k = 0; k < 256; k++){
		if (entering[k] == 0){
			continue;
		}
		pstr++;
		les.push_back (ListNode(k,entering[k]));//Помещаем лес в list
	}
	std::list <ListNode>::iterator A;
	std::list <ListNode>::iterator B;
	ListNode* left,* rigth;
	while (true) {
		A = min (les);
			left = new ListNode(*A);
		les.erase (A);
		B = min (les);
			rigth = new ListNode(*B);
		les.erase (B);
			big = new ListNode (left,rigth);
		les.push_front (*big);
		if (les.size() == 1) {
			break;
		}
	}

	ListNode *root = les.front();
}
std::list <ListNode>::iterator Huffman::min (std::list <ListNode> &list){
	std::list <ListNode>::iterator K = list.begin();
	std::list <ListNode>::iterator C = list.begin();
	
	while(C != list.end()){
		if(*K > *C){
			K=C;
		}
		C++;
	}
	return K;
}
void Huffman::run(ifstream & finI, ofstream & finO){
	Entering(finI);
	Tree();
}