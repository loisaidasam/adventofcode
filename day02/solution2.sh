#!/bin/bash

cat input.txt | xargs ./solution2_helper.sh | awk -f sum.awk

# Result: 3783758
