#[allow(unused_imports)]
use std::cmp::{max, min, Ordering, Reverse};
#[allow(unused_imports)]
use std::collections::{BTreeMap, BTreeSet, BinaryHeap, HashMap, HashSet, VecDeque};
#[allow(unused_imports)]
use std::io::{stdin, stdout, BufWriter, Write};
#[allow(unused_imports)]
use std::iter::FromIterator;

// TEMPLATE BEGIN
mod util {
    use std::fmt::Debug;
    use std::io::{stdin, stdout, BufWriter, StdoutLock};
    use std::str::FromStr;

    #[allow(dead_code)]
    pub fn line() -> String {
        let mut line: String = String::new();
        stdin().read_line(&mut line).unwrap();
        line.trim().to_string()
    }

    #[allow(dead_code)]
    pub fn chars() -> Vec<char> {
        line().chars().collect()
    }

    #[allow(dead_code)]
    pub fn gets<T: FromStr>() -> Vec<T>
        where
            <T as FromStr>::Err: Debug,
    {
        let mut line: String = String::new();
        stdin().read_line(&mut line).unwrap();
        line.split_whitespace()
            .map(|t| t.parse().unwrap())
            .collect()
    }

    #[allow(dead_code)]
    pub fn with_bufwriter<F: FnOnce(BufWriter<StdoutLock>)>(f: F) {
        let out = stdout();
        let writer = BufWriter::new(out.lock());
        f(writer)
    }
}

#[allow(unused_macros)]
macro_rules! get {
      ([$t:ty]) => {
          {
              let mut line: String = String::new();
              stdin().read_line(&mut line).unwrap();
              line.split_whitespace()
                  .map(|t| t.parse::<$t>().unwrap())
                  .collect::<Vec<_>>()
          }
      };
      ([$t:ty]; $n:expr) => {
          (0..$n).map(|_| get!([$t])).collect::<Vec<_>>()
      };
      ($t:ty) => {
          {
              let mut line: String = String::new();
              stdin().read_line(&mut line).unwrap();
              line.trim().parse::<$t>().unwrap()
          }
      };
      ($($t:ty),*) => {
          {
              let mut line: String = String::new();
              stdin().read_line(&mut line).unwrap();
              let mut iter = line.split_whitespace();
              (
                  $(iter.next().unwrap().parse::<$t>().unwrap(),)*
              )
          }
      };
      ($t:ty; $n:expr) => {
          (0..$n).map(|_|
              get!($t)
          ).collect::<Vec<_>>()
      };
      ($($t:ty),*; $n:expr) => {
          (0..$n).map(|_|
              get!($($t),*)
          ).collect::<Vec<_>>()
      };
  }

const BIG_STACK_SIZE: bool = true;

#[allow(dead_code)]
fn main() {
    use std::thread;
    if BIG_STACK_SIZE {
        thread::Builder::new()
            .stack_size(32 * 1024 * 1024)
            .name("solve".into())
            .spawn(solve)
            .unwrap()
            .join()
            .unwrap();
    } else {
        solve();
    }
}
// TEMPLATE END

fn solve() {
    // get!(type_0, ..., type_k-1; repetition)

    // let (v, e) = get!(usize, usize);
    // let edges = get!(usize, usize; e);
    // let mut g = vec![Vec::new(); v];
    // for (s, t) in edges { g[s].push(t); }

    util::with_bufwriter(|mut out| {
        writeln!(out, "Hello World!").unwrap();
    });
}