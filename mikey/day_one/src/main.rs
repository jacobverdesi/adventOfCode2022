use std::env;
use std::fs::File;
use std::io::{self, BufRead, Error, ErrorKind};

fn main() -> io::Result<()> {
    let args = env::args().collect::<Vec<_>>();
    let path = args
        .get(1)
        .ok_or(Error::new(ErrorKind::Other, "usage: day_one [path]"))?;
    let file = File::open(path)?;
    let lines = io::BufReader::new(file).lines();

    let mut current_elf: i64 = 0;
    let mut elves = Vec::<i64>::new();

    for try_line in lines {
        let line = try_line?;
        if let Ok(num) = line.parse::<i64>() {
            current_elf += num;
        } else {
            elves.push(current_elf);
            current_elf = 0;
        }
    }

    let max_cal_elf = elves.iter().max();

    if let Some(elf) = max_cal_elf {
        println!("The most calories is {}", elf);
    } else {
        println!("No elves found");
    }
    Ok(())
}
