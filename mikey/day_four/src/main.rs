fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_four [path]")?;

    {
        // part one
        let lines = common::open_lines(&path)?;
        let fully_contained_pairs = lines.fold((0, 0), |(part_one, part_two), line| {
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
                    let fully_contained = (a1 - b1) * (a2 - b2) <= 0; // Suhas came up with this
                    let partially_contained = !(a2 < b1 || b2 < a1); // And this!
                    (
                        if fully_contained {
                            part_one + 1
                        } else {
                            part_one
                        },
                        if partially_contained {
                            part_two + 1
                        } else {
                            part_two
                        },
                    )
                }
                _ => panic!("failed pattern at line {}", line),
            }
        });

        println!("part one: {}", fully_contained_pairs.0);
        println!("part two: {}", fully_contained_pairs.1);
    }

    Ok(())
}
