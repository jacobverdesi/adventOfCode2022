use common::parser;
use std::cmp::{max, min};
use std::collections::HashSet;

type Point = (i64, i64);

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
    has_floor: bool,
    min_x: i64,
    max_x: i64,
    max_y: i64,
) -> bool {
    match sand_at {
        (x, _) if !has_floor && x < min_x => false,
        (x, _) if !has_floor && x > max_x => false,
        (_, y) if !has_floor && y > max_y => false,
        (x, y) => {
            let center = !occupied_points.contains(&(x, y));
            let down = !occupied_points.contains(&(x, y + 1));
            let down_left = !occupied_points.contains(&(x - 1, y + 1));
            let down_right = !occupied_points.contains(&(x + 1, y + 1));
            let at_floor = has_floor && y == max_y + 1;

            if center == false {
                false
            } else if at_floor == true {
                occupied_points.insert((x, y));
                true
            } else if down == true {
                drop_sand((x, y + 1), occupied_points, has_floor, min_x, max_x, max_y)
            } else if down_left == true {
                drop_sand(
                    (x - 1, y + 1),
                    occupied_points,
                    has_floor,
                    min_x,
                    max_x,
                    max_y,
                )
            } else if down_right == true {
                drop_sand(
                    (x + 1, y + 1),
                    occupied_points,
                    has_floor,
                    min_x,
                    max_x,
                    max_y,
                )
            } else {
                occupied_points.insert((x, y));
                true
            }
        }
    }
}

fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_14 [path]")?;

    let mut occupied_points: HashSet<Point> = HashSet::new();
    let mut min_x: Option<i64> = None;
    let mut max_x: Option<i64> = None;
    let mut max_y: Option<i64> = None;

    // helper for either initializing or updating the Option<i64> values
    fn test_set<T: Copy>(p: fn(T, T) -> bool, candidate: T, el: &mut Option<T>) {
        if el.map(|inner| p(candidate, inner)).unwrap_or(true) {
            *el = Some(candidate);
        }
    }

    for line in common::open_lines(&path)?.map(|line| line.expect("error reading line")) {
        let mut prev_point: Option<Point> = None;
        let points = parse_points(&line, &mut 0);
        for point in points {
            test_set(|a, b| a < b, point.0, &mut min_x);
            test_set(|a, b| a > b, point.0, &mut max_x);
            test_set(|a, b| a > b, point.1, &mut max_y);
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

    {
        // part one
        let mut count = 0;
        let mut oc1 = occupied_points.clone();

        while drop_sand((500, 0), &mut oc1, false, min_x, max_x, max_y) {
            count += 1;
        }

        println!("part one: {}", count);
    }

    {
        // part two
        let mut count = 0;
        let mut oc2 = occupied_points.clone();

        while drop_sand((500, 0), &mut oc2, true, min_x, max_x, max_y) {
            count += 1;
        }

        println!("part two: {}", count);
    }

    Ok(())
}
