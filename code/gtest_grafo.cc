#include"gtest/gtest.h"
#include "grafo.h"

TEST(TestImportaTarefasArquivo, le_grafo) {
    char str_arq[] = "../code/arquivo.txt";

    FILE* fp = fopen(str_arq,"r");
    ASSERT_TRUE(fp);
    
    grafo* G = le_grafo(str_arq);
    ASSERT_TRUE(G);
    
    EXPECT_EQ(G->T->id_tarefa,100);
    EXPECT_EQ(G->T->prox->id_tarefa,101);
    EXPECT_EQ(G->T->prox->prox->id_tarefa,102);
   
}

TEST(TestGravaTarefasArquivo, imprime_grafo) {
    char str_arq[] = "../code/saida.txt";
    char str1[] = "primeira";
    char str2[] = "segunda";
    char str3[] = "terceira";
    
    grafo* G = cria_grafo();
    ASSERT_TRUE(G);

    G = insere_tarefa(G, 1, str1, 0, 1, 0, 0);
    G = insere_tarefa(G, 2, str2, 0, 2, 2, 1);
    G = insere_tarefa(G, 3, str3, 0, 3, 5, 1);

    G = insere_prerequisitos(G, 2, 1);
    G = insere_prerequisitos(G, 3, 2);

    imprime_grafo(G, str_arq);

    FILE* fp = fopen(str_arq, "r");
    ASSERT_TRUE(fp);

    G = le_grafo(str_arq);
    EXPECT_EQ(G->T->id_tarefa,1);
    EXPECT_EQ(G->T->prox->id_tarefa,2);
    EXPECT_EQ(G->T->prox->prox->id_tarefa,3);
    ASSERT_TRUE(!G->T->prerequisitos_tarefa);
    EXPECT_EQ(G->T->prox->prerequisitos_tarefa->id_prerequisito, 1);
    EXPECT_EQ(G->T->prox->prox->prerequisitos_tarefa->id_prerequisito, 2);

}

TEST(TestRemoveTarefa,remove_tarefa) {
    char str1[] = "primeira";
    char str2[] = "segunda";
    char str3[] = "terceira";
    char str4[] = "quarta";

    grafo* G = cria_grafo();
    //ASSERT_TRUE(G);

    G = insere_tarefa(G, 1, str1, 0, 1, 0, 0);
    G = insere_tarefa(G, 2, str2, 0, 2, 2, 1);
    G = insere_tarefa(G, 3, str3, 0, 3, 5, 1);
    G = insere_tarefa(G, 4, str4, 5, 2, 5, 2);

    G = insere_prerequisitos(G, 2, 1);
    G = insere_prerequisitos(G, 3, 2);
    G = insere_prerequisitos(G, 4, 3);
    G = insere_prerequisitos(G, 4, 2);

    G = remove_tarefa(G, 2);

    EXPECT_EQ(G->T->id_tarefa, 1);
    EXPECT_EQ(G->T->prox->id_tarefa, 3);
    EXPECT_EQ(G->T->prox->prox->id_tarefa,4);
    EXPECT_TRUE(!G->T->prerequisitos_tarefa);
    EXPECT_TRUE(!G->T->prox->prerequisitos_tarefa);
    EXPECT_EQ(G->T->prox->prox->prerequisitos_tarefa->id_prerequisito, 3);    
    EXPECT_TRUE(!G->T->prox->prox->prerequisitos_tarefa->prox);

}

TEST(TestRemovePreRequisito,remove_prerequisitos) {
    char str1[] = "primeira";
    char str2[] = "segunda";
    char str3[] = "terceira";
    char str4[] = "quarta";

    grafo* G = cria_grafo();
    ASSERT_TRUE(G);

    G = insere_tarefa(G, 1, str1, 0, 1, 0, 0);
    G = insere_tarefa(G, 2, str2, 0, 2, 2, 0);
    G = insere_tarefa(G, 3, str3, 0, 3, 5, 0);
    G = insere_tarefa(G, 4, str4, 5, 2, 5, 3);

    G = insere_prerequisitos(G, 4, 1);
    G = insere_prerequisitos(G, 4, 2);
    G = insere_prerequisitos(G, 4, 3);
    
    G = remove_prerequisitos(G, 4);

    EXPECT_EQ(!G->T->prox->prox->prox->prerequisitos_tarefa->id_prerequisito, 0);

}

