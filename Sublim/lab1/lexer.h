#include <string>
using namespace std;
 
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
 
class CToken
{
private:
 
    E_TOKEN_TYPES  _Type;//тип лексемы
    string         _Text;//текст лексемы
 
public:
 
    E_TOKEN_TYPES  Type(void)const {return _Type;}
    string         Text(void)const {return _Text;}
 
    CToken(void);
    CToken(const CToken&);
    CToken(E_TOKEN_TYPES, const string&);
};

CToken& CToken::operator=(const CToken& other)
{
    _Type = other._Type;
    _Text = other._Text;
 
    return *this;
}
 
bool CToken::operator==(const CToken& other)const
{
    return _Type==other._Type && _Text==other._Text;
}