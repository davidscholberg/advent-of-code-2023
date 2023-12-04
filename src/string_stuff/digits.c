#include <stdbool.h>

#include "digits.h"

#define alphabet_size 26
#define digit_count 10
#define digit_word_min_length 3

#define ascii_digit_to_int(digit) (digit - 48)
#define char_shares_first_letter(c) (c == 't' || c == 'f' || c == 's')
#define is_lower_alpha(c) (c >= 'a' && c <= 'z')
#define to_lower(c) ((c >= 'A' && c <= 'Z') ? (c + 32) : c)

// Struct that holds a digit word, the length of the digit word, and the amount to skip ahead in a
// string that contains the digit word (note that this value is shorter than the length of the digit
// word for those words that contain ending letters that match the starting letters of other
// digits).
typedef struct digit_word {
    const char* const word;
    const int word_length;
    const int skip_ahead;
} digit_word;

// Array of all possible digit_words, along with their lengths and skip_ahead values.
static const digit_word digit_words[digit_count] = {
    {"zero", 4, 3},
    {"one", 3, 2},
    {"two", 3, 2},
    {"three", 5, 4},
    {"four", 4, 4},
    {"five", 4, 3},
    {"six", 3, 3},
    {"seven", 5, 4},
    {"eight", 5, 4},
    {"nine", 4, 3},
};

// Map of first letters of digit words to the location in digit_words array to start checking.
// Values of -1 indicate that the letter is not a first letter of any digit word.
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
    int digit_words_index = digit_first_letter_map[first_char - 'a'];
    if (digit_words_index == -1) {
        return -1;
    }
    int digit_letter_index = 1;
    // We need 1 retry in the event that the first letter can spell two different digit words (there
    // are three first letters for which this is the case).
    int retries = char_shares_first_letter(first_char) ? 1 : 0;
    while (digit_letter_index < haystack_length) {
        const digit_word* const current_digit_word = &(digit_words[digit_words_index]);
        if (to_lower(haystack[digit_letter_index]) ==
            current_digit_word->word[digit_letter_index]) {
            if (digit_letter_index + 1 < current_digit_word->word_length) {
                digit_letter_index++;
            } else {
                *skip_ahead = current_digit_word->skip_ahead;
                return digit_words_index;
            }
        } else if (digit_letter_index == 1 && retries > 0) {
            retries--;
            digit_words_index++;
        } else {
            return -1;
        }
    }

    return -1;
}
