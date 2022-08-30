add_library(
    lib-materials-microfacets STATIC
    microfacetdistribution.hpp microfacetdistribution.cpp
    beckmannspizzichino.hpp beckmannspizzichino.cpp
)

target_include_directories(lib-materials-microfacets PUBLIC "${CMAKE_SOURCE_DIR}/src")