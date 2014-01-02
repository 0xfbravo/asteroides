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

int menu() {
	int opcao;
		printf("\t\t     ---------------------------------------------\n");
		printf("\t\t     |               MENU DE JOGO                |\n");
		printf("\t\t     ---------------------------------------------\n");
		printf("\t\t     | 1. Jogar!                                 |\n");
		printf("\t\t     | 2. Ranking                                |\n");
		printf("\t\t     | 3. Loja de Utilidades                     |\n");
		printf("\t\t     | 4. Opção 4 (Pensar em Algo)               |\n");
		printf("\t\t     | 0. Sair do Jogo                           |\n");
		printf("\t\t     ---------------------------------------------\n");

		printf("\t\t\t   Digite o número da sua opção: ");
		scanf("%d",&opcao);

		switch(opcao){
			case 0:
				printf("\t\t\t       Até mais!\n");
				break;
			case 1:
				system("clear");
				jogar = 1;
				break;
			case 2:
				system("clear");
				printf("\t\t   -------------------------------------------------------\n");
				printf("\t\t   |                 Ranking de Jogadores                |\n");
				printf("\t\t   -------------------------------------------------------\n");
				printf("\t\t   |     COLOCAÇÃO  |    NICKNAME    |     PONTUAÇÃO     |\n");
				printf("\t\t   -------------------------------------------------------\n");
				/*
				     Futuramente utilização de:
				printf("\t\t   | Nº Lugar - %s   PONTOS: %u   |\n",jogadorN,pontosN);
				
					E também alguma função para verificar quantidade de caracteres em nomes e pontos,
					completando-os com espaços, para que não seja perdida a formatação do Ranking.
					Algo como:
						ESPAÇOS = NICK-NOME_MAX
						if(NICK < NOME_MAX){
							NICK = NICK+ESPAÇOS
						}
				*/
				printf("\t\t   | 1º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 2º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 3º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 4º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 5º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 6º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 7º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 8º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 9º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");
				printf("\t\t   | 10º Lugar -  NOMEDEATE21CARACTERES   PONTOS: %u |\n",PONTUACAO_MAX);
				printf("\t\t   | --------------------------------------------------- |\n");

				/*
	 			 -- Ao terminar o jogo, caso a pontuação seja maior que o alguma pontuação, adiciona o nick no Ranking --
				 -- Utilização posterior --

				if(pontuacao > pontuacao){
				printf("Favor digite um nick para ser lembrado: ");
				scanf("%s",nome);
				return 0;
				} else {
				return 0;
				}
				*/
				break;
			case 3:
				printf("\t\t\t       LOJA - Ainda em criação!\n");
				break;
			case 4:
				printf("\t\t\t       OPÇÃO 4 - Ainda em criação!\n");
				break;
			default:
				system("clear");
				printf("\t\t     ---------------------------------------------\n");
				printf("\t\t     |   Opção inválida, digite uma das opções.  |\n");
				printf("\t\t     ---------------------------------------------\n");
				break;
			}
	return 0;
}
