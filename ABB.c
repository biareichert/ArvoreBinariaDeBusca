#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ABB_privado.h"


int criaABB(noABB **pp){
    /*Criamos um nó "especial" para representar o ponteiro para
    a raiz da árvore*/
    noABB *raiz = (noABB*)malloc(sizeof(noABB));
    if(!raiz){ 
        /*Se a alocação der errado retornamos fracasso para a aplicação*/
        return FRACASSO;
    }else{
        *raiz = NULL;
        (*pp)= raiz;
        
        return SUCESSO;
    }

    return FRACASSO;
}

void reiniciaABB(struct noABB *p){
    
    if(p != NULL){
        /*Se a árvore não estiver vazia nós caminhamos recursivamente 
        pela árvore para liberar os seus nós*/
        reiniciaABB(p->esq);
        reiniciaABB(p->dir);

        free(p->dados);
        free(p);
        p = NULL;
    }
}


void destroiABB(noABB *pp){
    reiniciaABB(*pp);
    free(pp); 
}

int insereABB(noABB *p, void *novo, int (* cmp)(void *p1, void *p2), int tipo){
    struct noABB *new, *aux1, *aux2;
    int retorno;

    /*Alocação de memória para o novo nó (noABB)*/
    if((new = (struct noABB*)malloc(sizeof(struct noABB))) != NULL){
        /*Alocação de memória para o dado do tipo void* */
        if((new->dados=(void*)malloc(sizeof(novo)))!=NULL){

            /*Iniciando as variáveis da struct noABB do novo nó*/
            new->taminfo = sizeof(novo);
            new->tipo = tipo;
            new->dir = NULL;
            new->esq = NULL;
            memcpy(new->dados, novo, new->taminfo);

            if(*p == NULL){
                /*Se a árvore está vazia então estamos inserindo o primeiro elemento,
                para isso só precisamos fazer o ponteiro da raiz (*p) apontar para 
                o nosso novo nó (new)*/
                *p = new;

                return SUCESSO;

            }else{
                /*Se já existe algum elemento na árvore vamos percorre-la para encontrar
                o local da inserção*/
                aux1 = *p;
                aux2 = NULL;

                while(aux1 != NULL){
                    /*Os ponteiros aux1 e aux2 irão partir da raiz. aux1 irá apontar para NULL
                    quando encontrar o local adequado. aux2 irá apontar para o pai de aux1.*/

                    aux2 = aux1;
                    retorno = (* cmp)(novo, aux1->dados); /*0 - novo = aux1->dados; > valor positivo - novo > aux1->dados; valor negativo - novo < aux1->dados*/
                   
                    if(retorno == 0 ){
                        /*Se o retorno da comparação for 0 significa que ele encontrou um nó 
                        com o mesmo valor do que desejamos inserir na árvore.*/
                        //printf("O elemento já existe!\n");
                        
                        /*Dado que não precisaremos adicionar nenhum novo nó, então podemos
                        desalocar as linhas 49 e 51*/
                        free(new->dados);
                        free(new);

                        return FRACASSO;

                    }else{
                        if(retorno > 0){
                            /*Se o retorno da comparação for > 0 significa que o novo elemento
                            é maior do que o nosso aux1. Portanto, vamos caminhar para a direita*/
                            aux1 = aux1->dir;

                        }else{
                            /*Se o retorno da comparação for < 0 significa que o novo elemento
                            é menor do que o nosso aux1. Portanto, vamos caminhar para a esquerda*/
                            aux1 = aux1->esq;

                        }
                    }
                }

                /*Saindo do while significa que temos o aux1 apontando para NULL que é o local
                onde devemos inserir o novo elemento. E o aux2 é o pai do aux1.*/

                if(retorno > 0){
                    /*Se o último retorno mandou o aux1 para a direita, então o pai do aux1
                    vai receber o novo nó a sua direita*/
                    aux2->dir = new;

                    return SUCESSO;
                }else{
                    /*Se o último retorno mandou o aux1 para a esquerda, então o pai do aux1
                    vai receber o novo nó a sua esquerda*/
                    aux2->esq = new;

                    return SUCESSO;
                }
            }
        }else{
            /*Se a alocação de new->dados der errado precisamos desalocar
            o new que foi alocado anteriormente*/
            free(new);
            return FRACASSO;
        }
    }else{
        /*Se a alocação de new der errado*/
        return FRACASSO;
    }

    return FRACASSO;
}

