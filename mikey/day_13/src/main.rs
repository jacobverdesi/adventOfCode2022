use common::parser;
use std::cmp::Ordering;

#[derive(Eq, PartialEq, Clone, Debug)]
enum Packet {
    Integer(i64),
    List(Vec<Packet>),
}

impl Packet {
    fn is_ordered(&self, other: &Self) -> Option<bool> {
        match (self, other) {
            (Packet::Integer(x), Packet::Integer(y)) if x == y => None,
            (Packet::Integer(x), Packet::Integer(y)) => Some(x < y),
            (Packet::List(xs), Packet::List(ys)) => xs
                .iter()
                .zip(ys.iter())
                .find_map(|(x, y)| x.is_ordered(y))
                .or(if xs.len() == ys.len() {
                    None
                } else {
                    Some(xs.len() < ys.len())
                }),
            (x @ Packet::Integer(_), ys @ Packet::List(_)) => {
                Packet::List(vec![x.clone()]).is_ordered(ys)
            }
            (xs @ Packet::List(_), y @ Packet::Integer(_)) => {
                xs.is_ordered(&Packet::List(vec![y.clone()]))
            }
        }
    }
}

// this lets us call .sort() on a vec of packets
impl Ord for Packet {
    fn cmp(&self, other: &Self) -> Ordering {
        match self.is_ordered(other) {
            Some(ordered) => {
                if ordered {
                    Ordering::Less
                } else {
                    Ordering::Greater
                }
            }
            None => Ordering::Equal,
        }
    }
}

// what is the point of this?? apparently a requirement for Ord.
impl PartialOrd for Packet {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

fn parse_list(line: &str, cursor: &mut usize) -> Result<Vec<Packet>, String> {
    parser::char('[', line, cursor)?;
    let list = parser::sep_by(
        |line, cursor| parser::str(",", line, cursor),
        |line, cursor| parse_packet(line, cursor),
        line,
        cursor,
    );
    parser::char(']', line, cursor)?;
    Ok(list)
}

fn parse_packet(line: &str, cursor: &mut usize) -> Result<Packet, String> {
    parser::try_or(
        |line, cursor| parse_list(line, cursor).map(|list| Packet::List(list)),
        |line, cursor| parser::int(line, cursor).map(|int| Packet::Integer(int)),
        line,
        cursor,
    )
}

fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_13 [path]")?;
    let lines = common::open_lines(&path)?
        .map(|line| line.expect("error reading line"))
        .collect::<Vec<_>>();

    let packets = lines
        .iter()
        .filter_map(|line| {
            if !line.is_empty() {
                Some(parse_packet(line, &mut 0).expect("couldn't parse packet"))
            } else {
                None
            }
        })
        .collect::<Vec<_>>();

    {
        // part one
        println!(
            "part one: {}",
            packets
                .as_slice()
                .chunks(2)
                .enumerate()
                .filter_map(|(i, pair)| {
                    match &pair {
                        &[l, r] => {
                            if l.is_ordered(r).expect("unordered pair") {
                                Some(i + 1)
                            } else {
                                None
                            }
                        }
                        _ => panic!("unexpected non-pair el at index {}", i),
                    }
                })
                .sum::<usize>()
        );
    }

    {
        // part two
        let signals = vec![
            Packet::List(vec![Packet::List(vec![Packet::Integer(2)])]),
            Packet::List(vec![Packet::List(vec![Packet::Integer(6)])]),
        ];
        let mut packets = packets;
        packets.append(&mut signals.clone());
        packets.sort();
        println!(
            "part two: {}",
            packets
                .iter()
                .enumerate()
                .filter_map(|(i, packet)| {
                    if signals.contains(packet) {
                        Some(i + 1)
                    } else {
                        None
                    }
                })
                .product::<usize>()
        );
    }

    Ok(())
}
