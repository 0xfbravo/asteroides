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
#include "engine.h"
#include "menu.c"

int main(){

	printf("\t-----------------------------------------------------------------------\n");
	printf("\t|   _______                                   _      _                |\n");
	printf("\t|  (_______)         _                       (_)    | |               |\n");
	printf("\t|   _______   ___  _| |_  _____   ____  ___   _   __| | _____   ___   |\n");
	printf("\t|  |  ___  | /___)(_   _)| ___ | / ___)/ _ \\ | | / _  || ___ | /___)  |\n");
	printf("\t|  | |   | ||___ |  | |_ | ____|| |   | |_| || |( (_| || ____||___ |  |\n");
	printf("\t|  |_|   |_|(___/    \\__)|_____)|_|    \\___/ |_| \\____||_____)(___/   |\n");
	printf("\t|                           Projeto 2013                              |\n");
	printf("\t|       Trabalho de Laboratorio de Computação 1 - IM-UFRRJ 2013       |\n");
	printf("\t|---------------------------------------------------------------------|\n");
	printf("\t|                   Fellipe Bravo Ribeiro Pimentel                    |\n");
	printf("\t|                      Paulo Roberto Xavier                           |\n");
	printf("\t|                       Bianca Albuquerque                            |\n");
	printf("\t-----------------------------------------------------------------------\n\n");

	menu();
	return 0;	
}

int Jogar(int argv, char **argc){

	/* Inicialização da Janela */
	SDL_Init(SDL_INIT_VIDEO);
        if(SDL_Init(SDL_INIT_VIDEO) < 0){
                exit(-1);
        }

	/* Configurações da Janela */
	SDL_WM_SetCaption(NOME, NULL); /* Nome, definido em engine.h */
	janela = SDL_SetVideoMode(ALTURA, LARGURA, 32, SDL_HWSURFACE);
 
        /* Checa se a janela existe, caso contrário o programa é fechado */
	if(janela == NULL){
		SDL_Quit();
		exit(-1);
        }
	/* */
	temp = SDL_LoadBMP("resources/galaxia.bmp");
	espaco = SDL_DisplayFormat(temp);
	/* nave */
	naveDim.w = 80; /* Largura da "Nave" */
	naveDim.h = 80; /* Altura da "Nave" */
	naveDim.x = (ALTURA/2)-naveDim.h; /* Posição X */
	naveDim.y = (LARGURA/2)-naveDim.w; /* Posição Y */
	temp = SDL_LoadBMP("resources/nave.bmp");
	nave = SDL_DisplayFormat(temp);

	SDL_BlitSurface(espaco, NULL, janela, NULL);
	SDL_BlitSurface(nave, NULL, janela, NULL);

	/*
	Checagem se programa está aberto,
	enquanto estiver aberto verifica se o jogador apertou ESC (Escape) para sair do jogo e/ou teclas de movimentação
	 */
 	while(!aberto){
		/* Cor nula na sprite */
		SDL_SetColorKey(nave, SDL_SRCCOLORKEY, SDL_MapRGB(janela->format, 255, 0, 255));
		SDL_Event evento;
		SDL_Flip(janela);

		while(SDL_PollEvent(&evento)){
			DefGeral(evento);
		}
		/* Cria a nave na tela */
		//SDL_DisplayFormat(IMG_Load("nave.bmp"));
		//SDL_BlitSurface(nave, &naveDim, janela, &rcSprite);
        	/*
		 Update da tela enquanto o programa está aberto
		 Também para atualizar movimentação da nave.
		*/
        	SDL_UpdateRect(janela, 0, 0, 0, 0);
 	}
        SDL_Quit();
	system("clear");
	menu();
        exit(0);

	return 0;
}
