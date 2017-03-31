# -*- coding: UTF-8 -*-
import math
import pylab
import random
from matplotlib import mlab
L=20 # длительность сигнала и импульсной характеристики фильтра
N=100 # длительность входного процесса
s=[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1] # массив отсчетов импульсной характеристики
h=[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1] # массив отсчетов импульсной характеристики
x=[] # входной процесс
y=[]# выходной процесс
for i in range(0,N):# формирование входного процесса
    x.append(random.normalvariate(0,2))
    if i < L :
        x[i]=x[i]+ s[i]  # добавление сигнала в начале интервала
# процесс фильтрации  
for i in range(0,N):
    y.append(0)
    for k in range(0,L) :
        if ((i-k)>=0  ):
             y[i]=y[i]+x[i-k]*h[k]# процесс фильтрации
xmin = 0
xmax = N-1
xlist = mlab.frange (xmin, xmax, 1)
#Нарисуем график
pylab.plot (xlist,x,xlist,y)
#Покажем окно с нарисованным графиком
pylab.show()