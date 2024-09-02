#ifndef ABB_PRIVADO_H
#define ABB_PRIVADO_H

#include "ABB.h"

/*Struct do nó da árvore*/
 struct noABB{
    void *dados; /*armazena o dado genérico*/
    struct noABB *esq; /*ponteiro para o nó da esquerda*/
    struct noABB *dir; /*ponteiro para o nó da direita*/
    int taminfo; /*armazena o tamanho da informação (sizeof)*/
    int tipo; /*1: int. 2: caracter.*/
}; 


#endif