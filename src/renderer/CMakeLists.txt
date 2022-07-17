add_library(
    lib-renderer STATIC
    renderer.hpp
    screen.hpp screen.cpp
    camera.hpp camera.cpp
)

target_include_directories(lib-renderer PUBLIC "${CMAKE_SOURCE_DIR}/src")