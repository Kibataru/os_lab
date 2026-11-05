@echo off
git pull origin main
cmake -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build build
echo Run os_lab0.exe
pause
