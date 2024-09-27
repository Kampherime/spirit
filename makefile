default:
	@echo "No Command specified. Usage:"
	@echo "    build: Compiles the program."
	@echo "    run: Compiles the program and runs it."

all: 
	if [ ! -d ./bin ]; then mkdir bin && echo "Did not find bin. Made bin instead."; fi

build: 
	make -s all
	gcc -o ./bin/main src/main.c

run: 
	make -s all
	gcc -o ./bin/main src/main.c && ./bin/main
