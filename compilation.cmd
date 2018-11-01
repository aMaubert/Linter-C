@echo off

mkdir build

cd build

cmake .. -G "MSYS Makefiles"

make

move *.exe ..\bin\

cd ..




