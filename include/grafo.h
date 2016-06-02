#ifndef GRAFO_INCLUDED
#define GRAFO_INCLUDED

#define TAM_STRING 100

typedef struct Aresta {
    char v[TAM_STRING];
    double peso;
    struct Aresta *prox;
} aresta;

typedef struct Vertice {
    char v[TAM_STRING];
    int vorig;
    int c;
    double d;
    struct Vertice *prox;
    aresta *lista;
} vertice;

typedef struct Grafo {
    vertice *V;
}grafo;

grafo* cria_grafo();
grafo* insere_vertice(grafo* G,char* nomevertice);
grafo* insere_aresta(grafo* G, char* vorig, char* vdest, double peso);
grafo* remove_vertice(grafo* G, char* nomevertice);
grafo* remove_aresta(grafo* G, char* vorig, char* vdest);
double peso_caminho(grafo* G, char* vorig, char* vdest);
int grafo_conexo(grafo* G);
grafo* le_grafo(char *nomeArq);
void libera_grafo(grafo* G);
void imprime_grafo(grafo* G, char* nome_arq);
int verifica_consistencia(grafo* G);
int pesquisa_vertice(grafo* G, char* nomevertice);
int pesquisa_aresta(grafo* G, char* vorig, char* vdest, double peso);

#endif
/* GRAFO_INCLUDED */

