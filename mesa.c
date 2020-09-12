#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "mesa.h"

struct mesa
{
	int qtd_cadeiras;
	int ocupadas;
	cadeira_t* cadeiras;
	pthread_mutex_t mutex;
};

struct cadeira
{
	CadeiraEstado estado;
	mesa_t* mesa;
	void* pessoa;
	aviso_liberar_fn aviso_fn;
	garfo_t* garfo;
	cadeira_t* direita;
	cadeira_t* esquerda;
};

struct garfo
{
	int dentes;
	cadeira_t* dono;
};

cadeira_t* cadeira_criar(mesa_t* mesa)
{
	cadeira_t* c;

	srand(time(NULL));
	c = (cadeira_t*)malloc(sizeof(cadeira_t));
	c->estado = Livre;
	c->mesa = mesa;
	c->pessoa = NULL;
	c->aviso_fn = NULL;
	c->garfo = (garfo_t*)malloc(sizeof(garfo_t));
	c->garfo->dono = NULL;
	c->garfo->dentes = 4;
	c->direita = c;
	c->esquerda = c;
	return c;
}

void cadeira_destruir(cadeira_t* c)
{
	free(c->garfo);
	free(c);
}

mesa_t* mesa_criar(int cadeiras)
{
	mesa_t* m;
	cadeira_t* c;
	int i;

	if(cadeiras <= 1)
		return NULL;
	m = (mesa_t*)malloc(sizeof(mesa_t));
	m->qtd_cadeiras = cadeiras;
	m->ocupadas = 0;
	pthread_mutex_init(&m->mutex, NULL);
	m->cadeiras = cadeira_criar(m);
	for(i = 1; i < cadeiras; i++)
	{
		c = cadeira_criar(m);
		c->direita = m->cadeiras;
		c->esquerda = m->cadeiras->esquerda;
		m->cadeiras->esquerda->direita = c;
		m->cadeiras->esquerda = c;

		m->cadeiras = c;
	}
	return m;
}

cadeira_t* mesa_sentar(mesa_t* m, void* pessoa, aviso_liberar_fn aviso_fn)
{
	cadeira_t* c;
	if(m->ocupadas == m->qtd_cadeiras)
		return NULL;
	c = m->cadeiras;
	while(c->direita != m->cadeiras)
	{
		if(c->estado == Livre)
			break;
		c = c->direita;
	}
	assert(c->estado == Livre);
	c->estado = Ocupado;
	m->ocupadas++;
	c->pessoa = pessoa;
	c->aviso_fn = aviso_fn;
	return c;
}

void* mesa_liberar_cadeira(cadeira_t* c)
{
	void * pessoa;
	
	if(c->estado != Ocupado)
		return NULL;
	pessoa = c->pessoa;
	c->estado = Livre;
	assert(c->mesa->ocupadas > 0);
	c->mesa->ocupadas--;
	if(c->aviso_fn != NULL)
		c->aviso_fn(pessoa);
	c->pessoa = NULL;
	c->aviso_fn = NULL;
	return pessoa;
}

void mesa_pegar_garfos(cadeira_t* c)
{
	c->esquerda->garfo->dono = c;
	c->garfo->dono = c;
}

void mesa_soltar_garfos(cadeira_t* c)
{
	c->garfo->dono = NULL;
	c->esquerda->garfo->dono = NULL;
}

void mesa_iniciar_acao(cadeira_t* c)
{
	pthread_mutex_lock(&c->mesa->mutex);
}

void mesa_finalizar_acao(cadeira_t* c)
{
	pthread_mutex_unlock(&c->mesa->mutex);
}

void* mesa_pessoa_visinha(cadeira_t* c, Lado lado)
{
	if(lado == Direito)
		return c->direita->pessoa;
	return c->esquerda->pessoa;
}

void mesa_destruir(mesa_t* m)
{
	cadeira_t *c, *_ctmp;

	c = m->cadeiras;
	while(c->direita != m->cadeiras)
	{
		_ctmp = c;
		c = c->direita;
		if(_ctmp->estado == Ocupado)
			mesa_liberar_cadeira(_ctmp);
		cadeira_destruir(_ctmp);
	}
	_ctmp = m->cadeiras;
	if(_ctmp != NULL)
	{
		if(_ctmp->estado == Ocupado)
			mesa_liberar_cadeira(_ctmp);
		cadeira_destruir(_ctmp);
	}
	pthread_mutex_destroy(&m->mutex);
	free(m);
}
