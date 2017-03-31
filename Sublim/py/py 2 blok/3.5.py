# -*- coding: UTF-8 -*-
import math
import pylab
import random
from matplotlib import mlab
L=100 # Число отчетов сигнала
vh=[]# массив для входной последовательности сигнала с шумом
vih=[]# массив для модуля выходной последовательности сигнала с шумом
s=[]# массив для  сигнала
h=[]# массив для  импульсной характеристики согл. фильтра
vhmod=[]# массив для модуля входной последовательности сигнала с шумом
for i in range(0,L):
    if random.randint(0, 1)==1:
         s.append(complex(1,0))
    else:
         s.append(complex(-1,0))
for i in range(0,L):
   h.append(s[L-1-i].conjugate())
for i in range(0,500):
    x=complex(random.normalvariate(0, 0) ,random.normalvariate(0, 0))
    if i < 100 :
        x=x+s[i]
    vh.append(x);
    vhmod.append(abs(x));
for i in range(0,500):
    y=complex(0 ,0)
    for k in range(0,L) :
        if ((i-k)>=0  and (i-k)<L) :
             y=y+vh[i-k]*h[k]
    vih.append(abs(y));
xmin = 0
xmax = 499
xlist = mlab.frange (xmin, xmax, 1)
#Нарисуем график
pylab.plot (xlist, vih,xlist,vhmod)
#Покажем окно с нарисованным графиком
pylab.show()