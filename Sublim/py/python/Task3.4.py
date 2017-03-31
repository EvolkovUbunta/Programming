# -*- coding: UTF-8 -*-
import math
import pylab
from matplotlib import mlab
# Создаем функцию для вычисления значения диаграммы направленности
# n-элементной антенной решетки
# x - угол в градусах d_lambda - отношение расстояния между элементами к длине волны
def func1 (x,d_lambda,n):
 a_tetta=complex(0.0,0.0)
 fi=2*math.pi*d_lambda*math.sin(math.pi/180.0*x)
 fisig=2*math.pi*d_lambda*math.sin(math.pi/180.0*(-45))
 for i in range(1,n+1):
 	w=complex(math.cos(fisig*(i-1)),-math.sin(fisig*(i-1)))
 	a_tetta=a_tetta+complex(math.cos(fi*(i-1)),math.sin(fi*(i-1)))*w
 a=abs(a_tetta)
 return a
def func2 (x,d_lambda,n):
 a_tetta=complex(0.0,0.0)
 fi=2*math.pi*d_lambda*math.sin(math.pi/180.0*x)
 fisig=2*math.pi*d_lambda*math.sin(math.pi/180.0*(-45))
 fisig= fisig - fisig*0.2
 for i in range(1,n+1):
 	w=complex(math.cos(fisig*(i-1)),-math.sin(fisig*(i-1)))
 	a_tetta=a_tetta+complex(math.cos(fi*(i-1)),math.sin(fi*(i-1)))*w
 a=abs(a_tetta)
 return a
#Указываем X наименьшее и наибольшее
xmin = -90.0
xmax = 90.0
# Шаг между точками по оси х полградуса
dx = 0.5
#Создадим список координат по оси
#X на отрезке [-xmin; xmax]
xlist = mlab.frange (xmin, xmax, dx)
# Вычислим значение функции в заданных точках
ylist1 = [func1 (x,0.5,7) for x in xlist]
ylist2 = [func2 (x,0.5,7) for x in xlist]
#Нарисуем одномерный график
pylab.plot (xlist, ylist1, xlist, ylist2)
#Покажем окно с нарисованным графиком
pylab.show()