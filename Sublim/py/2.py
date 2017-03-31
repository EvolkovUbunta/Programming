# -*- coding: UTF-8 -*-
import math
import pylab
import random
from matplotlib import mlab
L=10 # Длительность  сигнала
s0=[]
s1=[]
h1=[]# Массив для отсчетов импульсной характеристики согласованного фильтра
h0=[]# Массив для отсчетов импульсной характеристики согласованного фильтра
x=[] #  Массив для входной смеси полезного сигнала с шумом
y1=[]  #  Массив для выходного процесса на выходе фильтра
y0=[]
A=0.9 #Максимальное по модулю значение сигнала
#Массив отсчетов сигнала для передачи логической 1
for i in range(0,L):
   s=A*i/(L-1)
   s0.append(s)
#Массив отсчетов сигнала для передачи логического 0
for i in range(0,L):
   s=-A*i/(L-1)
   s1.append(s)
#Импульсная характеристика фильтра согласованного с сигналом s1  
for i in range(0,L):
   h1.append(s1[L-1-i])
#Импульсная характеристика фильтра согласованного с сигналом s0    
for i in range(0,L):
   h0.append(s0[L-1-i])
#Отведение памяти под массивы входных и выходных отсчетов    
for i in range(0,L):
    x.append(0)
    y1.append(0)
    y0.append(0)
#Количество моделируемых ситуаций 
M=10000
col=0#Переменная для подсчета числа ошибок 
for jeks in range(0,M):# Цикл по числу экспериментов
#---------------1  посылка   ------------------------------
   for i in range(0,L):# Формирование входного процесса
      x[i]=random.normalvariate(0,1)
      # Передаем либо 0 - в  четных экспериментах, либо 1
      if jeks%2 ==1:
          x[i]=x[i]+ s1[i]
      else:
          x[i]=x[i]+ s0[i]
   for i in range(0,L):#Фильтрация в канале согласованным с s1
        y1[i]=0.0
        for k in range(0,L) :
           if (((i-k)>=0 ) ):
               y1[i]=y1[i]+x[i-k]*h1[k]
   for i in range(0,L):#Фильтрация в канале согласованным с s0
       y0[i]=0.0
       for k in range(0,L) :
            if (((i-k)>=0 ) ):
                y0[i]=y0[i]+x[i-k]*h0[k]
   ind1 =0
   ind0 =0
   #Принятие вывода - что передавалось?            
   if y0[L-1]>y1[L-1]:
         ind0+=1
   else:
        ind1+=1
#---------------2  посылка   ------------------------------
   for i in range(0,L):# Формирование входного процесса
      x[i]=random.normalvariate(0,1)
      # Передаем либо 0  либо 1
      if jeks%2 ==1:
          x[i]=x[i]+ s1[i]
      else:
          x[i]=x[i]+ s0[i]
   for i in range(0,L):#Фильтрация в канале согласованным с s1
       y1[i]=0.0
       for k in range(0,L) :
           if (((i-k)>=0 ) ):
               y1[i]=y1[i]+x[i-k]*h1[k]
   for i in range(0,L):#Фильтрация в канале согласованным с s0
       y0[i]=0.0
       for k in range(0,L) :
            if (((i-k)>=0 ) ):
                y0[i]=y0[i]+x[i-k]*h0[k]
   #Принятие вывода - что передавалось?            
   if y0[L-1]>y1[L-1]:
         ind0+=1
   else:
        ind1+=1
#---------------------3 посылка --------------------
   for i in range(0,L):# Формирование входного процесса
      x[i]=random.normalvariate(0,1)
      # Передаем либо 0 - в  четных экспериментах, либо 1
      if jeks%2 ==1:
          x[i]=x[i]+ s1[i]
      else:
          x[i]=x[i]+ s0[i]
   for i in range(0,L):#Фильтрация в канале согласованным с s1
        y1[i]=0.0
        for k in range(0,L) :
           if (((i-k)>=0 ) ):
               y1[i]=y1[i]+x[i-k]*h1[k]
   for i in range(0,L):#Фильтрация в канале согласованным с s0
       y0[i]=0.0
       for k in range(0,L) :
            if (((i-k)>=0 ) ):
                y0[i]=y0[i]+x[i-k]*h0[k]
   #Принятие вывода - что передавалось?            
   if y0[L-1]>y1[L-1]:
         ind0+=1
   else:
        ind1+=1
#  ------------    вывод о том, что передавалось    
   if (jeks%2 ==1) and (ind1 < ind0):
      col+=1
   if (jeks%2 ==0) and (ind0 < ind1):
      col+=1  
print (' вероятность ошибки в процентах = ',col/M*100)