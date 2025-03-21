@echo off
cd ..

g++ task24_reduce.cpp -o executable/task24_reduce.exe -I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" -L"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" -lmsmpi
mpiexec -n 6 executable/task24_reduce.exe

PAUSE