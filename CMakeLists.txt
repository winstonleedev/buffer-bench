cmake_minimum_required(VERSION 3.10)
project(buffer-bench)

set(CMAKE_CXX_STANDARD 17)
# set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_GRPC_GRPCPP_UNSECURE grpc++_unsecure)
# add_definitions("-DGRPC_USE_PROTO_LITE")

# GRPC and Protocol Buffers libraries location
list(APPEND CMAKE_PREFIX_PATH "/opt/grpc" "/opt/protobuf")

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(ZLIB)
find_package(Protobuf)
find_package(GRPC)
find_package(FlatC)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB PROTOS "${CMAKE_CURRENT_SOURCE_DIR}/protobuf/*.proto")
file(GLOB FLATPROTOS "${CMAKE_CURRENT_SOURCE_DIR}/flatbuffer/*.fbs")

message("PROTOS=${PROTOS}")
message("FLATPROTOS=${FLATPROTOS}")

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${CMAKE_CURRENT_BINARY_DIR} ${PROTOS})
compile_flatbuffers_schema_to_cpp(${FLATPROTOS} ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME}-client
        client.cpp
        flatbuffer/FBBench.cpp
        flatbuffer/bench_generated.h
        protobuf/benchpb.cpp
        ${PROTO_SRCS}
        ${GRPC_SRCS}
        bench.h
        raw/benchraw.cpp
        config.h)
target_include_directories(${PROJECT_NAME}-client
        PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${GRPC_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME}-client
        ${ZLIB_LIBRARIES}
        ${Protobuf_LIBRARIES}
        ${_GRPC_GRPCPP_UNSECURE}
)

add_executable(${PROJECT_NAME}-server
        client.cpp
        flatbuffer/FBBench.cpp
        flatbuffer/bench_generated.h
        protobuf/benchpb.cpp
        ${PROTO_SRCS}
        ${GRPC_SRCS}
        bench.h
        raw/benchraw.cpp
        config.h)
target_include_directories(${PROJECT_NAME}-server
        PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${GRPC_INCLUDE_DIR}
        )
target_link_libraries(${PROJECT_NAME}-server
        ${ZLIB_LIBRARIES}
        ${Protobuf_LIBRARIES}
        ${_GRPC_GRPCPP_UNSECURE}
        )