TEST(TestPesquisaPreRequisito,pesquisa_prerequisitos) {
    char str1[] = "primeira";
    char str2[] = "segunda";
    char str3[] = "terceira";
    char str4[] = "quarta";
    int T1, T2;

    grafo* G = cria_grafo();
    ASSERT_TRUE(G);

    G = insere_tarefa(G, 1, str1, 0, 1, 0, 0);
    G = insere_tarefa(G, 2, str2, 0, 2, 2, 0);
    G = insere_tarefa(G, 3, str3, 0, 3, 5, 0);
    G = insere_tarefa(G, 4, str4, 5, 2, 5, 3);

    G = insere_prerequisitos(G, 4, 1);
    G = insere_prerequisitos(G, 4, 2);
    G = insere_prerequisitos(G, 4, 3);
    
    T1 = pesquisa_prerequisitos(G, 4, 3);
    T2 = pesquisa_prerequisitos(G, 1, 2);

    EXPECT_EQ(T1, 1);
    EXPECT_EQ(T2, 0);

}

TEST(TestEditaTarefa,edita_tarefa) {
    char str1[] = "primeira";
    char str2[] = "segunda";
    char str3[] = "terceira";
    char str4[] = "quarta";
    char nome_tarefa[] = "nome alterado";
    int id_prerequisitos[10];

    grafo* G = cria_grafo();
    ASSERT_TRUE(G);

    G = insere_tarefa(G, 1, str1, 0, 1, 0, 0);
    G = insere_tarefa(G, 2, str2, 0, 2, 2, 0);
    G = insere_tarefa(G, 3, str3, 0, 3, 5, 0);
    G = insere_tarefa(G, 4, str4, 5, 2, 5, 3);

    G = insere_prerequisitos(G, 4, 1);
    G = insere_prerequisitos(G, 4, 2);
    G = insere_prerequisitos(G, 4, 3);

    id_prerequisitos[0] = 2;

    G = edita_tarefa(G, 4, 5, nome_tarefa, 0, 3, 6, 1, id_prerequisitos, FLG_NOME|FLG_INIC|FLG_PRER|FLG_EXEC|FLG_DURA|FLG_IDTR);    

    EXPECT_EQ(G->T->prox->prox->prox->id_tarefa, 5);
}

TEST(TestLiberaGrafo, libera_grafo) {
    char str1[] = "primeira";
    char str2[] = "segunda";
    char str3[] = "terceira";
    char str4[] = "quarta";

    grafo* G = cria_grafo();
    ASSERT_TRUE(G);

    G = insere_tarefa(G, 1, str1, 0, 1, 0, 0);
    G = insere_tarefa(G, 2, str2, 0, 2, 2, 0);
    G = insere_tarefa(G, 3, str3, 0, 3, 5, 0);
    G = insere_tarefa(G, 4, str4, 5, 2, 5, 3);

    G = insere_prerequisitos(G, 4, 1);
    G = insere_prerequisitos(G, 4, 2);
    G = insere_prerequisitos(G, 4, 3);

    libera_grafo(G);

    ASSERT_TRUE(G);
}

TEST(TestVerificaConsistencia, verifica_consistencia) {
    char str1[] = "primeira";
    char str2[] = "segunda";
    char str3[] = "terceira";
    char str4[] = "quarta";

    grafo* G = cria_grafo();
    ASSERT_TRUE(G);

    G = insere_tarefa(G, 1, str1, 0, 1, 0, 0);
    G = insere_tarefa(G, 2, str2, 0, 2, 2, 0);
    G = insere_tarefa(G, 3, str3, 0, 3, 5, 0);
    G = insere_tarefa(G, 4, str4, 5, 2, 5, 3);

    G = insere_prerequisitos(G, 4, 1);
    G = insere_prerequisitos(G, 4, 2);
    G = insere_prerequisitos(G, 4, 3);

    int i = verifica_consistencia(G);

    EXPECT_EQ(i, -1);
}

TEST(TestRecuperarTarefaPorID, procura_tarefa) {

    char str1[] = "primeira";
    char str2[] = "segunda";
    char str3[] = "terceira";
    char str4[] = "quarta";
    int id_prerequisitos[10];
    tarefa * T;

    grafo* G = cria_grafo();
    ASSERT_TRUE(G);

    G = insere_tarefa(G, 1, str1, 0, 1, 0, 0);
    G = insere_tarefa(G, 2, str2, 0, 2, 2, 0);
    G = insere_tarefa(G, 3, str3, 0, 3, 5, 0);
    G = insere_tarefa(G, 4, str4, 5, 2, 5, 3);

    G = insere_prerequisitos(G, 2, 1);
    G = insere_prerequisitos(G, 3, 2);
    G = insere_prerequisitos(G, 4, 3);

    T = procura_tarefa(G, 7);

    ASSERT_TRUE(T == NULL);
    ASSERT_EQ(pesquisa_tarefa(G,3), 1);

}

int main(int argc, char **argv) {
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
    }
