type Parser<T> = fn(line: &str, cursor: &mut usize) -> Result<T, String>;

pub fn try_or<A>(
    first: Parser<A>,
    second: Parser<A>,
    line: &str,
    cursor: &mut usize,
) -> Result<A, String> {
    match first(line, cursor) {
        r @ Ok(_) => r,
        _ => second(line, cursor),
    }
}

pub fn sep_by<S, T>(sep: Parser<S>, parser: Parser<T>, line: &str, cursor: &mut usize) -> Vec<T>
where
    T: std::fmt::Debug,
{
    let mut list = Vec::new();

    while let Ok(v) = parser(line, cursor) {
        list.push(v);
        if sep(line, cursor).is_err() {
            break;
        }
    }

    list
}

pub fn int(line: &str, cursor: &mut usize) -> Result<i64, String> {
    let len = peek_while(|c| c.is_ascii_digit(), line, *cursor);
    let slice = &line[*cursor..*cursor + len];
    match str::parse::<i64>(slice) {
        Ok(s) => {
            *cursor += len;
            Ok(s)
        }
        Err(_) => Err(format!("expected int, got {}", &line[*cursor..])),
    }
}

pub fn peek_while(p: fn(char) -> bool, line: &str, cursor: usize) -> usize {
    line[cursor..].chars().take_while(|c| p(*c)).count()
}

pub fn str<'a>(str: &'a str, line: &str, cursor: &mut usize) -> Result<&'a str, String> {
    check_len(line, *cursor + str.len())?;
    if line[*cursor..*cursor + str.len()].starts_with(str) {
        *cursor += str.len();
        Ok(str)
    } else {
        Err(format!("expected {}", str))
    }
}

pub fn char(char: char, line: &str, cursor: &mut usize) -> Result<char, String> {
    check_len(line, *cursor)?;
    let candidate = line.chars().nth(*cursor).unwrap();
    if char == candidate {
        *cursor += 1;
        Ok(char)
    } else {
        Err(format!("expected char {}, got {}", char, candidate))
    }
}

pub fn check_len(line: &str, cursor: usize) -> Result<(), String> {
    if cursor >= line.len() {
        Err("reached end of string".to_owned())
    } else {
        Ok(())
    }
}
