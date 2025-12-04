@echo off
setlocal

REM Move to script directory
cd /d %~dp0

REM Create build directory if missing
if not exist build (
    mkdir build
)

cd build

REM Configure
cmake ..

if %errorlevel% neq 0 (
    echo CMake configuration failed
    exit /b %errorlevel%
)

REM Build
cmake --build .

if %errorlevel% neq 0 (
    echo Build failed
    exit /b %errorlevel%
)

echo Build completed successfully
endlocal
