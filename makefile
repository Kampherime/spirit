default:
	@echo "No command specified. Usage:"
	@echo "    build: Compiles the program."
	@echo "    run: Compiles the program and runs it."
	@echo "    tests: Runs the test suite."
	@echo "    clean: Removes the binary files."

all: 
	if [ ! -d ./bin ]; then mkdir bin && echo "Did not find bin. Made bin instead."; fi

build: 
	make -s all
	gcc -o ./bin/main src/main.c

run: 
	make -s all
	gcc -o ./bin/main src/main.c && ./bin/main

# I have 10 dashes on either side. That's how I like to organize test suites, 
# but you don't have to do it this way.
tests: 
	make -s all
	gcc -o ./bin/test test/main_test.c 
	@echo "----------BEGINNING OF TEST SUITE----------"
	./bin/test
	@echo "----------   END OF TEST SUITE   ----------"

clean: 
	rm -r bin
