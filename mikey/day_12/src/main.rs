use std::collections::HashSet;

type Heightmap = Vec<i64>;

#[derive(Debug)]
struct Map {
    heightmap: Heightmap,
    width: usize,
    height: usize,
    destination: usize,
    start: usize,
}

fn build_map(lines: &[String]) -> Map {
    let mut heightmap = Heightmap::new();
    let mut width = 0;
    let mut height = 0;
    let mut destination = 0;
    let mut start = 0;
    let mut idx = 0;

    for line in lines {
        let line_trimmed = line[..].trim_end();
        width = line_trimmed.len();
        height += 1;
        for char in line_trimmed.chars() {
            match char {
                'E' => {
                    heightmap.push(25);
                    destination = idx;
                }
                'S' => {
                    heightmap.push(0);
                    start = idx;
                }
                letter => {
                    heightmap.push(letter as i64 - 97);
                }
            }
            idx += 1;
        }
    }

    Map {
        heightmap,
        width,
        height,
        destination,
        start,
    }
}

fn try_path(
    start: usize,
    map: &Map,
    distance_traveled: i64,
    existing_paths: &mut Vec<Option<i64>>,
) -> Option<i64> {
    if let Some(destination_distance) = existing_paths[map.destination] {
        if destination_distance <= distance_traveled {
            return None;
        }
    }
    if let Some(existing_distance) = existing_paths[start] {
        if existing_distance <= distance_traveled {
            return None;
        }
    }
    if start == map.destination {
        existing_paths[start] = Some(distance_traveled);
        return Some(distance_traveled);
    }

    existing_paths[start] = Some(distance_traveled);

    let current_height = map.heightmap[start];

    let mut candidates = Vec::new();
    if start + 1 % map.width != 0 && start < map.heightmap.len() - 1 {
        candidates.push(start + 1);
    }
    if start % map.width != 0 {
        candidates.push(start - 1);
    }
    if start / map.width != 0 {
        candidates.push(start - map.width);
    }
    if start / map.width != (map.height - 1) {
        candidates.push(start + map.width);
    }

    candidates
        .into_iter()
        .filter(|idx| map.heightmap[*idx] - current_height <= 1)
        .filter_map(|idx| try_path(idx, map, distance_traveled + 1, existing_paths))
        .min()
}

fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_12 [path]")?;
    let lines = common::open_lines(&path)?
        .map(|line| line.expect("error parsing line"))
        .collect::<Vec<_>>();

    let map = build_map(&lines);
    let mut existing_paths = vec![None; map.heightmap.len()];

    println!(
        "part one {}",
        try_path(map.start, &map, 0, &mut existing_paths).expect("must be a way")
    );

    Ok(())
}
