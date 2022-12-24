use std::env;
use std::fs::File;
use std::io::{self, BufRead, BufReader, Error, ErrorKind, Lines};

pub mod parser;

pub struct Fail {
    pub message: String,
}

impl Fail {
    pub fn new(message: String) -> Fail {
        Fail { message }
    }
}

impl From<Fail> for io::Error {
    fn from(error: Fail) -> Self {
        Error::new(ErrorKind::Other, error.message)
    }
}

// Takes ownership of element at `index` and consumes the Vec.
//
// see also: get_rekt
fn get_owned<T>(mut vec: Vec<T>, index: usize) -> Option<T> {
    if vec.get(index).is_none() {
        None
    } else {
        Some(vec.swap_remove(index))
    }
}

pub fn get_first_arg(usage: &str) -> Result<String, io::Error> {
    let args = env::args().collect::<Vec<_>>();
    let res = get_owned(args, 1).ok_or_else(|| Fail::new(usage.to_owned()))?;
    Ok(res)
}

pub fn open_lines(path: &str) -> Result<Lines<BufReader<File>>, io::Error> {
    let file = File::open(path)?;
    Ok(io::BufReader::new(file).lines())
}
