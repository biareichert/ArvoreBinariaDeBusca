#ifndef ABB_H
#define ABB_H

#define SUCESSO 1
#define FRACASSO 0

typedef struct noABB *noABB;

int criaABB(noABB **pp );
void destroiABB(noABB *pp);
void reiniciaABB(struct noABB *p);
int insereABB(noABB *p, void *novo, int (* cmp)(void *p1, void *p2), int tipo);
int removeABB(noABB *p, void *item, int (* cmp)(void *p1, void *p2));
int buscaABB(noABB *p, void *item, int (* cmp)(void *p1, void *p2));
int testaVaziaABB(noABB *p);
int percursoEmOrdem(noABB *p);
int percursoPreOrdem(noABB *p);
int percursoPosOrdem(noABB *p);
void imprimirItem(void *dado, int tipo);

#endif
