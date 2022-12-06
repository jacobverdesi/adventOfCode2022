#! /usr/bin/env python3


def score(datastream, packet_size):
    for idx, potential_start in (
        (idx, datastream[idx : idx + packet_size])
        for idx in range(0, len(datastream) - packet_size)
    ):
        if len(set(potential_start)) == packet_size:
            return idx + packet_size


def main():
    with open("resources/day_six_input.txt") as buffer:
        datastream = buffer.read()

    answer_one = score(datastream, packet_size=4)
    answer_two = score(datastream, packet_size=14)
    print(f"Answer one: {answer_one}")
    print(f"Answer two: {answer_two}")


if __name__ == "__main__":
    main()
