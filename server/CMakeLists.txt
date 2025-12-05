cmake_minimum_required(VERSION 3.10)
project(ProtoXEF_Server CXX)

set(SERVER_SRC
    src/main.cpp
)

# Add WIN32 flag for GUI application
add_executable(protoxef_server WIN32 ${SERVER_SRC})

target_include_directories(protoxef_server PRIVATE ../shared)
target_link_libraries(protoxef_server PRIVATE protoxef_shared)

# Optional: Enable console window in Debug builds for debugging
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(protoxef_server PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
endif()
