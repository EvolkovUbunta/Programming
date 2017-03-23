#include "func.h"

std::list <ListNode>::iterator Huffman::min (std::list <ListNode> &list){
	
	std::list <ListNode>::iterator K = list.begin();
	std::list <ListNode>::iterator C = list.begin();
	while(C != list.end()){
		if(*K > *C){K=C;}
		C++;
	}
	return K;

}