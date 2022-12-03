use std::collections::BTreeSet;

fn priority(c: char) -> i64 {
    if c.is_lowercase() {
        // a = 97
        ((c as u32) - 96) as i64
    } else {
        // A = 65
        ((c as u32) - 38) as i64
    }
}

fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_three [path]")?;

    // since i'm allocating the whole vec in part two to use `chunks`, just do it here :(
    // other options: use a crate like itertools, use nightly for `array_chunks` iter method
    let lines_iter = common::open_lines(&path)?;
    let lines = lines_iter
        .map(|line| line.expect("failed reading line"))
        .collect::<Vec<String>>();

    // Part one
    {
        let sum: i64 = lines
            .iter()
            .map(|line| {
                let chars = line.chars().collect::<Vec<_>>();
                let (compartment_a, compartment_b) = chars.split_at(chars.len() / 2);
                let compartment_a_set: BTreeSet<char> =
                    Vec::from(compartment_a).into_iter().collect(); // are these allocations necessary?
                let compartment_b_set: BTreeSet<char> =
                    Vec::from(compartment_b).into_iter().collect();
                compartment_a_set
                    .intersection(&compartment_b_set)
                    .map(|x| priority(*x))
                    .sum::<i64>()
            })
            .sum();

        println!("part one: {}", sum);
    }

    // Part two
    {
        let sum: i64 = lines
            .chunks(3) // unstable has `array_chunks` which would avoid the Vec allocation
            .map(|elf_group| {
                elf_group
                    .iter()
                    .map(|line| line.chars().collect::<BTreeSet<char>>())
                    .reduce(|accum, set| {
                        accum
                            .intersection(&set)
                            .cloned()
                            .collect::<BTreeSet<char>>()
                    })
                    .expect("expected at least one element for reduce")
                    .iter()
                    .map(|x| priority(*x) as i64)
                    .sum::<i64>()
            })
            .sum();

        println!("part two: {}", sum);
    }

    Ok(())
}
