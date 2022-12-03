use std::env;
use std::fs::File;
use std::io::{self, BufRead, Error, ErrorKind};

struct Fail {
    pub message: String,
}

impl Fail {
    fn new(message: String) -> Fail {
        Fail {
            message: message.to_string(),
        }
    }
}

impl From<Fail> for io::Error {
    fn from(error: Fail) -> Self {
        Error::new(ErrorKind::Other, error.message)
    }
}

#[derive(Clone, Copy, Debug, PartialEq)]
enum RPS {
    Rock,
    Paper,
    Scissors,
}

#[derive(Clone, Copy, Debug, PartialEq)]
enum Outcome {
    Win,
    Loss,
    Draw,
}

impl Outcome {
    fn value(&self) -> i64 {
        match self {
            Outcome::Win => 6,
            Outcome::Draw => 3,
            Outcome::Loss => 0,
        }
    }

    fn offset(&self) -> i64 {
        match self {
            Outcome::Win => 1,
            Outcome::Draw => 0,
            Outcome::Loss => -1,
        }
    }
}

impl RPS {
    fn ordered(&self) -> i64 {
        match self {
            RPS::Rock => 2,
            RPS::Scissors => 1,
            RPS::Paper => 0,
        }
    }

    fn from_ordered(v: i64) -> RPS {
        match v.rem_euclid(3) {
            2 => RPS::Rock,
            1 => RPS::Scissors,
            0 => RPS::Paper,
            _ => panic!("impossible"),
        }
    }

    fn value(&self) -> i64 {
        match self {
            RPS::Rock => 1,
            RPS::Paper => 2,
            RPS::Scissors => 3,
        }
    }

    fn outcome(&self, other: RPS) -> Outcome {
        match (self.ordered() - other.ordered()).rem_euclid(3) {
            2 => Outcome::Loss,
            1 => Outcome::Win,
            0 => Outcome::Draw,
            _ => panic!("impossible"),
        }
    }
}

fn hand_to_play(opponent: RPS, outcome: Outcome) -> RPS {
    RPS::from_ordered(opponent.ordered() + outcome.offset())
}

fn parse_player_one(char: char) -> Result<RPS, Fail> {
    match char {
        'A' => Ok(RPS::Rock),
        'B' => Ok(RPS::Paper),
        'C' => Ok(RPS::Scissors),
        other => Err(Fail::new(format!("unknown player one value {}", other))),
    }
}

fn parse_player_two(char: char) -> Result<RPS, Fail> {
    match char {
        'X' => Ok(RPS::Rock),
        'Y' => Ok(RPS::Paper),
        'Z' => Ok(RPS::Scissors),
        other => Err(Fail::new(format!("unknown player two value {}", other))),
    }
}

fn parse_outcome(char: char) -> Result<Outcome, Fail> {
    match char {
        'X' => Ok(Outcome::Loss),
        'Y' => Ok(Outcome::Draw),
        'Z' => Ok(Outcome::Win),
        other => Err(Fail::new(format!("unknown player two value {}", other))),
    }
}

fn parse_line_part_1(str: &str) -> Result<(RPS, RPS), Fail> {
    match str.chars().collect::<Vec<_>>().as_slice() {
        [player_one, ' ', player_two] => Ok((
            parse_player_one(*player_one)?,
            parse_player_two(*player_two)?,
        )),
        _ => Err(Fail::new(format!("couldn't parse line {}", str))),
    }
}

fn score_1(round: (RPS, RPS)) -> i64 {
    round.1.outcome(round.0).value() + round.1.value()
}

fn parse_line_part_2(str: &str) -> Result<(RPS, Outcome), Fail> {
    match str.chars().collect::<Vec<_>>().as_slice() {
        [player_one, ' ', player_two] => {
            Ok((parse_player_one(*player_one)?, parse_outcome(*player_two)?))
        }
        _ => Err(Fail::new(format!("couldn't parse line {}", str))),
    }
}

fn score_2(round: (RPS, Outcome)) -> i64 {
    hand_to_play(round.0, round.1).value() + round.1.value()
}

fn main() -> io::Result<()> {
    let args = env::args().collect::<Vec<_>>();
    let path = args
        .get(1)
        .ok_or(Fail::new("usage: day_one [path]".to_owned()))?;
    let file = File::open(path)?;
    let lines = io::BufReader::new(file).lines();

    let mut total_score_1: i64 = 0;
    let mut total_score_2: i64 = 0;

    for try_line in lines {
        let line = try_line?;
        let round_1 = parse_line_part_1(&line)?;
        total_score_1 += score_1(round_1);

        let round_2 = parse_line_part_2(&line)?;
        total_score_2 += score_2(round_2);
    }

    println!("part 1: {}", total_score_1);
    println!("part 2: {}", total_score_2);
    Ok(())
}
