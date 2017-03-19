#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream cin_code ("input.txt");
ifstream cin_key ("key.txt");     
ofstream cout_lexem ("lexem.txt");
ifstream cin_lexem("lexem.txt");      
ofstream cout_exp ("explain.txt");
ofstream cout_lex ("inp.txt");
ofstream cout_res ("res.txt");

const int Lex_Max = 1000;

string mg;
string lexem[Lex_Max];
int num_lex;

bool flagS, flagN, flagO;

char ch;

struct queue1
{
    string word;
    int num;
    queue1 *next;
} *list_v, *list_c, *list_k;


struct queue2
{
    string word;
    char id;
    int num;
    queue2 *next;
} *list_o;

int push0(queue1 *&head, string w)
{
    queue1 *temp = new queue1;                  
    temp -> next = NULL;
    temp -> word = w;

    if (head)
    {
        queue1 *t;
	for (t = head; t -> next != NULL; t = t -> next);
	temp -> num = t -> num + 1;
	t -> next = temp;
    }
    else
    {
        temp -> num = 0;
        head = temp;
    }
    return temp -> num;
}

void push1(queue1 *&head, string w, int n)
{
    queue1 *temp = new queue1;                  
    temp -> word = w;
    temp -> next = NULL;
    temp -> num = n;
    if (head)
    {
        queue1 *t;
	for (t = head; t -> next != NULL; t = t -> next);
	t -> next = temp;
    }
    else
    {
        head = temp;
    }
}

void push2(queue2 *&head, string w, char id, int n)
{
    queue2 *temp = new queue2;                  
    temp -> next = NULL;	
    temp -> id = id;
    temp -> word = w;
    temp -> num = n;
    if (head)
    {
        queue2 *t;
	for (t = head; t -> next != NULL; t = t -> next);
	t -> next = temp;
    }
    else
    {
        head = temp;
    }
}

void init()
{
    list_v = NULL;
    list_c = NULL;
    list_k = NULL;
    list_o = NULL;
    int k;
    char ch;
    cin_key >> k >> ch;
    string s;
    for (int i = 0; i < k; i++)
    {
        cin_key >> s;
	push1(list_k, s, i);
    }
    cin_key >> k;
    for (int i = 0; i < k; i++)
    {
        int n;
	cin_key >> n >> ch;
	for (int j = 0; j < n; j++)
	{
	    cin_key >> s;
            push2(list_o, s, ch, j);
	}
    }
}

bool Is_Symb(char ch)
{
	return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == '_')) ? true : false;
}

bool Is_Num(char ch)
{
	return (ch >= '0' && ch <= '9') ? true : false;
}

bool Is_Oper(char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '&' || ch == '|' || ch == '=' || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}') ? true : false;
}

bool Is_Separ(char ch)
{
	return (ch == ' ' || ch == '\n' || ch == ')' || ch == '(' || ch == ';' || ch == '}' || ch == '{' || (!flagO && mg != "" && Is_Oper(ch))) ? true : false;
}

void Clear_mg(string &mg)
{
	mg = "";
}


void InsertWord(string mg)
{
	bool flag = false;
	for (queue1 *temp = list_k; temp; temp = temp -> next)
		if (temp -> word == mg)
		{
			flag = true;
			char ch1 = '0' + temp -> num;
			lexem[num_lex] = "k";
			lexem[num_lex] += ch1;
			lexem[num_lex] += "   [" + temp -> word + "]";
			num_lex++;
			return;
		}
	for (queue1 *temp = list_v; temp; temp = temp -> next)
		if (temp -> word == mg)
		{
			flag = true;
			lexem[num_lex] = "j";
			char ch1 = '0' + temp -> num;
			lexem[num_lex] += ch1;
			lexem[num_lex] += "   [" + temp -> word + "]";
			num_lex++;
			return;
		}
	
	int nnum = push0(list_v, mg);
	lexem[num_lex] = "j";
	char ch1 = '0' + nnum;
	lexem[num_lex] += ch1;
	lexem[num_lex] += "   [" + mg + "]";
	num_lex++;
}

