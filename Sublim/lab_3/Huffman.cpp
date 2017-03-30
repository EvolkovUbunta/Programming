#include "HUFF.h"

Huffman::Huffman(){
	
	for (int i = 0 ; i < 256; ++i){
			entering[i] = 0;
	}
	pstr = 0;

}

void Huffman::enteriing(ifstream & finI){
	
	unsigned char pstr;
	finI >> pstr;
	while (!finI.eof()) {
		entering[pstr]++;
		finI >> pstr;
	}
}

void Huffman::tree(){
	
	unsigned short k = 0;
	list <ListNode> les;
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
void Huffman::pac(ifstream & finI, ofstream & finO){
	
	unsigned char s=0;
	unsigned char buf=0;
	unsigned char str1=0;
	unsigned char str2=0;
	
	finO << 'H' << 'U' << 'F' << 'F';
	for(unsigned short i = 0; i < 256 ; i++){ // in BIG ENDIAN
		for(char j = 3; j!=-1; j--){
			finO << enteringByte[4*i+j]; 
		}
	}

	finI >> s;
	while(!finI.eof()){
		for (str2 = 0; str2 < CodeBit[k[s]].size; ++str2)
		{
			if (str1 == 8) {
				finO << buf; 
				str1 = 0;
				buf = 0;
			}
			buf = buf | ((CodeBit[k[s]].code & (0x800000000000 >> str2)) ? 0x80 >> str1 : 0);
			++str1;
		}
		finI >> s;
	}
	if (str1 > 0){
		finO << buf;
	}
}

list <ListNode>::iterator Huffman::min (list <ListNode> &list){
	
	std::list <ListNode>::iterator K = list.begin();
	std::list <ListNode>::iterator C = list.begin();
	
	while(C != list.end()){
		if(*K > *C){K=C;}
		C++;
	}
	return K;

}


int Huffman::unPac(ifstream & fin_I, ofstream & fin_O){
	unsigned short i = 0;
 	unsigned char way = 0;
	char mass[4];
	for (i = 0; i < 4;++i) {
		fin_I >> mass[i];
	}
	
	for(i = 0; i < 256 ; i++){ 
		for(char j = 3; j!=-1; j--){
			fin_I >> enteringByte[4*i+j];
		}
	}

	tree();
	ListNode * b = big;
	fin_I >> way;
	while(!fin_I.eof()){
		for(unsigned char i = 0; i < 8; i++){
			if(way & (0x80 >> i)) b = b->rigth;
			else{
				 b = b->left;
			}
			if(b->rigth == NULL && b->left == NULL) {
				--entering[b->pstr];
				if(entering[b->pstr] == -1){
					return 0;
				}
				fin_O << b->pstr;
				b = big;
			}
		}
	fin_I >> way;
	}
}

void Huffman::run(ifstream & finI, ofstream & finO){
	enteriing(finI);
	tree();
	big->reCodFunc(Code(0,0),CodeBit,k);
	finI.clear();
	finI.seekg (0, std::ios::beg);
	pac(finI,finO);
}
