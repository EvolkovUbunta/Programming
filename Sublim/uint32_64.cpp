#include <iostream>
using namespace std;

int main(){
	unsigned short i = 0;
	i = i | 0x0000000000000000800000000;
	cout << i << endl;  
}