# Advent of Code 2025

## Usage

```
$ make DAY=day03 new
Created new day directory: day03
```

```
$ make DAY=day01 run
g++ -std=c++11 -o day01/a.out day01/solution.cpp
./day01/a.out < day01/input.txt
1048

```

## Days

### --- Day 1: Secret Entrance ---

Dial with rotations, ex:

```
L68
L30
R48
L5
R60
L55
L1
L99
R14
L82
```

Some simple looping

### --- Day 2: Gift Shop ---

Invalid product IDs by range.

Ex:

```
11-22,95-115,998-1012,1188511880-1188511890,222220-222224,
1698522-1698528,446443-446449,38593856-38593862,565653-565659,
824824821-824824827,2121212118-2121212124
```

String parsing, string to number conversion, long number handling.

### --- Day 3: Lobby ---

Banks of batteries with joltages, ex:

```
987654321111111
811111111111119
234234234234278
818181911112111
```

### --- Day 7: Laboratories ---

> To repair the teleporter, you first need to understand the beam-splitting properties of the tachyon manifold.

That's just gold.

Part 1:

For this one it's a space optimization. You don't need to read all the lines in first, just go line by line, maintaining a set of how many columns are currently active.

Space: `O(w)` where `w` is the width of a line of input, aka the number of columns.
Time: `O(n)` where `n` is the number of lines of input.

Part 2:

Optimized recursion.

### --- Day 8: Playground ---

Euclidean nearest neighbors in 3d space

### --- Day 9: Movie Theater ---

Rectangles with the largest area based on two opposing corners

### --- Day 10: Factory ---

Indicator light diagrams, button wiring schematics, and joltage requirements. Ex:

```
[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}
[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}
```

Something to do with bitwise arithmetic.
