def solution(A: list):
    num_even_pairs = [0] * len(A)

    for i in range(0, len(A)):
        # Rearrange A into [A[i:N], A[0, i - 1]]
        new_a = A[i:] + A[0:i]

        k = 0
        while k < len(new_a) - 1:
            sum_of_pair = (new_a[k] + new_a[k + 1])
            if (sum_of_pair % 2) == 0:
                # Even pair found
                num_even_pairs[i] += 1

                # Set k to i + 2 since neither the number at i nor i + 1 can't be paired to another number
                k += 2
            else:
                k += 1

    return max(num_even_pairs)


solution([4, 2, 5, 8, 7, 3, 7])
solution([14, 21, 16, 35, 22])
solution([5, 5, 5, 5, 5, 5])