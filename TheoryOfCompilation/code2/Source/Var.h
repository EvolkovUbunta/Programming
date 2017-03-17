//---------------------------------------------------------------------------

#ifndef VarH
#define VarH
//---------------------------------------------------------------------------
namespace ESL
{
//---------------------------------------------------------------------------

//возмодные типы данных скрипта
enum E_VAR_TYPES
{
    vtInt,
    vtString,  //строка, вида char[N]
    vtUnknown  //тип неопределен/неизвестен
};

//---------------------------------------------------------------------------

//предназначен дл€ хранени€ данных различного типа
class CVar
{
private:

    E_VAR_TYPES _Type;

    union UData
    {
        int    IVal;
        char*  SVal;
    };

    UData       _Data;

    static  int  _ErrorsCount; //количество ошибок в ходе работы c объектами CVar

    //копирует данные из другого экземпл€ра
    void  Copy(const CVar&);

public:

    E_VAR_TYPES  Type(void)const        {return _Type;}
    bool         WereErrors(void)const  {return _ErrorsCount>0;}

    //операторы преобразований:
    operator  int         ()const;
    operator  const char* ()const;

    CVar& operator= (const CVar&);
    bool  operator==(const CVar&);
    bool  operator!=(const CVar&);
    bool  operator> (const CVar&);
    bool  operator>=(const CVar&);
    bool  operator< (const CVar&);
    bool  operator<=(const CVar&);
    CVar& operator+ (const CVar&);
    CVar& operator+=(const CVar&);
    void  operator++(void);
    CVar& operator- (const CVar&);
    CVar& operator-=(const CVar&);
    void  operator--(void);
    CVar& operator* (const CVar&);
    CVar& operator*=(const CVar&);
    CVar& operator/ (const CVar&);
    CVar& operator/=(const CVar&);

    CVar(void);
    CVar(const int&);
    CVar(const char*);
    CVar(const CVar&);
    ~CVar(void);
};









//---------------------------------------------------------------------------
}

#endif
