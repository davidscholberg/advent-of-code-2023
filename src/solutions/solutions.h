#pragma once

#include <stdbool.h>

// Expands to the solution function declaration for the given day number and part.
#define solution_declaration(day, part) \
    bool day_##day##_##part(char* const out_buffer, const int out_buffer_size)

solution_declaration(01, a);
