@echo off
cd ..

g++ -fopenmp task31.cpp -o executable/task31.exe -I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" -L"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" -lmsmpi
mpiexec -n 6 executable/task31.exe

PAUSE