cmake_minimum_required(VERSION 3.10)

project(ProtoXEF CXX)

# Turn on folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add subprojects
add_subdirectory(shared)
add_subdirectory(client)
add_subdirectory(server)
