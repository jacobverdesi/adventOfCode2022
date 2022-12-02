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

impl RPS {
    fn ordered(&self) -> i32 {
        match self {
            RPS::Rock => 2,
            RPS::Scissors => 1,
            RPS::Paper => 0,
        }
    }

    fn value(&self) -> i64 {
        match self {
            RPS::Rock => 1,
            RPS::Paper => 2,
            RPS::Scissors => 3,
        }
    }

    fn outcome(&self, other: RPS) -> i64 {
        match (self.ordered(), other.ordered()) {
            (a, b) if (b + 1) % 3 == a => 6,
            (a, b) if a == b => 3,
            _ => 0,
        }
    }

    fn from_player_one(char: char) -> Result<RPS, Fail> {
        match char {
            'A' => Ok(RPS::Rock),
            'B' => Ok(RPS::Paper),
            'C' => Ok(RPS::Scissors),
            other => Err(Fail::new(format!("unknown player one value {}", other))),
        }
    }

    fn from_player_two(char: char) -> Result<RPS, Fail> {
        match char {
            'X' => Ok(RPS::Rock),
            'Y' => Ok(RPS::Paper),
            'Z' => Ok(RPS::Scissors),
            other => Err(Fail::new(format!("unknown player two value {}", other))),
        }
    }

    fn from_line(str: String) -> Result<(RPS, RPS), Fail> {
        match str.chars().collect::<Vec<_>>().as_slice() {
            [player_one, ' ', player_two] => Ok((
                Self::from_player_one(*player_one)?,
                Self::from_player_two(*player_two)?,
            )),
            _ => Err(Fail::new(format!("couldn't parse line {}", str))),
        }
    }

    fn score(round: (RPS, RPS)) -> i64 {
        round.1.outcome(round.0) + round.1.value()
    }
}

fn main() -> io::Result<()> {
    let args = env::args().collect::<Vec<_>>();
    let path = args
        .get(1)
        .ok_or(Fail::new("usage: day_one [path]".to_owned()))?;
    let file = File::open(path)?;
    let lines = io::BufReader::new(file).lines();

    let mut total_score: i64 = 0;

    for try_line in lines {
        let line = try_line?;
        let round = RPS::from_line(line)?;
        total_score += RPS::score(round);
    }

    println!("{}", total_score);
    Ok(())
}
