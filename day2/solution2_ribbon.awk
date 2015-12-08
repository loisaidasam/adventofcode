#!/usr/bin/env awk -f

{
    # 2x the shortest 2 sides + the cubic volume (all 3 sides)
    print 2*$1 + 2*$2 + $1*$2*$3
}
