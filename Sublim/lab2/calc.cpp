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
			opera[20] = 0;
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
		
		int operations_push(Tokens &Topera,char opera){
			if (strchr(operations,opera) == NULL) return 1;
			Topera.oper[Topera.ent] = opera;
			Topera.ent++;
			return 0;
		}

		char operations_pop(Tokens &Topera){
			Topera.oper[Topera.ent]=0;
			--Topera.ent;
			if(Topera.ent < 0) {
				Topera.ent = 0;
			}
			return oper[ent];
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
				//Если операций в стеке нет
				if (ent == 0){
					Topera.operations_push(Topera,oper[i]);
					continue;
				}
				//Если (
				if (oper[i] == '('){
					Topera.operations_push(Topera,'(');
					continue;
				}	
				//Если видим )
				if (oper[i] == ')')
				{
					while(1){
					//oper = Topera.operations_pop(Topera);
						if (oper[i]=='('){
							break;
						}
					Tpost.tokens_push_operations(oper[i]);
					}
					continue;
				}

				if (oper[ent-1] == '('){
					Topera.operations_push(Topera,oper[i]);
					continue;
				}

				else{
					if(prioryty(oper[ent -1], oper[i])){
						Tpost.tokens_push_operations(operations_pop(Topera));
						i--;
					}

					else{
						Topera.operations_push(Topera,oper[i]);
					}
				}
			}

			while(1){
				//oper=Topera.operations_pop(Topera);
				if(oper==0) {
					break;
				}
				tokens_push_operations(oper[i]);
			}

			for(int i=0; i < Tpost.ent;i++){
				if(Tpost.oper == 0){
					cout<< Tpost.numb[i] << endl;
				}
				else{ 
					cout << Tpost.oper[i] << endl;
				}
			}
		}
};


double calc(const char * str, int * status) {
		
		Tokens ob,Tpost;
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
		ob.postfix_write(Tpost);
}

int main(){
	int * status;
	const char * str = "1.333+2+(444*6+5)-17";
	cout << str << endl << endl;
	calc(str,status); 
	return 0;
}
