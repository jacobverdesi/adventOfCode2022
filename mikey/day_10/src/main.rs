fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_10 [path]")?;
    let lines = common::open_lines(&path)?.map(|line| line.expect("error parsing line"));

    let mut cycles = Vec::<i64>::new();

    let mut reg: i64 = 1;

    for line in lines {
        match line.split(" ").collect::<Vec<_>>().as_slice() {
            ["noop"] => cycles.push(reg), // skip a cycle
            ["addx", num] => {
                let n = str::parse::<i64>(num).expect("error parsing number");
                for _ in 0..2 {
                    cycles.push(reg);
                }
                reg += n;
            }
            x => panic!("unexpected input: {:?}", x),
        }
    }

    {
        // part one
        let interesting = [20, 60, 100, 140, 180, 220];

        let answer: i64 = cycles
            .iter()
            .enumerate()
            .map(|(i, reg)| (i + 1, reg))
            .filter(|(i, _)| interesting.contains(i))
            .map(|(i, reg)| (i as i64) * reg)
            .sum();
        println!("part one: {}", answer);
    }

    {
        // part two
        for (index, reg) in cycles.iter().enumerate() {
            let position = index % 40;
            let sprite = (reg - 1)..(reg + 2);
            if sprite.contains(&(position as i64)) {
                print!("#")
            } else {
                print!(".")
            }
            if position == 39 {
                println!();
            }
        }
    }

    Ok(())
}
