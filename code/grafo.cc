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

grafo* insere_tarefa(grafo* G,char* nometarefa){
    tarefa* novo = (tarefa *)malloc(sizeof(tarefa));
    if(!novo){
        printf("Erro na alocacao!\n");
        exit(1);
    }
    strcpy(novo->v, nometarefa);
    tarefa* tmp;
    if(G->T==NULL)
        G->T= novo;
    else {
        for(tmp=G->T;tmp->prox!=NULL;tmp=tmp->prox);
        tmp->prox = novo;
    }
    novo->prox = NULL;
    novo->vorig = 0;
    novo->lista = NULL;
    return G;
}

grafo* insere_requisitos(grafo* G, char* vorig, char* vdest, double peso){
    requisitos* e = (requisitos *)malloc(sizeof(requisitos));
    if(!e){
        printf("Erro na alocacao.\n");
        exit(1);
    }
    strcpy(e->v,vdest);
    e->peso=peso;
    tarefa* tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        if(strcmp(tmp->v,vorig)==0){
            tmp->vorig = 1;
            requisitos* tmp2;
            if(tmp->lista==NULL)
               tmp->lista = e;
            else {
               for(tmp2=tmp->lista;tmp2->prox!=NULL;tmp2=tmp2->prox);
               tmp2->prox = e;
           }
        }
    }
    e->prox=NULL;
    return G;
}

grafo* remove_tarefa(grafo* G, char* nometarefa){
    tarefa *tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        if(tmp->prox && strcmp(tmp->prox->v,nometarefa)==0){
            tarefa* k= tmp->prox;
            tmp->prox = k->prox;
            free(k);
        }
        else if(strcmp(tmp->v,nometarefa) == 0){
            G->T = tmp->prox;
            free(tmp);
            break;
        }
    }
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        requisitos* e;
        for(e=tmp->lista;e!=NULL;e=e->prox){
            if(e->prox && strcmp(e->prox->v,nometarefa)==0){
                requisitos* k = e->prox;
                e->prox = k->prox;
                free(k);
            }
            else if(strcmp(e->v,nometarefa)==0){
                tmp->vorig = 0;
                tmp->lista = e->prox;
                free(e);
                break;
            }
        }
    }
    return G;
}

grafo* remove_requisitos(grafo* G, char* vorig, char* vdest){
    tarefa *tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        if(strcmp(tmp->v,vorig)==0){
            requisitos* e;
            for(e=tmp->lista;e!=NULL;e=e->prox){
                if(e->prox && strcmp(e->prox->v,vdest)==0){
                    requisitos* k = e->prox;
                    e->prox = k->prox;
                    free(k);
                }
                else if(strcmp(e->v,vdest)==0){
                    tmp->vorig = 0;
                    tmp->lista = e->prox;
                    free(e);
                    break;
                }
            }
        }
    }
    return G;
}

typedef struct LISTA{
    tarefa* v;
    struct LISTA* prox;
}lista;

typedef struct FILA{
    lista* ini;
    lista* fim;
}fila;

fila* criaFila(){
    fila* f = (fila*)malloc(sizeof(fila));
    f->fim = f->ini = NULL;
    return f;
}

void insereFila(tarefa* v, fila* f){
    if(f){
        lista* novo = (lista*)malloc(sizeof(lista));
        novo->v = v;
        novo->prox = NULL;
        if(!f->ini)
            f->ini = novo;
        if(f->fim)
            f->fim->prox = novo;
        f->fim = novo;
    }
}

tarefa* retiraFila(fila* f){
    if(f && f->ini){
        lista* t = f->ini;
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
        requisitos* e;
        for(e=j->lista;e!=NULL;e=e->prox){
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
}

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
        insere_requisitos(G,vorig,vdest,peso);
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
        requisitos *e;
        for(e=tmp->lista;e!=NULL;e=e->prox)
            fprintf(fp,"%s, %s, %.2f\n", tmp->v, e->v, e->peso);
    }
    fclose(fp);
}



void libera_grafo(grafo* G){
    if(G){
        tarefa* v = G->T;
        while(v){
            requisitos* e = v->lista;
            while (e){
                requisitos* etmp = e->prox;
                free(e);
                e = etmp;
            }
            tarefa* vtmp = v->prox;
            free(v);
            v = vtmp;
        }
    }
}

int verifica_consistencia(grafo* G){
    tarefa *tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        tarefa* tmp2;
        for(tmp2=tmp->prox;tmp2!=NULL;tmp2=tmp2->prox){
            if(strcmp(tmp->v,tmp2->v) == 0)
                return 0;
        }
        requisitos* e;
        for(e=tmp->lista;e!=NULL;e=e->prox){
            requisitos* e2;
            for(e2=e->prox;e2!=NULL;e2=e2->prox){
                if(strcmp(e->v,e2->v) == 0)
                    return 0;
            }
        }
    }
    return 1;
}

int pesquisa_tarefa(grafo* G, char* nometarefa){
    tarefa *tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        if(strcmp(tmp->v,nometarefa)== 0)
            return 1; 
    }
    return 0;
}
         

int pesquisa_requisitos(grafo* G, char* vorig, char* vdest, double peso){
    tarefa *tmp;
    for(tmp=G->T;tmp!=NULL;tmp=tmp->prox){
        requisitos* e;
        for(e=tmp->lista;e!=NULL;e=e->prox){
            if(strcmp(tmp->v,vorig)==0 && strcmp(e->v,vdest)==0 &&
                e->peso==peso)
                return 1;
        }
    }
    return 0;
}

