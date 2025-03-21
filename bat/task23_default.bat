@echo off
cd ..

g++ task23_default.cpp -o executable/task23_default.exe -I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" -L"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" -lmsmpi
mpiexec -n 6 executable/task23_default.exe

PAUSE