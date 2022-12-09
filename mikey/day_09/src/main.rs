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

fn bounded<T>(el: T, max: T, min: T) -> T
where
    T: Ord,
{
    std::cmp::max(std::cmp::min(el, max), min)
}

fn move_tail(head: &Pos, old_tail: Pos) -> Pos {
    let diff_x = bounded(head.x - old_tail.x, 2, -2);
    let diff_y = bounded(head.y - old_tail.y, 2, -2);
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

fn get_move(command: &str) -> (Dir, i64) {
    match command.split(" ").collect::<Vec<_>>().as_slice() {
        [dir, num] => {
            let n = str::parse::<i64>(num).expect("error parsing num");
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

fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_09 [path]")?;
    let lines = common::open_lines(&path)?.map(|line| line.expect("error reading line"));

    let mut visits = Visits::new();
    let mut head: Pos = Pos::new();
    let mut tail: Pos = Pos::new();

    for line in lines {
        let (dir, n) = get_move(&line);
        for _ in 0..n {
            head = move_head(head, dir);
            tail = move_tail(&head, tail);
            visits.insert(tail.clone());
        }
    }

    println!("{}", visits.len());

    Ok(())
}
