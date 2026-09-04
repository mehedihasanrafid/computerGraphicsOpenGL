$ErrorActionPreference = "Stop"

cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel

Write-Host "Build complete: .\build\yacht_journey.exe"
