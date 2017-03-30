#include "HUFF.h"

ListNode::ListNode(){
	
	pstr = 0;
	entering = 0;
	//left = NULL;
	//rigth = NULL;

}

ListNode::ListNode(unsigned char P, uint32_t E){
	
	pstr = P;
	entering = E;
	left = NULL;
	rigth = NULL;

}

ListNode::ListNode(ListNode* lef, ListNode* rig){
	
	pstr= 0;
	entering = (*lef).entering + (*rig).entering;
	left = lef;
	rigth = rig;

}

ListNode::ListNode(const ListNode &ob){
	
	pstr = ob.pstr;
	entering = ob.entering;
	left = ob.left;
	rigth = ob.rigth;

}

int ListNode::operator > (ListNode ob) {
	
	return entering > ob.entering;

}

ListNode& ListNode::operator = (ListNode& ob) {
	
	entering = ob.entering;
	pstr = ob.pstr;
	left  = ob.left ;
	rigth = ob.rigth;

}

int ListNode::reCodFunc(Code bit, vector<Code>& CodeBit, unsigned char (&k)[256]){
	if(entering == 0) {
		return 1;
	}
	if (left == NULL && rigth == NULL) {
		CodeBit.push_back (bit);
		k[pstr] = CodeBit.size() - 1;
		return 1;
	}
	if (left != NULL ) {              
		Code bit0 (bit.code , bit.size + 1);
		(*left).reCodFunc  (bit0, CodeBit, k);
	}
	if (rigth != NULL ) {
		Code bit1 (bit.code| (0x800000000000 >> bit.size), bit.size + 1);
		(*rigth).reCodFunc (bit1, CodeBit, k);
	}
}