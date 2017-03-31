#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import math
import pylab
from matplotlib import mlab
# Создаем функцию
def func (x):
 return math.sin (x)/(x)
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
# Нарисуем одномерный график
pylab.plot (xlist, ylist)
# Покажем окно с нарисованным графиком
pylab.show()