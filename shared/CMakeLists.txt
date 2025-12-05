cmake_minimum_required(VERSION 3.10)
project(ProtoXEF_Shared CXX)

set(SHARED_SRC
    utils/example.cpp
    protocol/message.cpp
    window/window.cpp  # Add window creation code here
)

add_library(protoxef_shared ${SHARED_SRC})

# Public include directories so client and server can access them
target_include_directories(protoxef_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link against Windows libraries needed for Win32 API
target_link_libraries(protoxef_shared PUBLIC
    user32      # For window creation and message handling
    gdi32       # For graphics device interface
    kernel32    # For core Windows functions
)
