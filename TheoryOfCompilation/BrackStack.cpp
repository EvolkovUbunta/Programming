// BrackStack.cpp - автомат с магазинной памятью,
// распознающий вложенность круглых скобок.
// Построен на основе таблицы переходов,
// созданной по следующей q-грамматике:
// 1. S -> (B)B
// 2. B -> (B)B
// 3. B -> empty

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

// Магазинными символами автомата являются:
// S, B, маркер дна (bottom).

// Их значение должно быть за пределами видимых символов.
enum stackSymb {S = 256, B, bottom}; 

// Строка с входной цепочкой, имитирующая входную ленту
string str;
int i; // Текущее положение входной головки
stack <int, vector<int> > stck; // Стек для магазинных символов

// Функция, реализующая чтение символов в буфер из входного потока.
// Используется для ввода с клавиатуры распознаваемой строки.
// Ввод осуществляется до нажатия на клавишу Enter.
// Символ '\n' яляется концевым маркером входной строки.

void GetOneLine(istream &is, string &str) {
  char ch;
  str = "";
  for(;;) {
    is.get(ch);
    if(is.fail() || ch == '\n') break;
    str += ch;
  }
  str += '\n'; // Добавляется концевой маркер
}

// Инициализация устройств АМП

void Init() {
  // Инициализация стека
  while(!stck.empty())  stck.pop();
  stck.push(bottom);
  stck.push(S);

  // Инициализация входной головки
  i = 0;
}

// Устройство управления АМП, анализирующего вложенность скобок.
// Имитирует таблицу переходов АМП.

bool Parser() {

  // Инициализация устройств АМП
  Init();
  int step = 0;

  // Цикл анализа состояний
  for(;;) {
    // Тестовый вывод информации о текущем шаге, 
    // текущем символе, вершине стека
    cout <<"step " << step++ << ": str[" << i << "] = "<< str[i] 
         << " Top = "<< stck.top() << "\n";

    // Проверка содержимого на вершине стека
    switch(stck.top()) {
    // Анализ первой строки таблицы переходов
    case S:
        switch(str[i]) {
        case '(': // [S, (]
            stck.top() = B; // эквивалентно stck.pop(); stck.push(B);
            stck.push(')');
            stck.push(B);
            i++; // следующий входной символ
            break;
        case ')': // [S, )] - ) не может стоять в начале
            cout << "Position " << i << ", " 
                 << "Error 1: \')\' can not is in begin!\n";
            return false;
        case '\n': // [S, концевой маркер]
            cout << "Position " << i << ", " 
                 << "Error 2: Empty string!\n";
            return false;
        default: // Ошибка, такой символ не допустим
            cout << "Position " << i << ", " 
                 << "Incorrect symbol! " << str[i] << "\n";
            return false;
        }
        break;
    // Анализ второй строки таблицы переходов
    case B:
        switch(str[i]) {
        case '(': // [B, (]
            stck.top() = B; // эквивалентно stck.pop(); stck.push(B);
            stck.push(')');
            stck.push(B);
            i++; // следующий входной символ
            break;
        case ')': // [B, )] - вытолкнуть без сдвига 
            stck.pop();
            break;
        case '\n': // [B, концевой маркер] - вытолкнуть без сдвига
            stck.pop();
            break;
        default: // Ошибка, такой символ не допустим
            cout << "Position " << i << ", " 
                 << "Incorrect symbol! " << str[i] << "\n";
            return false;
        }
        break;
    // Анализ третьей строки таблицы переходов
    case ')':
        switch(str[i]) {
        case '(': // [), (] - в принципе недостижимо
            cout << "Position " << i << ", " 
                 << "Error 3: I want \')\'!\n";
            return false;
        case ')': // [), )] - вытолкнуть со сдвигом 
            stck.pop(); // вытолкнуть
            i++;  // сдвиг
            break;
        case '\n': // [), концевой маркер]
            cout << "Position " << i 
                 << ", Error 4: I want \')\'!\n";
            return false;
        default: // Ошибка, такой символ не допустим
            cout << "Position " << i << ", " 
                 << "Incorrect symbol! " << str[i] << "\n";
            return false;
        }
        break;
    // Анализ четвертой строки таблицы переходов
    case bottom:
        switch(str[i]) {
        case '(': // [bottom, (] - невозможно при пустом магазине
            cout << "Position " << i << ", "
                 << "Error 4: Impossible situation [bottom, \'(\']!\n";
            return false;
        case ')': // [bottom, )] - лишняя )
            cout << "Position " << i << ", "
                 << "Error 5: unnecessary \')\'!\n";
            return false;
        case '\n': // [bottom, концевой маркер] - допустить!
            return true;
        default: // Ошибка, такой символ не допустим
            cout << "Position " << i << ", " 
                 << "Incorrect symbol! " << str[i] << "\n";
            return false;
        }
        break;
    }
  }
}

// Главная функция используется для инициализации устройств
// АМП перед каждым новым прогоном и тестирования до тех пор,
// пока не будет прочитана пустая строка.

int main () {
  string strCursor;
  str = "";

  // Цикл распознавания различных входных цепочек
  do {
    // Чтение очередной входной цепочки в буфер
    cout << "Input bracket\'s expression!: ";

    // Формируем очередную строку скобок для распознавания.
    GetOneLine(cin, str);

    // Здесь начинается разбор принятой строки.
    if(Parser())
        cout << "+++++ OK! +++++\n";
    else
        cout << "--- Fatal error (look upper error message)! ---\n";

    // Вывод разобранной строки и значения позиции входой головки.
    cout << "Line: " << str;
    strCursor = " Pos: " + string(i, '-');
    strCursor +='^';
    cout << strCursor << " i = " << i << "\n\n";
  } while(str != "\n");

  cout << "Goodbye!\n";
  return 1;
}