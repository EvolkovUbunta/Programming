#include <fstream>
#include <string>
#include <map>

using namespace std;

ifstream cin_tok("inp.txt");
ifstream cin_gr("gram.txt");
ifstream cin_key("key.txt");
ifstream cin_res("res.txt");

ofstream cout_dop("dop.txt");
ofstream cout_ans("out.txt");
ofstream cout_gr("gram2.txt");

const int MaxRules = 100;
const int MaxLen = 100;
const int MaxNum = 100;

int num_rules = 0;
int num_tok = 0;

struct pare_ch
{
	char ch1, ch2;
	pare_ch()
	{
		ch1 = '!';
		ch2 = '!';
	}
	pare_ch(char c1, char c2)
	{
		ch1 = c1;
		ch2 = c2;
	}
};

bool operator ==(pare_ch x, pare_ch y)
{
	if (x.ch1 == y.ch1 && (x.ch2 == y.ch2 || x.ch2 == '*' || y.ch2 == '*'))
		return true;
	return false;
}

bool operator <(pare_ch x, pare_ch y)
{
	if (x.ch1 < y.ch1 || x.ch1 == y.ch1 && x.ch2 < y.ch2)
		return true;
	return false;
}

map <pare_ch, string> value;

struct rule
{
	char net;
	int num;
	pare_ch rul[MaxLen];
} rules[MaxRules];

typedef struct situation
{
	pare_ch net;
	int before, after;
	pare_ch chein[MaxLen];
	int num_s;
} sit[MaxNum];

struct razbor
{
	sit list_sit;
	int num;
} I[MaxNum];

bool operator ==(situation x, situation y)
{
	bool fl = false;
	if (x.net == y.net
		&& x.after == y.after
		&& x.before == y.before
		&& x.num_s == y.num_s)
    {
		fl = true;
		for (int t = 0; t < y.before + y.after; t++)
		{
			if (!(x.chein[t] == y.chein[t]))
			{
				fl = false;
				break;
			}
		}
	}
	
	return fl;
}

void Read_rules()
{
	cin_gr >> num_rules;
	for (int i = 0; i < num_rules; i++)
	{
		string s;
		cin_gr >> rules[i].net >> s;
		for (int j = 0; j < (int)s.length(); j+=2)
		{
			rules[i].rul[rules[i].num] = pare_ch(s[j], s[j + 1]);
			rules[i].num++;
		}
	}
}

void print_spisok(int i)
{
	cout_dop << "I" << i << endl;
	for (int w = 0; w < I[i].num; w++)
	{
		cout_dop << "[" << I[i].list_sit[w].net.ch1 << " -> ";
		for (int j = 0; j < I[i].list_sit[w].before; j++)
		{
			cout_dop << I[i].list_sit[w].chein[j].ch1 << I[i].list_sit[w].chein[j].ch2;
		}
		cout_dop << ".";
		for (int j = I[i].list_sit[w].before; j < I[i].list_sit[w].before + I[i].list_sit[w].after; j++)
		{
			cout_dop << I[i].list_sit[w].chein[j].ch1 << I[i].list_sit[w].chein[j].ch2;
		}
		cout_dop << ", " << I[i].list_sit[w].num_s << "] " << "\n";
	}
}

void Make_spisok_razbora()
{
	//I0
	for (int i = 0; i < num_rules; i++)
	{
		I[0].list_sit[I[0].num].net = pare_ch(rules[i].net, '_');
		I[0].list_sit[I[0].num].before = 0;
		I[0].list_sit[I[0].num].after = rules[i].num;
		for (int j = 0; j < rules[i].num; j++)
			I[0].list_sit[I[0].num].chein[j] = rules[i].rul[j];
		I[0].list_sit[I[0].num].num_s = 0;
		I[0].num++;
	}
	print_spisok(0);

	//Ii
	cin_tok >> num_tok;

	for (int i = 1; i <= num_tok; i++)
	{
		pare_ch ch;
		string s;
		cin_tok >> s;
		ch = pare_ch(s[0], s[1]);
		
		for (int j = 0; j < I[i - 1].num; j++)
		{
			if (I[i - 1].list_sit[j].after != 0
				&& I[i - 1].list_sit[j].chein[I[i - 1].list_sit[j].before] == ch)
			{
				I[i].list_sit[I[i].num] = I[i - 1].list_sit[j];
				I[i].list_sit[I[i].num].chein[I[i].list_sit[I[i].num].before] = ch;
				I[i].list_sit[I[i].num].before++;
				I[i].list_sit[I[i].num].after--;
				I[i].num++;
			}
		}

		bool f = false;
		while (!f)
		{
			f = true;
			//'.' before neterm.
			for (int j = 0; j < I[i].num; j++)
			{
				if (I[i].list_sit[j].chein[I[i].list_sit[j].before].ch2 == '_')
				{
                    for (int k = 0; k < num_rules; k++)
					{
						if (rules[k].net == I[i].list_sit[j].chein[I[i].list_sit[j].before].ch1)
						{
							situation y;
							y.net = pare_ch(rules[k].net, '_');
							y.before = 0;
							y.after = rules[k].num;

							for (int z = 0; z < rules[k].num; z++)
							{
								y.chein[z] = rules[k].rul[z];
								y.num_s = i;
							}
							
							bool fl = false;
							for (int z = 0; z < I[i].num; z++)
								if (y == I[i].list_sit[z])
									fl = true;
							if (!fl)
							{
								I[i].list_sit[I[i].num] = y;
								I[i].num++;
								f = false;
							}
						}
						
					}
				}
			}
			//after '.'
			for (int j = 0; j < I[i].num; j++)
			{
				if (I[i].list_sit[j].after == 0)
				{
					int num = I[i].list_sit[j].num_s;
					for (int z = 0; z < I[num].num; z++)
					{
						if (I[num].list_sit[z].chein[I[num].list_sit[z].before] == I[i].list_sit[j].net)
						{
							bool fl = false;
							situation y;
							y = I[num].list_sit[z];
							y.before++;
							y.after--;
							for (int z = 0; z < I[i].num; z++)
								if (y == I[i].list_sit[z])
									fl = true;
							if (!fl)
							{
								I[i].list_sit[I[i].num] = y;
								I[i].num++;
								f = false;
							}
						}

					}
				}
			}
		}
		print_spisok(i);
	}
}

