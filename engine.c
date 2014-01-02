/*
------------------------------------------------------------------------------------------------
|                                                                                              |
|               _______                                   _      _                             |             
|              (_______)         _                       (_)    | |                            |             
|               _______   ___  _| |_  _____   ____  ___   _   __| | _____   ___                |
|              |  ___  | /___)(_   _)| ___ | / ___)/ _ \ | | / _  || ___ | /___)               |
|              | |   | ||___ |  | |_ | ____|| |   | |_| || |( (_| || ____||___ |               |
|              |_|   |_|(___/    \__)|_____)|_|    \___/ |_| \____||_____)(___/                |
|                                         Projeto 2013                                         |
|                                                                                              |
|                     Trabalho de Laboratório de Computação 1 - IM-UFRRJ 2013                  |
|                          Participantes                                                       |
|				- Fellipe Bravo Ribeiro Pimentel                               |
|				- Paulo Roberto Xavier                                         |
|				- Bianca Albuquerque                                           |
|                                                                                              |
------------------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "engine.h"
#include "menu.c"

int main(int argv, char **argc){
	menu();
	/* Inicialização da Janela */
	SDL_Init(SDL_INIT_VIDEO);
        if(SDL_Init(SDL_INIT_VIDEO) < 0){ exit(-1); }

	/* Inicialização da Fonte */
	TTF_Init();
	if(TTF_Init() == -1){ exit(-1); }

	/* Configurações da Janela */
	SDL_WM_SetCaption(NOME, NULL); /* Nome, definido em engine.h */
	janela = SDL_SetVideoMode(ALTURA, LARGURA, 32, SDL_HWSURFACE);
 
        /* Checa se a janela existe, caso contrário o programa é fechado */
	if(janela == NULL){ SDL_Quit(); exit(-1); }

	/* Repetição de tecla, para movimentação */
	SDL_EnableKeyRepeat(40, 40);

	/* Espaço */
	temp = SDL_LoadBMP("resources/galaxia.bmp");
	espaco = SDL_DisplayFormat(temp);

	/* Nave */
	temp = SDL_LoadBMP("resources/nave.bmp");
	nave = SDL_DisplayFormat(temp);
	/* Cor nula na sprite */
	SDL_SetColorKey(nave, SDL_SRCCOLORKEY|SDL_RLEACCEL,(Uint32)SDL_MapRGB(nave->format, 255,0,255));

	naveTotal.x = 0; /* Inicio da sprite em X */
	naveTotal.y = 0; /* Inicio da sprite em Y */
	naveTotal.h = 150; /* Tamanho total da sprite */
	naveTotal.w = 150; /* Tamanho total da sprite */

	espacoTotal.x = 0; /* Local de Destino X da Nave */
	espacoTotal.y = 0; /* Local de Destino Y da Nave */
	espacoTotal.h = ALTURA; /* Tamanho total possível de deslocamento */
	espacoTotal.w = LARGURA; /* Tamanho total possível de deslocamento */

	
	/*
	Checagem se programa está aberto,
	enquanto estiver aberto verifica se o jogador apertou ESC (Escape) para sair do jogo e/ou teclas de movimentação
	 */
 	while(!aberto){
		if(vida >= 1){
			aleatorio = 1 + (rand()%10);
			SDL_Event evento;
			while(SDL_PollEvent(&evento)){ DefGeral(evento); }

				/* Desenha o Espaço por completo */
				SDL_BlitSurface(espaco, NULL, janela, NULL);
				/* Desenha a Nave */
				SDL_BlitSurface(naveAngulo, &naveTotal, janela, &espacoTotal);

				/* Escreve a Pontuação na tela */
				sprintf(txtpontos, "Pontuacao: ");
				texto(txtpontos, janela, 630, 5);

				/* Escreve o Combustivel na tela */				
				sprintf(txtcombustivel, "Combustivel: %d", combustivel);
				texto(txtcombustivel, janela, 630, 25);

				/* Escreve a Vida na tela */
				sprintf(txtvidas, "Vidas: %d", vida);
				texto(txtvidas, janela, 630, 45);
        			/*
				 Update da tela enquanto o programa está aberto
				 Também para atualizar movimentação da nave.
				*/

		} else {

			system("clear");
			printf("Infelizmente as suas vidas acabaram! :/\n");
			SDL_FreeSurface(nave); /* Evitar vazamento de memória */
    			SDL_FreeSurface(espaco); /* Evitar vazamento de memória */
			TTF_Quit();
        		SDL_Quit();
			return 0;
		}

        	SDL_UpdateRect(janela, 0, 0, 0, 0);
 	}
	SDL_FreeSurface(nave); /* Evitar vazamento de memória */
    	SDL_FreeSurface(espaco); /* Evitar vazamento de memória */
	TTF_Quit();
        SDL_Quit();
	system("clear");
	menu();
	return 0;	
}
