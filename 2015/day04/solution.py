
import hashlib
import sys


def solve(secret_key, starts_with):
    result = 1
    while True:
        hash_input = "%s%s" % (secret_key, result)
        hash_result = hashlib.md5(hash_input).hexdigest()
        if hash_result.startswith(starts_with):
            return result
        result += 1


if __name__ == '__main__':
    """
    $ python solution.py yzbqklnj 00000
    First decimal that creates a hash that starts with `00000` based on secret key `yzbqklnj`: 282749
    $ python solution.py yzbqklnj 000000
    First decimal that creates a hash that starts with `000000` based on secret key `yzbqklnj`: 9962624
    """
    secret_key = sys.argv[1]
    starts_with = sys.argv[2]
    result = solve(secret_key, starts_with)
    print "First decimal that creates a hash that starts with `%s` based on secret key `%s`: %s" % (
        starts_with,
        secret_key,
        result
    )
