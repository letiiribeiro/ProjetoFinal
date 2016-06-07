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
    if(G->T==NULL)
        G->T= t;
    else {
        for(tmp=G->T;tmp->prox!=NULL;tmp=tmp->prox);
        tmp->prox = t;
    }
    t->prox = NULL;
    t->prerequisitos_tarefa = NULL;
    return G;
}


grafo* edita_tarefa(grafo* G, int id_tarefa, char* nome_tarefa, int
tarefa_executada, int duracao_tarefa, int inicio_min_tarefa, int n_prerequisitos){
    tarefa *tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        if(tmp->id_tarefa == id_tarefa){
            strcpy(tmp->nome_tarefa, nome_tarefa);
            tmp->tarefa_executada = tarefa_executada;
            tmp->duracao_tarefa = duracao_tarefa;
            tmp->inicio_min_tarefa = inicio_min_tarefa;
            tmp-> n_prerequisitos = n_prerequisitos;
        }
   }
  
    return G;
}


grafo* insere_prerequisitos(grafo* G, int id_tarefa, int id_prerequisito, int
duracao_tarefa, int inicio_min_tarefa){
    prerequisitos* e = (prerequisitos *)malloc(sizeof(prerequisitos));
    if(!e){
        printf("Erro na alocacao.\n");
        exit(1);
    }
    e->id_prerequisito = id_prerequisito;
    e->duracao_tarefa = duracao_tarefa;
    e->inicio_min_tarefa = inicio_min_tarefa;
    tarefa* tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
            prerequisitos* tmp2;
            if(tmp->prerequisitos_tarefa==NULL)
               tmp->prerequisitos_tarefa = e;
            else {
               for(tmp2=tmp->prerequisitos_tarefa;tmp2->prox!=NULL;tmp2=tmp2->prox);
               tmp2->prox = e;
           }
        }
    e->prox=NULL;
    return G;
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


/*
 grafo* le_grafo(char *nomeArq){
    char linha[MAX_LINHA];
    FILE* fp = fopen(nomeArq,"r");
    if(!fp){
       printf("Arquivo nao encontrado.\n");
       exit(1);
    }
    grafo* G = cria_grafo();
    fgets(linha,MAX_LINHA,fp);
    linha[strlen(linha)-1]='\0';
    int i=0;
    while(linha[i] != '\0'){
    	int j = i;
        for(;linha[i]!=',' && linha[i]!=' ' && linha[i]!='\0';i++);
        char nometarefa[TAM_STRING];
        strncpy(nometarefa,&linha[j],i-j);
        nometarefa[i-j]='\0';
        insere_tarefa(G,nometarefa);
        while(linha[i] == ',' || linha[i] == ' ')
            i++;
    }
    fgets(linha,MAX_LINHA,fp);
    while(fgets(linha,MAX_LINHA,fp)){
        linha[strlen(linha)-1]='\0';
        for(i=0;linha[i]!=',' && linha[i]!=' ' && linha[i]!='\0';i++);
        char vorig[TAM_STRING];
        char vdest[TAM_STRING];
        char p[TAM_STRING];
        double peso;
        strncpy(vorig,linha,i);
        vorig[i]='\0';
        while(linha[i] == ',' || linha[i] == ' ')
            i++;
        int j = i;
        for(;linha[i]!=',' && linha[i]!=' ' && linha[i]!='\0';i++);
        strncpy(vdest,&linha[j],i-j);
        vdest[i-j]='\0';
        while(linha[i] == ',' || linha[i] == ' ')
            i++;
     	j = i;
        for(;linha[i]!=',' && linha[i]!=' ' && linha[i]!='\0';i++);
        strncpy(p,&linha[j],i-j);
        p[i-j]='\0';
        peso = atof(p);
        insere_prerequisitos(G,vorig,vdest,peso);
    }
    fclose(fp);
    return G;
}

void imprime_grafo(grafo* G, char* nome_arq){
    FILE* fp = fopen(nome_arq,"w");
    tarefa* tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox)
        if(tmp->prox == NULL)
            fprintf(fp,"%s\n",tmp->v);
        else
            fprintf(fp,"%s, ",tmp->v);

    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        tarefa* k = tmp->prox;
        while(k && (!k->vorig))
            k=k->prox;
        if(!k && tmp->vorig)
            fprintf(fp,"%s\n",tmp->v);
        else if(tmp->vorig)
            fprintf(fp,"%s, ",tmp->v);
    }

    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        prerequisitos *e;
        for(e=tmp->prerequisitos_tarefa;e!=NULL;e=e->prox)
            fprintf(fp,"%s, %s, %.2f\n", tmp->v, e->v, e->peso);
    }
    fclose(fp);
}

*/

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
            if(tmp->id_tarefa == tmp2-> id_tarefa)
                return 0;
        }
        prerequisitos* e;
        for(e=tmp->prerequisitos_tarefa;e!=NULL;e=e->prox){
            prerequisitos* e2;
            for(e2=e->prox;e2!=NULL;e2=e2->prox){
                if(e2->id_prerequisito == e2->id_prerequisito)
                    return 0;
            }
        }
    }
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

