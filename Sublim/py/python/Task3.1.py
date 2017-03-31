#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import math
import pylab
from matplotlib import mlab
# Создаем функцию
def func (x):
 return math.exp(-math.pow(x,2))
# Рисуем график функции
# X Указываем наименьшее и наибольшее
xmin = -3.0
xmax = 3.0
# Шаг между точками по оси х
dx = 0.1
# Создадим список координат по оси
#X [-xmin; xmax] на отрезке
xlist = mlab.frange (xmin, xmax, dx)
# Вычислим значение функции в заданных точках
ylist = [func (x) for x in xlist]
# Нарисуем одномернfabs(sin(x)/x)фик
pylab.plot (xlist, ylist)
# Покажем окно с нарисованным графиком
pylab.show()