all: client

client: client.o bignumber.o
	gcc client.o bignumer.o -lm -o client

client.o: client.c bignumer.h
	gcc -std=c99 -Wall -Wextra -Wvla -g -c client.c

bignumber.o: bignumber.c bignumber.h
	gcc -std=c99 -Wall -Wextra -Wvla -g -c bignumber.c