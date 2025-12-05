cmake_minimum_required(VERSION 3.10)
project(ProtoXEF_Client CXX)

set(CLIENT_SRC
    src/main.cpp
)

# Add WIN32 flag for GUI application
add_executable(protoxef_client WIN32 ${CLIENT_SRC})

target_include_directories(protoxef_client PRIVATE ../shared)
target_link_libraries(protoxef_client PRIVATE protoxef_shared)

# Optional: Enable console window in Debug builds for debugging
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(protoxef_client PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
endif()
