#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"
#include "string_stuff/digits.h"

// Day 1b: Take the strings from the input file and build a two-digit number for each line where the
// digits are the first and last digits contained in the string, and sum these numbers. This
// challenge differs from 1a in that we must also look for digit words in addition to numerical
// digits.
bool day_01_b(char* const out_buffer, const int out_buffer_size) {
    int line_count = 0;
    char** lines = file_to_lines("day_01_string_array.txt", &line_count);
    // char** lines = file_to_lines("test.txt", &line_count);
    if (!lines) {
        fprintf(stderr, "❌ couldn't open input file\n");
        return false;
    }

    int sum = 0;
    for (int i = 0; i < line_count; i++) {
        // Determine the first and last numerical digit characters in the current string.
        int first_digit = -1;
        int last_digit = -1;
        int line_length = strlen(lines[i]);
        int char_index = 0;
        while (char_index < line_length) {
            int skip_ahead = 1;
            int current_digit =
                digit_at(&(lines[i][char_index]), line_length - char_index, true, &skip_ahead);
            if (current_digit != -1) {
                if (first_digit == -1) {
                    first_digit = current_digit;
                }
                last_digit = current_digit;
            }
            char_index += skip_ahead;
        }

        // Convert the first and last digit characters into a two digit number and add it to the
        // sum.
        sum += (first_digit * 10) + last_digit;
    }

    free(lines);

    int ret = snprintf(out_buffer, out_buffer_size, "%d", sum);
    if (ret <= 0 || ret >= out_buffer_size) {
        fprintf(stderr, "❌ couldn't fit result into output buffer\n");
        return false;
    }

    return true;
}
