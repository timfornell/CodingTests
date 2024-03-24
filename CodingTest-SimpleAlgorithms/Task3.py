from math import gcd

def solution(X: list, Y: list):
    if len(X) != len(Y):
        return 0

    pairs = []
    for x, y in zip(X, Y):
        greatest_common_denominator = gcd(x, y)

        # Make sure to not convert the values to float
        x = x // greatest_common_denominator
        y = y // greatest_common_denominator

        # Save in list
        pairs.append((x, y))

    # Get unique entries in list and count number of occurrences
    num_entries = [pairs.count(a)for a in set(pairs)]
    return max(num_entries)


solution ([1, 2, 3, 4, 0], [2, 3, 6, 8, 4])
solution([3, 3, 4], [5, 4, 3])
solution([4, 4, 7, 1, 2], [4, 4, 8, 1, 2])
solution([1, 2, 3, 1, 2], [2, 4, 6, 5, 10])
