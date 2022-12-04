#! /usr/bin/env python3


def score_1(pair):
    (min_1, max_1), (min_2, max_2) = (
        (int(range_) for range_ in individual.split("-"))
        for individual in pair.strip().split(",")
    )
    return ((min_1 >= min_2) and (max_1 <= max_2)) or (
        (min_2 >= min_1) and (max_2 <= max_1)
    )


def _range_inclusive(min_, max_):
    return range(int(min_), int(max_) + 1)


def score_2(pair):
    range_1, range_2 = (
        set(_range_inclusive(*individual.split("-")))
        for individual in pair.strip().split(",")
    )
    if range_1.intersection(range_2):
        return True
    return False


def main():
    with open("resources/day_four_input.txt") as buffer:
        paired_sections = buffer.readlines()

    answer_one = sum(map(score_1, paired_sections))
    answer_two = sum(map(score_2, paired_sections))
    print(f"Answer one: {answer_one}")
    print(f"Answer two: {answer_two}")


if __name__ == "__main__":
    main()
