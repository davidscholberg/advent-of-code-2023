#include <stdio.h>
#include <stdlib.h>

#include "solutions/run.h"

#define computed_answer_buffer_size 1024

int main(const int argc, const char** const argv) {
    static const char* const usage = "usage: %s challenge_id (e.g. ./build/aoc 1a)\n";

    if (argc != 2) {
        fprintf(stderr, "❌ invalid number of arguments\n");
        fprintf(stderr, usage, argv[0]);
        return EXIT_FAILURE;
    }

    int day = 0;
    char part_id = 0;
    if (sscanf(argv[1], "%d%c", &day, &part_id) != 2) {
        fprintf(stderr, "❌ invalid challenge id '%s'\n", argv[1]);
        fprintf(stderr, usage, argv[0]);
        return EXIT_FAILURE;
    }

    int part = 0;
    if (part_id == 'a' || part_id == 'A') {
        part = 1;
    } else if (part_id == 'b' || part_id == 'b') {
        part = 2;
    } else {
        fprintf(stderr, "❌ invalid part id '%c'\n", part_id);
        fprintf(stderr, usage, argv[0]);
        return EXIT_FAILURE;
    }

    char computed_answer[computed_answer_buffer_size];
    const solution_status status =
        run_solution(day - 1, part - 1, computed_answer, computed_answer_buffer_size);
    if (status == solution_not_found) {
        fprintf(stderr, "❌ solution not found for challenge id %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    if (status == solution_failure) {
        fprintf(stderr, "❌ solution failed for challenge id %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("challenge %s\n", argv[1]);
    printf("computed answer: %s\n", computed_answer);

    return EXIT_SUCCESS;
}
