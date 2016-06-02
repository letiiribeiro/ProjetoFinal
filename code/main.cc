#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

int menu_entrada(){
    int entrada;
    while(1){
        printf("\n\n\n********************************************************************\n");
        printf("*                           PROGRAMA DE GRAFO                      *\n");
        printf("*                                                                  *\n");
        printf("*       Digite o numero correspondente a entrada desejada:         *\n");
        printf("*                                                                  *\n");
        printf("*       1 - Entrar com nome do arquivo texto contendo o grafo.     *\n");
        printf("*       2 - Criar novo grafo.                                      *\n");
        printf("*       3 - Sair.                                                  *\n");
        printf("*                                                                  *\n");
        printf("********************************************************************\n\n\n\n");
        char buf[100];
        fgets(buf,100,stdin);
        buf[strlen(buf)-1]='\0';
        entrada = atoi(buf);
        if(entrada >= 1 && entrada <= 3)
            break;
    }
    return entrada;

}

int menu_operacao(){
    int operacao;
    while(1){
        printf("\n\n\n********************************************************************\n");
        printf("*                           PROGRAMA DE GRAFO                      *\n");
        printf("*                                                                  *\n");
        printf("*       Digite o numero correspondente a operacao desejada:        *\n");
        printf("*                                                                  *\n");
        printf("*       1 - Inserir novo tarefa.                                  *\n");
        printf("*       2 - Inserir nova requisitos.                                   *\n");
        printf("*       3 - Remover tarefa.                                       *\n");
        printf("*       4 - Remover requisitos.                                        *\n");
        printf("*       5 - Encontrar peso do caminho.                             *\n");
        printf("*       6 - Verificar se o grafo e conexo.                         *\n");
        printf("*       7 - Verificar se o grafo e consistente.                    *\n");
        printf("*       8 - Gravar grafo no arquivo.                               *\n");
        printf("*       9 - Sair.                                                  *\n");
        printf("*                                                                  *\n");
        printf("********************************************************************\n\n\n\n");
        char buf[100];
        fgets(buf,100,stdin);
        buf[strlen(buf)-1]='\0';
        operacao = atoi(buf);
        if(operacao >= 1 && operacao <=9)
            break;
    }
    return operacao;
}

int main(){
    grafo* G;
    int m_entrada = menu_entrada();
    if(m_entrada == 1){
        printf("Digite o nome do arquivo de entrada: ");
        char nome_arq[100];
        fgets(nome_arq,100,stdin);
        nome_arq[strlen(nome_arq)-1]='\0';
        G = le_grafo(nome_arq);
    }
    else if(m_entrada == 2)
        G = cria_grafo();
    else
        return 0; 
    while(1){
        int m_operacao = menu_operacao();
        if(m_operacao == 1){
            printf("Digite o tarefa a ser inserido: ");
            char nometarefa[100];
            fgets(nometarefa,100,stdin);
            nometarefa[strlen(nometarefa)-1]='\0';
            G = insere_tarefa(G,nometarefa);
        }
        else if(m_operacao == 2){
            char vorig[100];
            char vdest[100];
            char p[100];
            double peso;
            printf("Digite o tarefa de origem da requisitos: ");
            fgets(vorig,100,stdin);
            vorig[strlen(vorig)-1]='\0';
            printf("Digite o tarefa de destino da requisitos: ");
            fgets(vdest,100,stdin);
            vdest[strlen(vdest)-1]='\0';
            printf("Digite o peso da requisitos: ");
            fgets(p,100,stdin);
            p[strlen(p)-1]='\0';
            peso = atof(p);
            G = insere_requisitos(G,vorig,vdest,peso);
        }
        else if(m_operacao == 3){
            printf("Digite o tarefa a ser removido: ");
            char nometarefa[100];
            fgets(nometarefa,100,stdin);
            nometarefa[strlen(nometarefa)-1]='\0';
            G = remove_tarefa(G,nometarefa);
        }
        else if(m_operacao == 4){
            char vorig[100];
            char vdest[100];
            printf("Digite o tarefa de origem da requisitos a ser removida: ");
            fgets(vorig,100,stdin);
            vorig[strlen(vorig)-1]='\0';
            printf("Digite o tarefa de destino da requisitos a ser removida: ");
            fgets(vdest,100,stdin);
            vdest[strlen(vdest)-1]='\0';
            G = remove_requisitos(G,vorig,vdest);
        }
        else if(m_operacao == 5){
            char vorig[100];
            char vdest[100];
            printf("Digite o tarefa de origem do caminho: ");
            fgets(vorig,100,stdin);
            vorig[strlen(vorig)-1]='\0';
            printf("Digite o tarefa de destino do caminho: ");
            fgets(vdest,100,stdin);
            vdest[strlen(vdest)-1]='\0';
            printf("Peso total do caminho = %.1f.\n",peso_caminho(G,vorig,vdest));
        }
        else if(m_operacao == 6){
            if(grafo_conexo(G))
                printf("O grafo e conexo.\n");
            else
                printf("O grafo nao e conexo.\n");
        }
        else if(m_operacao == 7){
            if(verifica_consistencia(G))
                printf("O grafo e consistente.\n");
            else
                printf("O grafo nao e consistente.\n");
        }
        else if(m_operacao == 8){
            printf("Digite o nome do arquivo de saida: ");
            char nome_arq[100];
            fgets(nome_arq,100,stdin);
            nome_arq[strlen(nome_arq)-1]='\0';
            imprime_grafo(G,nome_arq);
        }
        else
            break;
    }
    libera_grafo(G);
    return 0;
}

