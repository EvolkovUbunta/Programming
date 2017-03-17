/**
	Калькулятор(программа) работает исключительно с операциями 
	'+','-','*','/','^','(',')' 
	(давать программе строчку типа 2 ? 2 запрещено), 
	А так же с  числами
	'0','1','2','3','4','5','6','7','8','9'.
	!!! Tолько с положительными числами. 
		(-1, -2 , -3 - нельзя)
	Возвратит status = 0 , если 2+2(
*/
#include <iostream>
#include <string.h>
#include <math.h>
#include <cstdlib>
#define LENGTH 100

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif
double calc(const char * str, int * status);
#ifdef __cplusplus
}
#endif

const char operations[7] = {'+','-','*','/','^','(',')'};//Operations
const char number[10] = {'0','1','2','3','4','5','6','7','8','9'};//Number

class StackO{
	char symbol[30];
	int ent;
public:
	StackO(){
		for (int i=0;i<30;i++){
			symbol[i] = 0;
		}
		ent = 0;
	}
	int aPtiority(char litle){
		if (litle == '+' || litle == '-') return 1;
		if (symbol[ent-1] == '^') return 1;
		if ((litle == '*' || litle == '/') && (symbol[ent-1] == '*' || symbol[ent-1] == '/')) return 1;
		return 0;	
	}
	char pushSymbol(char symb){
		if (strchr(operations,symb)==NULL) return 1;
		symbol[ent] = symb;
		ent++;
		return 0;
	}
	char PopSymbol(){
		symbol[ent]=0;
		--ent;
		if(ent < 0){
			ent = 0;
		}
		return symbol[ent];
	}
	int size(){
		return ent;
	}
	bool skob(){
		if(symbol[ent-1] == '(') return true;
		else return false;
	}	
};
class Calculation{
	char symbol		[LENGTH];
	double numeric  [LENGTH];
	int ent;
public:
	Calculation(){
		for(int i=0; i < LENGTH; i++){
			symbol[i] = 0;
			numeric[i]= 0;
		}
		ent = 0;
	}
	int tokensPushNumber(double numb){
		numeric[ent] = numb;
		symbol[ent] =0;
		ent++;
		return 0;
	} 
	int tokensPushOperations(char symb){
		symbol[ent] = symb;
		ent++;
		return 0;
	}
	int itIsSymbol(char symb){
		if(strchr(operations,symb) == NULL) {
			return 1;
		}
		return 0;
	}
	int postfixWrite(Calculation &calc,int * status){
		char symb;
		StackO ob;
		int i=-1;
		for(i=0;i < ent; i++){
			if(symbol[i] == 0){
				calc.tokensPushNumber(numeric[i]);
			continue;
			}
			if(ob.size() ==0){
				ob.pushSymbol(symbol[i]);
			continue;
			}
			if(symbol[i] == '('){
				ob.pushSymbol('(');
			continue;
			}
			if (symbol[i] == ')'){
				while(1){
					if (ob.size()==0){
						*status = 1;
						return 0;
					}
					symb = ob.PopSymbol();
					if (symb == '('){
						break;
					}
					calc.tokensPushOperations(symb);
				}
			continue;
			}
			if (ob.skob()){
				ob.pushSymbol(symbol[i]);
			continue;
			} else {
				if (ob.aPtiority (symbol[i])){
					calc.tokensPushOperations(ob.PopSymbol());
					i--;
				}
				else {
					ob.pushSymbol(symbol[i]);
				}
			}
		}
		while (1){
			symb = ob.PopSymbol ();
			if (symb == 0) {
				break;
			}
			calc.tokensPushOperations(symb);

		}
	}
	int calculation(int *status){
		for(int i=2 ; i<ent; i++){
			if (symbol[i]==0) {
				continue;
			} 
			if(symbol[i] =='+'){
				numeric[i] = numeric[i-1]+numeric[i-2];
			}
			if(symbol[i] =='-'){
				numeric[i] = numeric[i-2]-numeric[i-1];
			}
			if(symbol[i] =='*'){
				numeric[i] = numeric[i-1]*numeric[i-2];
			}
			if(symbol[i] =='/'){
				numeric[i] = numeric[i-2]/numeric[i-1];
			} 
			if(symbol[i] =='^'){ 
				numeric[i] = pow(numeric[i-2],numeric[i-1]);
			} 	 
			symbol[i]=0;
			for(;i<ent;i++){
				numeric[i-2]=numeric[i];
				symbol[i-2]=symbol[i];
			}
			ent=ent-2;
			i=1;
		}
		(*status) = 0;
		double result;
		result = numeric[0];
		return result;
	}
	void inficsWrite(const char * str){
		const char *d = str;
		for (int i=0; i< strlen(str);){
			if(str[i] >= '0' && str[i] <='9'){
				tokensPushNumber(atof(str+i));
				d = strpbrk(str+i,operations);
				i+=d-(str+i);
			}
			else {
				tokensPushOperations(str[i]);
				i=i+1;
			}
		}
	}
	void show(){
		for( int i = 0; i < ent ; i++){
			if(symbol[i] == 0){
				cout << numeric[i] << endl << endl;
			} else {
				cout << symbol[i] << endl << endl;			
			  }
		}
	}
};
double calc(const char * str, int * status) {
		Calculation calc;
		Calculation postCal;
		calc.inficsWrite(str);
		calc.postfixWrite(postCal,status);
		postCal.calculation(status); 
}
