#include "HUFF.h"

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