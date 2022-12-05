#! /usr/bin/env python3


def _process_crate_text(crates):
    columns = dict()
    rows = [
        dict(zip(range(1, 10), [row[i : i + 4] for i in range(0, len(row), 4)]))
        for row in crates.split("\n")[:-1]
    ]
    for row in reversed(rows):
        for column, value in row.items():
            if (value := value[1]) != " ":
                if column not in columns:
                    columns[column] = list()
                columns[column].append(value)
    return columns


def score_1(crates, instructions):
    crates = _process_crate_text(crates)

    for instruction in instructions:
        _, amount, _, from_crate, _, to_crate = instruction.split(" ")
        amount = int(amount)
        from_crate = crates[int(from_crate)]
        to_crate = crates[int(to_crate)]

        for _ in range(amount):
            to_crate.append(from_crate.pop())

    return "".join(values[-1] for values in crates.values())


def score_2(crates, instructions):
    crates = _process_crate_text(crates)

    for instruction in instructions:
        _, amount, _, from_crate, _, to_crate = instruction.split(" ")
        amount = int(amount)
        from_crate_idx = int(from_crate)
        to_crate_idx = int(to_crate)

        crates[to_crate_idx] += crates[from_crate_idx][-amount:]
        crates[from_crate_idx] = crates[from_crate_idx][:-amount]

    return "".join(values[-1] for values in crates.values())


def main():
    with open("resources/day_five_input.txt") as buffer:
        crates, instructions = buffer.read().split("\n\n")

    instructions = instructions.strip().split("\n")

    answer_one = score_1(crates=crates, instructions=instructions)
    answer_two = score_2(crates=crates, instructions=instructions)

    print(f"Answer one: {answer_one}")
    print(f"Answer two: {answer_two}")


if __name__ == "__main__":
    main()
