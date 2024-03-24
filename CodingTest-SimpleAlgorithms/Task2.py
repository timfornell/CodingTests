def solution(client):
    in_storage = []
    max_storage = len(in_storage)

    # Get one package at a time
    for package in range(1, len(client)):
        # Check who is first in line
        current_client = client[0]

        # check if current package matches the client
        if current_client == package:
            # Let client leave with package
            client.remove(current_client)

            # take next package
            continue

        # Current package does not match the current client => Put in storage
        in_storage.append(package)

        if current_client in in_storage:
            # Let client take their package from storage
            in_storage.remove(current_client)
            client.remove(current_client)

        # Do this last so that if a client gets something from storage, it isn't included
        max_storage = max(max_storage, len(in_storage))

    return max_storage

solution([3, 2, 4, 5, 1])
solution([1, 2, 3, 4, 5])
solution([3, 2, 7, 5, 4, 1, 6])