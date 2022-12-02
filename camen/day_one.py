#! /usr/bin/env python3


def main():
    with open("resources/day_one_input.txt") as buffer:
        elves_calories = buffer.read()

    total_calories_per_elf = list(
        map(lambda elf: sum(map(int, elf.split("\n"))), elves_calories.split("\n\n"))
    )

    answer_one = max(total_calories_per_elf)
    answer_two = sum((sorted(total_calories_per_elf, reverse=True))[:3])
    print(f"Answer one: {answer_one}")
    print(f"Answer two: {answer_two}")


if __name__ == "__main__":
    main()
