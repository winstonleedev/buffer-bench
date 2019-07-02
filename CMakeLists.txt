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
# find_package(MyFlatC)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB PROTOS "${CMAKE_CURRENT_SOURCE_DIR}/protobuf/*.proto")
file(GLOB FLATPROTOS "${CMAKE_CURRENT_SOURCE_DIR}/flatbuffer/*.fbs")

message("PROTOS=${PROTOS}")

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${CMAKE_CURRENT_BINARY_DIR} ${PROTOS})

# compile_flatbuffers_schema_to_cpp(${FLATPROTOS} ${CMAKE_CURRENT_BINARY_DIR} HEADERS_FBS)

add_executable(${PROJECT_NAME}-fb-client
        flatbuffer/fbbench.cpp
        flatbuffer/fbbench.grpc.fb.cc
        flatbuffer/fbbench.grpc.fb.h
        flatbuffer/fbbench_generated.h
        client-fb.cpp
        bench.h
        config.h flatbuffer/fbbench.h)
target_include_directories(${PROJECT_NAME}-fb-client
        PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${GRPC_INCLUDE_DIR}
        )
target_link_libraries(${PROJECT_NAME}-fb-client
        PUBLIC
        ${ZLIB_LIBRARIES}
        ${_GRPC_GRPCPP_UNSECURE}
        flatbuffers
        )

add_executable(${PROJECT_NAME}-fb-server
        flatbuffer/fbbench.cpp
        flatbuffer/fbbench.grpc.fb.cc
        flatbuffer/fbbench.grpc.fb.h
        flatbuffer/fbbench_generated.h
        server-fb.cpp
        bench.h
        config.h flatbuffer/fbbench.h)
target_include_directories(${PROJECT_NAME}-fb-server
        PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${GRPC_INCLUDE_DIR}
        )
target_link_libraries(${PROJECT_NAME}-fb-server
        PUBLIC
        ${ZLIB_LIBRARIES}
        ${_GRPC_GRPCPP_UNSECURE}
        flatbuffers
        )

########################

add_executable(${PROJECT_NAME}-pb-client
        protobuf/benchpb.cpp
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
        ${Protobuf_LIBRARIES}
        ${_GRPC_GRPCPP_UNSECURE}
        )

add_executable(${PROJECT_NAME}-pb-server
        protobuf/benchpb.cpp
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
        ${Protobuf_LIBRARIES}
        ${_GRPC_GRPCPP_UNSECURE}
        )

#############################

add_executable(${PROJECT_NAME}-raw-client
        raw/benchraw.cpp
        client-raw.cpp
        bench.h
        config.h)
target_link_libraries(${PROJECT_NAME}-raw-client
        PUBLIC
        ${ZLIB_LIBRARIES}
        )

add_executable(${PROJECT_NAME}-raw-server
        raw/benchraw.cpp
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
        )