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

    if(id_tarefa < 0)
        return G;
    
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

grafo* edita_tarefa(grafo* G, int id_tarefa, int novo_id_tarefa, char* nome_tarefa, int
tarefa_executada, int duracao_tarefa, int inicio_min_tarefa, int
n_prerequisitos,int* id_prerequisitos, int flag){
    tarefa *tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        if(tmp->id_tarefa == id_tarefa){
            if(flag&1)
                strcpy(tmp->nome_tarefa, nome_tarefa);
            if(flag&2)
                tmp->tarefa_executada = tarefa_executada;
            if(flag&4)
                tmp->duracao_tarefa = duracao_tarefa;
            if(flag&8)
                tmp->inicio_min_tarefa = inicio_min_tarefa;
            if(flag&16){
                tmp->n_prerequisitos = n_prerequisitos;
                int i;
                prerequisitos* p;
                for(p=tmp->prerequisitos_tarefa;p;){
                    prerequisitos* l = p->prox;
                    free(p);
                    p = l;
                }
                tmp->prerequisitos_tarefa = NULL;
                for(i=0;i<n_prerequisitos;i++){
                    tarefa* t;
                    for(t=G->T;t&&t->id_tarefa!=id_prerequisitos[i];t=t->prox); 
                    G = insere_prerequisitos(G,id_tarefa,id_prerequisitos[i]);
                }
            }
            if(flag&32){
                if(!pesquisa_tarefa(G,novo_id_tarefa)){
                    tarefa *t;
                    for(t=G->T;t!=NULL;t=t->prox){
                        prerequisitos* e;
                        for(e=t->prerequisitos_tarefa;e!=NULL;e=e->prox){
                            if(e->id_prerequisito == id_tarefa)
                                e->id_prerequisito = novo_id_tarefa;
                        }
                    }
                    tmp->id_tarefa = novo_id_tarefa;
                }
            }
            break;   
        } 
        else 
            printf("Error: insira a tarefa primeiro para editar.\n");
    }
    return G;
}

