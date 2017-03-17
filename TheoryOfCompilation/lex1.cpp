#include <iostream>
using namespace std;
#include "string.h"
#include "stack"
#include <string>
class Memory{
	CString *data;
	int size;
public:
	Memory(){
		size=0;
		data=0;
	}
	~Memory(){
		delete [] data;
	}
	void SetMemory(const int n){
		delete [] data;
		data=new CString[n+size];
		size+=n;
	}
	CString& operator[](const int i){
		if(i<size)
			return data[i];
		throw "Obrashenie k nesushestvujuchemu elementu memory";
	}
};
struct Lexem{
	int type;
	int line;
	CString attribute;

	Lexem(int _t=0, int _l=0, CString str=""){
		type=_t;
		line=_l;
		attribute=str;
	}
};
class Interpretator{
	ostream& out;
	Lexem* data;
	int size;
	int buffer;
	Memory mem;
	Stack<CString> _stack;
	CString strnull,notnull;

public:
	static int Line;
	Interpretator(ostream& o):out(o){
		buffer=100;
		size=0;
		data=new Lexem[100];
	}
	~Interpretator(){
		delete [] data;
	}
	int GetMaxCellsMemory(){
		int n=1;
		for(int i=0;i<size;i++)
			if(data[i].type==16){
				int c=atoi(data[i].attribute.GetStr());
				if(n<c)
				n=c;
			}
		return n+1;
	}
	void AddLexem(int t, int l, CString str=""){
		Lexem a(t,l,str);
		if(size>=buffer){
			Lexem *t=new Lexem[buffer+100];
			buffer+=100;
			for(int i=0;i<size;i++)
				t[i]=data[i];
			delete [] data;
			data=t;
		}
		data[size]=a;
		size++;
	}
	void RunInterpretator(){
		int i=0;
		if(!size) return;
		mem.SetMemory(GetMaxCellsMemory());
		CString first="", second="";
		strnull=" ";
		notnull="aaa";
		do{
			Line=data[i].line;
			switch(data[i].type){
				case 0:
					second=_stack.Pop();
					first=_stack.Pop();
					_stack.Push(first+second);
					i++;
					break;
				case 1:
					second=_stack.Pop();
					first=_stack.Pop();
					first.LeftCut(second);
					_stack.Push(first);
					i++;
					break;
				case 2:
					second=_stack.Pop();
					first=_stack.Pop();
					first.RightCut(second);
					_stack.Push(first);
					i++;
					break;
				case 3:
					first=_stack.Pop();
					first.DelLeftSym();
					_stack.Push(first);
					i++;
					break;
				case 4:
					first=_stack.Pop();
					first.DelLeftSym();
					_stack.Push(first);
					i++;
					break;
				case 5:
					_stack.Push(data[i].attribute);
					i++;
					break;
				case 6:
					second=_stack.Pop();
					first=_stack.Pop();
					if(first==second)
						_stack.Push(notnull);
					else
						_stack.Push(strnull);
					i++;
					break;
				case 7:
					second=_stack.Pop();
					first=_stack.Pop();
					if(first!=second)
						_stack.Push(first);
					else
						_stack.Push(strnull);
					i++;
					break;
				case 8:
					second=_stack.Pop();
					first=_stack.Pop();
					if(first<second)
						_stack.Push(notnull);
					else
						_stack.Push(strnull);
					i++;
					break;
				case 9:
					second=_stack.Pop();
					first=_stack.Pop();
					if(first<=second)
						_stack.Push(first);
					else
						_stack.Push(strnull);
					i++;
					break;
				case 10:
					second=_stack.Pop();
					first=_stack.Pop();
					if(first>second)
						_stack.Push(first);
					else
						_stack.Push(strnull);
					i++;
					break;
				case 11:
					second=_stack.Pop();
					first=_stack.Pop();
					if(first>=second)
						_stack.Push(first);
					else
						_stack.Push(strnull);
					i++;
					break;
				case 12:
					first=_stack.Pop();
					cout<<first;
					out<<first;
					i++;
					break;
				case 13:
					cin>>first;
					_stack.Push(first);
					i++;
					break;
				case 14:
					i=atoi(data[i].attribute.GetStr());
					if(i>size)
						throw "Popjtka obratitsia k nesush metke";
					break;
				case 15:
					first=_stack.Pop();
					if(first==strnull)
						i++;
					else
						i=atoi(data[i].attribute.GetStr());
					if(i>size)
						throw "Popjtka obratitsia k nesush metke";
					break;
				case 16:

					mem[atoi(data[i].attribute.GetStr())] =_stack.Pop();
					i++;
					break;
				case 17:
					_stack.Push(mem[atoi(data[i].attribute.GetStr())]);
					i++;
					break;
				default:
					throw "Unknow command";
			}
		}while(i<size);

	}
};