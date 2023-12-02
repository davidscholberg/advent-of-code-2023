#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"

#define ascii_digit_to_int(digit) (digit - 48)

// Day 1a: Take the strings from the input file and build a two-digit number for each line where the
// digits are the first and last digits contained in the string, and sum these numbers.
bool day_01_a(char* const out_buffer, const int out_buffer_size) {
    int line_count = 0;
    char** lines = file_to_lines("day_01_a_string_array.txt", &line_count);
    if (!lines) {
        fprintf(stderr, "❌ couldn't open input file\n");
        return false;
    }

    int sum = 0;
    for (int i = 0; i < line_count; i++) {
        // Determine the first and last numerical digit characters in the current string.
        char first_digit_char = 0;
        char last_digit_char = 0;
        for (int j = 0; j < (int)strlen(lines[i]); j++) {
            char current_char = lines[i][j];
            if (current_char >= '0' && current_char <= '9') {
                if (first_digit_char == 0) {
                    first_digit_char = current_char;
                    last_digit_char = current_char;
                } else {
                    last_digit_char = current_char;
                }
            }
        }

        // Convert the first and last digit characters into a two digit number and add it to the
        // sum.
        sum += (ascii_digit_to_int(first_digit_char) * 10) + ascii_digit_to_int(last_digit_char);
    }

    free(lines);

    int ret = snprintf(out_buffer, out_buffer_size, "%d", sum);
    if (ret <= 0 || ret >= out_buffer_size) {
        fprintf(stderr, "❌ couldn't fit result into output buffer\n");
        return false;
    }

    return true;
}
