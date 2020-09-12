#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "filosofo.h"
#define MAX_CADEIRAS 5
#define MAX_FILOSOFOS MAX_CADEIRAS

int main(int argc, char *argv[])
{
	int i;
	mesa_t* mesa;
	const char* filosofos[MAX_FILOSOFOS] =
	{
		"Parmênides", "Platão", "Tales", "Sócrates", "Aristóteles"
	};

	setlocale(LC_ALL, "");
	mesa = mesa_criar(MAX_CADEIRAS);
	for(i = 0; i < MAX_CADEIRAS; i++)
		filosofo_criar(filosofos[i], mesa);
	mesa_destruir(mesa);
	return 0;
}
