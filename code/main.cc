#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "grafo.h"

#define LARGURA 50
#define ALTURA 10

int startx = 0;
int starty = 0;

char vOpcoes[3][70];
char vOperacoes[8][70];
char vVisualizador[7][70];

int n_opcoes = 3;
int n_operacoes = 8;
int n_visualizador = 7;

void print_menu(WINDOW *menu_win, int highlight) {

    int x,y,i;
    x = 1; 
    y = 1;

    box(menu_win,0,0);
    for(i=0; i< n_opcoes; i++){
        if(highlight == i+1) 
        {
            wattron(menu_win,A_REVERSE);
            mvwprintw(menu_win,y,x,"\t%s",vOpcoes[i]);
            wattroff(menu_win,A_REVERSE);
        }
        else
            mvwprintw(menu_win,y,x,"\t%s",vOpcoes[i]);
            ++y;
    }

    wrefresh(menu_win);
}

void print_operacoes(WINDOW *menu_win, int highlight) {

    int x,y,i;
    x = 1; 
    y = 1;

    box(menu_win,0,0);
    for(i=0; i< n_operacoes; i++){
        if(highlight == i+1) 
        {
            wattron(menu_win,A_REVERSE);
            mvwprintw(menu_win,y,x,"\t%s",vOperacoes[i]);
            wattroff(menu_win,A_REVERSE);
        }
        else
            mvwprintw(menu_win,y,x,"\t%s",vOperacoes[i]);
            ++y;
    }

    wrefresh(menu_win);
}

void print_visualizador(WINDOW *menu_win, int highlight) {

    int x,y,i;
    x = 1; 
    y = 1;

    box(menu_win,0,0);
    for(i=0; i< n_visualizador; i++){
        if(highlight == i+1) 
        {
            wattron(menu_win,A_REVERSE);
            mvwprintw(menu_win,y,x,"\t%s",vVisualizador[i]);
            wattroff(menu_win,A_REVERSE);
        }
        else
            mvwprintw(menu_win,y,x,"\t%s",vVisualizador[i]);
            ++y;
    }

    wrefresh(menu_win);
}

void imprimirRotulo(WINDOW *tmpJanela,int y, int x, char *sRotulo){

    wattron(tmpJanela,COLOR_PAIR(1));
    mvwprintw(tmpJanela,y,x,sRotulo);
    wattroff(tmpJanela,COLOR_PAIR(1));

}

