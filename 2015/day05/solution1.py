
import sys


def _num_vowels(input_str):
    vowels = set(['a', 'e', 'i', 'o', 'u'])
    vowels_found = [char for char in input_str if char in vowels]
    return len(vowels_found)


def _has_repeating_char(input_str):
    last_char = None
    for char in input_str:
        if char == last_char:
            return True
        last_char = char
    return False


def _has_forbidden_strings(input_str):
    FORBIDDEN_STRS = ('ab', 'cd', 'pq', 'xy')
    for forbidden_str in FORBIDDEN_STRS:
        if forbidden_str in input_str:
            return True
    return False


def _is_nice(input_str):
    return (_num_vowels(input_str) >= 3 and
            _has_repeating_char(input_str) and
            not _has_forbidden_strings(input_str))


def num_nice(input_strs):
    result = 0
    for input_str in input_strs:
        if _is_nice(input_str):
            result += 1
    return result


if __name__ == '__main__':
    """
    $ python solution1.py input.txt
    Found 238 nice strings
    """
    with open(sys.argv[1], 'r') as fp:
        result = num_nice(fp)
    print "Found %s nice strings" % result
