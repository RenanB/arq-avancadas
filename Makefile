all: produtor-consumidor produtor-consumidor-v2

produtor-consumidor: produtor-consumidor.c
	gcc -pthread -o produtor-consumidor produtor-consumidor.c
produtor-consumidor-v2: produtor-consumidor-v2.c
	gcc -pthread -o produtor-consumidor-v2 produtor-consumidor-v2.c
clean:
	rm -f produtor-consumidor produtor-consumidor-V2
