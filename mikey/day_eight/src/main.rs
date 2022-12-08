struct Forest {
    rows: Vec<Vec<u32>>,
    cols: Vec<Vec<u32>>,
}

impl Forest {
    fn from_rows(rows: Vec<Vec<u32>>) -> Forest {
        let cols = transpose(&rows);
        Forest { rows, cols }
    }

    fn walk(&self) -> ForestWalker {
        ForestWalker {
            x: 0,
            y: 0,
            forest: self,
        }
    }

    fn is_visible(&self, x: usize, y: usize) -> bool {
        let row_max = self.rows.len();
        let col_max = self.cols.len();

        if x == 0 || y == 0 || x == (row_max - 1) || y == (col_max - 1) {
            return true;
        }
        let item = self.rows[y][x];

        Self::largest_in_slice(item, &self.rows[y][0..x]) || // left
        Self::largest_in_slice(item, &self.rows[y][(x+1)..row_max]) || // right
        Self::largest_in_slice(item, &self.cols[x][0..y]) || // top
        Self::largest_in_slice(item, &self.cols[x][(y+1)..col_max]) // bottom
    }

    fn scenic_score(&self, x: usize, y: usize) -> u64 {
        let row_max = self.rows.len();
        let col_max = self.cols.len();
        let item = self.rows[y][x];

        Self::distance_to_block(item, &self.rows[y][0..x], true) * // left
        Self::distance_to_block(item, &self.rows[y][(x+1)..row_max], false) * // right
        Self::distance_to_block(item, &self.cols[x][0..y], true) * // top
        Self::distance_to_block(item, &self.cols[x][(y+1)..col_max], false) // bottom
    }

    fn largest_in_slice(tree: u32, slice: &[u32]) -> bool {
        slice.iter().max().expect("slice must be non-empty") < &tree
    }

    fn distance_to_block(tree: u32, slice: &[u32], reverse: bool) -> u64 {
        let len = slice.len();
        for i in 0..len {
            let candidate = if reverse {
                slice[(len - 1) - i]
            } else {
                slice[i]
            };
            if candidate >= tree {
                return i as u64 + 1;
            }
        }
        len as u64
    }
}

struct ForestWalker<'a> {
    x: usize,
    y: usize,
    forest: &'a Forest,
}

impl<'a> Iterator for ForestWalker<'a> {
    type Item = (usize, usize);

    fn next(&mut self) -> Option<(usize, usize)> {
        let x = self.x;
        let y = self.y;

        if x < self.forest.cols.len() && y < self.forest.rows.len() {
            if x + 1 < self.forest.cols.len() {
                self.x += 1;
            } else {
                self.x = 0;
                self.y += 1;
            }
            Some((x, y))
        } else {
            None
        }
    }
}

fn transpose<T>(v: &Vec<Vec<T>>) -> Vec<Vec<T>>
where
    T: Clone,
{
    (0..v[0].len())
        .map(|x| (0..v.len()).map(|y| v[y][x].clone()).collect::<Vec<_>>())
        .collect::<Vec<_>>()
}

fn main() -> std::io::Result<()> {
    let path = common::get_first_arg("usage: day_eight [path]")?;
    let lines = common::open_lines(&path)?;
    let rows = lines
        .map(|l| {
            let line = l.expect("error parsing line");
            line.chars()
                .map(|c| c.to_digit(10).expect("error parsing char"))
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    let forest = Forest::from_rows(rows);

    println!(
        "part one: {}",
        forest
            .walk()
            .filter(|(x, y)| forest.is_visible(*x, *y))
            .count()
    );
    println!(
        "part two: {}",
        forest
            .walk()
            .map(|(x, y)| forest.scenic_score(x, y))
            .max()
            .expect("no trees!")
    );

    Ok(())
}
