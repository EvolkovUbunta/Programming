#include <iostream>
#include <string.h>
#include <cstdlib>
#define LENGTH 100

using namespace std;

const char operations[7] = {'+','-','*','/','^','(',')'};//Operations
const char number[] = {'0','1','2','3','4','5','6','7','8','9'};//Number

class Tokens{
		public:
			char   oper [LENGTH];
			double numb [LENGTH];
			int ent;

	};

int tokens_push_number(class Tokens * tok,double numbe){
        tok->numb[tok->ent] = numbe;
        tok->oper[tok->ent] = 0;
        tok->ent++;
        return 0;
}

int tokens_push_number_str(class Tokens * tok,const char* numbe){
    if(strlen(number)!=0){
        tok->numb[tok->ent] = atof(numbe);
        tok->oper[tok->ent] = 0;
        tok->ent++;
        return 0;
    }
    return 1;
}

int tokens_push_operations(class Tokens * tok, char operat){
    if (strchr(operations,operat) == NULL) return 1;
    tok->oper[tok->ent] = operat;
    tok->ent++;
    return 0;
}

double calc(const char * str, int * status) {

	Tokens ob;
	double result;
	cout << str << endl << endl;
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