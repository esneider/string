.SILENT:

build:
	clang -std=c99 -Wall -Wextra -Werror -pedantic *.c -o test

run: build
	./test
	rm test
