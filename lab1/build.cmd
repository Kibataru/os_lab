@echo off
chcp 65001 > nul
git pull origin main
cmake -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build build
echo Запуск утилиты:
.\build\test_runner.exe
pause