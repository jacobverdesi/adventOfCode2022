use std::env;
use std::fs::File;
use std::io::{self, BufRead, Error, ErrorKind};

struct Fail {
    pub message: String,
}

impl Fail {
    fn new(message: String) -> Fail {
        Fail { message }
    }
}

impl From<Fail> for io::Error {
    fn from(error: Fail) -> Self {
        Error::new(ErrorKind::Other, error.message)
    }
}

#[derive(Clone, Copy, Debug, PartialEq)]
enum Hand {
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

impl Hand {
    fn ordered(&self) -> i64 {
        match self {
            Hand::Rock => 2,
            Hand::Scissors => 1,
            Hand::Paper => 0,
        }
    }

    fn value(&self) -> i64 {
        match self {
            Hand::Rock => 1,
            Hand::Paper => 2,
            Hand::Scissors => 3,
        }
    }

    fn outcome_from_other_hand(&self, other: Hand) -> Outcome {
        match (self.ordered() - other.ordered()).rem_euclid(3) {
            2 => Outcome::Loss,
            1 => Outcome::Win,
            0 => Outcome::Draw,
            _ => panic!("impossible"),
        }
    }

    fn other_hand_from_outcome(&self, outcome: Outcome) -> Hand {
        match (self.ordered() + outcome.offset()).rem_euclid(3) {
            2 => Hand::Rock,
            1 => Hand::Scissors,
            0 => Hand::Paper,
            _ => panic!("impossible"),
        }
    }
}

fn parse_player_one(char: char) -> Result<Hand, Fail> {
    match char {
        'A' => Ok(Hand::Rock),
        'B' => Ok(Hand::Paper),
        'C' => Ok(Hand::Scissors),
        other => Err(Fail::new(format!("unknown player one value {}", other))),
    }
}

fn parse_player_two(char: char) -> Result<Hand, Fail> {
    match char {
        'X' => Ok(Hand::Rock),
        'Y' => Ok(Hand::Paper),
        'Z' => Ok(Hand::Scissors),
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

fn parse_line<A, B>(
    str: &str,
    first_parser: fn(char) -> Result<A, Fail>,
    second_parser: fn(char) -> Result<B, Fail>,
) -> Result<(A, B), Fail> {
    match str.chars().collect::<Vec<_>>().as_slice() {
        [first, ' ', second] => Ok((first_parser(*first)?, second_parser(*second)?)),
        _ => Err(Fail::new(format!("couldn't parse line {}", str))),
    }
}

fn main() -> io::Result<()> {
    let args = env::args().collect::<Vec<_>>();
    let path = args
        .get(1)
        .ok_or_else(|| Fail::new("usage: day_one [path]".to_owned()))?;
    let file = File::open(path)?;
    let lines = io::BufReader::new(file).lines();

    let mut total_score_1: i64 = 0;
    let mut total_score_2: i64 = 0;

    for try_line in lines {
        let line = try_line?;

        // Q1 calculation
        {
            let (p1_hand, p2_hand) = parse_line(&line, parse_player_one, parse_player_two)?;
            total_score_1 += p2_hand.outcome_from_other_hand(p1_hand).value() + p2_hand.value();
        }

        // Q2 calculation
        {
            let (p1_hand, outcome) = parse_line(&line, parse_player_one, parse_outcome)?;
            total_score_2 += p1_hand.other_hand_from_outcome(outcome).value() + outcome.value();
        }
    }

    println!("part 1: {}", total_score_1);
    println!("part 2: {}", total_score_2);
    Ok(())
}
