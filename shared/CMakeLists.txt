cmake_minimum_required(VERSION 3.10)

project(ProtoXEF_Shared CXX)

set(SHARED_SRC
    utils/example.cpp
    protocol/message.cpp
)

add_library(protoxef_shared ${SHARED_SRC})

target_include_directories(protoxef_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
