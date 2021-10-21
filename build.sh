#! /usr/bin/sh
mkdir -vp build

echo creating objects and libraries
g++ $@ -fPIC -c -o build/sc.o src/*.cc -Iheaders
g++ -shared -o build/libsc.so build/sc.o
ar rs build/libsc.a build/sc.o

mkdir -vp bin
mv build/libsc.so bin/ -v
mv build/libsc.a bin/ -v
rm -rf build -v

echo done