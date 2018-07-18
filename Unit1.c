/***************************************************************************
 *   Copyright (C) 2007 by Andre Duarte 30702453                           *
 *   andreduartesp@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>




typedef struct{
		short valor, nipe,pilha,posic;
}carta;


typedef struct{
	short tam, topo;
}pilha;


void empilha(carta *carta, pilha *pilha, short indcarta, short indpilha){
        if(indcarta != EOF){
                pilha[indpilha].tam++;
                carta->posic = pilha[indpilha].tam;
                pilha[indpilha].topo = indcarta;
                carta->pilha = indpilha;
        }
}


short desempilha(pilha *pilha, short indpilha, carta *baralho){
        short a,b;

        if(pilha[indpilha].tam == 0) return EOF;
        if(indpilha >=13)return EOF;
        b = pilha[indpilha].topo;
        baralho[b].posic++;
        pilha[indpilha].tam--;
        for(a = 0; a <= 51; a++){
                if(pilha[indpilha].tam == baralho[a].posic && indpilha == baralho[a].pilha){
                        pilha[indpilha].topo = a;
                        break;
                }
        }
return b;
}


short pega(short posicx, short posicy, pilha *pilha, carta *baralho){
        short indice;

        if(posicy == 32){
                indice = (posicx  / 6);
                indice = desempilha(pilha, indice, baralho);
                }
        else{
                indice = (posicx  / 6) + 8;
                indice = desempilha(pilha, indice, baralho);
                }
        return indice;
}


void solta(short posicx, short posicy, pilha *pilha, carta *baralho, short indicbar){
        short indicpilha;

        if(posicy == 32){
                indicpilha = (posicx  / 6);
                if(baralho[pilha[indicpilha].topo].valor == baralho[indicbar].valor + 1 &&
                   baralho[pilha[indicpilha].topo].nipe%2 != baralho[indicbar].nipe%2){
                        empilha(&baralho[indicbar], pilha, indicbar, indicpilha);
                }
                else if(pilha[indicpilha].tam == 0) empilha(&baralho[indicbar], pilha, indicbar, indicpilha);
                else{
                        empilha(&baralho[indicbar], pilha, indicbar, baralho[indicbar].pilha);
                        clrscr();
                        gotoxy(10,10);
                        textcolor(WHITE);
                        cprintf("Jogada invalida, pressione qualquer tecla");
                        getch();
                }
        }
        else{
                indicpilha = (posicx  / 6) + 8;
                if(indicpilha <= 12){
                        if(pilha[indicpilha].tam == 0)empilha(&baralho[indicbar], pilha, indicbar, indicpilha);
                        else empilha(&baralho[indicbar], pilha, indicbar, baralho[indicbar].pilha);
                }
                else {
                        if(baralho[indicbar].valor == 1 && pilha[indicpilha].tam == 0)empilha(&baralho[indicbar], pilha, indicbar, indicpilha);
                        else{
                                if(baralho[pilha[indicpilha].topo].valor == baralho[indicbar].valor - 1 &&
                                   baralho[pilha[indicpilha].topo].nipe == baralho[indicbar].nipe){
                                        empilha(&baralho[indicbar], pilha, indicbar, indicpilha);
                                }
                                else{
                                        empilha(&baralho[indicbar], pilha, indicbar, baralho[indicbar].pilha);
                                        clrscr();
                                        gotoxy(10,10);
                                        textcolor(WHITE);
                                        cprintf("Jogada invalida, pressione qualquer tecla");
                                        getch();
                                }
                        }
                }
        }
}


void imprime(carta *baralho, short b, short d, short controle){
        short a,c;

        clrscr();
        _setcursortype(0);
        textcolor(LIGHTGRAY);
        gotoxy(28,5);
        cprintf("||");
        for(a = 52, c = 6; a <= 59; a++, c += 6){
                gotoxy(c, 5);
                cprintf("-**-");
        }
        if(controle == 1){
                gotoxy(2,39);
                textcolor(WHITE);
                cprintf("Escolha uma posicao e pessione \"Espaco\" para selecionar uma carta");
        }
        if(controle == 2){
                gotoxy(2,39);
                textcolor(WHITE);
                cprintf("Escolha uma posicao e pessione \"Espaco\" para soltar a carta      ");
        }
        gotoxy(2,40);
        cprintf("'esc'- Sair     'N' - Novo Jogo");
        for(a = 0; a <= 51; a++){
                if(baralho[a].pilha <=8){
		        gotoxy(baralho[a].pilha * 6, baralho[a].posic * 1 + 10);
                        if(baralho[a].nipe == 1){
                                textcolor(LIGHTRED);
                                cprintf ("%2d-%c", baralho[a].valor,3);
                        }
                        if(baralho[a].nipe == 2){
                                textcolor(DARKGRAY);
                                cprintf ("%2d-%c", baralho[a].valor,5);
                        }
                        if(baralho[a].nipe == 3){
                                textcolor(LIGHTRED);
                                cprintf ("%2d-%c", baralho[a].valor,4);
                        }
                        if(baralho[a].nipe == 4){
                                textcolor(DARKGRAY);
                                cprintf ("%2d-%c", baralho[a].valor,6);
                        }
                }
                if(baralho[a].pilha <= 16 && baralho[a].pilha >= 9){
                        gotoxy((baralho[a].pilha - 8) * 6, 5);
                        if(baralho[a].nipe == 1){
                                textcolor(LIGHTRED);
                                cprintf ("%2d-%c", baralho[a].valor,3);
                        }
                        if(baralho[a].nipe == 2){
                                textcolor(DARKGRAY);
                                cprintf ("%2d-%c", baralho[a].valor,5);
                        }
                        if(baralho[a].nipe == 3){
                                textcolor(LIGHTRED);
                                cprintf ("%2d-%c", baralho[a].valor,4);
                        }
                        if(baralho[a].nipe == 4){
                                textcolor(DARKGRAY);
                                cprintf ("%2d-%c", baralho[a].valor,6);
                        }
                }
        }
        textcolor(14);
        gotoxy(b + 2,d);
        cprintf("^");
        gotoxy(b + 2, d + 1);
        printf("|");
}


void inicializa(carta *baralho){
	short a,b,c = 0;

	for(a = 1; a <= 13; a++){
		for(b = 1; b<= 4; b++, c++){
			baralho[c].valor = a;
			baralho[c].nipe = b;
		}
	}
	for(a = 1, c = 0; a <= 8; a++){
		for(b = 1;; b++, c++){
			baralho[c].pilha = a;
			baralho[c].posic = b;
			if(a <= 4 && b == 8) break;
			if(a > 4 && b == 7) break;
		}
	}
	for(a = 52; a <= 59; a++) baralho[a].valor = 0;
}


void embaralha(carta *baralho){
	int a,b,c,d;
	carta *tmp;

	tmp = malloc(52 * sizeof(carta));
	for(a = 0; a <= 51; a++){
		tmp[a] = baralho[a];
	}
	for(d = 1; d <= 52; d++){
		srand (time(NULL));
		a = rand()%51;
		for(b = a - 1, c = 0; a <= 51 || b>=0; a++, b--){
			if(a <= 51){
				baralho[a].pilha = tmp[c].pilha;
				baralho[a].posic = tmp[c].posic;
				c++;
			}
                        if(a < b){
                                baralho[a].pilha = tmp[c].pilha;
				baralho[a].posic = tmp[c].posic;
				c++;
                        }
			if(b >= 0){
				baralho[b].pilha = tmp[c].pilha;
				baralho[b].posic = tmp[c].posic;
				c++;
			}
		}
	}
        free(tmp);
}


void inicpilha(carta *baralho, pilha *pilha){
        short a;

        for(a = 0; a<= 51; a++){
                if(baralho[a].pilha == 1 && baralho[a].posic == 7) pilha[1].topo = a;
                if(baralho[a].pilha == 2 && baralho[a].posic == 7) pilha[2].topo = a;
                if(baralho[a].pilha == 3 && baralho[a].posic == 7) pilha[3].topo = a;
                if(baralho[a].pilha == 4 && baralho[a].posic == 7) pilha[4].topo = a;
                if(baralho[a].pilha == 5 && baralho[a].posic == 6) pilha[5].topo = a;
                if(baralho[a].pilha == 6 && baralho[a].posic == 6) pilha[6].topo = a;
                if(baralho[a].pilha == 7 && baralho[a].posic == 6) pilha[7].topo = a;
                if(baralho[a].pilha == 8 && baralho[a].posic == 6) pilha[8].topo = a;
        }
        for(a = 1; a<=8; a++){
                if(a <= 4) pilha[a].tam = 7;
                else pilha[a].tam = 6;
        }
        for(a = 9; a <= 16; a++){
                pilha[a].tam = 0;
                pilha[a].topo = 0;
        }
}


void fim(carta *baralho, pilha * pilha){
        short opcao,a,b,c = 0;

        if(baralho[pilha[13].topo].valor == 13 &&
           baralho[pilha[14].topo].valor == 13 &&
           baralho[pilha[15].topo].valor == 13 &&
           baralho[pilha[16].topo].valor == 13){
                clrscr();
                gotoxy(10,10);
                textcolor(WHITE);
                cprintf("Voce Venceu, Quer jogar novamente?(S/N)");
                        opcao = toupper(getch());
                        switch(opcao){
                                case 'S':
                                        inicializa(baralho);
                                        embaralha(baralho);
                                        inicpilha(baralho, pilha);
                                        break;
                                case 'N':
                                        exit(0);
                        }
        }
        for(a = 1; a <= 12; a++){
                for(b = 1; b <= 8; b++){
                        if(baralho[pilha[a].topo].valor == baralho[pilha[b].topo].valor + 1 &&
                           baralho[pilha[a].topo].nipe%2 != baralho[pilha[b].topo].nipe%2){
                                c++;
                        }
                }
        }
        for(a = 1; a <= 12; a++){
                for(b = 12; b <= 16; b++){
                        if(baralho[pilha[a].topo].valor == 1 && pilha[a].tam == 0)c++;
                        else{
                                if(baralho[pilha[a].topo].valor == baralho[pilha[b].topo].valor - 1 &&
                                   baralho[pilha[a].topo].nipe == baralho[pilha[b].topo].nipe){
                                        c++;
                                }
                        }
                }
        }
        for(a = 1; a <= 12; a++) if(pilha[a].tam == 0) c++;;
        if(c == 0){
                clrscr();
                gotoxy(10,10);
                textcolor(WHITE);
                cprintf("Voce perdeu, Que jogar novamente?(S/N)");
                opcao = toupper(getch());
                switch(opcao){
                        case 'S':
                                inicializa(baralho);
                                embaralha(baralho);
                                inicpilha(baralho, pilha);
                                break;
                        case 'N':
                                exit(0);
                }
        }
}


int main(int argc, char* argv[]){
        short a = 6, opcao, b = 32, indice, controle = 1, indice2;
	carta baralho[60];
	pilha pilha[17];

	inicializa(baralho);
	embaralha(baralho);
        inicpilha(baralho, pilha);
        while (opcao != 27){
                if (controle == 1) fim(baralho, pilha);
                imprime(baralho,a,b,controle);
                opcao = toupper(getch());
                switch(opcao){
                        case 75:
                                if(a > 6) a -= 6;
                                break;
                        case 77:
                                if(a < 48) a += 6;
                                break;
                        case 72:
                                b = 7;
                                break;
                        case 80:
                                b = 32;
                                break;
                        case 32:
                                if(controle == 1){
                                        indice2 = pega(a, b, pilha, baralho);
                                        if(indice2 != EOF)controle = 2;
                                }
                                else{
                                        solta(a, b, pilha, baralho, indice2);
                                        controle = 1;
                                }
                                break;
                        case 27:
                                exit(0);
                                break;
                        case 'N':
                                controle = 1;
                                inicializa(baralho);
	                        embaralha(baralho);
                                inicpilha(baralho, pilha);
                                break;
                }
        }
	return 0;
}


