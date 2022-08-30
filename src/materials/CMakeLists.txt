add_subdirectory(microfacets)
add_subdirectory(fresnels)

add_library(
    lib-materials STATIC
    materials.hpp
    brdf.hpp brdf.cpp
    lambertian.hpp lambertian.cpp
    torrancesparrow.hpp torrancesparrow.cpp
)

target_include_directories(lib-materials PUBLIC "${CMAKE_SOURCE_DIR}/src")