grafo* insere_prerequisitos(grafo* G, int id_tarefa, int id_prerequisito){

    prerequisitos* e = (prerequisitos *)malloc(sizeof(prerequisitos));
    tarefa* tmp;

    if(!e) {
        printf("Erro na alocacao.\n");
        exit(1);
    }

    e->id_prerequisito = id_prerequisito;

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
        if(tmp->prox && tmp->prox->id_tarefa == id_tarefa){
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

grafo* remove_prerequisitos(grafo* G, int id_tarefa){
    tarefa *tmp;
    int achou;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox) {
            prerequisitos* e;
            achou = 0;

            for(e=tmp->prerequisitos_tarefa;e!=NULL;e=e->prox){
                if(e->prox && e->prox->id_prerequisito == id_tarefa){
                    prerequisitos* k = e->prox;
                    e->prox = k->prox;
                    achou = 1;
                    free(k);
                }
                else if(e->id_prerequisito == id_tarefa){
                    tmp->prerequisitos_tarefa = e->prox;
                    achou = 1;
                    free(e);
                    break;
                }
            }

            if(achou) {
                tmp->n_prerequisitos--;
            }
    }
    return G;
}
/*
 grafo* le_grafo(FILE * fp) {

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
			fscanf(fp, " %d", &pre_requisito);
		//	fscanf(fp, "%c", &lixo);

			if(pesquisa_tarefa(G, pre_requisito)) {						// verifica se pre-requisito existe, se sim, insere na prerequisitos_tarefa
				G = insere_prerequisitos(G, id_tarefa, pre_requisito);
			}
		}

		fscanf(fp, "%c", &lixo);

	}

	fclose(fp);
	return G;

 }
*/
grafo* le_grafo(FILE* fp){
    char buffer[100];
    int i;
    grafo* G = cria_grafo();
    
    while(fgets(buffer,100,fp) != NULL){
        i = 0;
        buffer[strlen(buffer)-1] = '\0';
        while(buffer[i] != 0x20)
            i++;
        buffer[i] = '\0';
        int id_tarefa = atoi(buffer);
        i += 2;
        int ini = i;
        while(buffer[i] != 0x27)
            i++;
        buffer[i] = '\0';
        char nome_tarefa[100];
        strcpy(nome_tarefa,&buffer[ini]);
        i += 2;
        ini = i;
        while(buffer[i] != 0x20)
            i++;
        buffer[i] = '\0';
        int tarefa_executada = atoi(&buffer[ini]);
        i++;
        ini = i;
        while(buffer[i] != 0x20)
            i++;
        buffer[i] = '\0';
        int duracao_tarefa = atoi(&buffer[ini]);
        i++;
        ini = i;
        while(buffer[i] != 0x20)
            i++;
        buffer[i] = '\0';
        int inicio_min_tarefa = atoi(&buffer[ini]);
        i++;
        ini = i;
        while(buffer[i] != 0x20)
            i++;
        buffer[i] = '\0';
        int n_prerequisitos = atoi(&buffer[ini]);
        int prerequisitos[n_prerequisitos];
        G = insere_tarefa(G, id_tarefa, nome_tarefa, tarefa_executada,
        duracao_tarefa, inicio_min_tarefa, n_prerequisitos);
        int j;
        for(j=0;j<n_prerequisitos;j++) {
            i++;
            ini = i;
            while(buffer[i] != 0x20)
                i++;
            buffer[i] = '\0';
            prerequisitos[j] = atoi(&buffer[ini]);
            G = insere_prerequisitos(G, id_tarefa, prerequisitos[j]);
        }
    }

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
        if(tmp->n_prerequisitos != 0)
            fprintf(fp, "%d ", tmp->n_prerequisitos);
        else
            fprintf(fp, "%d", tmp->n_prerequisitos);

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
                return tmp->id_tarefa;
            } else 
                return -1;
        }
        prerequisitos* e;
        for(e=tmp->prerequisitos_tarefa;e!=NULL;e=e->prox){
            prerequisitos* e2;
            for(e2=e->prox;e2!=NULL;e2=e2->prox){
                if(e->id_prerequisito == e2->id_prerequisito){
                    return tmp->prerequisitos_tarefa->id_prerequisito;
                } else 
                    return -1;
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
        if(tmp->id_tarefa == id_tarefa){
            prerequisitos* e;
            for(e=tmp->prerequisitos_tarefa;e!=NULL;e=e->prox){
                if(e->id_prerequisito == id_prerequisito)
                    return 1;
            }
        }
    }
    return 0;
}

int tempo_minimo(grafo* G, int id_tarefa){
    tarefa* tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        if(tmp->id_tarefa == id_tarefa){
            if(tmp->tempo_min != -1)
                return tmp->tempo_min;
            if(tmp->prerequisitos_tarefa == NULL){
                tmp->tempo_min = tmp->inicio_min_tarefa + tmp->duracao_tarefa;
                return tmp->tempo_min;
            }
            prerequisitos* p = tmp->prerequisitos_tarefa;
            int acc = 0;
            while(p){
                acc += tempo_minimo(G,p->id_prerequisito);                                 
                p = p->prox;
            }
            tmp->tempo_min = acc;
            return tmp->tempo_min;
        }
    }
    return 0;
}

typedef struct LISTA{
    int t;
    struct LISTA *prox, *ant;
} lista;

lista* insere_lista(lista* a, int id){
    lista* l = (lista*) malloc(sizeof(lista));  
    l->t = id;
    l->ant = NULL;
    l->prox = a;
    if(a)
            a->ant = l;
    return l;
}

