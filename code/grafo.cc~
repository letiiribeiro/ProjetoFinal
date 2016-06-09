#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "grafo.h"

#define MAX_LINHA 1000

grafo* cria_grafo(){
    grafo* G = (grafo *)malloc(sizeof(grafo));
    if(!G){
        printf("Erro na alocacao!\n");
        exit(1);
    }
    G->T=NULL;
    return G;
}

grafo* insere_tarefa(grafo* G, int id_tarefa, char* nome_tarefa, int tarefa_executada, int duracao_tarefa, int inicio_min_tarefa, int n_prerequisitos) {

    tarefa* t = (tarefa *)malloc(sizeof(tarefa));

    if(!t){
        printf("Erro na alocacao!\n");
        exit(1);
    }

    t->id_tarefa = id_tarefa;
    strcpy(t->nome_tarefa, nome_tarefa);
    t->tarefa_executada = tarefa_executada;
    t->duracao_tarefa = duracao_tarefa;
    t->inicio_min_tarefa = inicio_min_tarefa;
    t-> n_prerequisitos = n_prerequisitos;

    tarefa* tmp;

    if(G->T == NULL)
        G->T = t;
    else {
        for(tmp = G->T; tmp->prox != NULL;tmp = tmp->prox);
        tmp->prox = t;
    }

    t->prox = NULL;
    t->prerequisitos_tarefa = NULL;

    return G;
}


grafo* edita_tarefa(grafo* G, int id_tarefa, char* nome_tarefa, int
tarefa_executada, int duracao_tarefa, int inicio_min_tarefa, int
n_prerequisitos,int* id_prerequisitos, int flag){
    tarefa *tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        if(tmp->id_tarefa == id_tarefa){
            if((flag&1)==1)
                strcpy(tmp->nome_tarefa, nome_tarefa);
            if((flag&2)==2)
                tmp->tarefa_executada = tarefa_executada;
            if((flag&4)==4)
                tmp->duracao_tarefa = duracao_tarefa;
            if((flag&8)==8)
                tmp->inicio_min_tarefa = inicio_min_tarefa;
            if((flag&16)==16)
                tmp->n_prerequisitos = n_prerequisitos;
            if((flag&32)==32){
                int i;
                for(i=0;i<n_prerequisitos;i++)
                    G = remove_prerequisitos(G, id_tarefa,id_prerequisitos[i]);
                    G = insere_prerequisitos(G,id_tarefa,id_prerequisitos[i],duracao_tarefa,inicio_min_tarefa);
            }
            break;   
        } else 
              printf("Error: insira a tarefa primeiro para editar.\n");
    }
    return G;
}

grafo* insere_prerequisitos(grafo* G, int id_tarefa, int id_prerequisito, int
duracao_tarefa, int inicio_min_tarefa) {

    prerequisitos* e = (prerequisitos *)malloc(sizeof(prerequisitos));
    tarefa* tmp;

    if(!e) {
        printf("Erro na alocacao.\n");
        exit(1);
    }

    e->id_prerequisito = id_prerequisito;
    e->duracao_tarefa = duracao_tarefa;
    e->inicio_min_tarefa = inicio_min_tarefa;

    tmp = procura_tarefa(G, id_tarefa);

    prerequisitos* tmp2;

    if(tmp->prerequisitos_tarefa == NULL)
	   tmp->prerequisitos_tarefa = e;
	else {
	   for(tmp2 = tmp->prerequisitos_tarefa; tmp2->prox != NULL; tmp2 = tmp2->prox);
	   tmp2->prox = e;
	}

    e->prox = NULL;

    return G;
}

tarefa * procura_tarefa(grafo* G, int id_tarefa) {

    tarefa *tmp;

    for(tmp = G->T; tmp != NULL; tmp = tmp->prox) {
        if(tmp->id_tarefa == id_tarefa)
            return tmp;
    }

    return NULL;
}

grafo* remove_tarefa(grafo* G, int id_tarefa){
    tarefa *tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        if(tmp->prox && tmp->id_tarefa == id_tarefa){
            tarefa* k = tmp->prox;
            tmp->prox = k->prox;
            free(k);
        }
        else if(tmp->id_tarefa == id_tarefa){
            G->T = tmp->prox;
            free(tmp);
            break;
        }
    }
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        prerequisitos* e;
        for(e=tmp->prerequisitos_tarefa;e!=NULL;e=e->prox){
            if(e->prox && e->prox->id_prerequisito == id_tarefa){
                prerequisitos* k = e->prox;
                e->prox = k->prox;
                free(k);
            }
            else if(e->id_prerequisito==id_tarefa){
                tmp->prerequisitos_tarefa = e->prox;
                free(e);
                break;
            }
        }
    }
    return G;
}

