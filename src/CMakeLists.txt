target_include_directories(
    aoc
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
    aoc
    PRIVATE
    file_io.c
    file_io.h
    main.c
)

add_subdirectory(solutions)
add_subdirectory(string_stuff)
