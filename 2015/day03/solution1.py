
import sys


def main(moves):
    seen = set()
    position = [0, 0]
    seen.add(tuple(position))
    for move in moves:
        change = {
            '^': (0, 1),
            '>': (1, 0),
            'v': (0, -1),
            '<': (-1, 0),
        }.get(move)
        position[0] += change[0]
        position[1] += change[1]
        seen.add(tuple(position))
    return len(seen)


if __name__ == '__main__':
    filename = sys.argv[1]
    with open(filename, 'r') as fp:
        result = main(fp.read())
    print "Santa saw %s houses" % result
    # Santa saw 2565 houses
