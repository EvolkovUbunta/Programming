//---------------------------------------------------------------------------

#include <ctype.h>
#include <stdlib.h>
#include <algorithm>

#pragma hdrstop

#include "Lexer.h"
#include "Utils.h"
//---------------------------------------------------------------------------

namespace ESL
{
//---------------------------------------------------------------------------
CToken ErrorToken(ttUnknown, "ErrorToken");
//---------------------------------------------------------------------------

CToken& CToken::operator=(const CToken& other)
{
    _Type = other._Type;
    _Text = other._Text;

    return *this;
}

//---------------------------------------------------------------------------

bool CToken::operator==(const CToken& other)const
{
    return _Type==other._Type && _Text==other._Text;
}

//---------------------------------------------------------------------------

CToken::CToken(void): _Type(ttUnknown) {};

//---------------------------------------------------------------------------

CToken::CToken(const CToken& other): _Type(other._Type), _Text(other._Text) {};

//---------------------------------------------------------------------------

CToken::CToken(E_TOKEN_TYPES type, const string& text):
    _Type(type), _Text(text) {};

//---------------------------------------------------------------------------

void CLexer::DefineTokenType(CToken& token)const
{
    //поиск в массиве разделителей
    if(_Deviders.find(token.Text())!=_Deviders.npos)
        token._Type = ttDevider;
    //поиск в массиве операторов
    else if(_Operators.find(token.Text())!=_Operators.npos)
        token._Type = ttOperator;
    //поиск в массиве зарезервированных слов
    else if(find(_ResWordsArray.begin(),_ResWordsArray.end(),token.Text())!=
                                                          _ResWordsArray.end())
        token._Type = ttResWord;
    //поиск в массиве функций
    else if(find(_FunctionsArray.begin(),_FunctionsArray.end(),token.Text())!=
                                                          _FunctionsArray.end())
        token._Type = ttFunction;
    //проверка: является ли токен целым числом
    else
    {
        unsigned i;
        for(i=0;i<token._Text.length();++i)
            if(!isdigit(token.Text()[i]))
                break;

        if(i==token.Text().length())//если все символы текста токена - цифры
            token._Type = ttIntConstant;
        /*никаких соответствий не найдено, значит токен - название какой-либо
        переменной. Если это не так (т.е. текст токена некорректен - например
        опечатка или название несуществующей переменной), то ошибка будет
        выявлена на стадии выполнения опкода виртуальной машиной*/
        else
            token._Type = ttVariable;
    }
}

//---------------------------------------------------------------------------

CToken CLexer::SkanStringConstant(const string& text)
{
    //_OffSet сейчас находится в позиции первой кавычки
    //поиск второй закрывающей кавычки
    const unsigned pos = text.find_first_of('"',++_OffSet);

    if(pos==text.npos)//если зыкрывающая кавычка не найдена
        MACRO_ERROR_RET("CLexer::SkanStringConstant: '' expected",ErrorToken);

    //все в порядке, кавычка найдена
    const unsigned begin = _OffSet;

    _OffSet = pos+1; //перемещение позиции за кавычку

    return CToken(ttStrConstant, string(text, begin, pos-begin));
}

//---------------------------------------------------------------------------

CToken CLexer::SkanToken(const string& text)
{
    //если в текущей позиции кавычка, значит далее следует строковая константа
    if(text[_OffSet]=='"')
        return SkanStringConstant(text);
    //пропуск комментария если надо
    if(text[_OffSet]=='%')
        SkipComment(text);

    SkipSpacing(text);//фильтрация заполнителей

    CToken ret;
    //строка, содержащая разделяющие символы
    static const string delim = _Deviders + _Operators;
    //позиция ближайшего разделяющего символа
    const unsigned delimpos = text.find_first_of(delim, _OffSet);

    //если это последняя лексема в text
    //то выделяем фрагмент текста между позицией и концом файла
    if(delimpos==text.npos)
        ret._Text = text.substr(_OffSet);
    //позиция не последняя, те есть выделяем текст, заключенный между
    //текушей позицией и ближайшим разделяющим символом
    else
    {
        //либо, если находимся на разделителе выделяем его
        ret._Text = text.substr(_OffSet,max(delimpos-_OffSet,unsigned(1)));

        //перемещение на следующую лексему
        _OffSet = max(delimpos,_OffSet+1);
    }

    DefineTokenType(ret);//определение типа токена, по тексту в нем
    return ret;
}

//---------------------------------------------------------------------------

void CLexer::SkipSpacing(const string& text)
{
    //если текущая позиция не заполнитель
    if(!text[_OffSet] || !strchr(" \t\r\n", text[_OffSet]))
        return;//то пропускать то и нечего

    //перемещение позиции на последний заполняющий символ
    _OffSet = text.find_first_not_of(" \t\r\n", _OffSet) - 1;
}

//---------------------------------------------------------------------------

void CLexer::SkipComment(const string& text)
{
    while(text[_OffSet]=='%')
        _OffSet = text.find_first_of("\n", _OffSet) + 1;
}

//---------------------------------------------------------------------------

void CLexer::SaveTokens(ostream& os)const
{
    if(os.bad())
        MACRO_ERROR_RET_VOID("CLexer::SaveTokens error");

    string types[] = {"ttResWord",     "ttOperator", "ttStrConstant",
                      "ttIntConstant", "ttVariable", "ttFunction",
                      "ttDevider",     "ttUnknown"};

    for(unsigned i=0;i<_TokensBuffer.size();++i)
        os<<types[_TokensBuffer[i].Type()]<<
            ": '"<<_TokensBuffer[i].Text()<<"'"<<endl;
}

//---------------------------------------------------------------------------

bool CLexer::Lex(const string& text)
{
    _OffSet = 0;
   _TokensBuffer.clear();

    //если текст text пуст - выход
    if (text.empty())
        MACRO_ERROR_RET("CLexer::Lex tryng to lex empty text", false);

    unsigned prev_offset=-1;//предидующея позиция; для отслеживания смещения
    CToken   token;//очередной токен
    //сканиурем токены, пока не дойдем до конца скрипта
    do
    {
        //если смещения на следующую лексему по какой-либо причине не произошло
        if(prev_offset==_OffSet)
            MACRO_ERROR_RET("CLexer::Lex error. Possibly end missed",false);

        prev_offset = _OffSet;
        token       = SkanToken(text);

        if(token==ErrorToken)return false;//ошбика при сканировании токена

        _TokensBuffer.push_back(token);
    }
    while(token.Text()!="end");

    return true;
}

//---------------------------------------------------------------------------

void  CLexer::Init(//указатель на первый элемент массива строк-данных
                   const string* data,
                   unsigned rwc,  //число зарезервироавнных слов
                   unsigned opc,  //число операторов
                   unsigned fnc,  //число функций
                   unsigned dvc)  //число разделителей
{
    unsigned i;

    //копирование зарезервированных слов
    _ResWordsArray.resize(rwc);
    const string* rwend = data + rwc;
    copy(data,rwend,_ResWordsArray.begin());

    //копирование операторов
    const string* opend = rwend + opc;
    for(i=0;i<opc;++i)
        _Operators += rwend[i];

    //копирование функций
    _FunctionsArray.resize(fnc);
    const string* fnend = opend + fnc;
    copy(opend,fnend,_FunctionsArray.begin());

    //копирование разделителей
    for(i=0;i<dvc;++i)
        _Deviders += fnend[i];
}

//---------------------------------------------------------------------------

void CLexer::AddFunctions(const string* data, unsigned fnc)
{
    _FunctionsArray.insert(_FunctionsArray.end(),data,data+fnc);
}

//---------------------------------------------------------------------------
}
