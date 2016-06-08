#ifndef GRAFO_INCLUDED
#define GRAFO_INCLUDED

#define TAM_STRING 100

typedef struct PreRequisitos {
    int id_prerequisito;
    int duracao_tarefa;
    int inicio_min_tarefa;
    struct PreRequisitos *prox;
} prerequisitos;

typedef struct Tarefa {
    int id_tarefa;
    char nome_tarefa[TAM_STRING];
    int tarefa_executada;
    int duracao_tarefa;
    int inicio_min_tarefa;
    int n_prerequisitos;
    struct Tarefa *prox;
    prerequisitos *prerequisitos_tarefa;
} tarefa;

typedef struct Grafo {
    tarefa *T;
} grafo;

grafo* cria_grafo();
grafo* insere_tarefa(grafo* G, int id_tarefa, char* nome_tarefa, int tarefa_executada, int
duracao_tarefa, int inicio_min_tarefa, int n_prerequisitos);
grafo* edita_tarefa(grafo* G, int id_tarefa, char* nome_tarefa, int tarefa_executada, int
duracao_tarefa, int inicio_min_tarefa, int n_prerequisitos, int
id_prerequisito, int duracao_prerequisito, int inicio_prerequisito);
grafo* insere_prerequisitos(grafo* G, int id_tarefa, int id_prerequisito, int
duracao_tarefa, int inicio_min_tarefa);
grafo* remove_tarefa(grafo* G, int id_tarefa);
grafo* remove_prerequisitos(grafo* G, int id_tarefa, int id_prerequisito);
int peso_caminho(grafo* G, char* vorig, char* vdest);
int grafo_conexo(grafo* G);
grafo* le_grafo(char *nomeArq);
void libera_grafo(grafo* G);
void imprime_grafo(grafo* G, char* nome_arq);
int verifica_consistencia(grafo* G);
int pesquisa_tarefa(grafo* G, int id_tarefa);
int pesquisa_prerequisitos(grafo* G, int id_tarefa, int id_prerequisito);
tarefa * procura_tarefa(grafo*, int);

#endif
/* GRAFO_INCLUDED */

