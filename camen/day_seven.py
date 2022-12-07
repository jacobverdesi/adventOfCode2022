#! /usr/bin/env python3


def score_1():
    pass


def score_2():
    pass


def main():
    with open("resources/day_seven_input.txt") as buffer:
        commands = buffer.read()

    answer_one = score_1()
    answer_two = score_2()
    print(f"Answer one: {answer_one}")
    print(f"Answer two: {answer_two}")


if __name__ == "__main__":
    main()
