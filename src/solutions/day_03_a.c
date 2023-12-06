#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"
#include "string_stuff/engine_schematic.h"

// Day 3a: Parse the given engine schematic and sum all of the part numbers.
bool day_03_a(char* const out_buffer, const int out_buffer_size) {
    int line_count = 0;
    char** lines = file_to_lines("day_03_string_array.txt", &line_count);
    if (!lines) {
        fprintf(stderr, "❌ couldn't open input file\n");
        return false;
    }

    int sum_of_part_numbers = sum_engine_part_numbers(lines, line_count);
    free(lines);

    int ret = snprintf(out_buffer, out_buffer_size, "%d", sum_of_part_numbers);
    if (ret <= 0 || ret >= out_buffer_size) {
        fprintf(stderr, "❌ couldn't fit result into output buffer\n");
        return false;
    }

    return true;
}
