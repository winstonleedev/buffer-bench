cmake_minimum_required(VERSION 3.10)
project(flatbuffers_bench)

set(CMAKE_CXX_STANDARD 17)

find_package(ZLIB)
find_package(Protobuf)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME}
        main.cpp
        flatbuffer/FBBench.cpp
        flatbuffer/bench_generated.h
        protobuf/benchpb.cpp
        protobuf/bench.pb.h
        protobuf/bench.pb.cc
        bench.h
        raw/benchraw.cpp)

target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES} ${Protobuf_LIBRARIES})