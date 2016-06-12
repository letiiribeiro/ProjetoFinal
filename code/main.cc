#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

#define LARGURA 50
#define ALTURA 10

int startx = 0;
int starty = 0;

char *vOpcoes[] = {
    "(1) Importar arquivo com tarefas",
    "(2) Criar novas tarefas",
    "(3) Sair",
};

char *vOperacoes[] = {
    "(1) Inserir tarefa",
    "(2) Inserir novo pré-requisito",
    "(3) Remover tarefa",
    "(4) Remover pré-requisito",
    "(5) Editar tarefa",
    "(6) Verificar consistencia de tarefa",
    "(7) Gerar arquivo com tarefas",
    "(8) Sair",
};

int n_opcoes = sizeof(vOpcoes) / sizeof(char *);
int n_operacoes = sizeof(vOperacoes) / sizeof(char*);

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
    grafo * G;

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
        imprimirRotulo(janela,starty+6,startx+6,msg4);

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
    grafo * G;

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

void erro_id_inexistente() {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty;
    char c;
    char msg1[] = "ATENCAO!";
    char msg2[] = "ID informado não existe";
    char msg3[] = "Pressione qualquer tecla para retornar";
    grafo * G;

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
    int startx, starty, i = 0, id_pre_requisito, id_tarefa;
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

grafo * tela_inserir_pre_requisito(grafo* G, int n_prerequisitos, int id_tarefa) {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty, i, id_pre_requisito;
    tarefa * tarefa;

    char msg1[] = "ID do pré-requisito: _____";
    char msg2[] = "[ENTER]";

    init_pair(1,COLOR_GREEN,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA, LARGURA, startx, starty);

    wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    for(i = 0; i < n_prerequisitos; i++) {
        
        imprimirRotulo(janela,starty+2,startx+1,msg1);
        imprimirRotulo(janela,starty+5,startx+20,msg2);

        echo();
        wmove(janela,starty+2,startx+23);
        wscanw(janela,"%d",&id_pre_requisito);

        if(pesquisa_tarefa(G,id_pre_requisito)) {
            G = insere_prerequisitos(G,id_tarefa,id_pre_requisito);
        } else {
            destruir_menu(janela);
            erro_insere_pre_requisito();
            tarefa = procura_tarefa(G, id_tarefa);
            tarefa->n_prerequisitos = i;
            return G;
        }

        i++;

    } 

    destruir_menu(janela);
    return G;

}

grafo * inserir_tarefa(grafo* G) {

    WINDOW * janela;
    int telaAltura, telaLargura;
    int startx, starty;
    int id_tarefa, tarefa_executada, duracao_tarefa, ini_min_tarefa, n_prerequisitos, i;
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

    //G = editar_tarefa(G,id,id_tarefa,nome_tarefa,tarefa_executada,duracao_tarefa,ini_min_tarefa,n_prerequisitos,id_prerequisitos,FLG_NOME|FLG_INIC|FLG_PRER);

    if (n_prerequisitos != 0) {
        destruir_menu(janela);
        G = tela_inserir_pre_requisito(G, n_prerequisitos, id_tarefa);
        return G;
    }

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

grafo * operacoes_grafo(grafo * G) {

    WINDOW * menu_win;
    int c;
    int highlight = 1;
    int opcao = 1;
    char nomeArquivo[100];

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
                    menu_win = newwin(ALTURA, LARGURA, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh(); 

                } else if (opcao == 2) {
                    destruir_menu(menu_win);
                    G = inserir_novo_pre_requisito(G);
                    menu_win = newwin(ALTURA, LARGURA, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh(); 

                } else if (opcao == 3) {
                    destruir_menu(menu_win);
                    G = remover_tarefa(G);
                    menu_win = newwin(ALTURA, LARGURA, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh();

                } else if(opcao == 4) {
                    destruir_menu(menu_win);
                    G = remover_pre_requisitos(G);
                    menu_win = newwin(ALTURA, LARGURA, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh();

                } else if(opcao == 5) {
                    destruir_menu(menu_win);
                    G = editar_tarefa(G);
                    menu_win = newwin(ALTURA, LARGURA, startx, starty);
                    keypad(menu_win,TRUE);
                    refresh();

                } else if(opcao == 7) {
                    destruir_menu(menu_win);
                    imprimir_em_arquivo(G);
                    menu_win = newwin(ALTURA, LARGURA, startx, starty);
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
    grafo * G;
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
        G = le_grafo(fp);

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