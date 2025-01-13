compile:
	@gcc -o KlaudObfuscator main.c obfuscate.c utils.c

run:
	@./KlaudObfuscator test.c 2
