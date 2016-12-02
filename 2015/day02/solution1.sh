#!/bin/bash

cat input.txt | xargs ./solution1_helper.sh | awk -f sum.awk

# Result: 1588178
