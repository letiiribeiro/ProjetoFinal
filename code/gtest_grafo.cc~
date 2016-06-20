#include"gtest/gtest.h"
#include "grafo.h"
/*
TEST(TestInsereVertice, insere_vertice){
    char str_arq[] = "../code/grafo.txt";
    char str_vertice[] = "HELLO";
    
    grafo* G = le_grafo(str_arq);
    G = insere_vertice(G, str_vertice);
    EXPECT_EQ(1, pesquisa_vertice(G, str_vertice));
    libera_grafo(G);
    G = cria_grafo(); //testando para grafo criado manualmente
    G = insere_vertice(G, str_vertice);
    EXPECT_EQ(1, pesquisa_vertice(G, str_vertice));
    libera_grafo(G);
}

TEST(TestRemoveVertice, remove_vertice){
    char str_arq[] = "../code/grafo.txt";
    char str_vertice[] = "HELLO";
    
    grafo* G = le_grafo(str_arq);
    G = insere_vertice(G, str_vertice);
    G = remove_vertice(G, str_vertice);
    EXPECT_NE(1, pesquisa_vertice(G, str_vertice));
    libera_grafo(G);
    G = cria_grafo();
    G = insere_vertice(G, str_vertice);
    G = remove_vertice(G, str_vertice);
    EXPECT_NE(1, pesquisa_vertice(G, str_vertice));
    libera_grafo(G);
    
}

TEST(TestInsereAresta, insere_aresta){
    char str_arq[] = "../code/grafo.txt";
    char str_vorig[] = "HELLO";
    char str_vdest[] = "ITSME";
    double peso = 9.0;
    
    grafo* G = le_grafo(str_arq);
    G = insere_vertice(G, str_vorig);
    G = insere_vertice(G, str_vdest);
    G = insere_aresta(G, str_vorig, str_vdest, peso);
    EXPECT_EQ(1, pesquisa_aresta(G, str_vorig, str_vdest, peso));
    libera_grafo(G);
    G = cria_grafo();
    G = insere_vertice(G, str_vorig);
    G = insere_vertice(G, str_vdest);
    G = insere_aresta(G, str_vorig, str_vdest, peso);
    EXPECT_EQ(1, pesquisa_aresta(G, str_vorig, str_vdest, peso));
    libera_grafo(G);
    
}

TEST(TestRemoveAresta, remove_aresta){
    char str_arq[] = "../code/grafo.txt";
    char str_vorig[] = "HELLO";
    char str_vdest[] = "ITSME";
    double peso = 9.0;
    
    grafo* G = le_grafo(str_arq);
    G = insere_vertice(G, str_vorig);
    G = insere_vertice(G, str_vdest);
    G = insere_aresta(G, str_vorig, str_vdest, peso);
    G = remove_aresta(G, str_vorig, str_vdest);
    EXPECT_NE(1, pesquisa_aresta(G, str_vorig, str_vdest, peso));
    libera_grafo(G);
    G = cria_grafo();
    G = insere_vertice(G, str_vorig);
    G = insere_vertice(G, str_vdest);
    G = insere_aresta(G, str_vorig, str_vdest, peso);
    G = remove_aresta(G, str_vorig, str_vdest);
    EXPECT_NE(1, pesquisa_aresta(G, str_vorig, str_vdest, peso));
    libera_grafo(G);
    
}

TEST(TestPesoCaminho, peso_caminho){
    char str_arq[] = "../code/grafo.txt";
    char str_vorig[] = "A";
    char str_vdest[] = "C";
    double pesocaminho;
    double peso = 5.0;
    
    grafo* G = le_grafo(str_arq);
    pesocaminho = peso_caminho(G, str_vorig, str_vdest);
    EXPECT_EQ(7.0, pesocaminho);
    libera_grafo(G);
    G = cria_grafo();
    G = insere_vertice(G, str_vorig);
    G = insere_vertice(G, str_vdest);
    G = insere_aresta(G, str_vorig, str_vdest, peso);
    pesocaminho = peso_caminho(G, str_vorig, str_vdest);
    EXPECT_EQ(5.0, pesocaminho);
    
}

TEST(TestGrafoConexo, grafo_conexo){
    char str_arq[] = "../code/grafo.txt";
    char str_vorig[] = "B";
    char str_vdest[] = "A";
    double peso = 7.5;
    
    grafo* G = le_grafo(str_arq);
    EXPECT_EQ(0, grafo_conexo(G));
    G = insere_aresta(G, str_vorig, str_vdest, peso);
    EXPECT_EQ(1, grafo_conexo(G));
    libera_grafo(G);
} 

TEST(TestVerificaConsistencia, verifica_consistencia){
    char str_arq[] = "../code/grafo.txt";
    char str_vertice[] = "A";
    char str_vorig[] = "B";
    char str_vdest[] = "C";
    double peso = 4.0;
    
    grafo* G = le_grafo(str_arq);
    EXPECT_EQ(1, verifica_consistencia(G));
    G = insere_vertice(G, str_vertice);
    EXPECT_EQ(0, verifica_consistencia(G)); 
    G = remove_vertice(G, str_vertice);
    G = insere_aresta(G, str_vorig, str_vdest, peso);
    EXPECT_EQ(0, verifica_consistencia(G));
    libera_grafo(G);
}    
*/

TEST(TestImportaTarefasArquivo, le_grafo) {
    char str_arq[] = "../code/arquivo.txt";

    FILE* fp = fopen(str_arq,"r");
    ASSERT_TRUE(fp);
    
    grafo* G = le_grafo(fp);
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

    G = le_grafo(fp);
    EXPECT_EQ(G->T->id_tarefa,1);
    EXPECT_EQ(G->T->prox->id_tarefa,2);
    EXPECT_EQ(G->T->prox->prox->id_tarefa,3);
    ASSERT_TRUE(!G->T->prerequisitos_tarefa);
    EXPECT_EQ(G->T->prox->prerequisitos_tarefa->id_prerequisito, 1);
    EXPECT_EQ(G->T->prox->prox->prerequisitos_tarefa->id_prerequisito, 2);


}

int main(int argc, char **argv) {
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
    }
