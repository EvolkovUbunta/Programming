#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_LEN 100

const char charOp[7] = {'+','-','*','/','^','(',')'};
const char charAct[5]= {'+','-','*','/','^'};

struct ActSt{
    char act[25];
    int  top;
};

struct Lex{
    char   act [MAX_LEN];
    double num [MAX_LEN];
    int    top;
};

// добавить на вершину число
int lexPushNum(struct Lex * lex,double number){
        lex -> num [ lex->top] = number;
        lex -> act [ lex->top] = 0;
        lex -> top++;
        return 0;
}

// добавить на вершину число
int lexPushNumStr(struct Lex * lex,const char* number){
    if(strlen(number)!=0){
        lex -> num [ lex -> top ] = atof( number );
        lex -> act [ lex -> top] = 0;
        lex -> top ++;
        return 0;
    }
    return 1;
}

// добавить на вершину действие
int lexPushAct(struct Lex * lex, char act){
    if (strchr(charOp,act) == NULL) return 1;
    lex->act[lex->top] = act;
    lex->top++;
    return 0;
}

// является действием (кроме '(' ')')
int isAct(char act){
    if (strchr(charAct,act) == NULL) return 1;
    return 0;
}

// добавить на вершину действие
int actStPush(struct ActSt * ActS, char act){
    if (strchr(charOp,act) == NULL) return 1;
    ActS->act[ActS->top] = act;
    ++ ActS->top;
    return 0;
}

// сравнить по приоритету
// 1 если приориет big >= lit
int isBigAct(char big,char lit){
       if (lit == '+' || lit == '-') return 1;
       if (big == '^' ) return 1;
       if ((lit == '*' || lit == '/')&&(big == '*' || big == '/')) return 1;
       return 0;
}

char actStPop(struct ActSt * ActS){
    ActS->act[ActS->top]=0;
    -- ActS->top ;    
    if (ActS->top < 0) ActS->top =0;
    return ActS->act[ ActS->top];
}

void clear(struct Lex * lex){
    int j=0;
    for (int i = 0 ; i< lex->top; i++){
        if (lex->act[i]==1)continue;
        if (lex->act[i]!=0) lex->act[j]=lex->act[i];
        else{
            lex->act[j]=0;
            lex->num[j]= lex->num[i];
        }
        j++;
    }
    lex->top = j;
}

void math(struct Lex * lex){
    int i;
    for(i = 2; i < lex->top; i++ ){
        if(lex->act[i]!=0) break;
    }
    if (lex->act[i] == '+')
        lex->num[i-2]=lex->num[i-1]+lex->num[i-2];
    if (lex->act[i] == '-')
        lex->num[i-2]=lex->num[i-1]-lex->num[i-2];
    if (lex->act[i] == '*')
        lex->num[i-2]=lex->num[i-1]*lex->num[i-2];
    if (lex->act[i] == '/')
        lex->num[i-2]=lex->num[i-2]/lex->num[i-1];
    if (lex->act[i] == '^')
        lex->num[i-2]=pow(lex->num[i-2],lex->num[i-1]);
    lex->act[i] = lex->act[i-1] = 1;
    lex->act[i-2] = 0;
}

double calc(const char * str, int * status) {
    printf("%s\n",str);
    struct Lex lex,resLex;
    struct ActSt ActS;
    resLex.top = ActS.top = ActS.act[0] = 0;
    lex.top = 0;
    int indexBegin,indexEnd;
    indexBegin = 0;
    char *myStr;
    char dobl[10];
    printf("\n%s\n",str);

    for(;;) {
        memset(dobl, 0, sizeof (dobl));
        myStr = strpbrk (str + indexBegin, charOp);
        if(myStr == NULL) {
            lexPushNumStr(&lex, str + indexBegin);
            break;
        }
        indexEnd = ( myStr - str) ;
        strncpy(dobl, str + indexBegin, indexEnd - indexBegin);
        indexBegin = indexEnd + 1;
        lexPushNumStr (&lex, dobl);
        lexPushAct (&lex, str[indexBegin-1]);
    }

    char act;
    int i=-1;
    for ( i =0; i< lex.top; i++){
        // если число
        if (lex.act[i]==0){
            lexPushNum(&resLex,lex.num[i]);
            continue;
        }
        // если стек с операциями пуст
        if (ActS.top == 0 ) {
            actStPush(&ActS,lex.act[i]);
            continue;
        }
        // или сейчас смотрим на '('
        if (lex.act[i] == '('){
            actStPush(&ActS,'(');
            continue;
        }
        // если смотрим на ')'
        if ( lex.act[i] == ')')
        {
            while(1) {
                act = actStPop(&ActS);
                if (act=='(') {
                    break;
                }
                lexPushAct(&resLex,act);
            }
            continue;
        }
        if (ActS.act[ ActS.top - 1 ] == '('){
            actStPush(&ActS,lex.act[i]);
            continue;
        }
        else {
        // сравниваем приоритет операций
            if (isBigAct(ActS.act[ ActS.top - 1 ],lex.act[ i ])){
                lexPushAct(&resLex,actStPop(&ActS));
                i--;
            }
            else   {
                actStPush(&ActS,lex.act[i]);
            }
        }
    }
    // обрабатываем остаток стека с операциями
    while(1){
        act=actStPop(&ActS);
        if (act== 0) break;
        lexPushAct(&resLex,act);
    }
    double result=0;
    // считаем
    for (int i = 0 ; i < resLex.top ; i++){
        if (resLex.act[i] == 0)
              printf ("number [%d] = %f\n",i,resLex.num[i]);
         else printf ("char   [%d] = %c\n",i,resLex.act[i]);
    }

    while(1){
        if(resLex.top==1) break;
        math(&resLex);
        clear(&resLex);
    }
    result= resLex.num[0];
    (*status) = 0;
    return result;
}

int main(int argc, char *argv[])
{
    int * status;
    status = malloc(sizeof( int));
    double result;
    result = calc("9/5",status);
    printf("result = %f\n",result);
    return 0;
}