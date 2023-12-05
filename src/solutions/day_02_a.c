#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"
#include "string_stuff/cube_game.h"

#define red_cube_total 12
#define green_cube_total 13
#define blue_cube_total 14

// Day 2a: Given the list of cube games in the input, get the sum of game IDs for which the game is
// a valid game considering the given total number of cubes of each color
bool day_02_a(char* const out_buffer, const int out_buffer_size) {
    int* game_lengths = 0;
    cube_game* cube_games = parse_cube_games("day_02_string_array.txt", &game_lengths);
    if (!cube_games) {
        fprintf(stderr, "❌ error reading input file\n");
        return false;
    }

    const cube_game* current_cube_game = cube_games;
    int game_index = 0;
    int sum_of_valid_game_ids = 0;
    while (*current_cube_game != 0) {
        bool valid_game = true;
        for (int i = 0; i < game_lengths[game_index]; i++) {
            const cube_game_round* const current_round = *current_cube_game + i;
            if (current_round->red_count > red_cube_total ||
                current_round->green_count > green_cube_total ||
                current_round->blue_count > blue_cube_total) {
                valid_game = false;
                break;
            }
        }

        if (valid_game) {
            sum_of_valid_game_ids += game_index + 1;
        }

        current_cube_game++;
        game_index++;
    }

    free(cube_games);

    int ret = snprintf(out_buffer, out_buffer_size, "%d", sum_of_valid_game_ids);
    if (ret <= 0 || ret >= out_buffer_size) {
        fprintf(stderr, "❌ couldn't fit result into output buffer\n");
        return false;
    }

    return true;
}
