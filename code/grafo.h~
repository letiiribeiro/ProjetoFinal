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
*
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
*
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
*	    Retorna um ponteiro para a estrutura de dados Grafo. 
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
*
*	Descrição:
*       Testa se o id da tarefa é negativo, caso seja é invalidado e não insere
*   na lista de tarefas. Caso o id seja válido, testa se a lista é vazia, seta
*   cada parâmetro passado para a tarefa e insere na lista de tarefas. 
*
*	Parâmetros:
*       Recebe todos os parâmetros que compoem uma tarefa.
*
*	Retorno:
*	    Retorna a estrutura de dados Grafo. 
*
*	Assertivas de Entrada:
*		G!= NULL;
*
*	Assertivas de Saida:
*       G != NULL; G->T != NULL; G->T->id_tarefa = id_tarefa; G->T->nome_tarefa
*       = nome_tarefa; G->T->tarefa_executada = tarefa_executada;
*       G->T->duracao_tarefa = duracao_tarefa; G->T->inicio_min_tarefa =
*       inicio_min_tarefa; G->T->n_prerequisitos = n_prerequisitos;  
*
***********************************************************************************/
grafo* insere_tarefa(grafo* G, int id_tarefa, char* nome_tarefa, int tarefa_executada, int
duracao_tarefa, int inicio_min_tarefa, int n_prerequisitos);
/*******************************************************************************//**
*	Função: Editar uma tarefa
*
*	Descrição:
*      Percorre a lista de tarefas com o id da tarefa a ser editada
*      e usa uma flag para testar quais campos o
*      usuario quer editar, caso ele edite o numero de pre requisitos, o
*      programa percorre a lista de pre requisitos da tarefa que esta sendo
*      editada, apaga todos os pre requisitos da lista e insere os novos pre
*      requisitos que o usuario digitar. Caso o usuario deseje modificar o id
*      da tarefa, percorre a lista de pre requisitos modificando o campo
*      id_prerequisito para apontar para o novo id da tarefa.
*
*	Parâmetros:
*      Recebe todos os parametros que compoem uma tarefa e seus pre requisitos
*      alem de flag para a interface com o usuario.
*
*	Valor Retornado:
*	    Retorna um ponteiro para a estrutura Grafo.
*
*	Assertiva Entrada:
*		G!=NULL; G->T!=NULL;
*
*	Assertiva Saida:
*       G->T->id_tarefa = novo_id_tarefa;
*       G->T->prerequisitos_tarefa->id_prerequisito = novo_id_tarefa; G->T->nome_tarefa
*       = nome_tarefa; G->T->tarefa_executada = tarefa_executada;
*       G->T->duracao_tarefa = duracao_tarefa; G->T->inicio_min_tarefa =
*       inicio_min_tarefa; G->T->n_prerequisitos = n_prerequisitos; 
*
***********************************************************************************/
grafo* edita_tarefa(grafo* G, int id_tarefa, int novo_id_tarefa, char* nome_tarefa, int
tarefa_executada, int duracao_tarefa, int inicio_min_tarefa, int
n_prerequisitos,int* id_prerequisitos, int flag);
/*******************************************************************************//**
*	Função: Inserir Pre Requisitos.
*
*	Descrição:
*       Percorre a lista de tarefas para achar a com o id onde sera
*       inserido o pre requisito e o insere no final da lista de pre
*       requisitos.
*
*	Parâmetros:
*       Recebe o id da tarefa que possui o pre requisito e o id do pre
*       requisito.
*
*	Valor Retornado:
*	    Retorna um ponteiro para a estrutura de dados Grafo.
*
*	Assertiva Entrada:
*		G != NULL; G->T->id_tarefa != NULL; 
*
*	Assertiva Saida:
*       G->T->prerequisitos_tarefa != NULL;
*       G->T->prerequisitos_tarefa->id_prerequisito = id_prerequisito;
*
***********************************************************************************/
grafo* insere_prerequisitos(grafo* G, int id_tarefa, int id_prerequisito);
/*******************************************************************************//**
*	Função: 
*       Remover tarefa.
*
*	Descrição:
*       Percorre a lista de tarefa até encontrar a tarefa a ser removida,
*       remove a tarefa e percorre a lista de pre 
*       requisitos para remover os pre requisitos dessa tarefa.
*
*	Parâmetros:
*       Recebe o Grafo e o Id da tarefa a ser removida.
*
*	Retorno:
*	    Retorna um ponteiro para a estrutura de dados Grafo. 
*
*	Assertivas de Entrada:
*		G != NULL;
*
*	Assertivas de Saida:
*       G->T->id_tarefa == NULL;
*
***********************************************************************************/
grafo* remove_tarefa(grafo* G, int id_tarefa);
/*******************************************************************************//**
*	Função: 
*       Remover pré requisitos de uma tarefa.
*
*	Descrição:
*       Percorre a lista de tarefa até encontrar a tarefa 
*       que terá seus pré requisitos removidos,
*       percorre a lista de pré requisitos para remover os
*       pré requisitos dessa tarefa.
*
*	Parâmetros:
*       Recebe o Grafo e o Id da tarefa que terá seus pré requisitos removidos.
*
*	Retorno:
*	    Retorna um ponteiro para a estrutura de dados Grafo. 
*
*	Assertivas de Entrada:
*		G != NULL;
*
*	Assertivas de Saida:
*       G->T->prerequisitos_tarefa->id_tarefa == NULL;
*
***********************************************************************************/
grafo* remove_prerequisitos(grafo* G, int id_tarefa);
/*******************************************************************************//**
*	Função: 
*       Leitura de grafo presente em arquivo.
*
*	Descrição:
*       Utiliza a função fgets para leitura para armazenar num buffer 
*       o conteúdo de cada linha, as condições de parada da leitura 
*       são 0x20(espaço) ou 0x27('), para valores inteiros utiliza a 
*       função atoi(attom to integer) para conversão de char para inteiro.
*
*	Parâmetros:
*       Recebe o nome do arquivo que conterá o Grafo.
*
*	Retorno:
*	    Retorna um ponteiro para a estrutura de dados Grafo.
*
*	Assertivas de Entrada:
*		nomeArquivo != NULL;
*
*	Assertivas de Saida:
*       G != NULL; G->T != NULL; G->T->id_tarefa = id_tarefa; G->T->nome_tarefa
*       = nome_tarefa; G->T->tarefa_executada = tarefa_executada;
*       G->T->duracao_tarefa = duracao_tarefa; G->T->inicio_min_tarefa =
*       inicio_min_tarefa; G->T->n_prerequisitos = n_prerequisitos; 
*       G->T->prerequisitos_tarefa != NULL;
*
***********************************************************************************/
grafo* le_grafo(char * nomeArquivo);
/*******************************************************************************//**
*	Função: 
*       Libera a memória do Grafo.
*
*	Descrição:
*       Remove primeiro todos os elementos das listas de pré requisitos,
*       depois todos os elementos da lista de tarefas e finalmente,
*       libera a memória do grafo.
*
*	Parâmetros:
*       Recebe um ponteiro para a estrutura de dados Grafo.
*
*	Retorno:
*	    Não possui. 
*
*	Assertivas de Entrada:
*		G != NULL;
*
*	Assertivas de Saida:
*       G == NULL; G->T == NULL; G->T->prerequisitos_tarefa == NULL;
*
***********************************************************************************/
void libera_grafo(grafo* G);
/*******************************************************************************//**
*	Função: 
*       Imprime o grafo em um arquivo.
*
*	Descrição:
*       Utiliza a função fprintf para imprimir no arquivo cada campo
*       conforme a especificação do projeto sugeria.
*
*	Parâmetros:
*       Recebe um ponteiro para Grafo e o nome do arquivo onde irá 
*       imprimir o grafo.
*
*	Retorno:
*	    Não possui. 
*
*	Assertivas de Entrada:
*		G != NULL; nome_arq != NULL;
*
***********************************************************************************/
void imprime_grafo(grafo* G, char* nome_arq);
/*******************************************************************************//**
*	Função: 
*       Verificar consistência do Grafo.
*
*	Descrição:
*       Percorre a lista de tarefas procurando se existem duas tarefas iguais,
*       caso existam, retorna a tarefa inconsistente. Percorre a lista de pré
*       requisitos da mesma maneira, retornando a inconsistência.
*
*	Parâmetros:
*       Recebe um ponteiro para a estrutura de dados Grafo.
*
*	Retorno:
*	    Retorna a tarefa ou pré requisito inconsistentes. Caso não encontre
*       inconsistências no grafo, retorna -1. 
*
*	Assertivas de Entrada:
*		G != NULL;
*
*	Assertivas de Saida:
*       int i = G->T->id_tarefa|| G->T->prerequisitos_tarefa->id_prerequisito || -1
*
***********************************************************************************/
int verifica_consistencia(grafo* G);
/*******************************************************************************//**
*	Função: 
*       Pesquisa a tarefa no grafo.
*
*	Descrição:
*       Percorre a lista de tarefas no grafo caso encontre a tarefa
*       com o id requerido, retorna 1, caso contrário, 0.
*
*	Parâmetros:
*       Recebe um ponteiro para a estrutura de dados Grafo e o id da tarefa
*       que deseja pesquisar.
*
*	Retorno:
*	    Retorna um inteiro, 0 ou 1.
*
*	Assertivas de Entrada:
*		G != NULL;
*
*	Assertivas de Saida:
*       int = 0 || 1;
*
***********************************************************************************/
int pesquisa_tarefa(grafo* G, int id_tarefa);
/*******************************************************************************//**
*	Função: 
*       Pesquisa o pre requisito da tarefa no grafo.
*
*	Descrição:
*       Percorre a lista de tarefas ate encontrar a tarefa com o id passado e percorre 
*       a sua lista de pre requisitos, caso encontre o pre requisito
*       com o id requerido, retorna 1, caso contrário, 0.
*
*	Parâmetros:
*       Recebe um ponteiro para a estrutura de dados Grafo e o id do pre requisito
*       que deseja pesquisar.
*
*	Retorno:
*	    Retorna um inteiro, 0 ou 1.
*
*	Assertivas de Entrada:
*		G != NULL;
*
*	Assertivas de Saida:
*       int = 0 || 1;
*
***********************************************************************************/
int pesquisa_prerequisitos(grafo* G, int id_tarefa, int id_prerequisito);
/*******************************************************************************//**
*	Função: 
*       Procura um tarefa no grafo e a retorna caso a encontre.
*
*	Descrição:
*       Aloca memoria para o grafo e o retorna.
*
*	Parâmetros:
*       Não possui nenhum parâmetro.
*
*	Retorno:
*	    Retorna um ponteiro para a estrutura de dados Tarefa.
*
*	Assertivas de Entrada:
*		G != NULL;
*
*	Assertivas de Saida:
*       int = G->T->id_tarefa || 0.
*
***********************************************************************************/
tarefa* procura_tarefa(grafo* G, int id_tarefa);
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
*	    Retorna um inteiro, o tempo mínimo para concluir todas as tarefas.
*
*	Assertivas de Entrada:
*		G != NULL;
*
*	Assertivas de Saida:
*       G != NULL;
*
***********************************************************************************/
int tempo_minimo_total(grafo* G);
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
*	    Retorna um vetor de inteiros. 
*
*	Assertivas de Entrada:
*		G != NULL;
*
*	Assertivas de Saida:
*       G != NULL;
*
***********************************************************************************/
int* caminhos(grafo* G);
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
*	    Retorna um vetor de inteiros. 
*
*	Assertivas de Entrada:
*		G != NULL;
*
*	Assertivas de Saida:
*       G != NULL;
*
***********************************************************************************/
int* tarefas_concluidas(grafo* G, int periodo);

#endif
/* GRAFO_INCLUDED */

