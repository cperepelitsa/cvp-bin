# cvp-bin

Dumping ground for miscellaneous CLI utilities I've made over the years.  
Many were written when I was much dumber and not updated much since, so there are
undoubtedly bugs galore, and not much effort has been made to make anything
platform-independent. Use at your own risk.

All say what they do at the top of the respective source file.
Most also say useful things when run with "-h" or without arguments.

`make` and `make clean` are your friends.

# Tools

- **arith**: outputs some statistical information for a list of numbers

- **badchar**: check files for bytes outside the pretty/printable ASCII range

- **cstat**: dumps the C stat(2) struct for a file

- **decolor**: extremely simple `sed` filter to remove terminfo color escapes

- **exts**: outputs counts by file extension of a list of files

- **floatdump**: dumps IEEE 754 binary representation of floats

- **genpass**: generates passwords

- **gzipip**: compresses a file in-place (very dangerous)

- **lsd**: list directories in current working dir

- **lsf**: list files in current working dir

- **minus**: filters out arguments from list given on stdin

- **pacman-group**: reformat output of `pacman` and `yay` into columns

- **pargrep**: find paragraphs in indented notes

- **rfile**: choose a random file

- **shf**: filter lines of input according to exit code of a shell command

- **statv**: dumps everything coreutils' `stat` binary can tell you, somewhat nicely

- **swapnames**: swaps the names of two files

- **tdiff**: outputs duration between timestamps

- **vcut**: runs mpv; screenshots taken determine start/end times for clips to extract
  (requires mpv, ffmpeg, and dc)

- **vinf**: dump basic audio and video encoding information for media files (requires
  ffmpeg)

- **wgetr**: recursively download an offline copy of a website