void Read_v_c_key()
{
	int n;
	char ch;
	string s;
	cin_key >> n >> ch;
	for (int i = 0; i < n; i++)
	{
		cin_key >> s;
		value[pare_ch(ch, i + '0')] = s;
	}
	cin_key >> n;
	int m;
	for (int i = 0; i < n; i++)
	{
		cin_key >> m >> ch;
		for (int j = 0; j < m; j++)
		{
			cin_key >> s;
			value[pare_ch(ch, j + '0')] = s;
		}
	}
	cin_res >> n;
	for (int i = 0; i < n; i++)
	{
		cin_res >> s;
		value[pare_ch('j', i + '0')] = s;
	}
	cin_res >> n;
	for (int i = 0; i < n; i++)
	{
		cin_res >> s;
		value[pare_ch('c', i + '0')] = s;
	}
}

void Print_Rule(situation sit)
{
	cout_ans << sit.net.ch1 << " -> ";
	for (int i = 0; i < sit.before + sit.after; i++)
		if (sit.chein[i].ch2 == '_')
		{
			cout_ans << sit.chein[i].ch1 << " ";
		}
		else
		{
			cout_ans << value[sit.chein[i]] << " ";
		}
	cout_ans << endl;

}

void Rec(situation sit, int num_sp)
{
	Print_Rule(sit);
	int k, l, r;
	l = num_sp;
	k = sit.before - 1;

	while (k > -1) 
	{
		situation temp = sit;
		temp.after += temp.before - k;//a = (b + a)/all/ - (k + 1)/new before/
		temp.before = k;

		bool f = false;
		if (sit.chein[k].ch2 == '_') //neterminal
		{
			for (int i = 0; i < num_tok + 1; i++)
			{
				for (int j = 0; j < I[i].num; j++)
				{
					if (I[i].list_sit[j] == temp)
					{
						for (int z = 0; z < I[l].num; z++)
						{
							if (I[l].list_sit[z].net == sit.chein[k]
							&& I[l].list_sit[z].after == 0
								&& I[l].list_sit[z].num_s == i)
							{
								r = i;
								Rec(I[l].list_sit[z], l);
								f = true;
								k--;
								l = r;
								break;
							}
						}
					}
					if (f)
						break;
				}
				if (f)
					break;
			}
		}
		else //terminal
		{
			k--;
			l--;
		}
	}
}

void Analiz()
{
	Read_v_c_key();
	//find na4
	bool f = false;
	for (int i = 0; i < I[num_tok].num; i++)
	{
		if (I[num_tok].list_sit[i].after == 0
			&& I[num_tok].list_sit[i].net.ch1 == rules[0].net
			&& I[num_tok].list_sit[i].num_s == 0)
		{
			f = true;
			Rec(I[num_tok].list_sit[i], num_tok);
			break;
		}
	}
	if (!f)
	{
		cout_ans << "---------ERROR!!!---------";
	}
}

int main()
{
	Read_rules();
	Make_spisok_razbora();
	Analiz();
/*	gram out  */    
	for (int i = 0; i < num_rules; i++)
	{
		cout_gr << rules[i].net << " -> ";
		for (int j = 0; j < rules[i].num; j++)
			if (rules[i].rul[j].ch2 == '_')
				cout_gr << rules[i].rul[j].ch1 << " ";
			else
				if (rules[i].rul[j].ch2 == '*')
					cout_gr << rules[i].rul[j].ch1 << "* ";
				else
					cout_gr << value[rules[i].rul[j]] << " ";
		cout_gr << endl;
	}
//*/
	return 0;
}

