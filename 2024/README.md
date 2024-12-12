# Advent of Code 2024

## Usage

This year I have a handy dandy Makefile!

```
🎵 ~/Source/adventofcode/2024 $ make DAY=day04 run
```

## Days

### --- Day 1: Historian Hysteria ---

Sorting

### --- Day 2: Red-Nosed Reports ---

"Reports" and "levels" within a report, either going up or down, and differing by a certain range.

> part 2 of day 2 was a bit of a doozy, i feel like it'd make a decent harder-level interview question. specifically you could keep going and say alright, tolerating a single bad level is good, but what about tolerating two? more? it's a good measure of complexity too - if you brute force all of the combinations of bad levels to remove and walk through them the complexity is surely higher than a greedy/"best effort and fix" approach. etc.

### --- Day 3: Mull It Over ---

Regex

`mul()`

```
xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))
```

and `do()` / `don't()`

```
xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))
```

### --- Day 4: Ceres Search ---

Word search for `XMAS`, oof

### --- Day 5: Print Queue ---

"page ordering rules"

### --- Day 6: Guard Gallivant ---

Map of guard and obstructions

Use of set to store walked coords

### --- Day 7: Bridge Repair ---

Add / multiply operators to make equations true

### --- Day 8: Resonant Collinearity ---

Antennas and "antinodes"

### --- Day 9: Disk Fragmenter ---

Disk map, file checksums

### --- Day 10: Hoof It ---

Depth first search

### --- Day 11: Plutonian Pebbles ---

Linked lists

Part 2 isn't reasonable to brute force, you have to figure out an optimization/pattern.
