use common::parser;
use std::cmp::{max, min};
use std::collections::HashSet;

type Point = (i64, i64);
type Line = (Point, Point);

fn parse_point(line: &str, cursor: &mut usize) -> Result<Point, String> {
    let x = parser::int(line, cursor)?;
    parser::char(',', line, cursor)?;
    let y = parser::int(line, cursor)?;
    Ok((x, y))
}

fn parse_points(line: &str, cursor: &mut usize) -> Vec<Point> {
    parser::sep_by(
        |line, cursor| parser::str(" -> ", line, cursor),
        |line, cursor| parse_point(line, cursor),
        line,
        cursor,
    )
}

struct Coords {
    first: Point,
    last: Point,
    finished: bool,
}

impl Coords {
    fn new(first: Point, last: Point) -> Coords {
        Coords {
            first,
            last,
            finished: false,
        }
    }
}

impl Iterator for Coords {
    type Item = Point;

    fn next(&mut self) -> Option<Self::Item> {
        if self.finished {
            None
        } else if self.first == self.last {
            self.finished = true;
            Some(self.first)
        } else {
            let old_first = self.first.clone();
            self.first = (
                self.first.0 + max(-1, min(1, self.last.0 - self.first.0)),
                self.first.1 + max(-1, min(1, self.last.1 - self.first.1)),
            );
            Some(old_first)
        }
    }
}

fn drop_sand(
    sand_at: Point,
    occupied_points: &mut HashSet<Point>,
    min_x: i64,
    max_x: i64,
    max_y: i64,
) -> bool {
    match sand_at {
        (x, _) if x < min_x => true,
        (x, _) if x > max_x => true,
        (_, y) if y > max_y => true,
        (x, y) => {
            let down = occupied_points.contains(&(x, y + 1));
            if !down {
                return drop_sand((x, y + 1), occupied_points, min_x, max_x, max_y);
            }
            let down_left = occupied_points.contains(&(x - 1, y + 1));
            let down_right = occupied_points.contains(&(x + 1, y + 1));

            if !down_left {
                return drop_sand((x - 1, y + 1), occupied_points, min_x, max_x, max_y);
            }
            if !down_right {
                return drop_sand((x + 1, y + 1), occupied_points, min_x, max_x, max_y);
            }

            println!("drop at {} {}", x, y);
            occupied_points.insert((x, y));
            return false;
        }
    }
}

fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_13 [path]")?;

    let mut occupied_points: HashSet<Point> = HashSet::new();
    let mut min_x: Option<i64> = None;
    let mut max_x: Option<i64> = None;
    let mut max_y: Option<i64> = None;

    for line in common::open_lines(&path)?.map(|line| line.expect("error reading line")) {
        let mut prev_point: Option<Point> = None;
        let points = parse_points(&line, &mut 0);
        for point in points {
            if min_x.map(|x| point.0 < x).unwrap_or(true) {
                min_x = Some(point.0)
            }
            if max_x.map(|x| point.0 > x).unwrap_or(true) {
                max_x = Some(point.0)
            }
            if max_y.map(|y| point.1 > y).unwrap_or(true) {
                max_y = Some(point.1)
            }
            if let Some(prev_point) = prev_point {
                let coords = Coords::new(prev_point, point);
                for coord in coords {
                    occupied_points.insert(coord);
                }
            }
            prev_point = Some(point);
        }
    }

    let min_x = min_x.expect("didn't get min x");
    let max_x = max_x.expect("didn't get max x");
    let max_y = max_y.expect("didn't get max y");

    let mut count = 0;

    while !drop_sand((500, 0), &mut occupied_points, min_x, max_x, max_y) {
        count += 1;
    }

    println!("{}", count);

    Ok(())
}
