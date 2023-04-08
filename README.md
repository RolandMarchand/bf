# Brainfuck Interpreter

This is a simple interpreter for the esoteric programming language Brainfuck, written in C.

## Usage

To run the interpreter, compile the source code and execute the resulting binary, passing the Brainfuck source code file as the only argument. For example:

```bash
gcc -o bf bf.c
./bf source.bf
```

## Features

The interpreter supports the following Brainfuck commands:

* `>` Increment the data pointer
* `<` Decrement the data pointer
* `+` Increment the value at the data pointer
* `-` Decrement the value at the data pointer
* `.` Output the value at the data pointer
* `,` Input a value and store it in the current data pointer
* `[` Jump past the matching `]` if the value at the data pointer is 0
* `]` Jump back to the matching `[` if the value at the data pointer is not 0

Any other characters in the source code are treated as comments and ignored.

# License
Copyright (C) 2022 2023 by Roland Marchand
roland.marchand@protonmail.com

Permission to use, copy, modify, and/or distribute this software for
any purpose with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.
