#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "digits.h"
#include "engine_schematic.h"

#define adjacent_coords_count 8
#define side_coord_count 3
#define vertical_coords_count 2

#define is_engine_part_symbol(c) ((!is_ascii_digit(c)) && ((c) != '.'))
#define is_coord_valid(c, row_count, column_count)                     \
    (((c).row >= 0) && ((c).column >= 0) && ((c).row < (row_count)) && \
     ((c).column < (column_count)))

// Struct holding a row and column value representing coordinates in a 2D grid.
typedef struct coord {
    int row;
    int column;
} coord;

// Holds the line array with the engine schematic, as well as the row and column counts.
typedef struct engine_schematic {
    char** lines;
    const int row_count;
    const int column_count;
} engine_schematic;

// For the gear symbol located at the given coords in the given schematic, return the gear ratio if
// it's a valid gear, otherwise return -1.
int get_gear_ratio(const int row, const int column, const engine_schematic* const schematic);

// Check if the given coords of the given schematic contain an engine part symbol.
bool has_engine_part_symbol(
    const coord* const coords,
    const int coords_length,
    const engine_schematic* const schematic
);

// Tells if the number that starts at row,column is a part number. A part number is a number that is
// adjacent (including diagonally) to a non-period symbol.
bool is_engine_part_number(
    const int row,
    const int column,
    const engine_schematic* const schematic
);

int get_gear_ratio(const int row, const int column, const engine_schematic* const schematic) {
    // All coords surrounding the given row and column point.
    const coord adjacent_coords[adjacent_coords_count] = {
        {row - 1, column - 1},
        {row - 1, column},
        {row - 1, column + 1},
        {row, column - 1},
        {row, column + 1},
        {row + 1, column - 1},
        {row + 1, column},
        {row + 1, column + 1},
    };

    // Coords that point to the start of numbers that are adjacent to the given row and column.
    coord adjacent_numbers[adjacent_coords_count] = {
        {-1, -1},
        {-1, -1},
        {-1, -1},
        {-1, -1},
        {-1, -1},
        {-1, -1},
        {-1, -1},
        {-1, -1},
    };

    // Check for adjacent numbers.
    for (int i = 0; i < adjacent_coords_count; i++) {
        if (is_coord_valid(adjacent_coords[i], schematic->row_count, schematic->column_count)) {
            int current_row = adjacent_coords[i].row;
            int current_column = adjacent_coords[i].column;
            if (is_ascii_digit(schematic->lines[current_row][current_column])) {
                adjacent_numbers[i].row = current_row;
                adjacent_numbers[i].column = current_column - 1;
                // Find the beginning of the number.
                while (is_coord_valid(
                           adjacent_numbers[i],
                           schematic->row_count,
                           schematic->column_count
                       ) &&
                       is_ascii_digit(
                           schematic->lines[adjacent_numbers[i].row][adjacent_numbers[i].column]
                       )) {
                    adjacent_numbers[i].column--;
                }
                // At this point, the column needs to be incremented by one to be at the beginning
                // of the number.
                adjacent_numbers[i].column++;
            }
        }
    }

    // Eliminate duplicate adjacent numbers and get the unique adjacent numbers count.
    int adjacent_number_count = 0;
    for (int i = 0; i < adjacent_coords_count; i++) {
        if (adjacent_numbers[i].row == -1) {
            continue;
        }

        adjacent_number_count++;

        for (int j = i + 1; j < adjacent_coords_count; j++) {
            if (adjacent_numbers[j].row == -1) {
                continue;
            }

            if (adjacent_numbers[i].row == adjacent_numbers[j].row &&
                adjacent_numbers[i].column == adjacent_numbers[j].column) {
                adjacent_numbers[j].row = -1;
                adjacent_numbers[j].column = -1;
            }
        }
    }

    if (adjacent_number_count != 2) {
        return -1;
    }

    int gear_ratio = 1;
    for (int i = 0; i < adjacent_coords_count; i++) {
        if (adjacent_numbers[i].row == -1) {
            continue;
        }

        gear_ratio *=
            atoi(&(schematic->lines[adjacent_numbers[i].row][adjacent_numbers[i].column]));
    }

    return gear_ratio;
}

bool has_engine_part_symbol(
    const coord* const coords,
    const int coords_length,
    const engine_schematic* const schematic
) {
    for (int i = 0; i < coords_length; i++) {
        if (is_coord_valid(coords[i], schematic->row_count, schematic->column_count)) {
            int current_row = coords[i].row;
            int current_column = coords[i].column;
            if (is_engine_part_symbol(schematic->lines[current_row][current_column])) {
                return true;
            }
        }
    }

    return false;
}

bool is_engine_part_number(
    const int row,
    const int column,
    const engine_schematic* const schematic
) {
    // side_coords represents the coordinates either to the left or the right of the
    // number. We start with values to the left of the number.
    coord side_coords[side_coord_count] = {
        {row - 1, column - 1},
        {row, column - 1},
        {row + 1, column - 1},
    };

    // Check the left side coords.
    if (has_engine_part_symbol(side_coords, side_coord_count, schematic)) {
        return true;
    }

    // vertical_coords are the coords directly above or below a digit of the current number.
    coord vertical_coords[vertical_coords_count] = {
        {row - 1, column},
        {row + 1, column},
    };

    // Check all of the vertical coords for the current number.
    const char* number_ptr = &(schematic->lines[row][column]);
    while (is_ascii_digit(*number_ptr)) {
        if (has_engine_part_symbol(vertical_coords, vertical_coords_count, schematic)) {
            return true;
        }
        number_ptr++;
        vertical_coords[0].column++;
        vertical_coords[1].column++;
    }

    // Set the side_coords to the right side coords and check them.
    side_coords[0].column = vertical_coords[0].column;
    side_coords[1].column = vertical_coords[0].column;
    side_coords[2].column = vertical_coords[0].column;
    if (has_engine_part_symbol(side_coords, side_coord_count, schematic)) {
        return true;
    }

    return false;
}

int sum_engine_part_numbers(char** lines, const int line_count) {
    const int column_count = strlen(lines[0]);

    const engine_schematic schematic = {
        lines,
        line_count,
        column_count,
    };

    int engine_part_number_sum = 0;
    for (int i = 0; i < line_count; i++) {
        const char* line_ptr = lines[i];

        while (true) {
            // Find next number or hit end of line
            while (!is_ascii_digit(*line_ptr) && *line_ptr != 0) {
                line_ptr++;
            }

            if (*line_ptr == 0) {
                break;
            }

            const int row = i;
            const int column = line_ptr - lines[i];
            if (is_engine_part_number(row, column, &schematic)) {
                engine_part_number_sum += atoi(line_ptr);
            }

            // Advance past current number.
            while (is_ascii_digit(*line_ptr)) {
                line_ptr++;
            }
        }
    }

    return engine_part_number_sum;
}

int sum_engine_gear_ratios(char** lines, const int line_count) {
    const int column_count = strlen(lines[0]);

    const engine_schematic schematic = {
        lines,
        line_count,
        column_count,
    };

    // For each gear symbol encountered, determine if it's a valid gear and add the gear ratio to
    // the running sum.
    int gear_ratio_sum = 0;
    for (int i = 0; i < line_count; i++) {
        for (int j = 0; j < column_count; j++) {
            if (lines[i][j] == '*') {
                int gear_ratio = get_gear_ratio(i, j, &schematic);
                if (gear_ratio != -1) {
                    gear_ratio_sum += gear_ratio;
                }
            }
        }
    }

    return gear_ratio_sum;
}
