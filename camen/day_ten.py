#! /usr/bin/env python3

# addx V (current cycle to end of next cycle)
# noop nothing
# signal strength = cycle number * x


def _build_register(instructions):
    register = []
    last_value = 1
    for instruction in instructions:
        register.append(last_value)

        instruction = instruction.strip()
        if instruction != "noop":
            register.append(last_value)
            add_value = int(instruction.split(" ")[1])
            value = last_value + add_value
            last_value = value

    return register


def score_1(register):
    return sum(idx * register[idx - 1] for idx in range(20, 260, 40))


def score_2(register, screen_width=40):
    PIXELS = {
        True: "#",
        False: ".",
    }

    pixels = [
        PIXELS[abs((position % screen_width) - value) < 2]
        for (position, value) in enumerate(register)
    ]
    for i in range(0, len(pixels), screen_width):
        print("".join(pixels[i : i + screen_width]))


def main():
    with open("resources/day_ten_input.txt") as buffer:
        instructions = buffer.readlines()

    register = _build_register(instructions)

    answer_one = score_1(register)
    answer_two = score_2(register)
    print(f"Answer one: {answer_one}")
    print(f"Answer two: BPJAZGAP")  # Look at image printed by `score_2()``


if __name__ == "__main__":
    main()
