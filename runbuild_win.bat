@echo off
setlocal enabledelayedexpansion

:: Initialize variables to store any arguments
set ARG_CLOC=

:: Build the CMake project
cmake --build .
if ERRORLEVEL 1 (
  echo Build failed. Exiting.
  exit /b 1
)

:: Parse named arguments
for %%a in (%*) do (
    if "%%~a"=="-cloc" (
        set ARG_CLOC=-cloc
    )
)

:: Run the executable (will run the tests)
.\kaizen.exe -verbose %ARG_CLOC%