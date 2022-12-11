use std::collections::HashSet;

#[derive(Clone, PartialEq, Eq, Hash, Debug)]
struct Pos {
    x: i64,
    y: i64,
}

#[derive(Clone, Copy)]
enum Dir {
    Left,
    Right,
    Up,
    Down,
}

use Dir::*;

impl Pos {
    fn new() -> Pos {
        Pos { x: 0, y: 0 }
    }
}

type Visits = HashSet<Pos>;

fn move_tail(head: &Pos, old_tail: Pos) -> Pos {
    let diff_x = head.x - old_tail.x;
    let diff_y = head.y - old_tail.y;
    let dir_x = if diff_x.is_negative() { -1 } else { 1 };
    let dir_y = if diff_y.is_negative() { -1 } else { 1 };
    let moves_x = if diff_x.abs() * (diff_x.abs() + (diff_y.abs() - 1)) > 1 {
        dir_x
    } else {
        0
    };
    let moves_y = if diff_y.abs() * (diff_y.abs() + (diff_x.abs() - 1)) > 1 {
        dir_y
    } else {
        0
    };
    Pos {
        x: old_tail.x + moves_x,
        y: old_tail.y + moves_y,
    }
}

fn get_move(command: &str) -> (Dir, usize) {
    match command.split(" ").collect::<Vec<_>>().as_slice() {
        [dir, num] => {
            let n = str::parse::<usize>(num).expect("error parsing num");
            match *dir {
                "R" => (Right, n),
                "U" => (Up, n),
                "L" => (Left, n),
                "D" => (Down, n),
                _ => panic!("error parsing dir {}", dir),
            }
        }
        _ => panic!("error parsing line {}", command),
    }
}

fn move_head(head: Pos, dir: Dir) -> Pos {
    match dir {
        Right => Pos {
            x: head.x + 1,
            y: head.y,
        },
        Up => Pos {
            x: head.x,
            y: head.y + 1,
        },
        Left => Pos {
            x: head.x - 1,
            y: head.y,
        },
        Down => Pos {
            x: head.x,
            y: head.y - 1,
        },
    }
}

fn run_snake(commands: &[String], snake_length: usize) -> Visits {
    let mut snake = Vec::<Pos>::new();
    let mut visits = Visits::new();
    for _ in 0..snake_length {
        snake.push(Pos::new());
    }

    for command in commands {
        let (dir, n) = get_move(command);
        for _ in 0..n {
            for i in 0..snake_length {
                if i == 0 {
                    snake[0] = move_head(snake[0].clone(), dir);
                } else {
                    snake[i] = move_tail(&snake[i - 1], snake[i].clone());
                }
                if i == (snake_length - 1) {
                    visits.insert(snake[i].clone());
                }
            }
        }
    }
    visits
}

fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_09 [path]")?;
    let lines = common::open_lines(&path)?
        .map(|line| line.expect("error reading line"))
        .collect::<Vec<_>>();

    println!("part 1 {}", run_snake(lines.as_slice(), 2).len());
    println!("part 2 {}", run_snake(lines.as_slice(), 10).len());

    Ok(())
}
