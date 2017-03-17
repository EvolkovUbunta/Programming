#!/usr/bin/env python
# -*- coding: UTF-8 -*-
#Импортируем библиотеку Math
import math
#Импортируем один из пакетов Matplotlib
import pylab
import random
#Импортируем пакет со вспомогательными функциями
from matplotlib import mlab
mass=[]  # массив для значений на выходе антенны 
xlist = mlab.frange (1, 500, 1)# набор итераций от 1 до 500-й
w=complex(1 ,0)# начальное значение весового коэффициента
d_lambda=0.5
for k in range(1,501):# 500 итераций
    # х1 - комплексное значение первой случайной помехи
    x1=complex(random.normalvariate(0, 10) ,random.normalvariate(0, 10))
    # х2 - комплексное значение второй случайной помехи
    x2=complex(random.normalvariate(0, 10) ,random.normalvariate(0, 10))
     # 1-я помехах с угла 30 градусов, 2-я с угла 45 градусов
     # x2elem - значения суммы помех во  втором антенном элементе
    fi=2*math.pi*d_lambda*math.sin(math.pi/180.0*30) 
    x2elem=x1*complex(math.cos(fi) ,math.sin(fi))
    fi=2*math.pi*d_lambda*math.sin(math.pi/180.0*45) 
    x2elem=x2elem+x2*complex(math.cos(fi) ,math.sin(fi))
     # x1elem - значения суммы помех во  1-м антенном элементе
    x1elem=x1+x2
    # e - значение на выходе АР
    e=x1elem+w*x2elem
    # e_osh - значение ошибки
    e_osh=-e
    w=w+2*0.0001*e_osh*x2elem.conjugate()
    mass.append(abs(e))
pylab.plot (xlist, mass)
#Покажем окно с нарисованным графиком
pylab.show()