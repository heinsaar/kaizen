@echo off
setlocal enabledelayedexpansion

:: Initialize variables to store any arguments
set ARG_CLOC=

:: Default to Debug build
set BUILD_TYPE=Debug

:: Parse named arguments
for %%a in (%*) do (
    if "%%~a"=="-cloc" (
        set ARG_CLOC=-cloc
    )
    if "%%~a"=="-debug" (
        set  BUILD_TYPE=Debug
    )
    if "%%~a"=="-release" (
        set  BUILD_TYPE=Release
    )
)

echo BUILD_TYPE=!BUILD_TYPE!

:: Build the CMake project
cmake --build . --config !BUILD_TYPE!
if ERRORLEVEL 1 (
  echo Build failed. Exiting.
  exit /b 1
)

:: Run the executable (will run the tests)
.\kaizen.exe -verbose %ARG_CLOC%