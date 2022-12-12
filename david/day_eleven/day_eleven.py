from typing import List


class Monkey(object):
    def __init__(self, monkey_input: list) -> None:

        self.monkey = int(monkey_input[0].split(" ")[-1][0])
        self.items = [int(i) for i in monkey_input[1].split(":")[-1].strip().split(",")]
        self.operation = monkey_input[2].split("=")[-1].strip().split(" ")
        self.divisible_by = int(monkey_input[3].split(":")[-1].strip().split(" ")[-1])
        self.test_response_true = int(monkey_input[4].split(" ")[-1])
        self.test_response_false = int(monkey_input[5].split(" ")[-1])
        self.inspections = 0

    def __str__(self):

        return str(
            (
                self.monkey,
                self.items,
                self.operation,
                self.divisible_by,
                self.test_response_true,
                self.test_response_false,
                self.inspections
            )
        )


def operation_mapper(input: int, op: list) -> int:
    old = input 
    new = old if op[-1] =="old" else int(op[-1])
    if op[1] == "+":
        return old + new
    if op[1] == "*":
        return old * new


def update_monkey_items(monkey: Monkey, monkeys: List[Monkey]):
    for i in range(len(monkey.items)):
        monkey.inspections +=1
        item = monkey.items[i]
        item = operation_mapper(item, monkey.operation)
        item //=3
        if item%monkey.divisible_by==0:
            monkeys[monkey.test_response_true].items.append(item)
        else:
            monkeys[monkey.test_response_false].items.append(item)
    monkey.items = []


def execute_rounds(monkeys:List[Monkey], rounds:int, func: any)->List[Monkey]:
    for _ in range(rounds):
        for monkey in monkeys:
            func(monkey, monkeys)
    return monkeys


def question_one(monkeys, rounds, update_monkey_items=update_monkey_items):
    monkeys = execute_rounds(monkeys, rounds, update_monkey_items)
    last_two = sorted([i.inspections for i in monkeys])[-2:]
    return last_two[0] * last_two[1]


if __name__ == "__main__":
    with open("./sample.txt", "r") as readfile:
        content = readfile.read()

    monkeys = sorted(
        [Monkey(i.split("\n")) for i in content.split("\n\n")], key=lambda x: x.monkey
    )

    print(question_one(monkeys, 20))
