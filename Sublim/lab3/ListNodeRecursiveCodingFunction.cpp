#include "HUFF.h"

int ListNode::recursiveCodingFunction(Code bit, std::vector<Code>& CodeBit, unsigned char (&k)[256]){
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
		(*left).recursiveCodingFunction  (bit0, CodeBit, k);
	}
	if (rigth != NULL ) {
		Code bit1 (bit.code| (0x80 >> bit.size), bit.size + 1);
		(*rigth).recursiveCodingFunction (bit1, CodeBit, k);
	}
}