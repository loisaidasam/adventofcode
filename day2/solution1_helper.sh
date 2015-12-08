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

    # "Wrapping paper" up each solution
    awk -f ./solution1_wrapper.awk
done
