//---------------------------------------------------------------------------

#ifndef LexerH
#define LexerH

#pragma warning(disable:4786)
#include <string>
#include <vector>
using namespace std;

//---------------------------------------------------------------------------
namespace ESL
{
//---------------------------------------------------------------------------

//возможные типы лексем
enum E_TOKEN_TYPES
{
    ttResWord = 0, //ключевое (зарезервированное) слово
    ttOperator,    //оператор
    ttStrConstant, //строковая константа
    ttIntConstant, //числовая константа
    ttVariable,    //переменная
    ttFunction,    //функция
    ttDevider,     //разделитель
    ttUnknown      //тип не определен, либо не известен
};

//---------------------------------------------------------------------------

class CToken
{
friend class CLexer;
private:

    E_TOKEN_TYPES  _Type;//тип лексемы
    string         _Text;//текст лексемы

public:

    E_TOKEN_TYPES  Type(void)const {return _Type;}
    string         Text(void)const {return _Text;}

    CToken&        operator= (const CToken&);
    bool           operator==(const CToken&)const;

    CToken(void);
    CToken(const CToken&);
    CToken(E_TOKEN_TYPES, const string&);
};

typedef vector<CToken> TokensArray;

//---------------------------------------------------------------------------

typedef vector<string> StringsArray;

//предназначен для преобразования указанного текста в поток (массив) токенов
class CLexer
{
private:

    //распознаваемые лексическим анализатором...
    StringsArray  _ResWordsArray,  //зарезервированные слова
                  _FunctionsArray; //функции
    string        _Operators,      //операторы
                  _Deviders;       //разделители

    TokensArray   _TokensBuffer; //токены, полученные при последнем
                                 //"лексировании" текста
    unsigned      _OffSet; //позиция в текущем лексируемом тексте

    //определяет тип токена, если он еще не определен
    void    DefineTokenType(CToken&)const;
    //сканиурет строковую константу (фрагмент текста, заключенный в "")
    CToken  SkanStringConstant(const string&);
    //возвращает очередной токен, возвращает _ErrorToken в случае ошибки
    CToken  SkanToken(const string&);

    //если подряд идут несколько пробелов, то эта функция перемещает позцию
    //на последний из них
    void    SkipSpacing(const string&);
    //если текущая пощиция находится на символе начала комментария %, то эта
    //функция "вырезает" комментарий, т.е. перемещает позицию за него
    void    SkipComment(const string&);   

public:

    const TokensArray& GetTokens(void)const {return _TokensBuffer;}
    //сохраняет буфер токенов в файл
    void  SaveTokens(ostream& os)const;

    //"лексирует" передаваемый текст. True в случае успеха
    bool  Lex(const string&);

    //инициализирует лексический анализатор. Эта функция должны быть вызвана
    //до первого "лексирования"
    void  Init(const string*, unsigned, unsigned, unsigned, unsigned);
    //добавляет дополнительные функции в _FunctionsArray
    void  AddFunctions(const string*, unsigned);
};

//---------------------------------------------------------------------------
}


#endif
#pragma warning(default:4786)