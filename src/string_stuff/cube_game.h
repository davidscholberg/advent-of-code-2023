#pragma once

// Struct that contains the count of cubes revealed during a round of the cube game.
typedef struct cube_game_round {
    int red_count;
    int green_count;
    int blue_count;
} cube_game_round;

// Pointer to an array of cube_game_rounds. This array represents a full cube game.
typedef cube_game_round* cube_game;

// Parse the cube games from the given resource file into a null-terminated array of cube_games.
// *game_lengths will be set to point to the array of game lengths. The returned pointer must be
// freed by the caller (note that *game_lengths will be freed when you free the returned pointer so
// you should not free *game_lengths).
cube_game* parse_cube_games(const char* const filename, int** game_lengths_ptr);