int buscaABB(noABB *p, void *item, int (* cmp)(void *p1, void *p2)){
    int retorno;

    if(p != NULL){
        /*Se a árvore não está vazia então vamos percorre-la para buscar o item passado por
        parametro. O ponteiro aux vai partir da raiz.*/
        struct noABB *aux = *p;
        
        while(aux != NULL){
            retorno = (*cmp)(item, aux->dados);
            if(retorno == 0){
                /*Se o retorno da comparação for 0 significa que o aux encontrou o item buscado*/
                return SUCESSO;

            }else{
                if(retorno > 0){
                    /*Se o retorno da comparação for > 0 significa que o item buscado é maior do que 
                    o nosso aux. Portanto, vamos caminhar para a direita*/
                    aux = aux->dir;

                }else{
                    /*Se o retorno da comparação for < 0 significa que o item buscado é menor do que 
                    o nosso aux. Portanto, vamos caminhar para a esquerda*/
                    aux = aux->esq;

                }    
            }
        }
        
    }else{
        //printf("A Árvore está vazia!\n");
        return FRACASSO;
    }

    return FRACASSO;
}

int testaVaziaABB(noABB *p){
    if(*p == NULL){
        /*Árvore vazia*/
        return SUCESSO;
    }

    /*Árvore não vazia*/
    return FRACASSO;
}

void imprimirItem(void *dado, int tipo){
    switch (tipo){
        case 1: 
            /*Item do tipo int*/
            printf("%d ",*(int*)dado);
            break;
            
        case 2:
            /*Item do tipo char*/
            printf("%c ",*(char*)dado);
            break;

        default:
            break;
    }
}

int percursoEmOrdem(noABB *p){
    if(*p != NULL){
        /*Se a árvore não está vazia vamos percorre-la recursivamente*/
        percursoEmOrdem(&((*p)->esq));
        imprimirItem((*p)->dados,(*p)->tipo);
        percursoEmOrdem(&((*p)->dir));

        return SUCESSO;
    }

    return FRACASSO;
}


int percursoPreOrdem(noABB *p){
    if(*p != NULL){
        /*Se a árvore não está vazia vamos percorre-la recursivamente*/
        imprimirItem((*p)->dados,(*p)->tipo);
        percursoPreOrdem(&((*p)->esq));
        percursoPreOrdem(&((*p)->dir));
        
        return SUCESSO;
    }

    return FRACASSO;
}
    

int percursoPosOrdem(noABB *p){
      if(*p != NULL){
        /*Se a árvore não está vazia vamos percorre-la recursivamente*/
        percursoPosOrdem(&((*p)->esq));
        percursoPosOrdem(&((*p)->dir));
        imprimirItem((*p)->dados,(*p)->tipo);

        return SUCESSO;
    }

    return FRACASSO;
}


