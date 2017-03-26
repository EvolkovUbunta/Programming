#include "HUFF.h"

Huffman::Huffman(){
	
	for (int i = 0 ; i < 256; ++i){
			entering[i] = 0;
	}
	pstr = 0;

}

void Huffman::run(ifstream & finI, ofstream & finO){
	Entering(finI);
	Tree();
	big->recursiveCodingFunction(Code(0,0),CodeBit,k);
	finI.clear();
	finI.seekg (0, std::ios::beg);
	writeFile(finI,finO);
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

void Huffman::writeFile(ifstream & finI, ofstream & finO){
	finO << 'H' << 'U' << 'F' << 'F';
	for(unsigned short i = 0; i < 256 ; i++){ // in BIG ENDIAN
		for(char j = 3; j!=-1; j--){
			finO << enteringByte[4*i+j]; 
		}
	}
	unsigned char s=0;
	unsigned char buf=0;
	unsigned char str1=0;
	unsigned char str2=0;
	finI.unsetf (std::ios::skipws);
	finI >> s;
	while(!finI.eof()){
		for (str2 = 0; str2 < CodeBit[k[s]].size; ++str2)
		{
			if (str1 == 8) {
				finO << buf; 
				str1 = 0;
				buf = 0;
			}
			buf = buf | ((CodeBit[k[s]].code & 0x80 >> str2) << str2) >> str1;
			++str1;
		}
		finI >> s;
	}
	if (buf != 0){
		finO << buf;
	}
}

std::list <ListNode>::iterator Huffman::min (std::list <ListNode> &list){
	
	std::list <ListNode>::iterator K = list.begin();
	std::list <ListNode>::iterator C = list.begin();
	while(C != list.end()){
		if(*K > *C){K=C;}
		C++;
	}
	return K;

}

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

int Huffman::unpac(ifstream & fin_I, ofstream & fin_O){
	fin_I.unsetf(std::ios::skipws);
	unsigned short i;
 	unsigned char way;
	char mass[4];
	for (i = 0; i < 4;++i) {
		fin_I >> mass[i];
	}
	for(i = 0; i < 256 ; i++){ // in BIG ENDIAN
		for(char j = 3; j!=-1; j--){
			fin_I >> enteringByte[4*i+j];
		}
	}
	Tree();
	ListNode * b = big;
	fin_I >> way;
	while(!fin_I.eof()){
		for(unsigned char i = 0; i < 8; i++){
			if(way & (0x80 >> i)) b = b->rigth;
			else b = b->left;
			if(b->rigth == NULL && b->left == NULL) {
				fin_O << b->pstr;
				--entering[b->pstr];
				if(entering[b->pstr] == -1) return 0;
				b = big;
			}
		}
	fin_I >> way;
	}
}

