@echo off

:: Устанавливаем значения по умолчанию
set TASK_NAME=
set NUM_PROCESSES=1

:: Разбор аргументов
:parse
if "%1"=="" goto endparse
if "%1"=="-task" (
    set TASK_NAME=task%2
    shift
)
if "%1"=="-n" (
    set NUM_PROCESSES=%2
    shift
)
shift
goto parse
:endparse

:: Проверяем, задан ли TASK_NAME
if "%TASK_NAME%"=="" (
    echo Using: run_task.bat -task TASK_NAME [-n NUM_PROCESSES]
    exit /b
)

:: Компиляция
g++ %TASK_NAME%.cpp -o executable/%TASK_NAME%.exe -I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" -L"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" -lmsmpi

:: Запуск с MPI
mpiexec -n %NUM_PROCESSES% executable/%TASK_NAME%.exe

PAUSE
