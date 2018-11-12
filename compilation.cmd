@echo off

cd build

cmake .. -G "MSYS Makefiles"

make

move *.exe ..\bin\

cd ..
