cmake_minimum_required(VERSION 3.10)
project(flatbuffers_bench)

set(CMAKE_CXX_STANDARD 17)

# GRPC and Protocol Buffers libraries location
list(APPEND CMAKE_PREFIX_PATH "/opt/grpc" "/opt/protobuf")

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(ZLIB)
find_package(Protobuf)
find_package(GRPC)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB PROTOS "${CMAKE_CURRENT_SOURCE_DIR}/protobuf/*.proto")

message("PROTOS=${PROTOS}")

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${CMAKE_CURRENT_BINARY_DIR} {PROTOS})

add_executable(${PROJECT_NAME}
        main.cpp
        flatbuffer/FBBench.cpp
        flatbuffer/bench_generated.h
        protobuf/benchpb.cpp
        ${PROTO_SRCS}
        bench.h
        raw/benchraw.cpp
)
target_include_directories(${PROJECT_NAME}
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/protobuf"
        "${CMAKE_CURRENT_SOURCE_DIR}/flatbuffer"
        "${CMAKE_CURRENT_SOURCE_DIR}/raw"
        ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(${PROJECT_NAME}
        ${ZLIB_LIBRARIES}
        ${Protobuf_LIBRARIES}
        ${GRPC_LIBRARIES}
)