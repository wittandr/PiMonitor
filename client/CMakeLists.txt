cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 20)
project(PiMonitor VERSION 0.1.0)
find_package(gRPC CONFIG REQUIRED)


FILE(GLOB_RECURSE INCLUDE_CLIENT ${CMAKE_SOURCE_DIR}/include/*)
FILE(GLOB_RECURSE SOURCE_CLIENT ${CMAKE_SOURCE_DIR}/src/*)
FILE(GLOB_RECURSE SOURCE_PROTO ${CMAKE_SOURCE_DIR}/../protos/generated/*.cc)
FILE(GLOB_RECURSE INCLUDE_PROTO ${CMAKE_SOURCE_DIR}/../protos/generated/*.h)

source_group(TREE ${CMAKE_SOURCE_DIR}/src FILES ${SOURCE_CLIENT})
source_group(TREE ${CMAKE_SOURCE_DIR}/include FILES ${INCLUDE_CLIENT})
source_group(TREE ${CMAKE_SOURCE_DIR}/../protos/generated FILES ${SOURCE_PROTO})
source_group(TREE ${CMAKE_SOURCE_DIR}/../protos/generated FILES ${INCLUDE_PROTO})

add_executable(PiMonitorClient ${SOURCE_CLIENT} ${INCLUDE_CLIENT} ${SOURCE_PROTO} ${INCLUDE_PROTO})

set_property(TARGET PiMonitorClient PROPERTY CXX_STANDARD 17)

list(APPEND INCLUDE_LIST_CLIENT
	${PROJECT_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/../protos/generated
	)
	
target_include_directories(PiMonitorClient PUBLIC ${INCLUDE_LIST_CLIENT})

target_link_libraries(PiMonitorClient PRIVATE gRPC::grpc++)