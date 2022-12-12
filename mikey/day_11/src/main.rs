#[derive(Debug, Clone)]
enum Operator {
    Add,
    Multiply,
}

#[derive(Debug, Clone)]
enum Value {
    Old,
    Number(u64),
}

use Operator::*;
use Value::*;

use std::collections::VecDeque;

#[derive(Debug, Clone)]
struct Monkey {
    starting_items: VecDeque<u64>,
    operation: (Operator, Value),
    test_divisible_by: u64,
    if_true: usize,
    if_false: usize,
    times_inspected: u64,
}

// == parsing foolishness ==

fn parse_starting_items(lines: &[String], current_line: &mut usize) -> VecDeque<u64> {
    const START: usize = "  Starting items: ".len();
    let line = &lines[*current_line];
    let items = line[START..line.len()]
        .split(", ")
        .map(|n| str::parse::<u64>(n).expect("error parsing int"))
        .collect::<VecDeque<_>>();
    *current_line += 1;
    items
}

fn parse_operator(string: &str) -> Operator {
    match string {
        "+" => Add,
        "*" => Multiply,
        _ => panic!("failed to parse operator {}", string),
    }
}

fn parse_value(string: &str) -> Value {
    match string {
        "old" => Old,
        x => Number(str::parse::<u64>(x).expect("failed to parse u64")),
    }
}

fn parse_operation(lines: &[String], current_line: &mut usize) -> (Operator, Value) {
    const START: usize = "  Operation: new = old ".len();
    let line = &lines[*current_line];
    let tokens = line[START..line.len()].split(" ").collect::<Vec<_>>();
    let operation = match tokens.as_slice() {
        [operation, value] => (parse_operator(operation), parse_value(value)),
        _ => panic!("fail to parse operation {:?}", tokens),
    };
    *current_line += 1;
    operation
}

fn parse_test_divisible_by(lines: &[String], current_line: &mut usize) -> u64 {
    const START: usize = "  Test: divisible by ".len();
    let line = &lines[*current_line];
    let divisible_by =
        str::parse::<u64>(&line[START..line.len()]).expect("failed to parse divisible by");
    *current_line += 1;
    divisible_by
}

fn parse_if(lines: &[String], current_line: &mut usize, true_or_false: bool) -> usize {
    const START_TRUE: usize = "    If true: throw to monkey ".len();
    const START_FALSE: usize = "    If false: throw to monkey ".len();
    let line = &lines[*current_line];
    let monkey_index;
    if true_or_false {
        monkey_index = str::parse::<usize>(&line[START_TRUE..line.len()])
            .expect("failed to parse monkey index");
    } else {
        monkey_index = str::parse::<usize>(&line[START_FALSE..line.len()])
            .expect("failed to parse monkey index");
    }
    *current_line += 1;
    monkey_index
}

fn parse_monkey(lines: &[String], current_line: &mut usize) -> Option<Monkey> {
    if lines[*current_line].is_empty() {
        *current_line += 1;
        return None;
    }

    *current_line += 1; // skip monkey header

    Some(Monkey {
        starting_items: parse_starting_items(&lines, current_line),
        operation: parse_operation(&lines, current_line),
        test_divisible_by: parse_test_divisible_by(&lines, current_line),
        if_true: parse_if(&lines, current_line, true),
        if_false: parse_if(&lines, current_line, false),
        times_inspected: 0,
    })
}

// == monkey business logic ==

impl Monkey {
    fn operate(&self, x: u64) -> u64 {
        match self.operation {
            (Add, Old) => x + x,
            (Add, Number(y)) => x + y,
            (Multiply, Old) => x * x,
            (Multiply, Number(y)) => x * y,
        }
    }

    fn test(&self, x: u64) -> bool {
        x % self.test_divisible_by == 0
    }

    fn take_turn(
        &mut self,
        other_monkeys: &mut Vec<Monkey>,
        decrease_worry: bool,
        divisors_product: u64,
    ) {
        while !self.starting_items.is_empty() {
            let mut worry_item = self
                .starting_items
                .pop_front()
                .expect("starting_items must have items");
            worry_item = self.operate(worry_item);
            if decrease_worry {
                worry_item = worry_item / 3;
            }
            worry_item = worry_item % divisors_product; // chinese remainder thereom
            let target_monkey;
            if self.test(worry_item) {
                target_monkey = other_monkeys
                    .get_mut(self.if_true)
                    .expect("couldn't find monkey");
            } else {
                target_monkey = other_monkeys
                    .get_mut(self.if_false)
                    .expect("couldn't find monkey");
            }
            target_monkey.starting_items.push_back(worry_item);
            self.times_inspected += 1;
        }
    }
}

fn run_rounds(lines: &Vec<String>, decrease_worry: bool, number_rounds: usize) -> u64 {
    let mut current_line = 0;
    let mut monkeys = Vec::<Monkey>::new();

    while current_line < lines.len() {
        if let Some(monkey) = parse_monkey(lines.as_slice(), &mut current_line) {
            monkeys.push(monkey)
        }
    }

    let divisors_product = monkeys.iter().map(|m| m.test_divisible_by).product::<u64>();

    for _ in 0..number_rounds {
        for i in 0..monkeys.len() {
            let mut monkey = monkeys[i].clone();
            monkey.take_turn(&mut monkeys, decrease_worry, divisors_product);
            monkeys[i] = monkey;
        }
    }

    let mut times_inspected = monkeys
        .iter()
        .map(|monkey| monkey.times_inspected)
        .collect::<Vec<_>>();
    times_inspected.sort();
    times_inspected.reverse();
    times_inspected[0] * times_inspected[1]
}

fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_11 [path]")?;
    let lines = common::open_lines(&path)?
        .map(|line| line.expect("error parsing line"))
        .collect::<Vec<_>>();

    println!("part one {}", run_rounds(&lines, true, 20));
    println!("part two {}", run_rounds(&lines, false, 10000));

    Ok(())
}
