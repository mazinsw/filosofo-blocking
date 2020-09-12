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
#ifndef _MESA_H_
#define _MESA_H_

typedef struct mesa mesa_t;
typedef struct cadeira cadeira_t;
typedef struct garfo garfo_t;

/* protótipo de função de requisição de liberação de cadeira, 
 * data é a pessoa que foi associada com a cadeira */
typedef void (*aviso_liberar_fn)(void * data);

typedef enum
{
	Livre = 0,
	Ocupado
} CadeiraEstado;

/**
 * Cria uma mesa com uma quantidade de cadeiras para pessoas sentarem
 * 
 * parâmetros:
 *   cadeiras: quantidade de lugares que deve existir na mesa
 * retorno:
 *   uma mesa com cadeiras livres
 */
mesa_t*    mesa_criar(int cadeiras);

/**
 * Ocupa um lugar da mesa
 * 
 * parâmetros:
 *   m: mesa com os lugares livres para ser escolhido uma cadeira
 *   pessoa: pessoa que vai ocupar o espaço livre
 *   aviso_fn: função que será chamada quando o espaço for requisitado
 *     para ser liberado
 * retorno:
 *   uma cadeira que a pessoa sentou ou NULL caso não haja mais lugar
 *     disponível
 */
cadeira_t* mesa_sentar(mesa_t* m, void* pessoa, aviso_liberar_fn aviso_fn);

/**
 * Libera uma cadeira usada por uma pessoa
 * 
 * parâmetros:
 *   c: cadeira a ser liberada
 * retorno:
 *   a pessoa que está ocupando a cadeira
 */
void*      mesa_liberar_cadeira(cadeira_t* c);

/**
 * Pega garfos que estão sobre a mesa em frente a cadeira informada
 * 
 * parâmetros:
 *   c: cadeira em que a pessoa que irá pegar os garfos está sentada
 * retorno:
 *   1 caso consigar pegar os dois garfos ou 0 caso contrário
 */
int        mesa_pegar_garfos(cadeira_t* c);

/**
 * Libera os garfos para que outra pessoa possa comer
 * 
 * parâmetros:
 *   c: cadeira em que a pessoa que irá soltar os garfos está sentada
 */
void       mesa_soltar_garfos(cadeira_t* c);

/**
 * Destroi uma mesa e suas cadeiras, mas antes solicita às pessoas que
 * estão sentadas à se retirarem e espera até que a última libere a 
 * cadeira
 * 
 * parâmetros:
 *   m: mesa que será destruida
 */
void       mesa_destruir(mesa_t* m);

#endif /* _MESA_H_ */
