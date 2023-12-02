# Advent of Code 2023

These are my solutions to the [Advent of Code 2023 challenges][aoc-2023-site]. The solutions are written in [C][c-lang].

[aoc-2023-site]: https://adventofcode.com/2023
[c-lang]: https://en.wikipedia.org/wiki/C_(programming_language)

### Development Setup

To build and run this project, you'll need a C compiler and [CMake][cmake]. For example, if you want to use [GCC][gcc] on [Fedora Linux][fedora], you would run the following:

```bash
sudo dnf install gcc cmake
```

Building the project will depend on how your development environment handles CMake. Refer to the relevant documentation for instructions.


[cmake]: https://cmake.org/
[gcc]: https://gcc.gnu.org/
[fedora]: https://fedoraproject.org/

### Running Solutions

You can run the solution for a particular challenge by passing the challenge ID to the compiled binary. The challenge ID consists of the day number and either `a` or `b` depending on which part you want to run for the given day. Example:

```bash
./build/aoc 1a
```
