#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Num{
    double *num;
    int top;
};

struct Act{
    char* act;
    int top;
};

int countSize(const char* str){
    int i = 0;
    int kol = 1;
    char* p;
    while(1){
        p = strpbrk(str + i, "+-*/^()");
        if (p == NULL) break;
        i = p - str+1;
        ++ kol;
    }
    return kol;
}

void numPush(struct Num* num, double n){
    num->num[num->top] = n;
    ++num->top;
}

void numMath(struct Num* num,char operation){
    if (operation == '+')
        num->num[num->top-2] = num->num[num->top-2] + num->num[num->top-1];
    if (operation == '-')
        num->num[num->top-2] = num->num[num->top-2] - num->num[num->top-1];
    if (operation == '/')
        num->num[num->top-2] = num->num[num->top-2] / num->num[num->top-1];
    if (operation == '*')
        num->num[num->top-2] = num->num[num->top-2] * num->num[num->top-1];
    if (operation == '^')
        num->num[num->top-2] = pow(num->num[num->top-2],num->num[num->top-1]);
    --num->top;
}

void actPush(struct Act* act, char a){
    act->act[act->top]=a;
    ++act->top;
}

char actPop(struct Act* act){
    --act->top;
    return act->act[act->top];
}

int prior(char op){
    if ((op == '+')||(op == '-')){
        return 1;;
    }
    if((op == '/')||(op == '*')){
        return 2;
    }
    return 3;
}

int isBigger(char big,char lit){
    return prior(big) >= prior(lit);
}

double calc(const char * str, int * status) {
    printf("expression:\t\n%s\n",str);
    struct Num num;
    struct Act act;
    int len = strlen (str);
    int size = countSize(str);
    char* p;
    char pop;

    num.top = act.top = 0;
    num.num = calloc(size,sizeof(double));
    act.act = calloc(size,sizeof(char));

    for(int i = 0; i < len; ++i){
        if ((str[i]<= '9')&&(str[i]>='0')){
            numPush(&num,atof(str+i));
            p = strpbrk(str+i,"+-*/^()");
            if(p == NULL) break;
            i = p - str - 1 ;
            continue;
        }
        if (act.top==0){
            actPush(&act,str[i]);
            continue;
        }
        if(str[i] == '('){
            actPush(&act,str[i]);
            continue;
        }
        if (str[i] == ')'){
            while(1){
                pop = actPop(&act);
                if (pop == '(') break;
                numMath(&num,pop);
            }
            continue;
        }
        if (act.act[act.top-1]=='(')
        {
            actPush(&act,str[i]);
            continue;
        }
        if (isBigger(act.act[act.top-1],str[i])){
            numMath(&num,actPop(&act));
           --i;
           continue;
        }
        else {
            actPush(&act,str[i]);
        }
    }
    while(1){
        if (act.top==0)break;
        numMath(&num,actPop(&act));
    }
    return num.num[0];
}

int main(int argc, char *argv[])
{
    int* status = (int*)malloc(sizeof(int));
    double resault = calc("(6-2)*2^2",status);
    printf("resault = %f", resault);
    return 0;
}