#!/bin/bash

# echo "$@"

for input in "$@"
do
    # echo $input
    echo $input | \

    # Replace 'x' with ' '
    sed s/x/' '/g | \

    # One result per line
    xargs -n1 | \

    # Sort results
    sort -n | \

    # Three results per line (now sorted)
    xargs -n3 | \

    # "Ribbon" up each solution
    awk -f ./solution2_ribbon.awk
done
