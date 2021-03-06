#ifndef GRAFO_INCLUDED
#define GRAFO_INCLUDED

#define TAM_STRING 100
#define FLG_NOME 0x1
#define FLG_EXEC 0x2
#define FLG_DURA 0x4
#define FLG_INIC 0x8
#define FLG_PRER 0x10
#define FLG_IDTR 0x20
#define INT_MAX 2147483647

/*********************
* Exemplo de uso de edita_tarefa caso o usuario deseje alterar o nome e inicio
* e prerequisitos
* edita_tarefa(G,id_tarefa,novo_id_tarefa,nome_tarefa,tarefa_executada,duracao_tarefa,inicio_min_tarefa,n_prerequisitos,id_prerequisitos,FLG_NOME|FLG_INIC|FLG_PRER)
* 
flag = 0;

if(quis_nome)
    flag |= FLG_NOME;
*/

typedef struct PreRequisitos {
    int id_prerequisito;
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
    int tempo_min;
    int tempo_inic;
} tarefa;

typedef struct Grafo {
    tarefa *T;
} grafo;

/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
grafo* cria_grafo();
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
grafo* insere_tarefa(grafo* G, int id_tarefa, char* nome_tarefa, int tarefa_executada, int
duracao_tarefa, int inicio_min_tarefa, int n_prerequisitos);
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
grafo* edita_tarefa(grafo* G, int id_tarefa, int novo_id_tarefa, char* nome_tarefa, int
tarefa_executada, int duracao_tarefa, int inicio_min_tarefa, int
n_prerequisitos,int* id_prerequisitos, int flag);
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
grafo* insere_prerequisitos(grafo* G, int id_tarefa, int id_prerequisito);
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
grafo* remove_tarefa(grafo* G, int id_tarefa);
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
grafo* remove_prerequisitos(grafo* G, int id_tarefa);
/*******************************************************************************//**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
grafo* le_grafo(FILE* fp);
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
void libera_grafo(grafo* G);
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
void imprime_grafo(grafo* G, char* nome_arq);
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
int verifica_consistencia(grafo* G);
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
int pesquisa_tarefa(grafo* G, int id_tarefa);
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
int pesquisa_prerequisitos(grafo* G, int id_tarefa, int id_prerequisito);
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
tarefa* procura_tarefa(grafo* G, int id_tarefa);
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
int tempo_minimo(grafo* G, int id_tarefa);
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
int tempo_minimo_total(grafo* G);
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
int* caminhos(grafo* G);
/**
*	Função: retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*
*
*
*	Parâmetros:
*
*
*	Valor Retornado
*	
*	AssertivaEntrada
*		
*	AssertivaSaida
*
*
***********************************************************************************/
int* tarefas_concluidas(grafo* G, int periodo);

#endif
/* GRAFO_INCLUDED */

