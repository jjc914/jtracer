add_library(
    lib-materials-fresnels STATIC
    fresnel.hpp fresnel.cpp
)

target_include_directories(lib-materials-fresnels PUBLIC "${CMAKE_SOURCE_DIR}/src")