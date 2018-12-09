@echo off

rm -r bin

rm -r build

rmdir bin

rmdir build

mkdir bin

mkdir build

cd build

cmake .. -G "MSYS Makefiles"

make

move *.exe ..\bin\

cd ..
