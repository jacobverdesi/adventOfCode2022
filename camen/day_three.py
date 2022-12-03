#! /usr/bin/env python3


def to_priority(char):
    # a-z = 1-26; A-Z = 27-52
    priority = ord(char) % 96
    if priority < 27:
        return priority
    priority -= 38
    if not (27 <= priority <= 52):
        raise AssertionError(f"Expected input character a-Z, got {char}!")
    return priority


def score_1(rucksack):
    rucksack = rucksack.strip()
    half = len(rucksack) // 2
    compartment_1 = set(map(to_priority, set(rucksack[:half])))
    compartment_2 = set(map(to_priority, set(rucksack[half:])))

    common_items = compartment_2.intersection(compartment_1)
    return common_items.pop()


def score_2(rucksacks):
    one, two, three = (
        set(map(to_priority, set(rucksack.strip()))) for rucksack in rucksacks
    )
    common_items = three.intersection(two).intersection(one)
    return common_items.pop()


def main():
    with open("resources/day_three_input.txt") as buffer:
        rucksacks = buffer.readlines()

    answer_one = sum(map(score_1, rucksacks))
    answer_two = sum(
        map(score_2, [rucksacks[i : i + 3] for i in range(0, len(rucksacks), 3)])
    )
    print(f"Answer one: {answer_one}")
    print(f"Answer two: {answer_two}")


if __name__ == "__main__":
    main()
