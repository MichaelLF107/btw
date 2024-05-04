all:
	gcc main.c host.c cpu.c system.c -o main
	./main