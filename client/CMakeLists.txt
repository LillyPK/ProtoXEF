cmake_minimum_required(VERSION 3.10)

project(ProtoXEF_Client CXX)

set(CLIENT_SRC
    src/main.cpp
)

add_executable(protoxef_client ${CLIENT_SRC})

target_include_directories(protoxef_client PRIVATE ../shared)
target_link_libraries(protoxef_client PRIVATE protoxef_shared)
