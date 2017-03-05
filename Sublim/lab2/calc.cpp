#include <iostream>
#include <string.h>
#include <cstdlib>
#define LENGTH 100

using namespace std;

const char operations[7] = {'+','-','*','/','^','(',')'};//Operations
const char number[] = {'0','1','2','3','4','5','6','7','8','9'};//Number

class Tokens{
			char   oper [LENGTH];
			double numb [LENGTH];
			int ent;
		public:
			//Добавляем на вершину стека Number
			int tokens_push_number(double numbe){
				numb[ent] = numbe;
				oper[ent] = 0;
				ent++;
			return 0;
			}
			//Добавляем на вершину стека Opertations
			int tokens_push_operations(char operat){
				if (strchr(operations,operat) == NULL) return 1;
				oper[ent] = operat;
				ent++;
				return 0;
			}

};


double calc(const char * str, int * status) {

	Tokens ob;
	double result;
	cout << str << endl << endl;
	double opera[50];
	char *numb = new char [100];
	int k=0;
	const char *d = str;
	for (int i=0; i< strlen(str);){
		if(str[i] >= '0' && str[i] <='9'){
			ob.tokens_push_number(atof(str+i));
			cout << atof(str+i) << endl;
			d = strpbrk(str+i,operations);
			i+=d-(str+i);
	}
		else {
			cout<< str[i] << endl;
			i=i+1;
			tokens_push_operations(str[i-1]);
		  }
	}
}

int main(){
	int * status;
	const char * str = "1.333+2+(444*6+5)-17";
	calc(str,status); 
	return 0;
}