compile:
	@gcc -o KlaudObfuscator main.c obfuscate.c jumble.c utils.c

run:
	@./KlaudObfuscator test.c 2
