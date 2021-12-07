# cvp-bin

Dumping ground for miscellaneous CLI utilities I've made over the years.  
Many were written when I was much dumber and not updated much since, so there are
undoubtedly bugs galore, and not much effort has been made to make anything
platform-independent. Use at your own risk.

All say what they do at the top of the respective source file.
Most also say useful things when run with "-h" or without arguments.

`make` and `make clean` are your friends.

# Tools

- **approve**: run a command for each file, prompt to keep or delete (requires zsh and rlwrap)

- **apt-search**: APT package search with more pleasant output

- **arith**: outputs some statistical information for a list of numbers

- **badchar**: check files for bytes outside the pretty/printable ASCII range

- **cstat**: dumps the C stat(2) struct for a file

- **decolor**: removes terminfo color escapes from text

- **exts**: outputs counts by file extension of a list of files

- **genpass**: generates passwords

- **git-squash**: squash commits in a dev branch into a single commit

- **gzipip**: compresses a file in-place (risky!)

- **joinl**: joins consecutive lines of text

- **jsonpp**: JSON pretty-printer with actually helpful options (requires `jq`)

- **manless**: wrapper that adds a simple theme to the `less` pager when viewing `man` pages

- **minus**: filters out arguments from list given on stdin

- **pargrep**: find paragraphs in indented notes

- **rfile**: choose a random file

- **shf**: filter lines of input according to exit code of a shell command

- **statv**: dumps everything coreutils' `stat` binary can tell you, somewhat nicely

- **swap**: swaps the names of two files

- **tdiff**: outputs duration between timestamps

- **tcopy**: copies stdin to a tmux buffer

- **tpaste**: pastes last tmux-buffer to stdout

- **xmlpp**: XML/HTML pretty-printer with actually helpful options (requires `xmllint`)
