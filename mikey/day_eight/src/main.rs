struct Forest {
    rows: Vec<Vec<u32>>,
    cols: Vec<Vec<u32>>,
}

impl Forest {
    fn from_rows(rows: Vec<Vec<u32>>) -> Forest {
        let cols = transpose(&rows);
        Forest { rows, cols }
    }

    fn trees_visible(&self) -> u64 {
        let mut count = 0;

        for y in 0..self.rows.len() {
            for x in 0..self.cols.len() {
                if self.is_visible(x, y) {
                    count += 1
                }
            }
        }

        count
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

    fn largest_in_slice(i: u32, slice: &[u32]) -> bool {
        slice.iter().max().expect("slice must be non-empty") < &i
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

    println!("part one: {}", forest.trees_visible());

    Ok(())
}
