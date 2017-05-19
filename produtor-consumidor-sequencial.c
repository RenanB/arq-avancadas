#include <pthread.h>
#include <stdio.h>
#include <windows.h>

#define TRUE 1
#define	MAX_ITEMS 3

int count = 0, in = 0, out = 0;

int contadorConsumo = 0;

int buffer[MAX_ITEMS];

void produtor()
{
    //Sleep(rand()%1000);
    buffer[in] = rand()%100;
    count++;
    printf("Produzindo buffer[%d] = %d\n", in, buffer[in]);
    in = (in + 1) % MAX_ITEMS;
}

void consumidor()
{
    int my_task;
    my_task = buffer[out];
    count--;
    printf("Consumindo buffer[%d] = %d\n", out, my_task);
    out = (out + 1) % MAX_ITEMS;

    contadorConsumo++;
}

int main(int argc, char *argv[])
{
	while (contadorConsumo < 100000)
	{
        produtor();
        consumidor();
	}
}
