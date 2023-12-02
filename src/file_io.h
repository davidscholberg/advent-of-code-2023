#pragma once

// Read the given resource file into an array of strings with the newlines removed. The given file
// must have no empty lines except for the last line, which must be empty. The returned pointer must
// be freed by the caller. Returns null on error.
char** file_to_lines(const char* const filename, int* const line_count_ptr);
