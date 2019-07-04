cmake_minimum_required(VERSION 3.10)
project(buffer-bench)

set(CMAKE_CXX_STANDARD 17)
# set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_GRPC_GRPCPP_UNSECURE grpc++_unsecure)
# add_definitions("-DGRPC_USE_PROTO_LITE")

# GRPC and Protocol Buffers libraries location
list(APPEND CMAKE_PREFIX_PATH "/opt/grpc" "/opt/protobuf" "/opt/protobuf")

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
list(APPEND LIBRARIES "/usr/lib/x86_64-linux-gnu/libglog.so.0")

find_package(ZLIB)
find_package(Protobuf)
find_package(GRPC)
# find_package(MyFlatC)

include_directories(${PROTOBUF_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB PROTOS "${CMAKE_CURRENT_SOURCE_DIR}/protobuf/*.proto")
file(GLOB FLATPROTOS "${CMAKE_CURRENT_SOURCE_DIR}/flatbuffer/*.fbs")

message("PROTOS=${PROTOS}")

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${CMAKE_CURRENT_BINARY_DIR} ${PROTOS})

# compile_flatbuffers_schema_to_cpp(${FLATPROTOS} ${CMAKE_CURRENT_BINARY_DIR} HEADERS_FBS)

#add_custom_command(
#        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}
#        COMMAND MAKE
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/flatbuffer)
#
#add_executable(fbbench_client IMPORTED)
#
#add_executable(fbbench_server IMPORTED)

########################

add_executable(${PROJECT_NAME}-pb-client
        protobuf/benchpb.h
        ${PROTO_SRCS}
        ${GRPC_SRCS}
        client-pb.cpp
        bench.h
        config.h)
target_include_directories(${PROJECT_NAME}-pb-client
        PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${GRPC_INCLUDE_DIR}
        )
target_link_libraries(${PROJECT_NAME}-pb-client
        PUBLIC
        ${ZLIB_LIBRARIES}
        ${_GRPC_GRPCPP_UNSECURE}
        ${PROTOBUF_LIBRARY}
        )

add_executable(${PROJECT_NAME}-pb-server
        protobuf/benchpb.h
        ${PROTO_SRCS}
        ${GRPC_SRCS}
        server-pb.cpp
        bench.h
        config.h)
target_include_directories(${PROJECT_NAME}-pb-server
        PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${GRPC_INCLUDE_DIR}
        )
target_link_libraries(${PROJECT_NAME}-pb-server
        PUBLIC
        ${ZLIB_LIBRARIES}
        ${_GRPC_GRPCPP_UNSECURE}
        ${PROTOBUF_LIBRARY}
        )

#############################

add_executable(${PROJECT_NAME}-raw-client
        raw/benchraw.h
        client-raw.cpp
        bench.h
        config.h)
target_link_libraries(${PROJECT_NAME}-raw-client
        PUBLIC
        ${ZLIB_LIBRARIES}
        evpp
        )

add_executable(${PROJECT_NAME}-raw-server
        raw/benchraw.h
        server-raw.cpp
        bench.h
        config.h)
target_include_directories(${PROJECT_NAME}-raw-server
        PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        )
target_link_libraries(${PROJECT_NAME}-raw-server
        PUBLIC
        ${ZLIB_LIBRARIES}
        evpp
        )