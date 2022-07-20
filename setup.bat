@ECHO OFF
cls
echo [31mBootstrapping vcpkg, downloading and building dependencies ...[0m
CMAKE -B build -S . -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake
echo [31mBootstrapping vcpkg, downloading and building dependencies complete.[0m
echo [31mBuilding target ...[0m
cmake . 
echo [31mBuild complete.[0m
echo [31mCompiling target ...[0m
cd build
cmake --build . --config Release
echo [31mCompilation complete.[0m
PAUSE