#include "func.h"

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

}