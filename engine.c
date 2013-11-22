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
#include "engine.h"
#include "menu.c"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#ifdef __cplusplus
#include <string>
#endif

/*int main(){

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
}*/

int main(int argv, char **argc)
{
	int aberto = 1; /* Variável de looping */
	SDL_Surface *janela; /*  */
	SDL_Event evento; /* Definida para resgatar valores de eventos */
	janela = SDL_SetVideoMode(ALTURA, LARGURA, 32, SDL_HWSURFACE); /* Definição do Tamanho da Janela de Jogo, configuráveis em engine.h */
	SDL_FillRect(janela , NULL , 0x221122); /* Background da Janela */
	SDL_WM_SetCaption(NOME, NULL); /* NOME definido em engine.h */

	/*
	 Dimensões e Localização do Quadrado
	*/
	SDL_Surface *nave;
	SDL_Rect naveDim; /* Definida para localização da Nave */
	//naveDim.w = 10;
	//naveDim.h = 10;
	naveDim.x = ALTURA/2;
	naveDim.y = LARGURA/2;
	nave = SDL_LoadBMP("nave.bmp");
 
        /* Inicialização da Janela */
        if(SDL_Init(SDL_INIT_VIDEO) < 0){
                exit(-1);
        }
        /* Checa se a janela existe, caso contrário o programa é fechado com erro */
	if(janela == NULL){
		SDL_Quit();
		exit(-1);
        }
 
        /* Fazendo quadradin de 8 colorido pra eu me guiar */
        //SDL_FillRect(janela, &naveDim, SDL_MapRGB(janela->format, 102, 204, 153));

	/*
	Checagem se programa está aberto,
	enquanto estiver aberto verifica se o jogador apertou ESC (Escape) para sair do jogo
	 */
 	while(aberto){
		SDL_BlitSurface(nave, NULL, janela, &naveDim);
		SDL_Flip(janela);



		while(SDL_PollEvent(&evento)){
			if(evento.type == SDL_KEYDOWN){ /* Checa se alguma tecla foi pressionada */
				if(evento.key.keysym.sym == SDLK_ESCAPE){ /* Fecha o "looping" do programa, e pula para o SDL_Quit() */
				aberto = 0;
				}
				if(evento.key.keysym.sym == SDLK_RIGHT){ /* Adiciona 1 para o X da nave, deslocamento lateral direito */
					printf("Você pressionou a direita");
					naveDim.x += 1;
				}
				if(evento.key.keysym.sym == SDLK_LEFT){ /* Subtrai 1 para o X da nave, deslocamento lateral esquerdo */
					printf("Você pressionou a esquerda");
					naveDim.x -= 1;
				}
				if(evento.key.keysym.sym == SDLK_UP){ /* Adiciona 1 para o Y da nave, deslocamento SUPERIOR */
					printf("Você pressionou pra cima");
					naveDim.y += 1;
				}
				if(evento.key.keysym.sym == SDLK_DOWN){ /* Subtrai 1 para o Y da nave, deslocamento INFERIOR */
					printf("Você pressionou pra baixo");
					naveDim.y -= 1;
				}
			}
		}
        	/*
		 Update da tela enquanto o programa está aberto
		 Também para atualizar movimentação da nave.
		*/
        	SDL_UpdateRect(janela, 0, 0, 0, 0);
 	}

 	SDL_FreeSurface(nave);
        SDL_Quit();
        exit(0);
}
