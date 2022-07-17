add_library(
    lib-materials STATIC
    materials.hpp
    brdf.hpp brdf.cpp
    lambertian.hpp lambertian.cpp
    beckspizz.hpp beckspizz.cpp
)

target_include_directories(lib-materials PUBLIC "${CMAKE_SOURCE_DIR}/src")