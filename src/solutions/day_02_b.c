#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"
#include "string_stuff/cube_game.h"

// Day 2b: Given the list of cube games in the input, determine the fewest number of cubes required
// for each game, and sum the product of those numbers over all games.
bool day_02_b(char* const out_buffer, const int out_buffer_size) {
    int* game_lengths = 0;
    cube_game* cube_games = parse_cube_games("day_02_string_array.txt", &game_lengths);
    if (!cube_games) {
        fprintf(stderr, "❌ error reading input file\n");
        return false;
    }

    const cube_game* current_cube_game = cube_games;
    int game_index = 0;
    int sum_of_cube_powers = 0;
    while (*current_cube_game != 0) {
        cube_game_round fewest_cubes = {0, 0, 0};
        for (int i = 0; i < game_lengths[game_index]; i++) {
            const cube_game_round* const current_round = *current_cube_game + i;
            if (current_round->red_count > fewest_cubes.red_count) {
                fewest_cubes.red_count = current_round->red_count;
            }
            if (current_round->green_count > fewest_cubes.green_count) {
                fewest_cubes.green_count = current_round->green_count;
            }
            if (current_round->blue_count > fewest_cubes.blue_count) {
                fewest_cubes.blue_count = current_round->blue_count;
            }
        }

        sum_of_cube_powers +=
            fewest_cubes.red_count * fewest_cubes.green_count * fewest_cubes.blue_count;

        current_cube_game++;
        game_index++;
    }

    free(cube_games);

    int ret = snprintf(out_buffer, out_buffer_size, "%d", sum_of_cube_powers);
    if (ret <= 0 || ret >= out_buffer_size) {
        fprintf(stderr, "❌ couldn't fit result into output buffer\n");
        return false;
    }

    return true;
}
