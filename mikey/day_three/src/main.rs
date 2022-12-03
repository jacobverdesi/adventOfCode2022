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

    // Part one
    {
        let lines = common::open_lines(&path)?;
        let sum: i64 = lines
            .map(|line| {
                let line = line.expect("failed reading line");
                let chars = line.chars().collect::<Vec<_>>();
                let (compartment_a, compartment_b) = chars.split_at(chars.len() / 2);
                let compartment_a_set: BTreeSet<char> =
                    Vec::from(compartment_a).into_iter().collect();
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
        let lines = common::open_lines(&path)?;
        let sum: i64 = lines
            .collect::<Vec<_>>()
            .chunks(3) // unstable has `array_chunks` which would avoid the Vec allocation
            .map(|elf_group| {
                elf_group
                    .iter()
                    .map(|line| {
                        line.as_ref() // move from a reference to a result of T -> result of a reference of T
                            .expect("error reading line")
                            .chars()
                            .collect::<BTreeSet<char>>()
                    })
                    .reduce(|accum, set| {
                        accum
                            .intersection(&set)
                            .cloned()
                            .collect::<BTreeSet<char>>()
                    })
                    .expect("expected element for reduce")
                    .iter()
                    .map(|x| priority(*x) as i64)
                    .sum::<i64>()
            })
            .sum();

        println!("part two: {}", sum);
    }

    Ok(())
}
