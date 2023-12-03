#include <stdbool.h>

#include "digits.h"

#define alphabet_size 26
#define digit_count 10
#define digit_word_max_length 5
#define digit_word_min_length 3

#define ascii_digit_to_int(digit) (digit - 48)
#define char_shares_first_letter(c) (c == 't' || c == 'f' || c == 's')
#define is_lower_alpha(c) (c >= 'a' && c <= 'z')
#define to_lower(c) ((c >= 'A' && c <= 'Z') ? (c + 32) : c)

// Struct that holds a digit word letter, the numerical value of its corresponding digit
// word if the letter is the last letter of the word (or -1 otherwise), and the amount to skip ahead
// in a string if the digit words can overlap.
typedef struct digit_word_letter {
    char letter;
    int digit_value;
    int skip_ahead;
} digit_word_letter;

// 2D array that contains the spelling of each digit word, with the numerical value of the digit
// word located at the end of each word.
static const digit_word_letter digit_word_array[digit_count][digit_word_max_length] = {
    {
        {'z', -1, -1},
        {'e', -1, -1},
        {'r', -1, -1},
        {'o', 0, 3},
        {0, -1, -1},
    },
    {
        {'o', -1, -1},
        {'n', -1, -1},
        {'e', 1, 2},
        {0, -1, -1},
        {0, -1, -1},
    },
    {
        {'t', -1, -1},
        {'w', -1, -1},
        {'o', 2, 2},
        {0, -1, -1},
        {0, -1, -1},
    },
    {
        {'t', -1, -1},
        {'h', -1, -1},
        {'r', -1, -1},
        {'e', -1, -1},
        {'e', 3, 4},
    },
    {
        {'f', -1, -1},
        {'o', -1, -1},
        {'u', -1, -1},
        {'r', 4, 4},
        {0, -1, -1},
    },
    {
        {'f', -1, -1},
        {'i', -1, -1},
        {'v', -1, -1},
        {'e', 5, 3},
        {0, -1, -1},
    },
    {
        {'s', -1, -1},
        {'i', -1, -1},
        {'x', 6, 3},
        {0, -1, -1},
        {0, -1, -1},
    },
    {
        {'s', -1, -1},
        {'e', -1, -1},
        {'v', -1, -1},
        {'e', -1, -1},
        {'n', 7, 4},
    },
    {
        {'e', -1, -1},
        {'i', -1, -1},
        {'g', -1, -1},
        {'h', -1, -1},
        {'t', 8, 4},
    },
    {
        {'n', -1, -1},
        {'i', -1, -1},
        {'n', -1, -1},
        {'e', 9, 3},
        {0, -1, -1},
    },
};

// Map of first letters of digit words to the location in digit_word_array to start checking. Values
// of -1 indicate that the letter is not a first letter of any digit word.
static const int digit_first_letter_map[alphabet_size] = {
    -1,  // a
    -1,  // b
    -1,  // c
    -1,  // d
    8,   // e
    4,   // f
    -1,  // g
    -1,  // h
    -1,  // i
    -1,  // j
    -1,  // k
    -1,  // l
    -1,  // m
    9,   // n
    1,   // o
    -1,  // p
    -1,  // q
    -1,  // r
    6,   // s
    2,   // t
    -1,  // u
    -1,  // v
    -1,  // w
    -1,  // x
    -1,  // y
    0,   // z
};

int digit_at(
    const char* const haystack,
    int haystack_length,
    bool count_words,
    int* const skip_ahead
) {
    if (haystack_length <= 0) {
        return -1;
    }

    // Check if first character is a numerical digit.
    char first_char = haystack[0];
    if (first_char >= '0' && first_char <= '9') {
        *skip_ahead = 1;
        return ascii_digit_to_int(first_char);
    }

    if (!count_words) {
        return -1;
    }

    // Check if the leading characters in haystack form a digit word.
    if (haystack_length < digit_word_min_length) {
        return -1;
    }
    first_char = to_lower(first_char);
    if (!is_lower_alpha(first_char)) {
        return -1;
    }
    int digit_word_array_index = digit_first_letter_map[first_char - 'a'];
    if (digit_word_array_index == -1) {
        return -1;
    }
    int digit_word_index = 1;
    // We need 1 retry in the event that the first letter can spell two different digit words (there
    // are three first letters for which this is the case).
    int retries = char_shares_first_letter(first_char) ? 1 : 0;
    while (digit_word_index < haystack_length) {
        const digit_word_letter* const current_digit_word_letter =
            &(digit_word_array[digit_word_array_index][digit_word_index]);
        if (to_lower(haystack[digit_word_index]) == current_digit_word_letter->letter) {
            if (current_digit_word_letter->digit_value == -1) {
                digit_word_index++;
            } else {
                *skip_ahead = current_digit_word_letter->skip_ahead;
                return current_digit_word_letter->digit_value;
            }
        } else if (digit_word_index == 1 && retries > 0) {
            retries--;
            digit_word_array_index++;
        } else {
            return -1;
        }
    }

    return -1;
}
