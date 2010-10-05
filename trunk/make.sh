# Pretty nasty build script, but I think it's ok for a moment.
# Build:
swig -c++ -python src/pysh.i
g++ -g -Wno-deprecated -fPIC -c  src/pysh.cpp src/rgbe.cpp src/pysh_wrap.cxx -I /usr/include/python2.6
g++ -shared -Wl,-soname,_pysh.so -o _pysh.so pysh.o rgbe.o pysh_wrap.o

# Clean up:
rm -rf Pysh
mkdir Pysh
touch Pysh/__init__.py
echo "from pysh import *" > Pysh/__init__.py
mv _pysh.so Pysh
mv src/pysh.py Pysh
rm pysh.o pysh_wrap.o src/pysh_wrap.cxx rgbe.o

#ld -shared sh.o sh_wrap.o -o _sh.so
