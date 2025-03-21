@echo off
cd ..

g++ task19.cpp -o executable/task19.exe -I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" -L"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" -lmsmpi
mpiexec -n 6 executable/task19.exe

PAUSE