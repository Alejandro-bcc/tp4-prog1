// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct lista_t * lista_cria(){

	struct lista_t *p;

	if(!(p = malloc(sizeof(struct lista_t))))
		return NULL;

	p->prim = NULL;
	p->ult = NULL;
	p->tamanho = 0;

	return p;
}

struct lista_t * lista_destroi(struct lista_t *l){

    struct item_t *aux;

    if(l != NULL){
        while(l->prim != NULL){
            aux = l->prim;
            l->prim = aux->prox;
            free(aux);
        }

        aux = NULL;
        free(l);
    }

    return NULL;
}

int lista_insere(struct lista_t *l, int item, int pos){
    
    struct item_t *novo;
    struct item_t *aux;
    int cont;

	/* erro, ponteiro inválido ou alocação mal-sucedida */
    if(l == NULL || !(novo = malloc(sizeof(struct item_t))))
        return -1;

    novo->valor = item;
    
    /* a lista está vazia */
    if(l->prim == NULL){

        l->prim = novo;
        l->ult = novo;
        novo->ant = NULL;
        novo->prox = NULL;
        return ++l->tamanho;
    }
    
    /* insere na posição do primeiro elemento */
    if(pos == 0){
        
        novo->prox = l->prim;
        novo->ant = NULL;
        l->prim->ant = novo;
        l->prim = novo;
        return ++l->tamanho;
    }

    /* insere na posição do ultimo elememto */
    if(pos == l->tamanho-1){
        
        novo->prox = l->ult;
        novo->ant = l->ult->ant;
        l->ult->ant->prox = novo;
        l->ult->ant = novo;
        return ++l->tamanho;
    }
    
    /* posição inválida, insere no fim  */
    if(pos > l->tamanho-1 || pos == -1){
        
        novo->ant = l->ult;
        novo->prox = NULL;
        l->ult->prox = novo;
        l->ult = novo;
        return ++l->tamanho;
    }

    cont = 1;
    aux = l->prim->prox;
    while(cont != pos){
        aux = aux->prox;
        cont++;
    }
    novo->prox = aux;
	novo->ant = aux->ant;
    aux->ant->prox = novo;
    aux->ant = novo;
    aux = NULL;
    return ++l->tamanho;
}

int lista_retira(struct lista_t *l, int *item, int pos){

	struct item_t *aux;
	int cont;

	/* erro, ponteiros inválidos */
	if(l == NULL || item == NULL)
		return -1;

	/* lista vazia */
	if(l->prim == NULL)
		return l->tamanho;

	/* a lista possui um único elemento */
	if(l->prim->prox == NULL){
		*item = l->prim->valor;
		free(l->prim);
		l->prim = NULL;
		l->ult = NULL;
		return --l->tamanho;
	}


	/* retira o primeiro elemento */
	if(pos == 0){
		aux = l->prim;
		l->prim = aux->prox;
		l->prim->ant = NULL;
		*item = aux->valor;
		free(aux);
		aux = NULL;
		return --l->tamanho;
	}

	/* retira o ultimo elemento */
	if(pos >= l->tamanho-1 || pos == -1){
		aux = l->ult;
		l->ult = aux->ant;
		l->ult->prox = NULL;
		*item = aux->valor;
		free(aux);
		aux = NULL;
		return --l->tamanho;
	}
	
	cont = 1;
	aux = l->prim->prox;
	while(cont != pos){
		aux = aux->prox;
		cont++;
	}
	aux->ant->prox = aux->prox;
    aux->prox->ant = aux->ant;
    *item = aux->valor;
    free(aux);
    aux = NULL;
    return --l->tamanho;
}

int lista_consulta(struct lista_t *l, int *item, int pos){
	
	struct item_t *aux;
	int	cont;

	/* erro, ponteiros inválidos */
	if(l == NULL || item == NULL)
		return -1;
	
	/* posição invália, consulta o fim */
	if(pos > l->tamanho-1 || pos == -1){
	//	return -1;
		*item = l->ult->valor;
		return l->tamanho;
	}

	cont = 0;
	aux = l->prim;
	while(aux != NULL && cont != pos){
		aux = aux->prox;
		cont++;
	}

	*item = aux->valor;
	return l->tamanho;
}

int lista_procura(struct lista_t *l, int valor){

	struct item_t *aux;
	int cont;

	/* erro, ponteiro inválido ou lista vazia*/
	if(l == NULL || l->prim == NULL)
		return -1;

	cont = 0;
	aux = l->prim;

	while(aux != NULL && aux->valor != valor){
		aux = aux->prox;
		cont++;
	}

	/* elemento não encontrado */
	if(aux == NULL)
		return -1;

	return cont;
}

int lista_tamanho(struct lista_t *l){
	
	/* erro, ponteiro inválido */
	if(l == NULL)
		return -1;

	return l->tamanho;
}

void lista_imprime(struct lista_t *l){

	struct item_t *aux;

	aux = l->prim;
	while(aux != NULL){
		printf("%d", aux->valor);
		if(aux->prox != NULL)
			printf(" ");
		aux = aux->prox;
	}
}
