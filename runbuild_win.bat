@echo off

:: Build the CMake project
cmake --build .
if ERRORLEVEL 1 (
  echo Build failed. Exiting.
  exit /b 1
)

:: Run the executable (will run the tests)
.\kaizen.exe -verbose