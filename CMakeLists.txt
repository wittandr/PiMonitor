cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 20)
project(PiMonitor VERSION 0.1.0)

find_package(gRPC CONFIG REQUIRED)

FILE(GLOB_RECURSE INCLUDE_SERVER ${CMAKE_SOURCE_DIR}/server/include/*)
FILE(GLOB_RECURSE SOURCE_SERVER ${CMAKE_SOURCE_DIR}/server/src/*)
FILE(GLOB_RECURSE INCLUDE_CLIENT ${CMAKE_SOURCE_DIR}/client/include/*)
FILE(GLOB_RECURSE SOURCE_CLIENT ${CMAKE_SOURCE_DIR}/client/src/*)
FILE(GLOB_RECURSE SOURCE_PROTO ${CMAKE_SOURCE_DIR}/protos/generated/*.cc)
FILE(GLOB_RECURSE INCLUDE_PROTO ${CMAKE_SOURCE_DIR}/protos/generated/*.h)

source_group(TREE ${CMAKE_SOURCE_DIR}/server/src FILES ${SOURCE_SERVER})
source_group(TREE ${CMAKE_SOURCE_DIR}/server/include FILES ${INCLUDE_SERVER})
source_group(TREE ${CMAKE_SOURCE_DIR}/client/src FILES ${SOURCE_CLIENT})
source_group(TREE ${CMAKE_SOURCE_DIR}/client/include FILES ${INCLUDE_CLIENT})
source_group(TREE ${CMAKE_SOURCE_DIR}/protos/generated FILES ${SOURCE_PROTO})
source_group(TREE ${CMAKE_SOURCE_DIR}/protos/generated FILES ${INCLUDE_PROTO})

add_executable(PiMonitorServer ${SOURCE_SERVER} ${INCLUDE_SERVER} ${SOURCE_PROTO} ${INCLUDE_PROTO})
add_executable(PiMonitorClient ${SOURCE_CLIENT} ${INCLUDE_CLIENT} ${SOURCE_PROTO} ${INCLUDE_PROTO})

set_property(TARGET PiMonitorClient PROPERTY CXX_STANDARD 17)
set_property(TARGET PiMonitorServer PROPERTY CXX_STANDARD 17)
list(APPEND INCLUDE_LIST_SERVER
	${PROJECT_SOURCE_DIR}/server/include
	${CMAKE_SOURCE_DIR}/protos/generated
	)
list(APPEND INCLUDE_LIST_CLIENT
	${PROJECT_SOURCE_DIR}/client/include
	${CMAKE_SOURCE_DIR}/protos/generated
	)
	
target_include_directories(PiMonitorServer PUBLIC ${INCLUDE_LIST_SERVER})
target_include_directories(PiMonitorClient PUBLIC ${INCLUDE_LIST_CLIENT})

target_link_libraries(PiMonitorServer PRIVATE gRPC::grpc++)
target_link_libraries(PiMonitorClient PRIVATE gRPC::grpc++)