int removeABB(noABB *p, void *item, int (* cmp)(void *p1, void *p2)){
    struct noABB *aux1, *aux2, *aux3, *aux4;
    int retorno1;
    int retorno2;

    if(*p != NULL){
        /*Se a árvore não está vazia então vamos percorre-la para buscar o item passado por
        parametro. Os ponteiros aux1 e aux2 irão partir da raiz.*/
        aux1 = *p;
        aux2 = aux1;

        while(aux1 != NULL){
            retorno1 = (*cmp)(item, aux1->dados);
            
            if(retorno1 == 0){
                /*Se o retorno da comparação for 0 significa que o item desejado para remoção
                foi encontrado*/

                if(aux1->dir == NULL && aux1->esq == NULL){
                    /*Se o item desejado não possui filhos*/

                    if(aux2->dir != NULL){
                        /*Verificamos se o item desejado (aux1) é filho da direita do seu pai (aux2)*/
                        retorno2 = (*cmp)(aux1->dados, aux2->dir->dados);
                        if(retorno2 == 0){
                            /*Caso positivo, o ponteiro da direita do pai do item desejado irá apontar 
                            para NULL*/
                            aux2->dir = NULL;
                        }
                    }

                    if(aux2->esq != NULL){
                        /*Verificamos se o item desejado (aux1) é filho da esquerda do seu pai (aux2)*/
                        retorno2 = (*cmp)(aux1->dados, aux2->esq->dados);
                        if(retorno2 == 0){
                            /*Caso positivo, o ponteiro da esquerda do pai do item desejado irá apontar 
                            para NULL*/
                            aux2->esq = NULL;
                        }
                    }

                    if(aux1 == *p){
                        /*Se estamos removendo o último elemento da árvore a raiz irá apontar para NULL*/
                        *p = NULL;
                    }

                    free(aux1->dados);
                    free(aux1);
                    
                    return SUCESSO;

                }else{
                    if(aux1->dir == NULL && aux1->esq != NULL){
                        /*Se o item desejado possui um filho a esquerda*/

                        /*O ponteiro aux3 irá apontar para o filho do item que queremos
                        remover (aux1)*/
                        aux3 = aux1->esq;

                        if(aux2->esq != NULL){
                            /*Verificamos se o item desejado (aux1) é filho da esquerda do seu pai (aux2)*/
                            retorno2 = (*cmp)(aux1->dados, aux2->esq->dados);
                            if(retorno2 == 0){
                                /*Caso positivo, o ponteiro da esquerda do pai do item desejado irá apontar 
                                para o filho do aux1.*/
                                aux2->esq = aux3;
                            }
                        }

                        if(aux2->dir != NULL){
                            /*Verificamos se o item desejado (aux1) é filho da direita do seu pai (aux2)*/
                            retorno2 = (*cmp)(aux1->dados, aux2->dir->dados);
                            if(retorno2 == 0){
                                /*Caso positivo, o ponteiro da direita do pai do item desejado irá apontar 
                                para o filho do aux1.*/
                                aux2->dir = aux3;
                            }
                        }

                        if(aux1 == *p){
                            /*Se o elemento que queremos remover é a raiz, e esta possui filho apenas na 
                            esquerda, então o ponteiro da raiz (*p) deve apontar para o aux3.*/
                            *p = aux3;

                        }

                        free(aux1->dados);
                        free(aux1);
                        
                        return SUCESSO;

                    }
                    if(aux1->dir != NULL && aux1->esq == NULL){
                        /*Se o item desejado possui um filho a direita*/

                        /*O ponteiro aux3 irá apontar para o filho do item que queremos
                        remover (aux1)*/
                        aux3 = aux1->dir;

                        if(aux2->esq != NULL){
                            /*Verificamos se o item desejado (aux1) é filho da esquerda do seu pai (aux2)*/
                            retorno2 = (*cmp)(aux1->dados, aux2->esq->dados);
                            if(retorno2 == 0){
                                /*Caso positivo, o ponteiro da esquerda do pai do item desejado irá apontar 
                                para o filho do aux1.*/
                                aux2->esq = aux3;
                            }
                        }

                        if(aux2->dir != NULL){
                            /*Verificamos se o item desejado (aux1) é filho da direita do seu pai (aux2)*/
                            retorno2 = (*cmp)(aux1->dados, aux2->dir->dados);
                            if(retorno2 == 0){
                                /*Caso positivo, o ponteiro da direita do pai do item desejado irá apontar 
                                para o filho do aux1.*/
                                aux2->dir = aux3;
                            }
                        }

                        if(aux1 == *p){
                            /*Se o elemento que queremos remover é a raiz, e esta possui filho apenas na 
                            direita, então o ponteiro da raiz (*p) deve apontar para o aux3.*/
                            *p = aux3;

                        }

                        free(aux1->dados);
                        free(aux1);
                        
                        return SUCESSO;
                    }

                    if(aux1->dir != NULL && aux1->esq != NULL){
                        /*Se o item desejado possui dois filhos*/
                        
                        /*O ponteiro aux3 irá apontar para a subarvore a direita do elemento que 
                        vamos remover (aux1)*/
                        aux3 = aux1->dir;
                        aux4 = aux3;

                        while(aux3->esq != NULL){
                            /*Caminhamos pela árvore para encontrar o elemento mais a esquerda
                            da subarvore a direita. Dessa forma o ponteiro aux3 irá apontar 
                            para o elemento mais a esquerda e o aux4 irá apontar para o pai
                            do aux3.*/
                            /*Em casos onde a subarvore a direita não tem elementos a esquerda
                            o aux3 será igual ao aux4*/
                            aux4 = aux3;
                            aux3 = aux3->esq;
                        }

                        if(aux2->dir != NULL){
                            /*Verificamos se o item desejado (aux1) é filho da direita do seu pai (aux2)*/
                            retorno2 = (*cmp)(aux1->dados, aux2->dir->dados);
                            if(retorno2 == 0){
                                /*Caso positivo, o ponteiro da direita do pai do item desejado irá apontar 
                                para o aux3 que será o elemento mais a esquerda da subarvore a direita.*/
                                aux2->dir = aux3;
                            }
                        }

                        if(aux2->esq != NULL){
                            /*Verificamos se o item desejado (aux1) é filho da esquerda do seu pai (aux2)*/
                            retorno2 = (*cmp)(aux1->dados, aux2->esq->dados);
                            if(retorno2 == 0){
                                /*Caso positivo, o ponteiro da esquerda do pai do item desejado irá apontar 
                                para o aux3 que será o elemento mais a esquerda da subarvore a direita.*/
                                aux2->esq = aux3;
                            }
                        }

                        if(aux4 != aux3){
                            /*Se o aux3 possuir um filho a direita, o pai dele (aux4) irá apontar
                            para esse filho, dado que o aux3 irá substituir o aux1.*/
                            aux4->esq = aux3->dir;
                        }

                        if(aux1->esq != aux3){
                            /*O aux1 possui dois filhos, então aqui fazemos o aux3->esq apontar
                            para o filho a esquerda do aux1. Dado que vamos remover o aux1.*/
                            aux3->esq = aux1->esq;
                        }

                        if(aux1->dir != aux3){
                            /*O aux1 possui dois filhos, então aqui fazemos o aux3->dir apontar
                            para o filho a direita do aux1. Dado que vamos remover o aux1.*/
                            aux3->dir = aux1->dir;
                        }

                        if(aux1 == *p){
                            /*Se o elemento que queremos remover é a raiz, e esta possui dois filhos,
                            então o ponteiro da raiz (*p) deve apontar para o aux3.*/
                            *p = aux3;

                        }

                        free(aux1->dados);
                        free(aux1);
                        
                        return SUCESSO;
                    }
                }
            }else{
                aux2 = aux1;

                if(retorno1 > 0){
                    /*Se o retorno da comparação for > 0 significa que o item buscado é maior do que 
                    o nosso aux. Portanto, vamos caminhar para a direita*/
                    aux1 = aux1->dir;
                    
                }else{
                    /*Se o retorno da comparação for < 0 significa que o item buscado é menor do que 
                    o nosso aux. Portanto, vamos caminhar para a esquerda*/
                    aux1 = aux1->esq;
                }
            }
        }
        //printf("O elemento não foi encontrado!\n");
        return FRACASSO;

    }else{
        //printf("A árvore está vazia!\n");
        return FRACASSO;
    }

    return FRACASSO;
}