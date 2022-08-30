add_library(
    lib-math STATIC
    math.hpp math.cpp
    vec2.hpp vec2.cpp
    vec3.hpp vec3.cpp
    mat3x3.hpp mat3x3.cpp
    color.hpp color.cpp
    ray.hpp ray.cpp
    rayhit.hpp rayhit.cpp
)

target_include_directories(lib-math PUBLIC "${CMAKE_SOURCE_DIR}/src")