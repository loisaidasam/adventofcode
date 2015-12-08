#!/usr/bin/env awk -f

{
    # Sum up all results
    sum += $1
}

END {
    print sum
}
