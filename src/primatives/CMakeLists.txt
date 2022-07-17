add_library(
    lib-primatives STATIC
    primatives.hpp
    primative.hpp primative.cpp
    sphere.hpp sphere.cpp
    box.hpp box.cpp
)

target_include_directories(lib-primatives PUBLIC "${CMAKE_SOURCE_DIR}/src")