grafo* remove_prerequisitos(grafo* G, int id_tarefa, int id_prerequisito){
    tarefa *tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
            prerequisitos* e;
            for(e=tmp->prerequisitos_tarefa;e!=NULL;e=e->prox){
                if(e->prox && e->prox->id_prerequisito == id_tarefa){
                    prerequisitos* k = e->prox;
                    e->prox = k->prox;
                    free(k);
                }
                else if(e->id_prerequisito == id_tarefa){
                    tmp->prerequisitos_tarefa = e->prox;
                    free(e);
                    break;
                }
            }
        }
    return G;
}

 grafo* le_grafo(char *nomeArq) {

	FILE * fp = fopen(nomeArq, "r");

	if(!fp) {
		printf("error: impossivel abrir arquivo\n");
		exit(1);
	}

	grafo* G = cria_grafo();
	int id_tarefa, tarefa_executada, duracao_tarefa, inicio_min_tarefa, nro_pre_requisitos, i, pre_requisito;
	char lixo;
	char nome_tarefa[500];

	while(!feof(fp)) {

		fscanf(fp, "%d", &id_tarefa);		// le id_tarefa
		fscanf(fp, "%c", &lixo);			// descarta espaço ao lado de id_tarefa
		fscanf(fp, "%c", &lixo);			// descarta ' antes do nome tarefa
		fscanf(fp, "%[^']s", nome_tarefa);
		fscanf(fp, "%c", &lixo);			// descarta '
		fscanf(fp, "%c", &lixo);			// descarta próximo espaço
		fscanf(fp, "%d", &tarefa_executada);
		fscanf(fp, "%c", &lixo);			// descarta próximo espaço
		fscanf(fp, "%d", &duracao_tarefa);
		fscanf(fp, "%c", &lixo);			// descarta próximo espaço
		fscanf(fp, "%d", &inicio_min_tarefa);
		fscanf(fp, "%c", &lixo);			// descarta próximo espaço
		fscanf(fp, "%d", &nro_pre_requisitos);

		G = insere_tarefa(G, id_tarefa, nome_tarefa, tarefa_executada, duracao_tarefa, inicio_min_tarefa, nro_pre_requisitos); // TODO: acrescentar na estrutura esses itens?

		for(i = 0; i < nro_pre_requisitos; i++) {
			fscanf(fp, "%d", &pre_requisito);
			fscanf(fp, "%c", &lixo);

			if(pesquisa_tarefa(G, pre_requisito)) {						// verifica se pre-requisito existe, se sim, insere na prerequisitos_tarefa
				G = insere_prerequisitos(G, id_tarefa, pre_requisito, duracao_tarefa, inicio_min_tarefa);
			}
		}

		fscanf(fp, "%c", &lixo);

	}

	fclose(fp);
	return G;

 }

/*
typedef struct LISTA{
    tarefa* v;
    struct LISTA* prox;
}prerequisitos_tarefa;

typedef struct FILA{
    prerequisitos_tarefa* ini;
    prerequisitos_tarefa* fim;
}fila;

fila* criaFila(){
    fila* f = (fila*)malloc(sizeof(fila));
    f->fim = f->ini = NULL;
    return f;
}

void insereFila(tarefa* v, fila* f){
    if(f){
        prerequisitos_tarefa* t = (prerequisitos_tarefa*)malloc(sizeof(prerequisitos_tarefa));
        t->v = v;
        t->prox = NULL;
        if(!f->ini)
            f->ini = t;
        if(f->fim)
            f->fim->prox = t;
        f->fim = t;
    }
}

tarefa* retiraFila(fila* f){
    if(f && f->ini){
        prerequisitos_tarefa* t = f->ini;
        tarefa* v = t->v;
        f->ini = t->prox;
        if(!t->prox)
            f->fim = f->ini;
        free(t);
        return v;
    }
    else
        return NULL;
}

int filaVazia(fila* f){
    if(f && f->ini)
        return 0;
    return 1;
}

void BFS(grafo* G, char* vorig){
    tarefa* u;
    for(u=G->T;u!=NULL;u=u->prox)
        if(strcmp(u->v,vorig) != 0){
            u->c = -1;
            u->d = 0x7FFFFFFF;
        }
    for(u=G->T;u!=NULL;u=u->prox)
        if(strcmp(u->v,vorig) == 0)
            break;
    u->c = 0;
    u->d = 0;
    fila* Q = criaFila();
    insereFila(u,Q);
    while(!filaVazia(Q)){
        tarefa* j = retiraFila(Q);
        prerequisitos* e;
        for(e=j->prerequisitos_tarefa;e!=NULL;e=e->prox){
            tarefa* tmp;
            for(tmp=G->T;tmp!=NULL;tmp=tmp->prox)
                if(strcmp(tmp->v,e->v) == 0)
                    break;
            if(tmp && tmp->c == -1){
                tmp->c = 0;
                tmp->d = j->d + e->peso;
                insereFila(tmp,Q);
            }
        }
        j->c = 1;
    }
}

double peso_caminho(grafo* G, char* vorig, char* vdest){
    BFS(G,vorig);
    tarefa* tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox)
        if(strcmp(vdest,tmp->v)==0)
            return tmp->d;
    return -1;
}

int grafo_conexo(grafo* G){
    tarefa* tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        if(tmp->vorig == 1){
            BFS(G,tmp->v);
            tarefa* tmp2;
            for(tmp2=G->T;tmp2!=NULL;tmp2=tmp2->prox)
                if(tmp2->d == 0x7FFFFFFF)
                    return 0;
        }
   }
   return 1;
}*/

