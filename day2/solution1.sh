#!/bin/bash

cat input.txt | xargs ./solution1_helper.sh | awk -f solution1_adder.awk

# Result: 1588178
