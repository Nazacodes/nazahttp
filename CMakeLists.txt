cmake_minimum_required(VERSION 3.30)
project(nazahttp)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(nazahttp
    src/main.cpp
    src/request.cpp
    src/request.h
    src/response.cpp
    src/response.h
    src/server.cpp
    src/server.h)


target_link_libraries(nazahttp PRIVATE ws2_32)


set(SOURCE_FILES src/main.cpp)
add_executable(server_client ${SOURCE_FILES})