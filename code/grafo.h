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

/**
* Estrutura de lista para os pré requisitos
* contendo o Id e um ponteiro para apontar para o
* próximo elemento.
*/
typedef struct PreRequisitos {
    int id_prerequisito;
    struct PreRequisitos *prox;
} prerequisitos;
/**
* Estrutura de lista para as tarefas do grafo
* contendo o Id da tarefa(id_tarefa), o nome da 
* tarefa (nome_tarefa), se a tarefa já foi executada
* ou não (tarefa_executada), a duração da tarefa
* (duracao_tarefa), o periodo minimo em que uma tarefa pode iniciar
* (inicio_min_tarefa), o número de pre requisitos dessa tarefa
* (n_prerequisitos), um ponteiro para apontar para o próximo
* elemento (*prox) e um ponteiro para apontar para a lista
* de pré requisitos dessa tarefa (*prerequisitos_tarefa).
*/
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
/**
* Cabeça de Estrutura de Dados Grafo
* que possui um ponteiro para apontar para 
* a lista de tarefas.
*/
typedef struct Grafo {
    tarefa *T;
} grafo;

/*******************************************************************************//**
*	Função: 
*       Retornar Grafo sem tarefas e pre requisitos.
*
*	Descrição:
*       Aloca memoria para o grafo e o retorna.
*
*	Parâmetros:
*       Não possui nenhum parâmetro.
*
*	Retorno:
*	    Retorna a estrutura de dados Grafo. 
*
*	Assertivas de Entrada:
*		Não possui.
*
*	Assertivas de Saida:
*       G != NULL;
*
***********************************************************************************/
grafo* cria_grafo();
/*******************************************************************************//**
*	Função: 
*       Inserir tarefas na lista de tarefas.
*	Descrição:
*       Testa se o id da tarefa é negativo, caso seja é invalidado e não insere
*   na lista de tarefas. Caso o id seja válido, testa se a lista é vazia, seta
*   cada parâmetro passado para a tarefa e insere na lista de tarefas. 
*	Parâmetros:
*       Recebe todos os parâmetros que compoem uma tarefa.
*	Retorno:
*	    Retorna a estrutura de dados Grafo. 
*	Assertivas de Entrada:
*		G!= NULL;
*	Assertivas de Saida:
*       G != NULL; G->T != NULL;
***********************************************************************************/
grafo* insere_tarefa(grafo* G, int id_tarefa, char* nome_tarefa, int tarefa_executada, int
duracao_tarefa, int inicio_min_tarefa, int n_prerequisitos);
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
grafo* edita_tarefa(grafo* G, int id_tarefa, int novo_id_tarefa, char* nome_tarefa, int
tarefa_executada, int duracao_tarefa, int inicio_min_tarefa, int
n_prerequisitos,int* id_prerequisitos, int flag);
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
grafo* insere_prerequisitos(grafo* G, int id_tarefa, int id_prerequisito);
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
grafo* remove_tarefa(grafo* G, int id_tarefa);
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
grafo* le_grafo(char * nomeArquivo);
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
void libera_grafo(grafo* G);
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
void imprime_grafo(grafo* G, char* nome_arq);
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
int verifica_consistencia(grafo* G);
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
int pesquisa_tarefa(grafo* G, int id_tarefa);
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
int pesquisa_prerequisitos(grafo* G, int id_tarefa, int id_prerequisito);
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
tarefa* procura_tarefa(grafo* G, int id_tarefa);
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
int tempo_minimo(grafo* G, int id_tarefa);
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
int tempo_minimo_total(grafo* G);
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
int* caminhos(grafo* G);
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
int* tarefas_concluidas(grafo* G, int periodo);

#endif
/* GRAFO_INCLUDED */

