cmake_minimum_required(VERSION 3.24)
project(advent_of_code_2023 VERSION 0.1.0 LANGUAGES C)

add_executable(
    aoc
)

target_compile_features(aoc PUBLIC c_std_17)
target_compile_options(aoc PUBLIC -Wall -Wextra -Werror -Wpedantic)

add_subdirectory(resources)
add_subdirectory(src)
