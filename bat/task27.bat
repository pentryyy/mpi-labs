@echo off
cd ..

g++ task27_child.cpp -o executable/task27_child.exe -I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" -L"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" -lmsmpi
g++ task27_parent.cpp -o executable/task27_parent.exe -I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" -L"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" -lmsmpi

mpiexec -np 1 executable/task27_parent.exe

PAUSE