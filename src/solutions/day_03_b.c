#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"
#include "string_stuff/engine_schematic.h"

// Day 3b: Parse the given engine schematic and sum all of the gear ratios.
bool day_03_b(char* const out_buffer, const int out_buffer_size) {
    int line_count = 0;
    char** lines = file_to_lines("day_03_string_array.txt", &line_count);
    // char** lines = file_to_lines("test.txt", &line_count);
    if (!lines) {
        fprintf(stderr, "❌ couldn't open input file\n");
        return false;
    }

    int sum_of_gear_ratios = sum_engine_gear_ratios(lines, line_count);
    free(lines);

    int ret = snprintf(out_buffer, out_buffer_size, "%d", sum_of_gear_ratios);
    if (ret <= 0 || ret >= out_buffer_size) {
        fprintf(stderr, "❌ couldn't fit result into output buffer\n");
        return false;
    }

    return true;
}
