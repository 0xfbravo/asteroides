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

#define NOME_MAX 21 //Define o máximo de caracteres possíveis para o Nick do jogador
#define PONTUACAO_MAX 999999 //Define o máximo de pontos que um jogador conseguirá obter
#define ALTURA 800 //Tamanho da Janela
#define LARGURA 600 //Tamanho da Janela
#define NOME "Asteroides - Projeto 2013 - IM-UFRRJ" //Nome da Janela
#define FRAMERATE 30 //Velocidade de movimentação da nave
#define ACELERACAO 5 //Continua movimento da nave, mesmo após soltar botão
#define ATRITO 15 //Reduz a velocidade de movimentação da nave
#define MAX_VIDA 3 //Máximo de vidas do jogador
#define FONTE 16 //Tamanho da fonte

int aberto; /* Variável de looping */
int vida = MAX_VIDA; //Máximo de vidas do jogador
int aleatorio; /* Para gerar números aleatórios */
int combustivel = 12000;/* Máximo possível de combustível no tanque da nave */
int jogar;
int angulo = 0;
char txtpontos[100],txtcombustivel[100],txtvidas[100];
SDL_Surface *janela, *espaco, *nave, *temp, *naveAngulo;
SDL_Rect espacoTotal, naveTotal; /* Espaço total e Nave */
TTF_Font* fonte;

void texto(char* texto, SDL_Surface* dst, int x, int y){
	fonte = TTF_OpenFont("resources/Waree.ttf", FONTE);
	SDL_Color cor = {255, 0, 0}; //vermelho
	SDL_Surface* src = TTF_RenderText_Blended(fonte, texto, cor);
	SDL_Rect dst_rect = {x, y, 0, 0};
	SDL_BlitSurface(src, NULL, dst, &dst_rect);
	SDL_FreeSurface(src);
}

int DefGeral(SDL_Event evento){
		if(angulo >= 360)
			angulo -= 360;
		if(angulo <= -360)
			angulo += 360;

		if(combustivel <= 0){
			vida = vida-1;
			combustivel = 12000;
		}

		naveAngulo = rotozoomSurface(nave,angulo,1.0,0);

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
						if(combustivel > 0){
							combustivel = combustivel-(aleatorio*ACELERACAO);
							if(combustivel < 0){combustivel = 0;}
							espacoTotal.x -= (1*FRAMERATE)-ATRITO;
							angulo += 3;
							//printf("COMBUSTIVEL: %d \n\n",combustivel); /* DEBUG */
								if(espacoTotal.x < 0){
								espacoTotal.x = 800-naveTotal.w;
								}
						} else {
							printf("-- Você não possui combustível o suficiente para se movimentar! --\n");
							printf("Compre mais combustível com seus pontos, na Loja de Utilidades\n");
						}
						break;
	
	
					/* Adiciona 1 para o X da nave, deslocamento lateral direito */
					case SDLK_RIGHT:
						if(combustivel > 0){
							combustivel = combustivel-(aleatorio*ACELERACAO);
							if(combustivel < 0){combustivel = 0;}
							espacoTotal.x += (1*FRAMERATE)-ATRITO;
							angulo -= 3;
							//printf("COMBUSTIVEL: %d \n\n",combustivel); /* DEBUG */
								if(espacoTotal.x >= 800){
									espacoTotal.x = 0;
								}
						} else {
							printf("-- Você não possui combustível o suficiente para se movimentar! --\n");
							printf("Compre mais combustível com seus pontos, na Loja de Utilidades\n");
						}
						break;
	
	
					/* Subtrai 1 para o Y da nave, deslocamento SUPERIOR */
					case SDLK_UP:
						if(combustivel > 0){
							combustivel = combustivel-(aleatorio*ACELERACAO);
							if(combustivel < 0){combustivel = 0;}
							espacoTotal.y -= (1*FRAMERATE)-ATRITO;
							//printf("COMBUSTIVEL: %d \n\n",combustivel); /* DEBUG */
								if(espacoTotal.y < 0){
									espacoTotal.y = 600-naveTotal.w;
								}
						} else {
							printf("-- Você não possui combustível o suficiente para se movimentar! --\n");
							printf("Compre mais combustível com seus pontos, na Loja de Utilidades\n");
						}
						break;
	
	
					/* Adiciona 1 para o Y da nave, deslocamento INFERIOR */
					case SDLK_DOWN:
						if(combustivel > 0){
							combustivel = combustivel-(aleatorio*ACELERACAO);
							if(combustivel < 0){combustivel = 0;}
							espacoTotal.y += (1*FRAMERATE)-ATRITO;
							//printf("COMBUSTIVEL: %d \n\n",combustivel); /* DEBUG */
								if(espacoTotal.y >= 600){
									espacoTotal.y = 0;
								}
						} else {
							printf("-- Você não possui combustível o suficiente para se movimentar! --\n");
							printf("Compre mais combustível com seus pontos, na Loja de Utilidades\n");
						}
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
