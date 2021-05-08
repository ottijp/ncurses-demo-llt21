# ncurses demo (LLT 21st)

This is the demonstration program for "LLT 21st".

## environment

* Mac OS X: 10.15
* compiler: Apple clang version 12.0.0 (clang-1200.0.32.29)
* ncurses: 5.4

## build

```
$ make
gcc -o bin/1_print_char -lncurses 1_print_char.c
gcc -o bin/2_change_format -lncurses 2_change_format.c
gcc -o bin/3_keyboard_mouse -lncurses 3_keyboard_mouse.c
```

## run

Run binaries which are generated into `bin` directory.

```
$ bin/1_print_char
$ bin/2_change_format
$ bin/3_keyboard_mouse
```

