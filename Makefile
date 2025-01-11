CC = gcc

TARGET = main

compile:
	@gcc -o main main.c obfuscate.c utils.c

run:
	@./main test.c 2
