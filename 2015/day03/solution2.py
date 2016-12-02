
import sys


def main(moves):
    seen = set()
    position_santa = [0, 0]
    position_robo = [0, 0]
    seen.add(tuple(position_santa))
    for i, move in enumerate(moves):
        change = {
            '^': (0, 1),
            '>': (1, 0),
            'v': (0, -1),
            '<': (-1, 0),
        }.get(move)
        if i % 2 == 0:
            position_santa[0] += change[0]
            position_santa[1] += change[1]
            seen.add(tuple(position_santa))
        else:
            position_robo[0] += change[0]
            position_robo[1] += change[1]
            seen.add(tuple(position_robo))
    return len(seen)


if __name__ == '__main__':
    filename = sys.argv[1]
    with open(filename, 'r') as fp:
        result = main(fp.read())
    print "Santa and Robo Santa saw %s houses" % result
    # Santa and Robo Santa saw 2639 houses
