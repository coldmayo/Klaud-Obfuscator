# KlaudObfuscator

## The Gist

The Klaud Obfuscator takes C code, converts it to x86-64 assembly, does tranformations to make this code harder to read, and then compiles it into machine code.

What this does is make the resulting executable harder to understand when reversed engineered.

I am hoping to use this to make crackmes for myself and others.

## Use

```bash
# compile project code
$ make
# run program
$ ./main "c_file.c" 4
# arguments are the C file path and the # of layers of functions hiding main
```

## Why Klaud?

I just like him. He's my favorite character in all of media.
