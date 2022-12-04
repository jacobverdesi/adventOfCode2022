fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_four [path]")?;

    {
        // part one
        let lines = common::open_lines(&path)?;
        let fully_contained_pairs = lines
            .filter(|line| {
                let line = line.as_ref().expect("failed reading line");
                match line
                    .split(",")
                    .map(|assignment| {
                        assignment
                            .split("-")
                            .map(|s| s.parse::<i64>().expect("failed parsing"))
                    })
                    .flatten()
                    .collect::<Vec<_>>()
                    .as_slice()
                {
                    [a1, a2, b1, b2] => (a1 <= b1 && a2 >= b2) || (b1 <= a1 && b2 >= a2),
                    _ => panic!("failed pattern at line {}", line),
                }
            })
            .count();

        println!("part one: {}", fully_contained_pairs);
    }

    {
        // part two
        let lines = common::open_lines(&path)?;
        let partially_contained_pairs = lines
            .filter(|line| {
                let line = line.as_ref().expect("failed reading line");
                match line
                    .split(",")
                    .map(|assignment| {
                        assignment
                            .split("-")
                            .map(|s| s.parse::<i64>().expect("failed parsing"))
                    })
                    .flatten()
                    .collect::<Vec<_>>()
                    .as_slice()
                {
                    [a1, a2, b1, b2] => {
                        let r1 = *a1..*a2 + 1;
                        let r2 = *b1..*b2 + 1;
                        r1.contains(b1) || r1.contains(b2) || r2.contains(a1) || r2.contains(a2)
                    }
                    _ => panic!("failed pattern at line {}", line),
                }
            })
            .count();

        println!("part two: {}", partially_contained_pairs);
    }

    Ok(())
}