void InsertNumber(string mg)
{
	bool flag = false;
    for (queue1 *temp = list_c; temp; temp = temp -> next)
		if (temp -> word == mg)
		{
			flag = true;
			lexem[num_lex] = "c";
			char ch1 = '0' + temp -> num;
			lexem[num_lex] += ch1;
			lexem[num_lex] += "   [" + temp -> word + "]";
			num_lex++;
			return;
		}
	
	int nnum = push0(list_c, mg);
	lexem[num_lex] = "c";
	char ch1 = '0' + nnum;
	lexem[num_lex] += ch1;
	lexem[num_lex] += "   [" + mg + "]";
	num_lex++;
}

void InsertOper(string mg)
{
	for (queue2 *temp = list_o; temp != NULL; temp = temp -> next)
		if (temp -> word == mg)
		{
			lexem[num_lex] = temp -> id;
			char ch1 = '0' + temp -> num;
			lexem[num_lex] += ch1;
			lexem[num_lex] += "   [" + temp -> word + "]";
			num_lex++;
			return;
		}
}		


void Insert(string &mg, char ch)
{
	if (flagS)
		InsertWord(mg);
                
    if (flagN)
		InsertNumber(mg);

    if (flagO)
		InsertOper(mg);
                
	Clear_mg(mg);
}

void Error(char &s)
{
	lexem[num_lex++] = "###########___Botva!!!___###########";
    while (!Is_Separ(ch) && cin_code.peek()!=EOF)
		cin_code >> ch;
        Clear_mg(mg);

}

void automat(string &mg, char ch)
{
	if (mg.length() == 0)
	{
		if (!(ch == ' ' || ch == '\n'))
		{
			flagS = Is_Symb(ch);
			flagN = Is_Num(ch);
			flagO = Is_Oper(ch);
			mg += ch;
            return;
		}
		else
			return;
	}
    
	if (!Is_Separ(ch))
	{
		if ((Is_Symb(ch) || Is_Num(ch)) && flagS)
			mg += ch;
		else
			if (Is_Num(ch) && flagN)
				mg += ch;
			else
				if (Is_Oper(ch) && flagO)
					mg += ch;
				else
					if (flagN && Is_Symb(ch))
						Error(ch);
                    else
					{
						Insert(mg, ch);
						flagS = Is_Symb(ch);
						flagN = Is_Num(ch);
                        flagO = Is_Oper(ch);
                        mg += ch;
					}
		return;
	}
	if (Is_Separ(ch))
	{
		if (Is_Oper(ch))
		{
			Insert(mg, ' ');
			flagS = Is_Symb(ch);
			flagN = Is_Num(ch);
            flagO = Is_Oper(ch);
            mg = ch;
		}
		else
			Insert(mg, ch);
	}
}


void print2(queue1 *head, string s)
{
	for (head; head; head = head -> next)
		cout_exp << head -> word << "   " << s << head -> num << endl;
}

void print3(queue2 *head)
{
	for (head; head; head = head -> next)
		cout_exp << head -> word << "   " << head -> id << head -> num << endl;
}

void print(queue1 *list_k, queue2 *list_o, queue1 *list_v, queue1 *list_c)
{
    cout_exp << "Переменные: " << endl << endl;
    print2(list_v, "j");
    cout_exp << endl << "Константы: " << endl << endl;
    print2(list_c, "c");
	cout_exp << endl << "Ключевые слова: " << endl << endl;
	print2(list_k, "k");
	cout_exp << endl << "Операции: " << endl << endl;
    print3(list_o);
}

int main()
{
	init();
	while (cin_code.peek()!=EOF)
	{
		cin_code.get(ch);
		automat(mg, ch);
	}
	automat(mg, ' ');
	print(list_k, list_o, list_v, list_c);

	for(int i = 0; i < num_lex; i++)
		cout_lexem << lexem[i] << endl;
	
	cout_lex << num_lex << "\n";
	for(int i = 0; i < num_lex; i++)
		cout_lex << lexem[i][0] << lexem[i][1] << endl;

	cout_res << push0(list_v, "") << endl;
	for (queue1 *t = list_v; t -> next; t = t -> next)
		cout_res << t -> word << endl;
	cout_res << endl << push0(list_c, "") << endl;
	for (queue1 *t = list_c; t -> next; t = t -> next)
		cout_res << t -> word << endl;
	
	char str;
	while(true){
		cin_lexem.get(str);
		if(cin_lexem.eof()){
			break;
		}
	cout << str;
	}

	return 0;
}