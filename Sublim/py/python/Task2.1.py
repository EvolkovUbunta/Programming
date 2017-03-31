#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import math
import pylab
from matplotlib import mlab
# Создаем функцию
def func (x):
 return (10* math.log(math.fabs(math.sin(x)/x)))
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
ylist = [func (x) for x in xlist]
# Нарисуем одномернfabs(sin(x)/x)фик
pylab.plot (xlist, ylist)
# Покажем окно с нарисованным графиком
pylab.show()

