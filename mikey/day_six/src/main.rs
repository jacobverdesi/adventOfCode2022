use std::collections::HashSet;

fn get_marker(string: &str, num_distinct: usize) -> Option<usize> {
    for i in num_distinct - 1..string.len() {
        let candidate_string = &string[i - (num_distinct - 1)..(i + 1)];
        let set = candidate_string.chars().collect::<HashSet<_>>();
        if set.len() == num_distinct {
            return Some(i);
        }
    }
    None
}

fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_six [path]")?;
    let lines = common::open_lines(&path)?
        .map(|line| line.expect("error reading line"))
        .collect::<Vec<String>>();
    let first_line = lines.get(0).expect("must have at least one line");

    let first_answer = get_marker(&first_line, 4).expect("no result for answer 1");
    let second_answer = get_marker(&first_line, 14).expect("no result for answer 2");

    println!("first answer: {}", first_answer + 1);
    println!("second answer: {}", second_answer + 1);

    Ok(())
}
