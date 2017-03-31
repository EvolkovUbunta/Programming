#!/usr/bin/env python
# -*- coding: UTF-8 -*-
#Импортируем библиотеку Math
import math
#Импортируем один из пакетов Matplotlib
import pylab
import random
#Импортируем пакет со вспомогательными функциями
from matplotlib import mlab
def func (x,d_lambda,w1,w2):
     fi=2*math.pi*d_lambda*math.sin(math.pi/180.0*x)
     a=abs(complex(math.cos(fi),math.sin(fi))*w1+complex(math.cos(2*fi),math.sin(2*fi))*w2+1)
     return a
w1=complex(1 ,0)# начальное значение 1-го весового коэффициента
w2=complex(1 ,0)# начальное значение 2-го весового коэффициента
w3=complex(1, 0)# начальное значение 3-го весового коэффициента 
d_lambda=0.5
for k in range(1,701):# 500 итераций
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
    # x2elem - значения суммы помех во  третьем антенном элементе
    fi=2*2*math.pi*d_lambda*math.sin(math.pi/180.0*30) 
    x3elem=x1*complex(math.cos(fi) ,math.sin(fi))
    fi=2*2*math.pi*d_lambda*math.sin(math.pi/180.0*45) 
    x3elem=x3elem+x2*complex(math.cos(fi) ,math.sin(fi))
    # x4elem - значение суммы помех в четвертом антенном элементе 
    fi=2*2*math.pi*d_lambda*math.sin(math.pi/180.0*30) 
    x4elem=x1*complex(math.cos(fi) ,math.sin(fi))
    fi=2*2*math.pi*d_lambda*math.sin(math.pi/180.0*45) 
    x4elem=x4elem+x2*complex(math.cos(fi) ,math.sin(fi))
     # x1elem - значения суммы помех во  1-м антенном элементе
    x1elem=x1+x2
    # e - значение на выходе АР
    e=x1elem+w1*x2elem+w2*x3elem+w3*x4elem
    # e_osh - значение ошибки
    e_osh=-e
    w1=w1+2*0.0003*e_osh*x2elem.conjugate()
    w2=w2+2*0.0003*e_osh*x3elem.conjugate()
    w23=w3+2*0.0003*e_osh*x4elem.conjugate()
xmin = -90.0
xmax = 90.0
dx = 0.5
xlist = mlab.frange (xmin, xmax, dx)
ylist = [func (x,0.5,w1,w2) for x in xlist]
#Нарисуем одномерный график
pylab.plot (xlist, ylist)
#Покажем окно с нарисованным графиком
pylab.show()