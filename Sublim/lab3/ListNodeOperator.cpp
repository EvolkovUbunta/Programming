#include "func.h"

int ListNode::operator > (ListNode ob) {
	
	return entering > ob.entering;

}
ListNode& ListNode::operator = (ListNode& ob) {
	
	entering = ob.entering;
	pstr = ob.pstr;
	left  = ob.left ;
	rigth = ob.rigth;

}