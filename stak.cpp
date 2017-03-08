// Стековый калькулятор
#include <iostream>
#include <cmath>
using namespace std;


// поддерживаемые операции
enum Operation
{
  Eval = '=',
  Add  = '+',
  Sub  = '-',
  Mul  = '*',
  Div  = '/',
  Mod  = '%',
  Pow  = '^'
};


const int StackCalcSize = 1000;
// стек с числами, 
// поддерживающий арифметические операции
struct StackCalculator
{
  double stack[StackCalcSize];
  int stackTop;

  // операции со стеком
  bool empty() const
  { return stackTop == 0; }

  bool full() const
  { return stackTop == StackCalcSize; }

  void push (double v)
  { stack[stackTop++] = v; }

  double pop() // удобно возвращать значение
  { return stack[--stackTop]; }

  double top() const
  { return stack[stackTop - 1]; }

  // арифметические операции
  void add()
  { push (pop() + pop()); }

  void mul()
  { push (pop() * pop()); }

  void sub()
  {
    const double right = pop();
    push (pop() - right);
  }

  void div()
  {
    const double divisor = pop();
    push (pop() / divisor);
  }

  void mod()
  {
    const double divisor = pop();
    push (std::fmod (pop(), divisor));
  }

  void pow()
  {
    const double expon = pop();
    push (std::pow(pop(), expon));
  }

  // "любая" операция
  bool operation (Operation op)
  {
    switch (op)
    {
    case Add: add(); break;
    case Sub: sub(); break;
    case Mul: mul(); break;
    case Div: div(); break;
    case Mod: mod(); break;
    case Pow: pow(); break;
    default: return false;
    }
    return true;
  }
};


int main()
{
  using namespace std;
  for (;;)
  {
    // новый стек
    StackCalculator S = {};
    for (;;)
    {
      // проверить следующий символ
      char ch = '\0';
      cin >> ch;

      if (cin.eof())
        return 0; // выйти по Ctrl+Z

      if (ch == Eval)
      {
        cout << " = " << S.top() << endl;
        break; // нужен новый стек
      }

      // выполнить операцию или считать число
      if (!S.operation ((Operation)ch))
      {
        // не операция, значит, надо считать число
        cin.putback (ch); // вернуть символ
        double x;
        cin >> x;

        if (cin.fail())
        {
          cin.clear(); // игнорируем ошибку
          cin.get();   // убираем символ
        }
        else
          S.push (x);
      }
    }
  }
}
