struct Directory {
    size: u64,
    children: Vec<Directory>,
}

impl Directory {
    fn new() -> Directory {
        Directory {
            size: 0,
            children: Vec::new(),
        }
    }
}

fn all_directory_sizes(directory: &Directory, sizes: &mut Vec<u64>) {
    sizes.push(directory.size);
    for i in 0..directory.children.len() {
        all_directory_sizes(&directory.children[i], sizes);
    }
}

fn build_directory(lines: &[String], current_line: &mut usize, current_directory: &mut Directory) {
    let mut finished = false;

    while !finished {
        match lines.get(*current_line) {
            None => finished = true,
            Some(line) => {
                *current_line += 1;
                let words = line.split(" ").collect::<Vec<_>>();
                match &words[..] {
                    ["$", "cd", ".."] => finished = true,
                    ["$", "cd", _] => {
                        let mut next_directory = Directory::new();
                        build_directory(lines, current_line, &mut next_directory);
                        current_directory.size += next_directory.size;
                        current_directory.children.push(next_directory);
                    }
                    ["$", "ls"] => {}
                    ["dir", _] => {}
                    [size_str, _filename] => {
                        let size = size_str.parse::<u64>().expect("couldn't parse size");
                        current_directory.size += size;
                    }
                    _ => finished = true,
                }
            }
        }
    }
}

fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_six [path]")?;
    let lines = common::open_lines(&path)?
        .map(|line| line.expect("error parsing line"))
        .collect::<Vec<_>>();

    let mut root = Directory::new();
    build_directory(&lines, &mut 0, &mut root);

    let mut sizes: Vec<u64> = Vec::new();
    all_directory_sizes(&root, &mut sizes);

    // part one
    let part_one_total = sizes
        .clone()
        .into_iter()
        .filter(|x| *x <= 100000)
        .sum::<u64>();
    println!("part one: {}", part_one_total);

    // part two
    let target_size = 70000000 - 30000000;
    let current_size: u64 = root.size;
    let mut part_two_candidate_set = sizes
        .into_iter()
        .filter(|x| *x > current_size - target_size)
        .collect::<Vec<_>>();
    part_two_candidate_set.sort();
    println!("part two: {}", part_two_candidate_set[0]);

    Ok(())
}
