#!/usr/bin/python
from time import clock
import Pysh

print "Start: " + str(clock())
a = range(1000*1000*3)
print "Tuple created: " + str(clock())
Pysh.filterSH(a)
print "Tuple returned from c++: " + str(clock())
