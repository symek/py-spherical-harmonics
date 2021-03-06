#!/usr/bin/python
from time import clock
import Pysh
from array import array
from struct import unpack

def start(ar, size):
    """Basic performence test."""
    probe = Pysh.Probe(ar)
    print "Probe sent to c++: " + str(clock())
    x = probe.getProbeRef()
    print "Tuple returned from c++ by reference: " + str(clock())
    x = probe.getProbe()
    print "Tuple returned from c++ by value: " + str(clock())
    probe.prefilter()
    print "Probe prefiltered: " + str(clock())
    y = probe.getCoeffs()
    z = probe.getMatrix()
    print "Got matrices and coefficients: " + str(clock())
    del ar, probe
    print "Probe and array deleted: " + str(clock())
    return y, z

# Providing some input:
size = 1000
data = open("./grace_probe.float", 'rb').read()
data = unpack("%sf" % size*size*3, data)
print "Floats unpacked: %s" % clock()


# Perform a test:
coeffs, matrices = start(data, size)
#start(data, size)
#start(data, size)


"""
r = matrices[:16]
g = matrices[16:32]
b = matrices[32:]

print coeffs
print r
print g
print b

"""
print "------------------"
print "Probe::load() test: %s" % clock()

probe = Pysh.Probe()
print "Probe created: %s" % clock()
probe.load("./grace_probe.hdr")
print "Probe loaded: %s" % clock()
probe.prefilter()
print "Probe filtered: %s" % clock()
coeffs   = probe.getCoeffs()
matrices = probe.getMatrix()
print "Got matrices and coefficents: %s" % clock()












