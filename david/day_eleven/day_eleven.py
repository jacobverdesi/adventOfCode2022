from typing import List
from functools import reduce


class Monkey(object):
    def __init__(self, monkey_input: list) -> None:

        self.monkey = int(monkey_input[0].split(" ")[-1][0])
        self.items = [int(i) for i in monkey_input[1].split(":")[-1].strip().split(",")]
        self.operation = monkey_input[2].split("=")[-1].strip().split(" ")
        self.divisible_by = int(monkey_input[3].split(":")[-1].strip().split(" ")[-1])
        self.test_response_true = int(monkey_input[4].split(" ")[-1])
        self.test_response_false = int(monkey_input[5].split(" ")[-1])
        self.inspections = 0


def operation_mapper(input: int, op: list, divisor_product: int) -> int:
    old = input
    new = old if op[-1] == "old" else int(op[-1])
    if op[1] == "+":
        return old + new
    if op[1] == "*":
        old = old % divisor_product
        return old * new


def update_monkey_items(
    monkey: Monkey, monkeys: List[Monkey], divisor_product: int, divide=True
):
    for i in range(len(monkey.items)):
        monkey.inspections += 1
        item = monkey.items[i]
        item = operation_mapper(item, monkey.operation, divisor_product)
        if divide:
            item //= 3
        if item % monkey.divisible_by == 0:
            monkeys[monkey.test_response_true].items.append(item)
        else:
            monkeys[monkey.test_response_false].items.append(item)
    monkey.items = []


def execute_rounds(
    monkeys: List[Monkey], rounds: int, func: any, divide: bool
) -> List[Monkey]:
    divisor_product = reduce((lambda x, y: x * y), [m.divisible_by for m in monkeys])
    for _ in range(rounds):
        for monkey in monkeys:
            func(monkey, monkeys, divisor_product, divide)
    return monkeys


def get_max_inspections_product(
    monkeys: List[Monkey], rounds: int, divide: bool = True
):
    monkeys = execute_rounds(monkeys, rounds, update_monkey_items, divide)
    last_two = sorted([i.inspections for i in monkeys])[-2:]
    return last_two[0] * last_two[1]


if __name__ == "__main__":
    with open("./day_eleven.txt", "r") as readfile:
        content = readfile.read()

    monkeys = sorted(
        [Monkey(i.split("\n")) for i in content.split("\n\n")], key=lambda x: x.monkey
    )

    print(get_max_inspections_product(monkeys, 20))

    monkeys = sorted(
        [Monkey(i.split("\n")) for i in content.split("\n\n")], key=lambda x: x.monkey
    )
    print(get_max_inspections_product(monkeys, 10000, False))
