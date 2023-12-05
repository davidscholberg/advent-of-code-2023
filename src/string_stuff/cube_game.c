#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cube_game.h"
#include "file_io.h"

#define cube_color_count 3

// Parse the given game string into the given array of cube_game_rounds. It is assumed that space
// for enough cube_game_rounds has already been allocated.
void parse_cube_game(const char* game_str, cube_game_round* current_cube_game_round);

// Parse the given round string into the given cube_game_round and return the location of the game
// string just past the current round, or null if the end of the game has been reached. game_str is
// expected to begin at the first number of the round.
const char*
parse_cube_game_round(const char* game_str, cube_game_round* const current_cube_game_round);

void parse_cube_game(const char* game_str, cube_game_round* current_cube_game_round) {
    // Move game_str up to first round
    game_str = strstr(game_str, ": ") + 2;

    // Iterate through each round.
    while (1) {
        game_str = parse_cube_game_round(game_str, current_cube_game_round);

        if (*game_str == 0) {
            return;
        }

        // Move up to next round.
        game_str += 2;
        current_cube_game_round++;
    }
}

const char*
parse_cube_game_round(const char* game_str, cube_game_round* const current_cube_game_round) {
    // Iterate through each cube element of the current round (note that some cube elements may be
    // missing, indicating that there were no cubes with that color in the round).
    for (int i = 0; i < cube_color_count; i++) {
        // Get cube count and advance to color name.
        int cube_count = atoi(game_str);
        while ((*game_str >= '0' && *game_str <= '9') || *game_str == ' ') {
            game_str++;
        }

        // Set the correct count for the current color.
        if (*game_str == 'r') {
            current_cube_game_round->red_count = cube_count;
        } else if (*game_str == 'g') {
            current_cube_game_round->green_count = cube_count;
        } else {
            current_cube_game_round->blue_count = cube_count;
        }

        // Move to the end of the current cube element.
        while (*game_str != ',' && *game_str != ';' && *game_str != 0) {
            game_str++;
        }

        // Exit if we're at the end of the round or the game.
        if (*game_str == ';' || *game_str == 0) {
            return game_str;
        }

        game_str += 2;
    }

    // Shouldn't ever reach this point on correct input.
    return NULL;
}

cube_game* parse_cube_games(const char* const filename, int** game_lengths_ptr) {
    // Read file into line array.
    int line_count = 0;
    char** lines = file_to_lines(filename, &line_count);
    if (!lines) {
        fprintf(stderr, "❌ couldn't open input file\n");
        return NULL;
    }

    // Determine the overall space needed for the 2D array.
    // Size neeed for the cube game lengths array.
    int cube_game_lengths_size = sizeof(int) * line_count;
    // Size needed for the cube_game array (where each value points to the starting round of a cube
    // game). Note that this is one greater than the total number of games to account for the
    // terminating null pointer.
    int cube_games_size = sizeof(cube_game) * (line_count + 1);
    // Temporary array to hold the lengths of each game.
    int temp_game_lengths[line_count];

    // First pass: determine size needed for cube_game_rounds
    int total_rounds = 0;
    for (int i = 0; i < line_count; i++) {
        const char* const line = lines[i];
        int semicolons = 0;
        for (int j = 0; line[j] != 0; j++) {
            if (line[j] == ';') {
                semicolons++;
            }
        }
        int game_length = semicolons + 1;
        temp_game_lengths[i] = game_length;
        total_rounds += game_length;
    }

    // Allocate memory for the whole cube_games array.
    // Size needed for all cube_game_rounds.
    int cube_game_rounds_size = sizeof(cube_game_round) * total_rounds;
    unsigned char* const cube_games_mem = calloc(
        cube_game_rounds_size + cube_game_lengths_size + cube_games_size,
        sizeof(unsigned char)
    );

    // Second pass: fill in the cube_games array.
    cube_game* const cube_games = (cube_game*)cube_games_mem;
    int* const game_lengths = (int*)(cube_games_mem + cube_games_size);
    cube_game_round* const cube_game_rounds =
        (cube_game_round*)(cube_games_mem + cube_games_size + cube_game_lengths_size);
    cube_game_round* current_cube_game_round = cube_game_rounds;
    for (int i = 0; i < line_count; i++) {
        int game_length = temp_game_lengths[i];
        game_lengths[i] = game_length;
        cube_games[i] = current_cube_game_round;
        parse_cube_game(lines[i], current_cube_game_round);
        current_cube_game_round += game_length;
    }

    free(lines);

    *game_lengths_ptr = game_lengths;
    return cube_games;
}
