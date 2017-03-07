#include <iostream>
#include <string.h>
#include <cstdlib>
#define LENGTH 100

using namespace std;

const char operations[7] = {'+','-','*','/','^','(',')'};//Operations
const char number[10] = {'0','1','2','3','4','5','6','7','8','9'};//Number

class Tokens{
		char   oper [LENGTH];
		double numb [LENGTH];
		int ent;

	public:

		Tokens(){
			oper[LENGTH] = 0;
			numb[LENGTH] = 0;
			ent = 0;
		}
		//Добавляем на вершину стека Numbe.
		int tokens_push_number(double numbe){
			numb[ent] = numbe;
			oper[ent] = 0;
			ent++;
			return 0;
		}
		//Добавляем на вершину стека Opertations.
		int tokens_push_operations(char operat){
			if (strchr(operations,operat) == NULL) {
				return 1;
			}
			oper[ent] = operat;
			ent++;
			return 0;
		}
		//Операция.
		int tokens_operations(char oper){
			if(strchr(operations,oper) == NULL) {
				return 1;
			}
			return 0;
		}
		//Является операцией
		int is_operation(char oper){
    		if (strchr(operations,oper) == NULL) {
    			return 1;
    		}
    		return 0;
		}

		//Приоритер.
		int prioryty(char more, char litle){
			if (litle == '+' || litle == '-') return 1;
			if (more == '^') return 1;
			if ((litle == '*' || litle == '/') && (more == '*' || more == '/')) return 1;
			return 0;
		}
		
		int postfix_write (Tokens &Tpost){
			Tokens Topera;
			int i;
			for(i=0;i < ent;i++){
				if (oper[i]==0){
					Tpost.tokens_push_number(numb[i]);
					continue;
				}

				if (1){
					Topera.tokens_push_operations(oper[i]);
					continue;
				}
			}
		}
};


double calc(const char * str, int * status) {
		
		Tokens ob;
		double opera[50];
		char *numb = new char [100];
		int k=0;
		const char *d = str;
		for (int i=0; i< strlen(str);){
			if(str[i] >= '0' && str[i] <='9'){
				ob.tokens_push_number(atof(str+i));
				d = strpbrk(str+i,operations);
				i+=d-(str+i);
			}
			else {
				ob.tokens_push_operations(str[i]);
				i=i+1;
			  }
		}

}

int main(){
	int * status;
	const char * str = "1.333+2+(444*6+5)-17";
	cout << str << endl << endl;
	calc(str,status); 
	return 0;
}
