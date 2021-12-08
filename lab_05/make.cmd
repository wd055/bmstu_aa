@ECHO OFF
CHCP 65001
g++ -c conveyor.cpp
g++ -c counter.cpp
g++ -c request.cpp
g++ -c main.cpp
g++ -o app.exe main.o conveyor.o counter.o request.o