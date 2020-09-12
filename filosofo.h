//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#ifndef _FILOSOFO_H_
#define _FILOSOFO_H_
#include "mesa.h"

typedef struct filosofo filosofo_t;

typedef enum
{
	Ocioso = 0,
	Pensando,
	Faminto,
	Comendo,
} FilosofoEstado;


/**
 * Cria um filósofo sentado na cadeira da mesa
 * 
 * parâmetros:
 *   nome: nome do filósofo
 *   mesa: mesa que o folósofo vai sentar em uma de suas cadeiras livres
 * 	   para pensar e comer
 * retorno:
 *   um filósofo sentado na cadeira da mesa, ou NULL caso não haja 
 *     cadeira disponível
 */
filosofo_t* filosofo_criar(const char* nome, mesa_t* mesa);

/**
 * Faz o filósofo pensar por alguns minutos
 * 
 * parâmetros:
 *   f: o filósofo que irá pensar
 */
void        filosofo_pensar(filosofo_t* f);

/**
 * Faz o filósofo pegar os garfos e comer
 * 
 * parâmetros:
 *   f: o filósofo que irá comer
 */
void        filosofo_comer(filosofo_t* f);

/**
 * Destroi um filósofo liberando a cadeira ocupada da mesa primeiro
 * 
 * parâmetros:
 *   f: o filósofo que será destruido
 */
void        filosofo_destruir(filosofo_t* f);

#endif /* _FILOSOFO_H_ */
