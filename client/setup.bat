@ECHO OFF
cls
echo [31mDownloading and building dependencies ...[0m
CMAKE -B build -S . -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake -A x64
echo [31mBootstrapping vcpkg, downloading and building dependencies complete.[0m
echo [31mRunning protoc ...[0m
set tools=build/vcpkg_installed/x64-windows/tools
set plugin=%tools%/grpc/grpc_cpp_plugin.exe
set protoc=%tools%/protobuf/protoc.exe
rmdir /s /q "../protos/generated"
mkdir "../protos/generated"
@ECHO ON
start /B /wait %protoc% -I ../protos --grpc_out=../protos/generated --cpp_out=../protos/generated --plugin=protoc-gen-grpc=%plugin% ../protos/*
@ECHO OFF
echo [31mprotoc complete.[0m
echo [31mBuilding target ...[0m
cmake . 
echo [31mBuild complete.[0m
echo [31mCompiling target ...[0m
cd build
cmake --build . --config Release --target 
echo [31mCompilation complete.[0m
cd ..
PAUSE
