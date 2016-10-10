use std::collections::HashSet;
use std::env::args;
use std::io::{stdin, stderr, BufRead, Write};
use std::error::Error;
use std::process::exit;

fn fatal(msg: String) -> ! {
    let mut err_out = stderr();
    let _ = writeln!(err_out, "{}", msg);
    exit(1)
}

fn main() {
    let mut verbotten = HashSet::new();
    for arg in args().skip(1) {
        verbotten.insert(arg);
    }

    let stdin = stdin();
    for line_res in stdin.lock().lines() {
        if let Err(err) = line_res {
            fatal("read error: ".to_string() + err.description());
        }

        let line = line_res.unwrap();
        if !verbotten.contains(&line) {
            println!("{}", line);
        }
    }
}
