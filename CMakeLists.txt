cmake_minimum_required(VERSION 3.25)
project(AoC_2022)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER clang++) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_executable(AoC_2022
    main.cpp
)

target_include_directories(AoC_2022 PUBLIC
    .
)

target_compile_options(AoC_2022
    INTERFACE
    -Wall
    -Wextra
    -Wpedantic
    -Wmissing-include-dirs
    -Wswitch-enum
    -Wconversion
    -Wno-sign-compare
)