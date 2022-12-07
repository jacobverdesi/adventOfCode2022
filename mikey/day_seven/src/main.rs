enum Node {
    File(u64),
    Directory(Directory),
}

struct Directory {
    size: u64,
    children: Vec<Node>,
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
        match &directory.children[i] {
            Node::File(_) => {}
            Node::Directory(d) => all_directory_sizes(&d, sizes),
        }
    }
}

fn build_directory(lines: &[String], current_line: &mut usize, current_directory: &mut Directory) {
    let mut finished = false;

    while !finished {
        if let Some(line) = lines.get(*current_line) {
            let split_line = line.split(" ").collect::<Vec<_>>();
            match &split_line[..] {
                ["$", "ls"] => {
                    *current_line += 1;
                }
                ["$", "cd", ".."] => {
                    *current_line += 1;
                    finished = true;
                }
                ["$", "cd", _] => {
                    current_directory
                        .children
                        .push(Node::Directory(Directory::new()));
                    let idx = current_directory.children.len() - 1;
                    let next_directory = match current_directory.children.get_mut(idx) {
                        Some(Node::Directory(x)) => x,
                        _ => panic!("expected directory at the end of current directory"),
                    };
                    *current_line += 1;
                    build_directory(lines, current_line, next_directory);
                    current_directory.size += next_directory.size;
                }
                ["dir", _] => {
                    *current_line += 1;
                }
                [size_str, _filename] => {
                    let size = size_str
                        .parse::<u64>()
                        .expect(&format!("couldn't parse size {}", size_str));
                    current_directory.children.push(Node::File(size));
                    current_directory.size += size;
                    *current_line += 1;
                }
                _ => {
                    *current_line += 1;
                    finished = true;
                }
            }
        } else {
            finished = true;
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
