#! /usr/bin/env python3

DIRECTIONS = {
    "U": (0, 1),
    "D": (0, -1),
    "R": (1, 0),
    "L": (-1, 0),
}


def _move_one(current, direction):
    x_1, y_1 = current
    x_2, y_2 = DIRECTIONS[direction]
    return (
        x_1 + x_2,
        y_1 + y_2,
    )


def _move_follower(leader, follower):
    leader_x, leader_y = leader
    follower_x, follower_y = follower

    x_dist = leader_x - follower_x
    y_dist = leader_y - follower_y

    if max(abs(x_dist), abs(y_dist)) <= 1:
        return follower

    if x_dist == 0:
        if y_dist > 0:
            return _move_one(follower, "U")
        return _move_one(follower, "D")

    elif y_dist == 0:
        if x_dist > 0:
            return _move_one(follower, "R")
        return _move_one(follower, "L")

    if x_dist > 0:
        follower = _move_one(follower, "R")
    else:
        follower = _move_one(follower, "L")

    if y_dist > 0:
        follower = _move_one(follower, "U")
    else:
        follower = _move_one(follower, "D")

    return follower


def follow_the_leader(instructions, num_followers):
    start = (0, 0)

    head = start
    followers = {
        idx if idx < num_followers else "tail": start
        for idx in range(1, num_followers + 1)
    }

    locations = set()
    for direction, amount in instructions:
        for _ in range(int(amount)):

            head = _move_one(head, direction)
            leader = head
            for follower_name, follower in followers.items():
                follower = _move_follower(leader=leader, follower=follower)

                followers[follower_name] = follower
                leader = follower

                if follower_name == "tail":
                    locations.add(follower)

    return len(locations)


def main():
    with open("resources/day_nine_input.txt") as buffer:
        instructions = buffer.readlines()

    instructions = [instruction.strip().split(" ") for instruction in instructions]

    answer_one = follow_the_leader(instructions, num_followers=1)
    answer_two = follow_the_leader(instructions, num_followers=9)
    print(f"Answer one: {answer_one}")
    print(f"Answer two: {answer_two}")


if __name__ == "__main__":
    main()
