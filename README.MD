
# Brainf**k interpreter by Rane Wallin
---
## What it is
Brainf**k is a [programming language created by Urban Müller](https://en.wikipedia.org/wiki/Brainfuck) in 1993. It is made up of 8 commands represented by the symbols [, ], <, >, :, ;, +, and -. This is an interpreter for a modified version of the language.

## Usage
The interpreter is written in C. To use it, download bf.c and compile it. For instance, on Linux run `gcc bf.c -o bf` from the command line. You can then run it with `./bf <filename>`.

### Optional Flags

-v | Verbose mode prints out the first 10 elements in the Code and Data arrays

-r | Repeat execution of code until user exits (control-C in Linux)

-p | Pause between each command, only works in verbose mode


