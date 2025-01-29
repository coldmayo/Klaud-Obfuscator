In the code I need to change some basic assembly phrases and change them in a way that confuses the decompiler

Here I will be listing some of my ideas

# 1
If we store the function into rax and call that that could potentally hide some things
```
call printf
```
becomes
```
lea f__1(%rip), %rax
call %rax
```

# 2
Use XOR for Arithemetic Operations
```
mov eax, 5
add eax, 3
```
becomes
```
mov eax, 8
xor eax, 3
```

# 3
push address to the stack
```
call func
```
becomes
```
push func
ret
```

# 4
Use come esoteric alternatives?
```
mov eax, ebx
```
becomes
```
xchg eax, ebx
```

# 5
```
push eax
```
becomes
```
sub esp, 4
mov [esp], eax
```

