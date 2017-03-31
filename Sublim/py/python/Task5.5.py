# -*- coding: UTF-8 -*-
import math
import pylab
from matplotlib import mlab
# Создаем функцию для вычисления значения диаграммы направленности
# n-элементной антенной решетки
# x - угол в градусах d_lambda - отношение расстояния между элементами к длине волны
def func (x,d_lambda,n):
 mass1=[]
 xlist = mlab.frange (1, 500, 1)
 w=complex(1,0)
 fi=2*math.pi*d_lambda*math.sin(math.pi/180.0*x)
 for i in range(1,n+1):
 	x=complex(random.normalvariate(0, 10) ,random.normalvariate(0, 10))
 x2=x*complex(math.cos(-math.pi/4) ,math.sin(-math.pi/4))
 e=x+w*x2
 w=w-2*0.00005*e*x2.conjugate()
 w=w+complex(math.cos(fi*(i-1)),math.sin(fi*(i-1)))
 a=abs(w)
 mass1.append(e*e.conjugate())
 return mass1
#Указываем X наименьшее и наибольшее
xmin = -90.0
xmax = 90.0
# Шаг между точками по оси х полградуса
dx = 0.5
#Создадим список координат по оси
#X на отрезке [-xmin; xmax]
xlist = mlab.frange (xmin, xmax, dx)
ylist = [func (x,0.5,5) for x in xlist]
# Вычислим значение функции в заданных точках
#Нарисуем одномерный график
pylab.plot (xlist, mass1)
#Покажем окно с нарисованным графиком
pylab.show()