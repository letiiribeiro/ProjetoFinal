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

int main(int argc, char **argv) {
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
    }
