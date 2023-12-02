set(
    resources
    day_01_a_string_array.txt
)
foreach(resource IN LISTS resources)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${resource}
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/${resource}
            ${CMAKE_CURRENT_BINARY_DIR}/${resource}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${resource}
    )
endforeach()
list(TRANSFORM resources PREPEND ${CMAKE_CURRENT_BINARY_DIR}/)
add_custom_target(copy_resources ALL DEPENDS ${resources})
add_dependencies(aoc copy_resources)
