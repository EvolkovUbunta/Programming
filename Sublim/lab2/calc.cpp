#include <iostream>
#include <string.h>
#include <cstdlib>
using namespace std;

double calc(const char * str, int * status) {

	double result;
	cout << str << endl << endl;
	char operations[] = {'+','-','*','/','^','(',')'};//Operations
	char number[] = {'0','1','2','3','4','5','6','7','8','9'};//Number
	int opera[50];
	int k=0;
	char *numb = new char [100];

	const char *d = str;
	k=0;
	for (int i=0; i< strlen(str);){
		if(str[i] >= '0' && str[i] <='9'){
			cout << atoi(str+i) << endl;
			d = strpbrk(str+i,operations);
			i+=d-(str+i);
	}
		else {
			cout<< str[i] << endl;
			i=i+1;
		  }
	k++;
	}
}

int main(){
	int * status;
	const char * str = "1+2+(444*6+5)-17";
	calc(str,status); 
	return 0;
}