
# Day 2

## Part 1

### Test

```
$ g++ -o a.out solution.cpp && ./a.out < input-test.txt
7 6 4 2 1 Safe
1 2 7 Unsafe, diff (5)
9 7 6 2 Unsafe, diff (4)
1 3 2 Unsafe, incr
8 6 4 4 Unsafe, diff (0)
1 3 6 7 9 Safe
2
```

### Real

```
$ g++ -o a.out solution.cpp && ./a.out < input.txt 
591
```

