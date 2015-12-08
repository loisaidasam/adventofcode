#!/usr/bin/env awk -f

{
    # 3x the shortest side + 2x each other side
    print 3*$1*$2 + 2*$1*$3 + 2*$2*$3
}