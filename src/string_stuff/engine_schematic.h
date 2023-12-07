#pragma once

// Take the given array of strings that represents the engine schematic and return the sum of the
// engine part numbers in it.
int sum_engine_part_numbers(char** lines, const int line_count);

// Take the given array of strings that represents the engine schematic and return the sum of the
// gear ratios in it, where a gear ratio is the product of the only two numbers adjacent to the same
// * character.
int sum_engine_gear_ratios(char** lines, const int line_count);
