#include <stdbool.h>
#include <stdlib.h>

#include "run.h"
#include "solutions.h"

// Function pointer type for solution functions.
//
// A solution function is a function that solves a specific AoC challenge. The inputs are a string
// buffer and size. The function is meant to write the computed answer to the string buffer. The
// return value tells if the function succeeded or not.
typedef bool (*solution_fn)(char* const, const int);

#define part_count 2

static const solution_fn solutions[][part_count] = {
    {day_01_a, day_01_b},
};

static const int day_count = sizeof(solutions) / sizeof(solutions[0]);

solution_status run_solution(
    const int day_index,
    const int part_index,
    char* const out_buffer,
    const int out_buffer_size
) {
    if (day_index < 0 || day_index >= day_count) {
        return solution_not_found;
    }

    solution_fn solution_ptr = solutions[day_index][part_index];

    if (!solution_ptr) {
        return solution_not_found;
    }

    return solution_ptr(out_buffer, out_buffer_size) ? solution_success : solution_failure;
}
