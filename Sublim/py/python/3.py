# -*- coding: UTF-8 -*-
import math
import pylab
import random
from matplotlib import mlab
# Создаем функцию для вычисления значения диаграммы направленности
# двухэлементной антенной решетки
def func (x,d_lambda,w):
     fi=2*math.pi*d_lambda*math.sin(math.pi/180.0*x)
     a=abs(complex(math.cos(fi),math.sin(fi))*w+1)
     return a
fi=2*math.pi*0.5*math.sin(math.pi/180.0*45)
w=complex(1 ,0)
for k in range(1,501):
    x=complex(random.normalvariate(0, 10) ,random.normalvariate(0, 10))
    x2=x*complex(math.cos(fi) ,math.sin(fi))
    e=x+w*x2
    w=w-2*0.00005*e*x2.conjugate()
xmin = -90.0
xmax = 90.0
dx = 0.5
xlist = mlab.frange (xmin, xmax, dx)
ylist = [func (x,0.5,w) for x in xlist]
#Нарисуем одномерный график
pylab.plot (xlist, ylist)
#Покажем окно с нарисованным графиком
pylab.show()