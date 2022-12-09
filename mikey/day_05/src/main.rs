use std::collections::{HashMap, VecDeque};
use std::fs::File;
use std::io::{BufReader, Lines};

type Stacks = HashMap<usize, VecDeque<char>>;

fn process_stack_line(stacks: &mut Stacks, line: &str) -> bool {
    let mut any_chars = false;
    let chars = line
        .chars()
        .enumerate()
        .filter(|(i, _)| ((*i as i32) - 1) % 4 == 0)
        .map(|(_, c)| c);
    for (i, c) in chars.enumerate() {
        if char::is_uppercase(c) {
            any_chars = true;
            let v = stacks.entry(i).or_insert_with(VecDeque::new);
            v.push_back(c);
        }
    }

    any_chars
}

fn process_instruction_line(stacks: &mut Stacks, line: &str, part_two: bool) {
    if let [num, from, to] = line
        .split(' ')
        .filter_map(|s| s.parse::<usize>().ok())
        .collect::<Vec<usize>>()
        .as_slice()
    {
        let from_stack = stacks.get_mut(&(from - 1)).unwrap();
        let mut froms = (0..*num)
            .map(|_| from_stack.pop_front().unwrap())
            .collect::<Vec<_>>();
        if part_two {
            froms.reverse();
        }
        let to_stack = stacks.get_mut(&(to - 1)).unwrap();
        for from in froms {
            to_stack.push_front(from);
        }
    }
}

fn print_answers(stacks: &Stacks, part_two: bool) {
    let mut answers = stacks
        .iter()
        .map(|(k, stack)| (k, stack.front()))
        .collect::<Vec<_>>();
    answers.sort_by(|(k1, _), (k2, _)| k1.cmp(k2));
    if part_two {
        print!("Part two: ");
    } else {
        print!("Part one: ");
    }
    for (_, answer) in answers {
        print!("{}", answer.unwrap());
    }
    println!();
}

fn calculate(lines: Lines<BufReader<File>>, part_two: bool) {
    // BACK is bottom, FRONT is top.
    let mut stacks: Stacks = HashMap::new();
    let mut is_moving: bool = false;

    for line in lines {
        let line = line.as_ref().expect("failed reading line");

        if !is_moving {
            is_moving = !process_stack_line(&mut stacks, line);
        } else {
            process_instruction_line(&mut stacks, line, part_two);
        }
    }

    print_answers(&stacks, part_two);
}

fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_four [path]")?;
    let lines = common::open_lines(&path)?;
    calculate(lines, false);

    let lines = common::open_lines(&path)?;
    calculate(lines, true);

    Ok(())
}
