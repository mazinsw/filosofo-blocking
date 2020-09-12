#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

// na plataforma windows não existe a função sleep
#ifdef _WIN32
#  include <windows.h>
#  define sleep(a) Sleep(a)
#else
#  include <unistd.h>
#  define sleep(a) sleep(a/1000)
#endif
#include "filosofo.h"

struct filosofo
{
	mesa_t* mesa;
	cadeira_t* cadeira;
	const char* nome;
	FilosofoEstado estado;
	pthread_t thread;
};

static void* filosofo_iniciar(void* data)
{
	filosofo_t* f = (filosofo_t*)data;

	while(1)
	{
		filosofo_pensar(f);
		filosofo_comer(f);
	}
	return NULL;
}

static void acao_levantar(void* data)
{
	filosofo_t* f = (filosofo_t*)data;

// a ação de levantar espera pela boa vontade do filósofo de deixar a mesa
	pthread_join(f->thread, NULL);
	filosofo_destruir(f);
}

filosofo_t* filosofo_criar(const char* nome, mesa_t* mesa)
{
	filosofo_t* f;
	f = (filosofo_t*)malloc(sizeof(filosofo_t));
	f->mesa = mesa;
	f->nome = nome;
	f->estado = Ocioso;
	f->cadeira = mesa_sentar(f->mesa, f, acao_levantar);
	if(f->cadeira == NULL)
	{
		// nao há cadeira disponível na mesa
		free(f);
		return NULL;
	}
	pthread_create(&f->thread, NULL, filosofo_iniciar, (void*)f);
	return f;
}

void filosofo_pensar(filosofo_t* f)
{
	struct timeval tv;
	// o folósofo irá pensar por um intervalo de tempo não determinado
	unsigned int time = 1 + (rand() % 5);

	f->estado = Pensando;
	gettimeofday(&tv, NULL);
	printf("O filósofo %s está pensando...\t%ld.%ld s\n", f->nome, tv.tv_sec, tv.tv_usec);
	sleep(time * 1000);
}

void filosofo_comer(filosofo_t* f)
{
	struct timeval tv;
	unsigned int time = 1 + (rand() % 5);
	int conseguiu;

	conseguiu = mesa_pegar_garfos(f->cadeira);
	if(conseguiu)
	{
		f->estado = Comendo;
		gettimeofday(&tv, NULL);
		printf("O filósofo %s está comendo.\t%ld.%ld s\n", f->nome, tv.tv_sec, tv.tv_usec);
		sleep(time * 1000);
		mesa_soltar_garfos(f->cadeira);
		gettimeofday(&tv, NULL);
		printf("O filósofo %s soltou os garfos.\t%ld.%ld s\n", f->nome, tv.tv_sec, tv.tv_usec);
	}
	else
	{
		gettimeofday(&tv, NULL);
		printf("O filósofo %s não conseguiu pegar os garfos.\t%ld.%ld s\n", f->nome, tv.tv_sec, tv.tv_usec);
	}
}

void filosofo_destruir(filosofo_t* f)
{
	mesa_liberar_cadeira(f->cadeira);
	free(f);
}
