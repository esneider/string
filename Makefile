.SILENT:

build:
	clang *.c -o test

run: build
	./test
	rm test
