#pragma once

// Enum used to indicate the exit status of the run_solution function.
typedef enum solution_status {
    solution_not_found,
    solution_success,
    solution_failure
} solution_status;

// Run the solution for the given AoC day and part indices.
//
// day_index and part_index will be used as indices into the array of solution functions and
// therefore should be one less than the corresponding day and part numbers. The passed-in string
// buffer will have the computed answer written to it.
solution_status run_solution(
    const int day_index,
    const int part_index,
    char* const out_buffer,
    const int out_buffer_size
);
