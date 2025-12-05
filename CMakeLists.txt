cmake_minimum_required(VERSION 3.10)

if(NOT WIN32)
    message(FATAL_ERROR "This project can only be built on Windows.")
endif()

project(ProtoXEF CXX)

# Turn on folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add subprojects
add_subdirectory(shared)
add_subdirectory(client)
add_subdirectory(server)
