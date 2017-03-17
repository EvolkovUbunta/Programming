//---------------------------------------------------------------------------

#pragma hdrstop

#include "Var.h"
#include "Utils.h"
//---------------------------------------------------------------------------

//макросы для более удобного контроля ошибок (добавлен учет ошибок)
#ifndef _ESLNDEBUG
  //err - текст ошибки, ret - возвращаемый результат
  #define _MACRO_ERROR_RET(err,ret)  {ESLLog.WriteError(##err##);\
                                     ++_ErrorsCount;return(##ret##);}
  //err - текст ошибки; осуществляется выход из вызывающей функции
  #define _MACRO_ERROR_RET_VOID(err) {ESLLog.WriteError(##err##);\
                                     ++_ErrorsCount;return;}
  //err - текст ошибки; выхода из функции нет
  #define _MACRO_ERROR(err)          {ESLLog.WriteError(##err##);\
                                     ++_ErrorsCount;}
#else
  #define _MACRO_ERROR_RET(err,ret)  {++_ErrorsCount;return(##ret##);}
  #define _MACRO_ERROR_RET_VOID(err) {++_ErrorsCount;return;}
  #define _MACRO_ERROR(err)
#endif

//---------------------------------------------------------------------------

namespace ESL
{
//---------------------------------------------------------------------------
int CVar::_ErrorsCount = 0;
//---------------------------------------------------------------------------

void CVar::Copy(const CVar& val)
{
    //удаление старых данных (для строк)
    if(_Type==vtString)
        delete[] _Data.SVal;

    switch(val._Type)
    {
        case vtInt:    _Data.IVal = val._Data.IVal; break;

        case vtString: _Data.SVal = new char[strlen(val._Data.SVal)+1],
                       strcpy(_Data.SVal,val._Data.SVal);  break;
    }

    _Type = val._Type;
}

//---------------------------------------------------------------------------

CVar::operator int()const
{
    if(_Type!=vtInt)
        _MACRO_ERROR_RET("CVar::operator int - type missmatch",0);

    return _Data.IVal;
}

//---------------------------------------------------------------------------

CVar::operator const char* ()const
{
    if(_Type!=vtString)
        _MACRO_ERROR_RET("CVar::operator const char* - type missmatch",NULL);

    return _Data.SVal;
}

//---------------------------------------------------------------------------

CVar& CVar::operator=(const CVar& other)
{
    //присваивание только в случае совпадения типов
    //или неопределенности типа приемника; автопреобразований нет
    if(other._Type!=vtUnknown && (_Type==vtUnknown || _Type==other._Type))
        Copy(other);
    else
        _MACRO_ERROR("CVar::operator= type missmatch");

    return *this;
}

//---------------------------------------------------------------------------

bool CVar::operator==(const CVar& other)
{
    if(_Type!=other._Type)
        _MACRO_ERROR_RET("CVar::operator== type missmatch",false);

    //для объектов, размещаемых не в стеке - специфическое сравнение
    if(_Type==vtString)
        return strcmp(_Data.SVal, other._Data.SVal)==0;
    //для стековых объектов - общее сравнение
    else
        return memcmp(&_Data,&other._Data,sizeof(UData))==0;
}

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

bool CVar::operator>(const CVar&other)
{
    if(_Type!=other._Type)
        _MACRO_ERROR_RET("CVar::operator> type missmatch",false);

    //для нестековых объектов специфическое сравнение
    if(_Type==vtString)
        return strcmp(_Data.SVal,other._Data.SVal)>0;
    //для стековых - общее
    else
        return memcmp((void*)&_Data,(void*)&other._Data,sizeof(UData))>0;
}

//---------------------------------------------------------------------------

CVar::CVar(void): _Type(vtUnknown) {};

//---------------------------------------------------------------------------

CVar::CVar(const int& val): _Type(vtInt) {_Data.IVal = val;}

//---------------------------------------------------------------------------

CVar::CVar(const char* val): _Type(vtString)
{
    _Data.SVal = new char[strlen(val)+1];
    strcpy(_Data.SVal,val);
}

//---------------------------------------------------------------------------

CVar::CVar(const CVar& val): _Type(vtUnknown) {Copy(val);}

//---------------------------------------------------------------------------

CVar::~CVar(void)
{
    //освожбодаем память, если хранится строка
    if(_Type==vtString)
        delete[] _Data.SVal;
}

//---------------------------------------------------------------------------
}

