#include <iostream>
#include <string.h>
#include <cstdlib>
#define LENGTH 100

using namespace std;

class Tokens{
		public:
			char   oper [LENGTH];
			double numb [LENGTH];
			int ent;

	};

int tokens_push_number(class Tokens * tok,double number){
        tok->numb[tok->ent] = number;
        tok->oper[tok->ent] = 0;
        tok->ent++;
        return 0;
}

int tokens_push_number_str(class Tokens * tok,const char* number){
    if(strlen(number)!=0){
        tok->numb[tok->ent] = atof(number);
        tok->oper[tok->ent] = 0;
        tok->ent++;
        return 0;
    }
    return 1;
}

double calc(const char * str, int * status) {

	Tokens ob;
	double result;
	cout << str << endl << endl;
	char operations[] = {'+','-','*','/','^','(',')'};//Operations
	char number[] = {'0','1','2','3','4','5','6','7','8','9'};//Number
	double opera[50];
	char *numb = new char [100];

	const char *d = str;
	ob.ent=0;
	for (int i=0; i< strlen(str);){
		if(str[i] >= '0' && str[i] <='9'){
			cout << atof(str+i) << endl;
			d = strpbrk(str+i,operations);
			i+=d-(str+i);
	}
		else {
			cout<< str[i] << endl;
			i=i+1;
		  }
	ob.ent++;
	}
}

int main(){
	int * status;
	const char * str = "1.333+2+(444*6+5)-17";
	calc(str,status); 
	return 0;
}