lista* remove_lista(lista* a, int id, int* removeu){
    lista* l;
    int flg_ult = 0;
    int flg_prim = 0;
    lista* seg;
    for(l=a;l!=NULL;l=l->prox){
        if(l->t == id){
            lista* tmp = l->ant;
            if(tmp)
                tmp->prox = l->prox;
            if(l->prox)
                l->prox->ant = tmp;
            if(l->prox == NULL && l->ant == NULL)
                flg_ult = 1;
            if(l == a){
                flg_prim = 1;
                seg = l->prox;
            }
            free(l);
            *removeu = 1;
            break;
        }
    }
    *removeu = 0;
    if(flg_ult)
        return NULL;
    if(flg_prim)
        return seg;
    return a;
}

int tempo_minimo_total(grafo* G){
    tarefa* tmp;
    lista* l = NULL;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
         l = insere_lista(l,tmp->id_tarefa);
         tmp->tempo_min = -1;
    }
    int total = 0;
    while(l){
        int x = l->t;
        int removeu;
        tempo_minimo(G,x);
        for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
            if(tmp->tempo_min != -1)
                l = remove_lista(l,tmp->id_tarefa,&removeu);
            if(removeu)
                total += tmp->tempo_min;
        }
    }
    return total;
}

struct vetor{
    int id_tarefa;
    int tempo_min;
};

int compara(const void* a, const void* b){
    struct vetor x = *((struct vetor*)a);
    struct vetor y = *((struct vetor*)b);
    if(x.tempo_min == y.tempo_min)
        return 0;
    if(x.tempo_min < y.tempo_min)
        return -1;
    if(x.tempo_min > y.tempo_min)
        return 1; 
    return 0;
}

int* caminhos(grafo* G){
    tarefa* tmp;
    int i = 0;
    struct vetor V[100]; //assumindo que o numero maximo de tarefas no grafo e < 100
    lista* l = NULL;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
         l = insere_lista(l,tmp->id_tarefa);
         tmp->tempo_min = -1;
    }
    int total = 0;
    while(l){
        int x = l->t;
        int removeu;
        tempo_minimo(G,x);
        for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
            if(tmp->tempo_min != -1)
                l = remove_lista(l,tmp->id_tarefa,&removeu);
            if(removeu){
                total += tmp->tempo_min;
                V[i].id_tarefa = tmp->id_tarefa;
                V[i++].tempo_min = tmp->tempo_min;
            }
        }
    }
    qsort(V,i,sizeof(struct vetor),compara);
    int *VetorOrdenado = (int*) malloc(100*sizeof(int));
    int j;
    for(j=0;j<i;j++)
        VetorOrdenado[j] = V[j].id_tarefa;
    for(;j<100;j++)
        VetorOrdenado[j] = INT_MAX; 
    return VetorOrdenado;
} 

int* tarefas_concluidas(grafo* G, int periodo){
    tarefa* tmp;
    int i = 0;
    struct vetor V[100]; //assumindo que o numero maximo de tarefas no grafo e < 100
    lista* l = NULL;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
         l = insere_lista(l,tmp->id_tarefa);
         tmp->tempo_min = -1;
         tmp->tarefa_executada = 0;
    }
    int total = 0;
    while(l){
        int x = l->t;
        int removeu;
        tempo_minimo(G,x);
        for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
            if(tmp->tempo_min != -1)
                l = remove_lista(l,tmp->id_tarefa,&removeu);
            if(removeu){
                if(tmp->tempo_min <= periodo)
                    tmp->tarefa_executada = 1;
                total += tmp->tempo_min;
                V[i].id_tarefa = tmp->id_tarefa;
                V[i++].tempo_min = tmp->tempo_min;
            }
        }
    }
    qsort(V,i,sizeof(struct vetor),compara);
    int *VetorOrdenado = (int*) malloc(100*sizeof(int));
    int j,k=0;
    for(j=0;j<i;j++)
        if(V[j].tempo_min <= periodo)
            VetorOrdenado[k++] = V[j].id_tarefa;
    for(;k<100;k++)
        VetorOrdenado[k] = INT_MAX; 
    return VetorOrdenado;
}
