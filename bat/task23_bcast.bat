@echo off
cd ..

g++ task23_bcast.cpp -o executable/task23_bcast.exe -I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" -L"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" -lmsmpi
mpiexec -n 6 executable/task23_bcast.exe

PAUSE