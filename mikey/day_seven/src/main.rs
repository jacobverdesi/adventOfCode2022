enum Node {
    File(u64),
    Directory(Directory),
}

struct Directory {
    size: u64,
    children: Vec<Node>,
}

fn calc_part_1(directory: &Directory, total: &mut u64) {
    if directory.size <= 100000 {
        *total += directory.size;
    }
    for i in 0..directory.children.len() {
        match &directory.children[i] {
            Node::File(_) => {}
            Node::Directory(d) => calc_part_1(&d, total),
        }
    }
}

fn build_directory(lines: &[String], current_line: &mut usize, current_directory: &mut Directory) {
    let mut finished = false;

    while !finished {
        if let Some(line) = lines.get(*current_line) {
            let split_line = line.split(" ").collect::<Vec<_>>();
            match &split_line[..] {
                ["$", "ls"] => *current_line += 1,
                ["$", "cd", ".."] => {
                    *current_line += 1;
                    finished = true;
                }
                ["$", "cd", _] => {
                    current_directory.children.push(Node::Directory(Directory {
                        children: Vec::new(),
                        size: 0,
                    }));
                    let idx = current_directory.children.len() - 1;
                    let next_directory = match current_directory.children.get_mut(idx) {
                        Some(Node::Directory(x)) => x,
                        _ => panic!("expected directory at the end of current directory"),
                    };
                    *current_line += 1;
                    build_directory(lines, current_line, next_directory);
                    current_directory.size += next_directory.size;
                }
                ["dir", _] => *current_line += 1,
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

    let mut root = Directory {
        size: 0,
        children: Vec::new(),
    };
    build_directory(&lines, &mut 0, &mut root);
    let mut total: u64 = 0;
    calc_part_1(&root, &mut total);
    println!("{}", total);

    Ok(())
}
