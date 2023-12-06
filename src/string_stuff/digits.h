#pragma once

#include <stdbool.h>

#define is_ascii_digit(c) (((c) >= '0') && ((c) <= '9'))

// Tells what the digit is (if any) at the beginning of the haystack string. If count_words is true,
// then a digit written out as a word is counted. The amount of space in the string that needs to be
// skipped ahead is written to skip_ahead (this value accounts for the possibility of digit words
// overlapping). If the beginning of the string does not contain a digit, digit_length is not
// touched and -1 is returned.
int digit_at(
    const char* const haystack,
    int haystack_length,
    bool count_words,
    int* const skip_ahead
);
