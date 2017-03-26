#include "HUFF.h"

void Huffman::Tree(){
	list <ListNode> les;
	unsigned short k;
	for(k = 0; k < 256; k++){
		les.push_back (ListNode(k,entering[k]));
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