void destruir_menu(WINDOW *menu_win){
    wclear(menu_win);
    wborder(menu_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');  
    wrefresh(menu_win);
    delwin(menu_win); 
}

char * importar_de_arquivo(char * nomeArquivo) {
	WINDOW * janela;
	int telaAltura, telaLargura;
    int startx, starty;
    char msg1[] = "Nome arquivo:_______________________________";
    char msg2[] = "[ENTER]";

	init_pair(1,COLOR_GREEN,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    imprimirRotulo(janela,starty+2,startx+1,msg1);
    imprimirRotulo(janela,starty+5,startx+20,msg2);

    echo();
    wmove(janela,starty+2,startx+15);
    wgetstr(janela,nomeArquivo);

    wclear(janela);
    wborder(janela, ' ', ' ', ' ',' ',' ',' ',' ',' ');  
    wrefresh(janela);

    delwin(janela);

    return nomeArquivo;

}

void erro_insere_pre_requisito() {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty;
    char c;
    char msg1[] = "ATENCAO!";
    char msg2[] = "Inconsistencia na insercao de pre-requisito";
    char msg3[] = "Verifique se o(s) ID(s) informado(s) existe(m)";
    char msg4[] = "Pressione qualquer tecla para retornar";

    init_pair(1,COLOR_RED,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();    

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    
        imprimirRotulo(janela,starty+2,startx+20,msg1);
        imprimirRotulo(janela, starty+3,startx+2,msg2);
        imprimirRotulo(janela,starty+4,startx+2,msg3);
        imprimirRotulo(janela,starty+5,startx+6,msg4);

        c = wgetch(janela);

        if(c) {
            destruir_menu(janela);
        }

}

void erro_id_existente() {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty;
    char c;
    char msg1[] = "ATENCAO!";
    char msg2[] = "ID informado ja existe, insira novo ID";
    char msg3[] = "Pressione qualquer tecla para retornar";

    init_pair(1,COLOR_RED,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();    

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    
        imprimirRotulo(janela,starty+2,startx+20,msg1);
        imprimirRotulo(janela, starty+3,startx+8,msg2);
        imprimirRotulo(janela,starty+6,startx+6,msg3);

        c = wgetch(janela);

        if(c) {
            destruir_menu(janela);
        }

}

void erro_id_invalido() {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty;
    char c;
    char msg1[] = "ATENCAO!";
    char msg2[] = "ID negativo invalido!";
    char msg3[] = "Pressione qualquer tecla para retornar";

    init_pair(1,COLOR_RED,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();    

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    
        imprimirRotulo(janela,starty+2,startx+20,msg1);
        imprimirRotulo(janela, starty+3,startx+13,msg2);
        imprimirRotulo(janela,starty+6,startx+6,msg3);

        c = wgetch(janela);

        if(c) {
            destruir_menu(janela);
        }

}

void erro_id_inexistente() {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty;
    char c;
    char msg1[] = "ATENCAO!";
    char msg2[] = "ID informado não existe";
    char msg3[] = "Pressione qualquer tecla para retornar";

    init_pair(1,COLOR_RED,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();    

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    
        imprimirRotulo(janela,starty+2,startx+20,msg1);
        imprimirRotulo(janela, starty+3,startx+15,msg2);
        imprimirRotulo(janela,starty+6,startx+6,msg3);

        c = wgetch(janela);

        if(c) {
            destruir_menu(janela);
        }

}

grafo * inserir_novo_pre_requisito(grafo* G) {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty, id_pre_requisito, id_tarefa;
    char msg1[] = "ID da tarefa:        _____";
    char msg2[] = "ID do pré-requisito: _____";

    init_pair(1,COLOR_GREEN,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER); 
        
    imprimirRotulo(janela,starty+2,startx+1,msg1);
    imprimirRotulo(janela,starty+3,startx+1,msg2);

    echo();
    wmove(janela,starty+2,startx+23);
    wscanw(janela,"%d",&id_tarefa);

    wmove(janela,starty+3,startx+23);
    wscanw(janela,"%d",&id_pre_requisito);

    if(!pesquisa_tarefa(G,id_pre_requisito) || !(pesquisa_tarefa(G,id_pre_requisito))) {
        destruir_menu(janela);
        erro_insere_pre_requisito();
        return G;
    } 

    G = insere_prerequisitos(G,id_tarefa,id_pre_requisito);   

    destruir_menu(janela);
    return G;

}

int tela_inserir_pre_requisito_edicao() {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty, id_pre_requisito;

    char msg1[] = "ID do pré-requisito: _____";
    char msg2[] = "[ENTER]";

    init_pair(1,COLOR_GREEN,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);      
        
    imprimirRotulo(janela,starty+2,startx+1,msg1);
    imprimirRotulo(janela,starty+5,startx+20,msg2);

    echo();
    wmove(janela,starty+2,startx+23);
    wscanw(janela,"%d",&id_pre_requisito);
    
    return id_pre_requisito;
}

grafo * tela_inserir_pre_requisito(grafo* G, int n_prerequisitos, int id_tarefa) {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty, id_pre_requisito, i = 0;
    tarefa * tarefa; 

    if(n_prerequisitos == 0) {
        return G;
    } else {

        char msg1[] = "ID do pré-requisito: _____";
        char msg2[] = "[ENTER]";

        init_pair(1,COLOR_GREEN,COLOR_BLACK);

        getmaxyx(stdscr,telaAltura,telaLargura);
        starty = (LINES - telaAltura)/2;   
        startx = (COLS - telaLargura)/2; 
        refresh();

        janela = newwin(ALTURA, LARGURA, startx, starty);

        wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);      
            
        imprimirRotulo(janela,starty+2,startx+1,msg1);
        imprimirRotulo(janela,starty+5,startx+20,msg2);

        echo();
        wmove(janela,starty+2,startx+23);
        wscanw(janela,"%d",&id_pre_requisito);

        if(pesquisa_tarefa(G,id_pre_requisito)) {
            G = insere_prerequisitos(G,id_tarefa,id_pre_requisito);
            n_prerequisitos--;
            i++;
            destruir_menu(janela);
            G = tela_inserir_pre_requisito(G, n_prerequisitos, id_tarefa);
        } else {
            destruir_menu(janela);
            erro_insere_pre_requisito();
            tarefa = procura_tarefa(G, id_tarefa);
            tarefa->n_prerequisitos = i;
            return G;
        }    

    } 

    return G;

}

grafo * inserir_tarefa(grafo* G) {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty;
    int id_tarefa, tarefa_executada, duracao_tarefa, ini_min_tarefa, n_prerequisitos;
    char nome_tarefa[100];
    char msg1[] = "ID tarefa: _______";
    char msg2[] = "Nome:      _______________________________";
    char msg3[] = "Tarefa executada?  _____";
    char msg4[] = "Duração tarefa:    _____";
    char msg5[] = "Início mínimo:     _____";
    char msg6[] = "No pré-requisitos: _____";


    init_pair(1,COLOR_GREEN,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    imprimirRotulo(janela,starty+1,startx+1,msg1);
    imprimirRotulo(janela,starty+2,startx+1,msg2);
    imprimirRotulo(janela,starty+3,startx+1,msg3);
    imprimirRotulo(janela,starty+4,startx+1,msg4);
    imprimirRotulo(janela,starty+5,startx+1,msg5);
    imprimirRotulo(janela,starty+6,startx+1,msg6);
    

    echo();
    wmove(janela,starty+1,startx+13);
    wscanw(janela,"%d",&id_tarefa);

    wmove(janela,starty+2,startx+13);
    wgetstr(janela,nome_tarefa);    

    wmove(janela,starty+3,startx+21);
    wscanw(janela,"%d",&tarefa_executada);

    wmove(janela,starty+4,startx+21);
    wscanw(janela,"%d",&duracao_tarefa);

    wmove(janela,starty+5,startx+21);
    wscanw(janela,"%d",&ini_min_tarefa);

    wmove(janela,starty+6,startx+21);
    wscanw(janela,"%d",&n_prerequisitos);

    if(id_tarefa < 0) {
        destruir_menu(janela);
        erro_id_invalido();
        return G;
    }

    if(pesquisa_tarefa(G, id_tarefa)) {
        destruir_menu(janela);
        erro_id_existente();
        return G;
    }

    G = insere_tarefa(G,id_tarefa,nome_tarefa,tarefa_executada,duracao_tarefa,ini_min_tarefa,n_prerequisitos);

    if (n_prerequisitos != 0) {
        destruir_menu(janela);
        G = tela_inserir_pre_requisito(G, n_prerequisitos, id_tarefa);
        return G;
    }

    destruir_menu(janela);
    
    return G;

}

void imprimir_em_arquivo(grafo * G) {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty;
    char nomeArquivo[100];
    char msg1[] = "Arquivo de saída: ______________________";
    char msg2[] = "[ENTER]";

    init_pair(1,COLOR_GREEN,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    imprimirRotulo(janela,starty+2,startx+1,msg1);
    imprimirRotulo(janela,starty+5,startx+20,msg2);
    

    echo();
    wmove(janela,starty+2,startx+19);
    wgetstr(janela, nomeArquivo);

    imprime_grafo(G,nomeArquivo);

    destruir_menu(janela);
}

grafo * edicao_tarefa(grafo * G, int id) {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty;
    int id_tarefa, tarefa_executada, duracao_tarefa, ini_min_tarefa, n_prerequisitos, i;
    char nome_tarefa[100];
    char msg1[] = "Novo ID: _______";
    char msg2[] = "Novo nome:         ___________________________";
    char msg3[] = "Tarefa executada?  _____";
    char msg4[] = "Duração tarefa:    _____";
    char msg5[] = "Início mínimo:     _____";
    char msg6[] = "No pré-requisitos: _____";


    init_pair(1,COLOR_GREEN,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    imprimirRotulo(janela,starty+1,startx+1,msg1);
    imprimirRotulo(janela,starty+2,startx+1,msg2);
    imprimirRotulo(janela,starty+3,startx+1,msg3);
    imprimirRotulo(janela,starty+4,startx+1,msg4);
    imprimirRotulo(janela,starty+5,startx+1,msg5);
    imprimirRotulo(janela,starty+6,startx+1,msg6);
    

    echo();
    wmove(janela,starty+1,startx+11);
    wscanw(janela,"%d",&id_tarefa);

    wmove(janela,starty+2,startx+21);
    wgetstr(janela,nome_tarefa);    

    wmove(janela,starty+3,startx+21);
    wscanw(janela,"%d",&tarefa_executada);

    wmove(janela,starty+4,startx+21);
    wscanw(janela,"%d",&duracao_tarefa);

    wmove(janela,starty+5,startx+21);
    wscanw(janela,"%d",&ini_min_tarefa);

    wmove(janela,starty+6,startx+21);
    wscanw(janela,"%d",&n_prerequisitos);

    if(pesquisa_tarefa(G, id_tarefa)) {
        destruir_menu(janela);
        erro_id_existente();
        return G;
    }

    int * ids_pre_requisitos = (int*) malloc(100*sizeof(int));

    for(i = 0; i < n_prerequisitos; i++) {
        destruir_menu(janela);
        ids_pre_requisitos[i] = tela_inserir_pre_requisito_edicao();
    }

    G = edita_tarefa(G,id,id_tarefa,nome_tarefa,tarefa_executada,duracao_tarefa,ini_min_tarefa,n_prerequisitos,ids_pre_requisitos,FLG_NOME|FLG_INIC|FLG_PRER|FLG_EXEC|FLG_DURA|FLG_IDTR);

    destruir_menu(janela);

    return G;


}

grafo * editar_tarefa(grafo* G) {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty;
    int id_tarefa;
    char msg1[] = "ID tarefa a ser editada: ______";
    char msg2[] = "[ENTER]";

    init_pair(1,COLOR_GREEN,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    imprimirRotulo(janela,starty+2,startx+1,msg1);
    imprimirRotulo(janela,starty+5,startx+20,msg2);
    

    echo();
    wmove(janela,starty+2,startx+27);
    wscanw(janela, "%d", &id_tarefa);

    if(!pesquisa_tarefa(G, id_tarefa)) {
        destruir_menu(janela);
        erro_id_inexistente();
        return G;
    }

    destruir_menu(janela);
    G = edicao_tarefa(G, id_tarefa);        

    return G;

}

grafo * remover_tarefa(grafo* G) {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty;
    int id_tarefa;
    char msg1[] = "ID tarefa a ser removida: _______";
    char msg2[] = "[ENTER]";

    init_pair(1,COLOR_GREEN,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    imprimirRotulo(janela,starty+2,startx+1,msg1);
    imprimirRotulo(janela,starty+5,startx+20,msg2);
    

    echo();
    wmove(janela,starty+2,startx+28);
    wscanw(janela,"%d",&id_tarefa);

    if(!pesquisa_tarefa(G, id_tarefa)) {
        destruir_menu(janela);
        erro_id_inexistente();
        return G;
    }


    G = remove_tarefa(G, id_tarefa);

    destruir_menu(janela);

    return G;

}

void ver_tarefas(grafo * G) {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty, i;
    char msg1[] = "ID             Tarefa", c;
    tarefa * tmp;

    init_pair(1,COLOR_BLUE,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA+50, LARGURA+25, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    imprimirRotulo(janela,starty+1,startx+1,msg1);

    i = 3;

    for(tmp = G->T; tmp != NULL; tmp = tmp->prox) {
        mvwprintw(janela,starty+i,startx+1,"%d",tmp->id_tarefa);
        mvwprintw(janela,starty+i,startx+16,"%s",tmp->nome_tarefa);
        i++;
    }
    
    c = wgetch(janela);

    if(c) 
        destruir_menu(janela);
        return;

}

void mostrar_pre_requisitos(grafo * G) {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty, i, j;
    char msg1[] = "ID             Tarefa                Pré-requisitos", c;
    tarefa * tmp;
    prerequisitos * tmp2;

    init_pair(1,COLOR_BLUE,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA+50, LARGURA+50, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    imprimirRotulo(janela,starty+1,startx+1,msg1);

    i = 3;
    j = 38;

    for(tmp = G->T; tmp != NULL; tmp = tmp->prox) {
        mvwprintw(janela,starty+i,startx+1,"%d",tmp->id_tarefa);
        mvwprintw(janela,starty+i,startx+16,"%s",tmp->nome_tarefa);
      
        if (tmp->prerequisitos_tarefa != NULL) {
            tmp2 = tmp->prerequisitos_tarefa;

            while(tmp2 != NULL) {
                mvwprintw(janela, starty+i, startx+j, "%d", tmp2->id_prerequisito);
                tmp2 = tmp2->prox;
                j = j + 5;
            }
        }

        i++;
    }
    
    c = wgetch(janela);

    if(c) 
        destruir_menu(janela);
        return;

}


void ver_tarefas_concluidas(grafo * G) {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty, i;
    char msg1[] = "ID             Tarefa", c;
    tarefa * tmp;
    //int* tarefas_completadas;

    init_pair(1,COLOR_BLUE,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA+35, LARGURA+25, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    imprimirRotulo(janela,starty+1,startx+1,msg1);

    i = 3;

    for(tmp = G->T; tmp != NULL; tmp = tmp->prox) {
        mvwprintw(janela,starty+i,startx+1,"%d",tmp->id_tarefa);
        mvwprintw(janela,starty+i,startx+16,"%s",tmp->nome_tarefa);
        i++;
    }
    
    c = wgetch(janela);

    if(c) 
        destruir_menu(janela);
        return;

}


grafo * remover_pre_requisitos(grafo* G) {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty;
    int id_tarefa;
    char msg1[] = "Remover pre-requisitos da tarefa de ID: _______";
    char msg2[] = "[ENTER]";

    init_pair(1,COLOR_GREEN,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    imprimirRotulo(janela,starty+2,startx+1,msg1);
    imprimirRotulo(janela,starty+5,startx+20,msg2);
    

    echo();
    wmove(janela,starty+2,startx+42);
    wscanw(janela,"%d",&id_tarefa);

    if(!pesquisa_tarefa(G, id_tarefa)) {
        destruir_menu(janela);
        erro_id_inexistente();
        return G;
    }

    G = remove_prerequisitos(G, id_tarefa);

    destruir_menu(janela);

    return G;

}

void mostrar_tarefas_filtradas(grafo * G, int * tarefas) {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty, i, linha;
    int n_tarefas = sizeof(tarefas) / sizeof(int);
    char msg1[] = "ID             Tarefa", c;
    tarefa * tmp;

    init_pair(1,COLOR_BLUE,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA+35, LARGURA+25, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    imprimirRotulo(janela,starty+1,startx+1,msg1);

    linha = 3;

    for(i = 0; i < n_tarefas; i++) { 
        tmp = procura_tarefa(G, tarefas[i]);
        mvwprintw(janela,starty+linha,startx+1,"%d",tmp->id_tarefa);
        mvwprintw(janela,starty+linha,startx+16,"%s",tmp->nome_tarefa);
        linha++;
    }
    
    c = wgetch(janela);

    if(c) 
        destruir_menu(janela);
        return;
}

void filtrar_tarefas_completadas(grafo * G) {
    
    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty;
    int periodo;
    char msg1[] = "Período: _______";
    char msg2[] = "[ENTER]";
    int * tarefas;

    init_pair(1,COLOR_GREEN,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    imprimirRotulo(janela,starty+2,startx+1,msg1);
    imprimirRotulo(janela,starty+5,startx+20,msg2);
    
    echo();
    wmove(janela,starty+2,startx+11);
    wscanw(janela,"%d",&periodo);

    destruir_menu(janela);

    tarefas = tarefas_concluidas(G, periodo);
    mostrar_tarefas_filtradas(G, tarefas);

}

void mostrar_caminhos(grafo * G) {
    
    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty, i = 0;
    int * caminho;
    char c;
    char msg1[] = "Caminho com menor tempo:";
    char msg3[] = "[ENTER]";

    init_pair(1,COLOR_BLUE,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    caminho = caminhos(G);

    imprimirRotulo(janela,starty+2,startx+3,msg1);
    int coluna = 6;

    while(1) {
        if(caminho[i] == -1)
            break;
        else
            mvwprintw(janela,starty+3,startx+coluna,"%d -> ",caminho[i]);
        i++;
        coluna += 6;
    }
    

    imprimirRotulo(janela,starty+6,startx+19,msg3);

    c = wgetch(janela);

    if(c) 
        destruir_menu(janela);
        return;

}


void mostrar_tempo_min_total(grafo * G) {
    
    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty;
    int periodo;
    char c;
    char msg1[] = "O tempo minimo total para realizar";
    char msg2[] = "todas as tarefas é:";
    char msg3[] = "[ENTER]";

    init_pair(1,COLOR_BLUE,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    periodo = tempo_minimo_total(G);

    imprimirRotulo(janela,starty+2,startx+5,msg1);
    imprimirRotulo(janela,starty+3,startx+7,msg2);

    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    mvwprintw(janela,starty+3,startx+29,"%d",periodo);

    imprimirRotulo(janela,starty+6,startx+19,msg3);

    c = wgetch(janela);

    if(c) 
        destruir_menu(janela);
        return;

}

void visualizador_tarefas(grafo * G) {

    WINDOW * menu_win;
    int c;
    int highlight = 1;
    int opcao = 1;
    int LARGURA_V = LARGURA + 25;

    menu_win = newwin(ALTURA, LARGURA_V, startx, starty);
    keypad(menu_win,TRUE);
    refresh();

    do {
  
    print_visualizador(menu_win,highlight);
    c = wgetch(menu_win);

        switch(c) {
            case KEY_UP:
                if(highlight == 1)
                    highlight = n_visualizador;
                else
                    --highlight;
            break;

            case KEY_DOWN:
                if(highlight == n_visualizador)
                    highlight = 1;
                else
                    ++highlight;
            break;

            case 10:
                opcao = highlight;

                if(opcao == 1) {
                    destruir_menu(menu_win);
                    ver_tarefas(G);
                    menu_win = newwin(ALTURA, LARGURA_V, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh(); 

                } else if (opcao == 2) {
                    destruir_menu(menu_win);
                    mostrar_pre_requisitos(G);
                    menu_win = newwin(ALTURA, LARGURA_V, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh(); 

                } else if (opcao == 3) {
                    destruir_menu(menu_win);
                    mostrar_caminhos(G);
                    menu_win = newwin(ALTURA, LARGURA_V, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh();

                } else if(opcao == 4) {
                    destruir_menu(menu_win);
                    
                    menu_win = newwin(ALTURA, LARGURA_V, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh();

                } else if(opcao == 5) {
                    destruir_menu(menu_win);
                    filtrar_tarefas_completadas(G);
                    menu_win = newwin(ALTURA, LARGURA_V, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh();

                } else if(opcao == 6) {
                    destruir_menu(menu_win);
                    mostrar_tempo_min_total(G);
                    menu_win = newwin(ALTURA, LARGURA_V, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh();    

                } else if(opcao == 7) {
                    destruir_menu(menu_win);
                    return;
                }

            break;

            default:
                refresh();
            break;
        }
        
    } while(1);   

}

grafo * operacoes_grafo(grafo * G) {

    WINDOW * menu_win;
    int c;
    int highlight = 1;
    int opcao = 1;

    menu_win = newwin(ALTURA+2, LARGURA, startx, starty);
    keypad(menu_win,TRUE);
    refresh();

    do {
  
    print_operacoes(menu_win,highlight);
    c = wgetch(menu_win);

        switch(c) {
            case KEY_UP:
                if(highlight == 1)
                    highlight = n_operacoes;
                else
                    --highlight;
            break;

            case KEY_DOWN:
                if(highlight == n_operacoes)
                    highlight = 1;
                else
                    ++highlight;
            break;

            case 10:
                opcao = highlight;

                if(opcao == 1) {
                    destruir_menu(menu_win);
                    G = inserir_tarefa(G);
                    menu_win = newwin(ALTURA+2, LARGURA, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh(); 

                } else if (opcao == 2) {
                    destruir_menu(menu_win);
                    G = inserir_novo_pre_requisito(G);
                    menu_win = newwin(ALTURA+2, LARGURA, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh(); 

                } else if (opcao == 3) {
                    destruir_menu(menu_win);
                    G = remover_tarefa(G);
                    menu_win = newwin(ALTURA+2, LARGURA, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh();

                } else if(opcao == 4) {
                    destruir_menu(menu_win);
                    G = remover_pre_requisitos(G);
                    menu_win = newwin(ALTURA+2, LARGURA, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh();

                } else if(opcao == 5) {
                    destruir_menu(menu_win);
                    G = editar_tarefa(G);
                    menu_win = newwin(ALTURA+2, LARGURA, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh();

                } else if(opcao == 6) {
                    destruir_menu(menu_win);
                    visualizador_tarefas(G);
                    menu_win = newwin(ALTURA+2, LARGURA, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh();

                } else if(opcao == 7) {
                    destruir_menu(menu_win);
                    imprimir_em_arquivo(G);
                    menu_win = newwin(ALTURA+2, LARGURA, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh();

                } else if(opcao == 8) {
                    destruir_menu(menu_win);
                    return G;
                }

            break;

            default:
                refresh();
            break;
        }
        
    } while(1);   

}

grafo * abrir_arquivo(char * nomeArquivo) {

	WINDOW * janela;
	int telaAltura, telaLargura;
    int startx, starty;
    char c;
    grafo * G = cria_grafo();

    char msg1[] = "ATENCAO! Erro ao abir aquivo.";
    char msg2[] = "Escolha uma das opções abaixo:";
    char msg3[] = "1 - voltar ao menu principal";
    char msg4[] = "2 - sair ";
    char msg5[] = "Tarefas importadas com sucesso!";
    char msg6[] = "[ENTER]";

 	FILE * fp = fopen(nomeArquivo, "r");

	init_pair(1,COLOR_RED,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();    

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

	if(!fp) {
		imprimirRotulo(janela,starty+2,startx+10,msg1);
		imprimirRotulo(janela,starty+3,startx+10,msg2);
		imprimirRotulo(janela,starty+5,startx+10,msg3);
		imprimirRotulo(janela,starty+6,startx+10,msg4);

		c = wgetch(janela);

		if(c == '1') {
			destruir_menu(janela);
            return G;
		} else {
			destruir_menu(janela);
			endwin();
			exit(1);
		}

		
	} else {

        G = le_grafo(nomeArquivo);

		imprimirRotulo(janela,starty+2,startx+10,msg5);
        imprimirRotulo(janela,starty+4,startx+20,msg6);

        c = wgetch(janela);

		destruir_menu(janela);

        G = operacoes_grafo(G);
	}

    return G;

}

int main () {
	
	WINDOW * menu_win;
	int c;
	int highlight = 1;
	int opcao = 1;
	char nomeArquivo[100];
    grafo * G;

	initscr();

	strcpy(vOpcoes[0],"(1) Importar arquivo com tarefas");
	strcpy(vOpcoes[1],"(2) Criar novas tarefas");
	strcpy(vOpcoes[2],"(3) Sair");
	
	strcpy(vOperacoes[0],"(1) Inserir tarefa");
	strcpy(vOperacoes[1],"(2) Inserir novo pré-requisito");
	strcpy(vOperacoes[2],"(3) Remover tarefa");
	strcpy(vOperacoes[3],"(4) Remover pré-requisitos");
	strcpy(vOperacoes[4],"(5) Editar tarefa");
	strcpy(vOperacoes[5],"(6) Visualizador de tarefas");
	strcpy(vOperacoes[6],"(7) Gerar arquivo com tarefas");
	strcpy(vOperacoes[7],"(8) Voltar");
	
	strcpy(vVisualizador[0],"(1) Mostrar tarefas");
	strcpy(vVisualizador[1],"(2) Mostrar pre-requisitos de cada tarefa");
	strcpy(vVisualizador[2],"(3) Caminhos que indicam menor tempo de execucao");
	strcpy(vVisualizador[3],"(4) Quais tarefas foram completadas ou não");
	strcpy(vVisualizador[4],"(5) Filtrar tarefas completadas ate determinado periodo");
    strcpy(vVisualizador[5],"(6) Mostrar tempo minimo total");
	strcpy(vVisualizador[6],"(7) Voltar");
 
 	if(has_colors() == FALSE)
    {   
       endwin();
       printf("Seu terminal nao suporta cores\n");
       exit(1);
    }

    start_color(); 

    clear();
    noecho();
    cbreak();

    menu_win = newwin(ALTURA, LARGURA, startx, starty);
    keypad(menu_win,TRUE);
    refresh();

    do {
  
    print_menu(menu_win,highlight);
    c = wgetch(menu_win);

	    switch(c) {
	        case KEY_UP:
		        if(highlight == 1)
		            highlight = n_opcoes;
		        else
		    	    --highlight;
	        break;

	        case KEY_DOWN:
	            if(highlight == n_opcoes)
	            	highlight = 1;
	            else
	            	++highlight;
	        break;

	        case 10:
	        	opcao = highlight;

	        	if (opcao == 1) {
	        		destruir_menu(menu_win);
	        		strcpy(nomeArquivo, importar_de_arquivo(nomeArquivo));	
	        		G = abrir_arquivo(nomeArquivo);
	        		menu_win = newwin(ALTURA, LARGURA, startx, starty);
	        		keypad(menu_win,TRUE);
    				refresh();

	        	} else if (opcao == 2) {
                    destruir_menu(menu_win);
                    G = cria_grafo();
                    G = operacoes_grafo(G);
                    menu_win = newwin(ALTURA, LARGURA, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh();

                } else if(opcao == 3) {

	        		refresh();
	        		endwin();
	        		return 0;	
	        	}

	        break;
	     
	        default:
	            refresh();
	        break;
        }

    } while (1);

}
