
import sys


def _has_twice_without_overlapping(input_str):
    for index in xrange(len(input_str)-1):
        substr = input_str[index:index+2]
        remaining = input_str[index+2:]
        if substr in remaining:
            return True
    return False


def test_has_twice_without_overlapping():
    print "test_has_twice_without_overlapping()"
    assert _has_twice_without_overlapping('xyxy')
    assert _has_twice_without_overlapping('aabcdefgaa')
    assert not _has_twice_without_overlapping('aaa')
    print "ok"


def _has_repeating_letter_with_at_least_one_in_between(input_str):
    for index in xrange(len(input_str)-2):
        if input_str[index] == input_str[index+2]:
            return True
    return False


def test_has_repeating_letter_with_at_least_one_in_between():
    print "test_has_repeating_letter_with_at_least_one_in_between()"
    assert _has_repeating_letter_with_at_least_one_in_between('xyx')
    assert _has_repeating_letter_with_at_least_one_in_between('abcdefeghi')
    assert _has_repeating_letter_with_at_least_one_in_between('aaa')
    assert not _has_repeating_letter_with_at_least_one_in_between('abc')
    print "ok"


def _is_nice(input_str):
    return (_has_twice_without_overlapping(input_str) and
            _has_repeating_letter_with_at_least_one_in_between(input_str))


def num_nice(input_strs):
    result = 0
    for input_str in input_strs:
        if _is_nice(input_str):
            result += 1
    return result


if __name__ == '__main__':
    """
    $ python solution2.py input.txt
    Found 69 nice strings
    """
    # test_has_twice_without_overlapping()
    # test_has_repeating_letter_with_at_least_one_in_between()
    with open(sys.argv[1], 'r') as fp:
        result = num_nice(fp)
    print "Found %s nice strings" % result