void imprime_grafo(grafo* G, char* nome_arq) {

    FILE* fp = fopen(nome_arq,"w");
    tarefa* tmp;

    for(tmp = G->T; tmp != NULL; tmp = tmp->prox) {

		fprintf(fp, "%d ",tmp->id_tarefa);
		fprintf(fp, "'%s' ", tmp->nome_tarefa);
		fprintf(fp, "%d ", tmp->tarefa_executada);
		fprintf(fp, "%d ", tmp->duracao_tarefa);
		fprintf(fp, "%d ", tmp->inicio_min_tarefa);
		fprintf(fp, "%d ", tmp->n_prerequisitos);

		prerequisitos * tmp2 = tmp->prerequisitos_tarefa;

		if(!tmp2)
			fprintf(fp, "\n");
		else {

			for(tmp2 = tmp->prerequisitos_tarefa; tmp2 != NULL; tmp2 = tmp2->prox) {
				if (tmp2->prox == NULL)
					fprintf(fp, "%d\n", tmp2->id_prerequisito);
				else
					fprintf(fp, "%d ", tmp2->id_prerequisito);
			}

		}

    }

    fclose(fp);
}

void libera_grafo(grafo* G){
    if(G){
        tarefa* t = G->T;
        while(t){
            prerequisitos* p = t->prerequisitos_tarefa;
            while (p){
                prerequisitos* tmp = p->prox;
                free(p);
                p = tmp;
            }
            tarefa* tmp1 = t->prox;
            free(t);
            t = tmp1;
        }
    }
}

int verifica_consistencia(grafo* G){
    tarefa *tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        tarefa* tmp2;
        for(tmp2=tmp->prox;tmp2!=NULL;tmp2=tmp2->prox){
            if(tmp->id_tarefa == tmp2-> id_tarefa){
                printf("Inconsistencia encontrada. Possui duas tarefas com o mesmo id: %d.\n", tmp->id_tarefa);
                return 0;
            }
        }
        prerequisitos* e;
        for(e=tmp->prerequisitos_tarefa;e!=NULL;e=e->prox){
            prerequisitos* e2;
            for(e2=e->prox;e2!=NULL;e2=e2->prox){
                if(e->id_prerequisito == e2->id_prerequisito){
                    printf("Inconsistencia encontrada. A tarefa de id %d possui dois pre requisitos com o mesmo id: %d.\n", tmp->id_tarefa, e->id_prerequisito);
                    return 0;
                }
            }
        }
    }
    printf("Os Pre requisitos e tarefas sao consistentes.\n");
    return 1;
}

int pesquisa_tarefa(grafo* G, int id_tarefa){
    tarefa *tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        if(tmp->id_tarefa == id_tarefa)
            return 1;
    }
    return 0;
}


int pesquisa_prerequisitos(grafo* G, int id_tarefa, int id_prerequisito){
    tarefa *tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        prerequisitos* e;
        for(e=tmp->prerequisitos_tarefa;e!=NULL;e=e->prox){
            if(e->id_prerequisito == id_prerequisito)
                return 1;
        }
    }
    return 0;
}

