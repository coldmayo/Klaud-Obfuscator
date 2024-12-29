CC = gcc

TARGET = main

compile:
	@gcc -o main main.c obfuscate.c

run:
	@./main
