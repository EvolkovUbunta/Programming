# -*- coding: UTF-8 -*-
import math
import pylab
import random
from matplotlib import mlab
mass1=[]
xlist = mlab.frange (1, 500, 1)
w=complex(1 ,0)
for k in range(1,501):
 x=complex(random.normalvariate(0, 10) ,random.normalvariate(0, 10))
 x2=x*complex(math.cos(-math.pi/6) ,math.sin(-math.pi/6))
 e=x+w*x2
 w=w-2*0.00005*e*x2.conjugate()
 mass1.append(e*e.conjugate())
pylab.plot (xlist, mass1)
pylab.show()