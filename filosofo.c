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
#include "semaphore.h"

struct filosofo
{
	mesa_t* mesa;
	cadeira_t* cadeira;
	const char* nome;
	FilosofoEstado estado;
	pthread_t thread;
	pthread_semaphore_t sem;
};

static void* filosofo_iniciar(void* data)
{
	filosofo_t* f = (filosofo_t*)data;

	while(1)
	{
		filosofo_pensar(f);
		filosofo_pegar_garfos(f);
		filosofo_comer(f);
		filosofo_soltar_garfos(f);
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
	pthread_semaphore_init(&f->sem, NULL, NULL);
	pthread_create(&f->thread, NULL, filosofo_iniciar, (void*)f);
	return f;
}

void filosofo_pensar(filosofo_t* f)
{
	struct timeval tv;
	// o folósofo irá pensar por um intervalo de tempo não determinado
	unsigned int time = 1 + (rand() % 5);

	gettimeofday(&tv, NULL);
	printf("O filósofo %s está pensando...\t%ld.%ld s\n", f->nome, tv.tv_sec, tv.tv_usec);
	sleep(time * 1000);
}

void filosofo_teste(filosofo_t* f)
{
	filosofo_t* dir, *esq;

	dir = (filosofo_t*)mesa_pessoa_visinha(f->cadeira, Direito);
	esq = (filosofo_t*)mesa_pessoa_visinha(f->cadeira, Esquerdo);
	if(f->estado == Faminto && dir->estado != Comendo && esq->estado != Comendo)
	{
		mesa_pegar_garfos(f->cadeira);
		f->estado = Comendo;
		pthread_semaphore_post(&f->sem);
	}
}

void filosofo_pegar_garfos(filosofo_t* f)
{
	mesa_iniciar_acao(f->cadeira);
	f->estado = Faminto;
	filosofo_teste(f);
	mesa_finalizar_acao(f->cadeira);
	pthread_semaphore_wait(&f->sem);
}

void filosofo_soltar_garfos(filosofo_t* f)
{
	filosofo_t* visinho;
	struct timeval tv;

	mesa_iniciar_acao(f->cadeira);
	mesa_soltar_garfos(f->cadeira);
	f->estado = Pensando;
	gettimeofday(&tv, NULL);
	printf("O filósofo %s soltou os garfos.\t%ld.%ld s\n", f->nome, tv.tv_sec, tv.tv_usec);
	visinho = (filosofo_t*)mesa_pessoa_visinha(f->cadeira, Direito);
	filosofo_teste(visinho);
	visinho = (filosofo_t*)mesa_pessoa_visinha(f->cadeira, Esquerdo);
	filosofo_teste(visinho);
	mesa_finalizar_acao(f->cadeira);
}

void filosofo_comer(filosofo_t* f)
{
	struct timeval tv;
	unsigned int time = 1 + (rand() % 5);

	gettimeofday(&tv, NULL);
	printf("O filósofo %s está comendo.\t%ld.%ld s\n", f->nome, tv.tv_sec, tv.tv_usec);
	sleep(time * 1000);
}

void filosofo_destruir(filosofo_t* f)
{
	mesa_liberar_cadeira(f->cadeira);
	pthread_semaphore_destroy(&f->sem);
	free(f);
}
