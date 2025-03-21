@echo off
cd ..

g++ -fopenmp task30.cpp -o executable/task30.exe -I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" -L"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" -lmsmpi
mpiexec -n 6 executable/task30.exe

PAUSE