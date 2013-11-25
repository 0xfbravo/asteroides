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
	naveTotal.h = 96; /* Tamanho total da sprite */
	naveTotal.w = 96; /* Tamanho total da sprite */

	espacoTotal.x = 0; /* Local de Destino X da Nave */
	espacoTotal.y = 0; /* Local de Destino Y da Nave */
	espacoTotal.h = ALTURA; /* Tamanho total possível de deslocamento */
	espacoTotal.w = LARGURA; /* Tamanho total possível de deslocamento */


	/*
	Checagem se programa está aberto,
	enquanto estiver aberto verifica se o jogador apertou ESC (Escape) para sair do jogo e/ou teclas de movimentação
	 */
 	while(!aberto){
		SDL_Event evento;
		SDL_EnableKeyRepeat(100, 1);

		while(SDL_PollEvent(&evento)){
			DefGeral(evento);
		}
		/* Desenha o Espaço por completo */
		SDL_BlitSurface(espaco, NULL, janela, NULL);
		/* Desenha a Nave */
		SDL_BlitSurface(nave, &naveTotal, janela, &espacoTotal);
        	/*
		 Update da tela enquanto o programa está aberto
		 Também para atualizar movimentação da nave.
		*/
        	SDL_UpdateRect(janela, 0, 0, 0, 0);
 	}
        SDL_Quit();
	system("clear");
	menu();

	return 0;
}
