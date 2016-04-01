all: main reverse_last_iteration_DES last_fFunction

main: main.c
	gcc -o DES -g main.c

reverse_last_iteration_DES: reverse_last_iteration_DES.c
	gcc -o reverse -g reverse_last_iteration_DES.c

last_fFunction: last_fFunction.c
	gcc -o fFunction -g last_fFunction.c

clean:
	rm DES
	rm reverse
	rm fFunction
