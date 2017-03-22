#include "func.h"

ListNode::ListNode(){
	pstr = 0;
	entering = 0;
	left = NULL;
	rigth = NULL;
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
ListNode::ListNode(const ListNode &ob){
	pstr = ob.pstr;
	entering = ob.entering;
	left = ob.left;
	rigth = ob.rigth;
}
ListNode::ListNode(unsigned char P, uint32_t E){
	pstr = P;
	entering = E;
	left = rigth = NULL;
}
ListNode::ListNode(ListNode* lef, ListNode* rig){
	pstr= 0;
	entering = (*lef).entering + (*rig).entering;
	left = lef;
	rigth = rig;
}