echo [31mDownloading and building dependencies ...[0m
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake -A x64
echo [31mBootstrapping vcpkg, downloading and building dependencies complete.[0m
echo [31mRunning protoc ...[0m
tools="vcpkg_installed/x64-linux/tools"
plugin=$tools"/grpc/grpc_cpp_plugin"
protoc=$tools"/protobuf/protoc"
rmdir ../protos/generated
mkdir ../protos/generated
protofiles=$(find ../protos/ -name "*.proto")
$protoc --grpc_out=../protos/generated --cpp_out=../protos/generated --plugin=protoc-gen-grpc=$plugin -I protos $protofiles
echo [31mprotoc complete.[0m
echo [31mBuilding target ...[0m
cmake . -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake
echo [31mBuild complete.[0m
echo [31mCompiling target ...[0m
cd build
cmake --build . --config Release
echo [31mCompilation complete.[0m
cd ..
