cmake_minimum_required(VERSION 3.10)

project(ProtoXEF_Server CXX)

set(SERVER_SRC
    src/main.cpp
)

add_executable(protoxef_server ${SERVER_SRC})

target_include_directories(protoxef_server PRIVATE ../shared)
target_link_libraries(protoxef_server PRIVATE protoxef_shared)
