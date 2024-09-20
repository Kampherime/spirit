default:
	@echo "no cmd specified"

build: 
	gcc -o ./bin/main src/main.c

run: 
	gcc -o ./bin/main src/main.c && ./bin/main
