
import sys


def solve(text):
    floor = 0
    for i, instruction in enumerate(text, start=1):
        floor += {'(': 1, ')': -1}.get(instruction)
        if floor < 0:
            return i


if __name__ == '__main__':
    """
    $ python solution2.py input.txt
    Went into basement at floor 1771
    """
    floor = solve(open(sys.argv[1]).read())
    print "Went into basement at floor %s" % floor
