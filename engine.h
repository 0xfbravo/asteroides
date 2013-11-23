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

#define NOME_MAX 21 //Define o máximo de caracteres possíveis para o Nick do jogador
#define PONTUACAO_MAX 999999 //Define o máximo de pontos que um jogador conseguirá obter
#define ALTURA 800
#define LARGURA 600
#define NOME "Asteroides - Projeto 2013 - IM-UFRRJ"

int aberto; /* Variável de looping */
int nulo; /* Cor nula na sprite */
SDL_Surface *janela, *espaco, *nave, *temp;
SDL_Rect destino, naveDim, rcSprite; /* Localização da Nave */

int DefGeral(SDL_Event evento){

	switch (evento.type) {
		/* Fecha o "looping" do programa ao clicar no "X" de fechar o programa */
		case SDL_QUIT:
			aberto = 1;
		break;
	
		/* Captura das Teclas */
		case SDL_KEYDOWN:
			switch (evento.key.keysym.sym) {
				/* Fecha o "looping" do programa, e pula para o SDL_Quit() */
				case SDLK_ESCAPE:
					aberto = 1;
					break;
				/* Subtrai 1 para o X da nave, deslocamento lateral esquerdo */
				case SDLK_LEFT:
					printf("Você pressionou a esquerda\n"); /* DEBUG Captura */
					naveDim.x -= 1;
					break;
				/* Adiciona 1 para o X da nave, deslocamento lateral direito */
				case SDLK_RIGHT:
					printf("Você pressionou a direita\n"); /* DEBUG Captura */
					naveDim.x += 1;
					break;
				/* Subtrai 1 para o Y da nave, deslocamento SUPERIOR */
				case SDLK_UP:
					printf("Você pressionou pra cima\n"); /* DEBUG Captura */
					naveDim.y -= 1;
					break;
				/* Adiciona 1 para o Y da nave, deslocamento INFERIOR */
				case SDLK_DOWN:
					printf("Você pressionou pra baixo\n"); /* DEBUG Captura */
					naveDim.y += 1;
					break;
				/* Abre a Loja de Utilidades */
				case SDLK_PAGEDOWN:
					printf("Você abriu a Loja de Utilidades\n"); /* DEBUG Captura */
					break;
				/* Abre a Janela de Habilidades */
				case SDLK_PAGEUP:
					printf("Você abriu a Janela de Habilidades\n"); /* DEBUG Captura */
					break;
				/* Qualquer outra tecla que se aperte, nada acontecerá */
				default:
					break;
				}
	}
return 0;
}
