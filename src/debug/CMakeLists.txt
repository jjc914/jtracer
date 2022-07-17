add_library(
    lib-debug STATIC
    bar.hpp bar.cpp
)

target_include_directories(lib-debug PUBLIC "${CMAKE_SOURCE_DIR}/src")