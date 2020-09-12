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

/* protÃ³tipo de funÃ§Ã£o de requisiÃ§Ã£o de liberaÃ§Ã£o de cadeira, 
 * data Ã© a pessoa que foi associada com a cadeira */
typedef void (*aviso_liberar_fn)(void * data);

typedef enum
{
	Livre = 0,
	Ocupado
} CadeiraEstado;

typedef enum
{
	Esquerdo = 0,
	Direito
} Lado;

/**
 * Cria uma mesa com uma quantidade de cadeiras para pessoas sentarem
 * 
 * parÃ¢metros:
 *   cadeiras: quantidade de lugares que deve existir na mesa
 * retorno:
 *   uma mesa com cadeiras livres
 */
mesa_t*    mesa_criar(int cadeiras);

/**
 * Ocupa um lugar da mesa
 * 
 * parÃ¢metros:
 *   m: mesa com os lugares livres para ser escolhido uma cadeira
 *   pessoa: pessoa que vai ocupar o espaÃ§o livre
 *   aviso_fn: funÃ§Ã£o que serÃ¡ chamada quando o espaÃ§o for requisitado
 *     para ser liberado
 * retorno:
 *   uma cadeira que a pessoa sentou ou NULL caso nÃ£o haja mais lugar
 *     disponÃ­vel
 */
cadeira_t* mesa_sentar(mesa_t* m, void* pessoa, aviso_liberar_fn aviso_fn);

/**
 * Libera uma cadeira usada por uma pessoa
 * 
 * parÃ¢metros:
 *   c: cadeira a ser liberada
 * retorno:
 *   a pessoa que estÃ¡ ocupando a cadeira
 */
void*      mesa_liberar_cadeira(cadeira_t* c);

/**
 * Pega garfos que estÃ£o sobre a mesa em frente a cadeira informada
 * 
 * parÃ¢metros:
 *   c: cadeira em que a pessoa que irÃ¡ pegar os garfos estÃ¡ sentada
 */
void        mesa_pegar_garfos(cadeira_t* c);

/**
 * Libera os garfos para que outra pessoa possa comer
 * 
 * parÃ¢metros:
 *   c: cadeira em que a pessoa que irÃ¡ soltar os garfos estÃ¡ sentada
 */
void       mesa_soltar_garfos(cadeira_t* c);

/**
 * Informa que somente a pessoa que está sentada fará uma ação na mesa
 * 
 * parÃ¢metros:
 *   c: cadeira em que a pessoa que estÃ¡ sentada, fará uma ação
 */
void       mesa_iniciar_acao(cadeira_t* c);

/**
 * Informa que a pessoa não está mais fazendo uma ação na mesa
 * 
 * parÃ¢metros:
 *   c: cadeira em que a pessoa estÃ¡ sentada
 */
void       mesa_finalizar_acao(cadeira_t* c);

/**
 * Obtem a pessoa que está ao lado
 * 
 * parÃ¢metros:
 *   c: cadeira em que a pessoa que irÃ¡ soltar os garfos estÃ¡ sentada
 *   lado: informa de qual lado deve-se obter a pessoa
 * retorno:
 *   a pessoa que estÃ¡ ocupando a cadeira ao lado ou NULL caso a cadeira esteja
 *   livre
 */
void*      mesa_pessoa_visinha(cadeira_t* c, Lado lado);

/**
 * Destroi uma mesa e suas cadeiras, mas antes solicita Ã s pessoas que
 * estÃ£o sentadas Ã  se retirarem e espera atÃ© que a Ãºltima libere a 
 * cadeira
 * 
 * parÃ¢metros:
 *   m: mesa que serÃ¡ destruida
 */
void       mesa_destruir(mesa_t* m);

#endif /* _MESA_H_ */
