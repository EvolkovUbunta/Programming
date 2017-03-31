#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import math
import pylab
from matplotlib import mlab
# Создаем функцию
def func1 (x):
 return 10*math.log(math.fabs(math.sin(1*x)/(1*x)))
def func2 (x):
 return 10*math.log(math.fabs(math.sin(3*x)/(3*x)))
# Рисуем график функции
# X Указываем наименьшее и наибольшее
xmin = -20.0
xmax = 20.0
# Шаг между точками по оси х
dx = 0.1
# Создадим список координат по оси
#X [-xmin; xmax] на отрезке
xlist = mlab.frange (xmin, xmax, dx)
# Вычислим значение функции в заданных точках
ylist1 = [func1 (x) for x in xlist]
ylist2 = [func2 (x) for x in xlist]
# Нарисуем одномернfabs(sin(x)/x)фик
pylab.plot (xlist, ylist1, xlist, ylist2)
# Покажем окно с нарисованным графиком
pylab.show()