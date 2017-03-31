# -*- coding: UTF-8 -*-
import math
import pylab
from matplotlib import mlab
# Создаем функцию для вычисления значения диаграммы направленности
# двухэлементной антенной решетки
# x - d_lambda - угол в градусах отношение расстояния между элементами к длине волны
def func1 (x,d_lambda):
 fi=2*math.pi*d_lambda*math.sin(math.pi/180.0*x)
 a=abs(complex(math.cos(fi),math.sin(fi))+1)
 a=10*math.log10(a**2/4)
 return a
def func2 (x,d_lambda):
 fi=2*math.pi*d_lambda*math.sin(math.pi/180.0*x)
 a=abs(complex(math.cos(fi),math.sin(fi))+1)
 a=10*math.log10(a**2/4)
 return a
# функция направленности элементов
def func3(x):
 f = math.exp(-math.pow(x,2)/math.pow(20,2))
 return f
# X Указываем наименьшее и наибольшее
xmin = -85.0
xmax = 85.0
# Шаг между точками по оси х полградуса
dx = 0.5
# Создадим список координат по оси
#X [-xmin; xmax] на отрезке
xlist = mlab.frange (xmin, xmax, dx)
# Вычислим значение функции в заданных точках
ylist1 = [func1 (x,0.5) for x in xlist]
ylist2 = [func2 (x,2) for x in xlist]
ylist3 = [func3 (x) for x in xlist]
# Нарисуем одномерный график
pylab.plot (xlist, ylist1, xlist, ylist2, xlist, ylist3)
# Покажем окно с нарисованным графиком
pylab.show()