type Point = (i64, i64);

use common::parser;
use std::collections::HashSet;

fn parse_point(line: &str, cursor: &mut usize) -> Result<Point, String> {
    parser::str("x=", line, cursor)?;
    let x = parser::int(line, cursor)?;
    parser::str(", y=", line, cursor)?;
    let y = parser::int(line, cursor)?;
    Ok((x, y))
}

fn parse_sensor(line: &str, cursor: &mut usize) -> Result<(Point, Point), String> {
    parser::str("Sensor at ", line, cursor)?;
    let sensor = parse_point(line, cursor)?;
    parser::str(": closest beacon is at ", line, cursor)?;
    let beacon = parse_point(line, cursor)?;
    Ok((sensor, beacon))
}

fn manhattan_distance(a: Point, b: Point) -> i64 {
    (a.0 - b.0).abs() + (a.1 - b.1).abs()
}

fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_15 [path]")?;

    let lines = common::open_lines(&path)?.map(|line| line.expect("error parsing line"));

    let mut sensors = Vec::new();
    let mut occupied = HashSet::new();
    let mut max_distance_left = 0;
    let mut max_distance_right = 0;

    for line in lines {
        let (sensor, beacon) = parse_sensor(&line, &mut 0).expect("couldn't parse sensor");
        let distance = manhattan_distance(sensor, beacon);
        occupied.insert(beacon);
        occupied.insert(sensor);

        if max_distance_left > sensor.0 - distance {
            max_distance_left = sensor.0 - distance;
        }
        if max_distance_right < sensor.0 + distance {
            max_distance_right = sensor.0 + distance;
        }
        sensors.push((sensor, distance));
    }

    {
        // part one

        let mut count = 0;
        let y = 2000000;
        for x in max_distance_left..max_distance_right {
            let point = (x, y);
            if occupied.contains(&point) {
                continue;
            }
            for (sensor, distance) in sensors.iter() {
                let current_distance = manhattan_distance(*sensor, point);
                if *distance >= current_distance {
                    count += 1;
                    break;
                }
            }
        }

        println!("part one {}", count);
    }

    {
        // part two
        let mut answer = None;
        let max_coord = 4000000;
        for y in 0..max_coord {
            let mut x = 0;

            while x <= max_coord {
                if occupied.contains(&(x, y)) {
                    x += 1;
                }
                let mut sensor_tripped = false;
                for (sensor, distance) in &sensors {
                    let point = (x, y);
                    let current_distance = manhattan_distance(*sensor, point);
                    if *distance >= current_distance {
                        sensor_tripped = true;
                        x += (distance - current_distance) + 1;
                    }
                }
                if !sensor_tripped {
                    answer = Some((x, y));
                    break;
                }
            }
            if answer.is_some() {
                break;
            }
        }

        let answer = answer.expect("didn't get answer");

        println!("part two {}", answer.0 * 4000000 + answer.1);
    }

    Ok(())
}
