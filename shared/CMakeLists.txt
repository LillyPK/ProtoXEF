cmake_minimum_required(VERSION 3.10)
project(ProtoXEF_Shared CXX)

set(SHARED_SRC
    utils/example.cpp
    protocol/message.cpp
    window/window.cpp
)

set(SHARED_HEADERS
    window/window.hpp
    window/darkmode.hpp
)

add_library(protoxef_shared ${SHARED_SRC} ${SHARED_HEADERS})

# Public include directories so client and server can access them
target_include_directories(protoxef_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link against Windows libraries needed for Win32 API
target_link_libraries(protoxef_shared PUBLIC
    user32
    gdi32
    kernel32
    advapi32
    uxtheme    # <-- Just add this line
    dwmapi     # <-- And this for DWM effects
)
