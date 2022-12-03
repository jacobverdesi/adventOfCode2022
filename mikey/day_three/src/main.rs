use std::collections::BTreeSet;

fn priority(c: char) -> u32 {
    if c.is_lowercase() {
        // a = 97
        (c as u32) - 96
    } else {
        // A = 65
        (c as u32) - 38
    }
}

fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_three [path]")?;
    let lines = common::open_lines(&path)?;

    let sum: i64 = lines
        .map(|line| {
            let line = line.expect("failed reading line");
            let chars = line.chars().collect::<Vec<_>>();
            let (compartment_a, compartment_b) = chars.split_at(chars.len() / 2);
            let compartment_a_set: BTreeSet<char> = Vec::from(compartment_a).into_iter().collect();
            let compartment_b_set: BTreeSet<char> = Vec::from(compartment_b).into_iter().collect();
            compartment_a_set
                .intersection(&compartment_b_set)
                .map(|x| priority(*x))
                .sum::<u32>() as i64
        })
        .sum();

    println!("sum: {}", sum);

    Ok(())
}
