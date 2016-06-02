#ifndef GRAFO_INCLUDED
#define GRAFO_INCLUDED

#define TAM_STRING 100

typedef struct PreRequisitos {
    char v[TAM_STRING];
    double peso;
    struct PreRequisitos *prox;
} requisitos;

typedef struct Tarefa {
    char v[TAM_STRING];
    int vorig;
    int c;
    double d;
    struct Tarefa *prox;
    requisitos *lista;
} tarefa;

typedef struct Grafo {
    tarefa *T;
} grafo;

grafo* cria_grafo();
grafo* insere_tarefa(grafo* G,char* nometarefa);
grafo* insere_requisitos(grafo* G, char* vorig, char* vdest, double peso);
grafo* remove_tarefa(grafo* G, char* nometarefa);
grafo* remove_requisitos(grafo* G, char* vorig, char* vdest);
double peso_caminho(grafo* G, char* vorig, char* vdest);
int grafo_conexo(grafo* G);
grafo* le_grafo(char *nomeArq);
void libera_grafo(grafo* G);
void imprime_grafo(grafo* G, char* nome_arq);
int verifica_consistencia(grafo* G);
int pesquisa_tarefa(grafo* G, char* nometarefa);
int pesquisa_requisitos(grafo* G, char* vorig, char* vdest, double peso);

#endif
/* GRAFO_INCLUDED */

