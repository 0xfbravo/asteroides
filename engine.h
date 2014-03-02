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
|				- Bianca Albuquerque                                           |
|				- Fellipe Bravo Ribeiro Pimentel                               |
|                                                                                              |
------------------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"

// ----
//  Definições Gerais
// ----
#define LARGURA 1024 //Tamanho da Janela
#define ALTURA 768 //Tamanho da Janela
#define NOME "Asteroides - Projeto 2013 - IM-UFRRJ" //Nome da Janela
#define FRAMERATE 30 //FPS
// ----
//  Definições de Jogo
// ----
/* Valores Máximos */
#define NOME_MAX 21 //Define o máximo de caracteres possíveis para o Nick do jogador
#define PONTUACAO_MAX 999999 //Define o máximo de pontos que um jogador conseguirá obter
#define VIDA_MAX 3 //Máximo de vidas do jogador
#define COMBUSTIVEL_MAX 10000 //Máximo de Combustível da Nave
#define ACELERACAO_MAX 5 //Máxima velocidade atingida com a nave
#define ASTEROIDES_MAX 16 //Máximo de asteroides no jogo.
#define POSICAO_MAX 7 //Máximo de posições do Ranking
// ----
/* Demais valores */
#define ACELERACAO 0.0 //Velocidade de movimentação da nave
#define ATRITO 15 //Reduz a velocidade de movimentação da nave
#define PI 3.14159265

// -----------------------------

/* Ints */
int i,j;
int digitaNick = 1;
int digitou = 0;
int menuAberto = 0;
int jogando = 0;
int pause = 0;
int utilidades = 0;
int habilidades = 0;
int ranking = 0;
int menuInfo = 0;
int aviso = 1;
int vida = VIDA_MAX;
int combustivel = COMBUSTIVEL_MAX;
int angulo = 0;
int atirar;
int anguloTiro;
int velocidadeTiro = 12;
int centroNaveX,centroNaveY;
int pontuacao;
int criouAsteroide = 0;
int contarAsteroides;
int imunidade = 0;
int tempoMaximo = 30; // Tempo máximo para TIMER
int randomico;
int contaLetra;

// -----------------------------

/* Floats */
float dinheiro;
float velocidade = ACELERACAO;
float x,y;/* X e Y iniciais da Nave */
float Preco_Combustivel = 199.90;
float Preco_Vida = 255.90;
float Preco_Hab1 = 509.99;
float Preco_Hab2 = 499.99;

// -----------------------------

/* Chars */
char txtpontos[100],txtcombustivel[100],notificacao[400],txtvidas[100],nick[10],letra;

// -----------------------------

/* Funções */
int colisao_nave(float x, float y, SDL_Rect B, SDL_Surface *C);
int colisao_tiro(SDL_Rect A, SDL_Rect B);
int Comprar(float valor);
int EventosRanking();
void criarAsteroide(float xAsteroide, float yAsteroide, int tamanho, int posicao_vetor);
void InformacoesJogador();
void LogoASCII();
void Condicoes();
void verificarRanking();
void ConfSDL();
void Sair();

// -----------------------------

/* Demais valores */
FILE * arquivoRanking;
Uint32 start;

// -----------------------------

/* Struct's */
typedef struct {
	float x_Asteroide;
	float y_Asteroide;
	int tamanho;
	int explodiuTotal;
	int asteroideCriado;
	int anguloAsteroide;
	SDL_Rect asteroide;
	SDL_Surface *imgAsteroides;
} ASTEROIDE;

ASTEROIDE asteroideVetor[ASTEROIDES_MAX];
int verificarAsteroides(ASTEROIDE asteroideVetor[]);

// -----------------------------

typedef struct {
	int posicao;
	char nick[10];
	int pontuacao;
} RANKING;

RANKING jogador[POSICAO_MAX];

// -----------------------------

/* Valores do SDL */
SDL_Surface
 *janela_Menu,
 *janela_Jogo,
 *janela_Nick,
 *janela_Pause,
 *janela_Utilidades,
 *janela_Habilidades,
 *janela_Ranking,
 *janela_Informacoes,
 *logo,
 *bannerRanking,
 *bannerNotificacao,
 *pergaminho,
 *posicao1,
 *posicao2,
 *posicao3,
 *posicao4,
 *botaoMenu1,
 *botaoMenu2,
 *botaoMenu3,
 *botaoMenu4,
 *temp,
 *imgVida1,
 *imgVida2,
 *imgVida3,
 *espaco,
 *espaco2,
 *nave,
 *acelerar,
 *protecao,
 *tiro,
 *explosao,
 *naveAngulo,
 *acelerarAngulo,
 *protecaoAngulo,
 *imgJogador,
 *imgUtilidades,
 *imgHabilidades,
 *imgAsteroides,
 *imgIconeCombustivel,
 *imgIconeVida,
 *imgHab1,
 *imgHab2,
 *alpha,
 *imgInformacao1,
 *imgInformacao2,
 *imgInformacao3;

SDL_Rect
 PosicaoNave,
 imagemLogo,
 imagemRanking,
 imagemPergaminho,
 imgPosicao1,
 imgPosicao2,
 imgPosicao3,
 imgPosicao4,
 imgbotaoMenu1,
 imgbotaoMenu2,
 imgbotaoMenu3,
 imgbotaoMenu4,
 imgCombustivel,
 imgBannerNotificacao,
 imgVidas_Utilidade,
 imgHabilidade1,
 imgHabilidade2,
 vida1,
 vida2,
 vida3,
 espacoTotal,
 naveTotal,
 centroNave,
 tiroTotal,
 imagemJogador,
 imagemUtilidades,
 imagemHabilidades,
 asteroide,
 bgNotificacao,
 informacao1,
 informacao2,
 informacao3;

TTF_Font *fonte;
SDL_Event evento;


// -----------------------------------------------------------------------------------------------------
// Função que contém todas as informações Iniciais do SDL
// -----------------------------------------------------------------------------------------------------
void ConfSDL(){

	/* Configurações das Janelas */
	SDL_WM_SetCaption(NOME, NULL); /* Nome, definido em engine.h */
	janela_Menu = SDL_SetVideoMode(LARGURA, ALTURA, 32, SDL_HWSURFACE);
	janela_Nick = janela_Informacoes = janela_Ranking = janela_Habilidades = janela_Utilidades = janela_Pause = janela_Jogo = janela_Menu;

	/* Responsável por carregar o Background que é utilizado nas janelas Jogo & Menu */
	espaco = IMG_Load("resources/bg.jpg");

	/* Responsável por carregar o Background que é utilizado nas janelas Utilidades & Habilidades */
	espaco2 = IMG_Load("resources/bg2.jpg");

	// -----------------------------------------------------------------------------------------------------
	// Informações do Jogador
	//   Vida, Combustível, Dinheiro e etc
	// -----------------------------------------------------------------------------------------------------
	/* Imagem Coração (Vidas - 1, 2 e 3) */
	imgVida1 = IMG_Load("resources/heart.png");
	/* Localização da Imagem */
	vida1.x = 220;
	vida1.y = 67;
	vida1.h = 19;
	vida1.w = 20;

	imgVida2 = IMG_Load("resources/heart.png");
	/* Localização da Imagem */
	vida2.x = vida1.x + 22;
	vida2.y = vida1.y;
	vida2.h = 20;
	vida2.w = 19;

	imgVida3 = IMG_Load("resources/heart.png");
	/* Localização da Imagem */
	vida3.x = vida2.x + 22;
	vida3.y = vida1.y;
	vida3.h = 20;
	vida3.w = 19;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem Jogador */
	imgJogador = IMG_Load("resources/astronauta.png");
	/* Localização da Imagem */
	imagemJogador.x = 10;
	imagemJogador.y = 10;
	imagemJogador.h = 150;
	imagemJogador.w = 150;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem Loja de Utilidades */
	imgUtilidades = IMG_Load("resources/Botão_Asteroides.png");
	/* Localização da Imagem */
	imagemUtilidades.x = 170;
	imagemUtilidades.y = 95;
	imagemUtilidades.h = 30;
	imagemUtilidades.w = 200;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem (Botão) Janela de Habilidades */
	imgHabilidades = IMG_Load("resources/Botão_Asteroides_2.png");
	/* Localização da Imagem */
	imagemHabilidades.x = 170;
	imagemHabilidades.y = 130;
	imagemHabilidades.h = 30;
	imagemHabilidades.w = 200;


	// -----------------------------------------------------------------------------------------------------
	// Informações do Jogo
	//   Nave, Espaço, Asteroides e etc
	// -----------------------------------------------------------------------------------------------------
	/* Nave */
	temp = SDL_LoadBMP("resources/nave.bmp");
	nave = SDL_DisplayFormat(temp);
	/* Localização da Imagem */
	naveTotal.x = 0;
	naveTotal.y = 0;
	/* Cor nula na Nave */
	SDL_SetColorKey(nave, SDL_SRCCOLORKEY|SDL_RLEACCEL,(Uint32)SDL_MapRGB(nave->format, 255,0,255));
	x = (LARGURA/2)-naveTotal.w;
	y = (ALTURA/2)-naveTotal.h;

	protecao = IMG_Load("resources/Bolha3.png");
	acelerar = IMG_Load("resources/fogo_acelerar.png");

	// -----------------------------------------------------------------------------------------------------
	/* Tiro */
	tiro = IMG_Load("resources/tiro.bmp");
	/* Localização da Imagem */
	tiroTotal.h = 10;
	tiroTotal.w = 10;

	// -----------------------------------------------------------------------------------------------------
	// Informações de Menu
	//   Botões, Opções e etc
	// -----------------------------------------------------------------------------------------------------
	/* Logo - Asteroides */
	logo = IMG_Load("resources/Asteroides_Logo.png");
	/* Localização da Imagem */
	imagemLogo.x = 250;
	imagemLogo.y = 50;
	imagemLogo.h = 542;
	imagemLogo.w = 147;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem - Jogar */
	botaoMenu1 = IMG_Load("resources/Botão_Jogar.png");
	/* Localização da Imagem */
	imgbotaoMenu1.x = 320;
	imgbotaoMenu1.y = 280;
	imgbotaoMenu1.h = 50;
	imgbotaoMenu1.w = 381;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem - Informações */
	botaoMenu2 = IMG_Load("resources/Botão_Informações.png");
	/* Localização da Imagem */
	imgbotaoMenu2.x = imgbotaoMenu1.x;
	imgbotaoMenu2.y = imgbotaoMenu1.y+80;
	imgbotaoMenu2.h = 50;
	imgbotaoMenu2.w = 381;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem - Ranking */
	botaoMenu3 = IMG_Load("resources/Botão_Ranking.png");
	/* Localização da Imagem */
	imgbotaoMenu3.x = imgbotaoMenu1.x;
	imgbotaoMenu3.y = imgbotaoMenu2.y+80;
	imgbotaoMenu3.h = 50;
	imgbotaoMenu3.w = 381;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem - Sair */
	botaoMenu4 = IMG_Load("resources/Botão_Sair.png");
	/* Localização da Imagem */
	imgbotaoMenu4.x = imgbotaoMenu1.x;
	imgbotaoMenu4.y = imgbotaoMenu3.y+140;
	imgbotaoMenu4.h = 50;
	imgbotaoMenu4.w = 381;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem Combustivel */
	imgIconeCombustivel = IMG_Load("resources/Icone_Combustivel.png");
	/* Localização da Imagem */
	imgCombustivel.x = 330;
	imgCombustivel.y = 380;
	imgCombustivel.h = 90;
	imgCombustivel.w = 90;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem Vidas */
	imgIconeVida = IMG_Load("resources/Icone_Vida.png");
	/* Localização da Imagem */
	imgVidas_Utilidade.x = imgCombustivel.x + 280;
	imgVidas_Utilidade.y = imgCombustivel.y;
	imgVidas_Utilidade.h = 90;
	imgVidas_Utilidade.w = 90;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem Habilidade 1 (Imunidade) */
	imgHab1 = IMG_Load("resources/Icone_Imunidade.png");
	/* Localização da Imagem */
	imgHabilidade1.x = imgCombustivel.x;
	imgHabilidade1.y = imgCombustivel.y;
	imgHabilidade1.h = 90;
	imgHabilidade1.w = 90;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem Habilidade 2 (Super Tiro(?)) */
	imgHab2 = IMG_Load("resources/Icone_Tiro.png");
	/* Localização da Imagem */
	imgHabilidade2.x = imgCombustivel.x + 280;
	imgHabilidade2.y = imgCombustivel.y;
	imgHabilidade2.h = 90;
	imgHabilidade2.w = 90;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem Banner Ranking */
	bannerRanking = IMG_Load("resources/titulo_ranking.png");
	/* Localização da Imagem */
	imagemRanking.x = 250;
	imagemRanking.y = 105;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem Banner Ranking */
	pergaminho = IMG_Load("resources/pergaminho.png");
	/* Localização da Imagem */
	imagemPergaminho.x = 60;
	imagemPergaminho.y = 0;


	// -----------------------------------------------------------------------------------------------------
	/* Imagem Posicao 1 */
	posicao1 = IMG_Load("resources/posicao1.png");
	/* Localização da Imagem */
	imgPosicao1.x = 220;
	imgPosicao1.y = 245;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem Posicao 2 */
	posicao2 = IMG_Load("resources/posicao2.png");
	/* Localização da Imagem */
	imgPosicao2.x = imgPosicao1.x;
	imgPosicao2.y = imgPosicao1.y+47;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem Posicao 3 */
	posicao3 = IMG_Load("resources/posicao3.png");
	/* Localização da Imagem */
	imgPosicao3.x = imgPosicao1.x;
	imgPosicao3.y = imgPosicao2.y+47;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem Posicao4 */
	posicao4 = IMG_Load("resources/posicao4.png");
	/* Localização da Imagem */
	imgPosicao4.x = imgPosicao1.x;
	imgPosicao4.y = imgPosicao3.y+47;

	bannerNotificacao = IMG_Load("resources/banner.png");
	imgBannerNotificacao.x = 590;
	imgBannerNotificacao.y = 0;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem de Informação 1 */
	imgInformacao1 = IMG_Load("resources/Movimentacao.png");
	/* Localização da Imagem */
	informacao1.x = 100;
	informacao1.y = 350;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem de Informação 2 */
	imgInformacao2 = IMG_Load("resources/atirar.png");
	/* Localização da Imagem */
	informacao2.x = informacao1.x + 230;
	informacao2.y = informacao1.y;

	// -----------------------------------------------------------------------------------------------------
	/* Imagem de Informação 3 */
	imgInformacao3 = IMG_Load("resources/pause.png");
	/* Localização da Imagem */
	informacao3.x = informacao2.x + 380;
	informacao3.y = informacao1.y - 40;
}


// -----------------------------------------------------------------------------------------------------
// Função para reportar ao desenvovedor possíveis erros
//     Observação: ainda em desenvolvimento.
//
//          LISTA DE ERROS E CÓDIGOS
//
//  Erro 001 - 
//  Erro 002 - Problema de Inicialização da Janela
//  Erro 003 - Problema de Inicialização da Fonte
//  Erro 004 - 
//
// -----------------------------------------------------------------------------------------------------
void erro(int codigo){

	printf("Ocorreu algum erro inesperado!\n");
	printf("Codigo para o desenvolvedor: %d\n",codigo);

}


// -----------------------------------------------------------------------------------------------------
// Função para facilitar a escrita pelo SDL
// -----------------------------------------------------------------------------------------------------
void escreverTexto(int janela,int posicao_x, int posicao_y,char* texto, int R, int G, int B,int tamanho_texto){

	/*
	   Modo de uso
	escreverTexto(Número_da_Janela,x,y,"Texto",RED,GREEN,BLUE,TAMANHO_DO_TEXTO);

		Organização de Janelas:
		   0 - Janela do Menu
		   1 - Janela do Jogo
		   2 - Janela da Loja de Utilidades
                   3 - Janela da Loja de habilidades
		   4 - Janela do Ranking
		   5 - Janela de Modo de Espera
		   6 - Janela de Informações
		   7 - Janela de Nick
	*/
	  TTF_ByteSwappedUNICODE(1);
	  fonte = TTF_OpenFont("resources/Waree.ttf", tamanho_texto);
	  SDL_Color cor = {R, G, B};
	  SDL_Surface* src = TTF_RenderUTF8_Solid(fonte, texto, cor);
	  SDL_Rect posicaoTexto = {posicao_x, posicao_y, 0, 0};

	if(janela == 0){ SDL_BlitSurface(src, NULL, janela_Menu, &posicaoTexto); }
	else if(janela == 1) { SDL_BlitSurface(src, NULL, janela_Jogo, &posicaoTexto); }
	else if(janela == 2) { SDL_BlitSurface(src, NULL, janela_Utilidades, &posicaoTexto); }
	else if(janela == 3) { SDL_BlitSurface(src, NULL, janela_Habilidades, &posicaoTexto); }
	else if(janela == 4) { SDL_BlitSurface(src, NULL, janela_Ranking, &posicaoTexto); }
	else if(janela == 5) { SDL_BlitSurface(src, NULL, janela_Pause, &posicaoTexto); }
	else if(janela == 6) { SDL_BlitSurface(src, NULL, janela_Informacoes, &posicaoTexto); }
	else if(janela == 7) { SDL_BlitSurface(src, NULL, janela_Nick, &posicaoTexto); }

	  SDL_FreeSurface(src);
	  TTF_CloseFont(fonte);

}


// -----------------------------------------------------------------------------------------------------
// Função para verificar todas as condições de Jogo.
// -----------------------------------------------------------------------------------------------------
void Condicoes(){

	// ---------------------------------
	//     Temporizador da Imunidade
	// ---------------------------------
  	//int segundos=0;
	//if(imunidade == 1){
		//segundos++;
		//if(segundos >= tempoMaximo){
		//	imunidade = 0;
		//}
	//}
	naveAngulo = rotozoomSurface(nave,angulo,1.0,0);
	// -----------------------------------
	//        Inicialização do SDL
	// -----------------------------------
	if(TTF_Init() == -1){ exit(-1); erro(3); }
	if(SDL_Init(SDL_INIT_VIDEO) < 0){ exit(-1); erro(2); }
	if(
	    janela_Menu == NULL ||
	    janela_Jogo == NULL ||
	    janela_Ranking == NULL ||
	    janela_Utilidades == NULL ||
	    janela_Habilidades == NULL
        )
	{ SDL_Quit(); exit(-1); erro(2); }

	// -----------------------------------
	//   Informações Gerais - Asteroides
	// -----------------------------------
	for(i = 0; i < ASTEROIDES_MAX; i++){
	if(asteroideVetor[i].anguloAsteroide >= 360){ asteroideVetor[i].anguloAsteroide -= 360; }
	if(asteroideVetor[i].anguloAsteroide < 0){ asteroideVetor[i].anguloAsteroide += 360; }
		randomico = rand()%1024 + 1;
		// Criação dos Quatro Asteroides Iniciais
		if(asteroideVetor[i].asteroideCriado == 0 && i < 4){
			criarAsteroide(randomico, randomico, 3, i);
		}
		// Ultrapassar tela
		if(asteroideVetor[i].asteroide.y <= 0){ asteroideVetor[i].asteroide.y = ALTURA-250; }
		else if(asteroideVetor[i].asteroide.x >= LARGURA){ asteroideVetor[i].asteroide.x = 0; }
		else if(asteroideVetor[i].asteroide.y >= ALTURA){ asteroideVetor[i].asteroide.y = 0; }
		else if(asteroideVetor[i].asteroide.x <= 0){ asteroideVetor[i].asteroide.x = LARGURA-250; }

		// Movimentação do Asteroide na Tela
		asteroideVetor[i].asteroide.x-=sin(asteroideVetor[i].anguloAsteroide * PI/180.0);
		asteroideVetor[i].asteroide.y-=cos(asteroideVetor[i].anguloAsteroide * PI/180.0);

		// Criação dos Asteroides Secundários
 		if(asteroideVetor[i].tamanho == 3){
		asteroideVetor[i].imgAsteroides = IMG_Load("resources/asteroides.png");
		SDL_BlitSurface(asteroideVetor[i].imgAsteroides, NULL, janela_Jogo, &asteroideVetor[i].asteroide);
		}
		else if(asteroideVetor[i].tamanho == 2){
		asteroideVetor[i].imgAsteroides = IMG_Load("resources/asteroides2.png");
		SDL_BlitSurface(asteroideVetor[i].imgAsteroides, NULL, janela_Jogo, &asteroideVetor[i].asteroide);
		}
		else if(asteroideVetor[i].tamanho == 1){
		asteroideVetor[i].imgAsteroides = IMG_Load("resources/asteroides3.png");
		SDL_BlitSurface(asteroideVetor[i].imgAsteroides, NULL, janela_Jogo, &asteroideVetor[i].asteroide);
		}


		// -----------------------------------
		//              Colisões
		// -----------------------------------
		// Checar colisão do Tiro com algum dos Asteroides.
		if(atirar == 1){
			if(colisao_tiro(tiroTotal, asteroideVetor[i].asteroide) == 1){
				explosao = IMG_Load("resources/explosion.png");
				SDL_SetColorKey(explosao, SDL_SRCCOLORKEY|SDL_RLEACCEL,(Uint32)SDL_MapRGB(explosao->format, 0,0,0));
				SDL_BlitSurface(explosao, NULL, janela_Jogo, &asteroideVetor[i].asteroide);
				SDL_Flip(janela_Jogo);
				SDL_Delay(7);
				if(asteroideVetor[i].tamanho == 3){
					asteroideVetor[i].tamanho -= 1;
					asteroideVetor[i].asteroide.x = randomico;
					asteroideVetor[i].asteroide.y = randomico;
					j = verificarAsteroides(asteroideVetor);
					criarAsteroide(randomico, randomico, 2, j);
				}
				else if(asteroideVetor[i].tamanho == 2){
					asteroideVetor[i].tamanho -= 1;
					asteroideVetor[i].asteroide.x = randomico;
					asteroideVetor[i].asteroide.y = randomico;
					j = verificarAsteroides(asteroideVetor);
					criarAsteroide(randomico, randomico, 1, j);
				}
				else if(asteroideVetor[i].tamanho == 1){
					asteroideVetor[i].tamanho -= 1;
					asteroideVetor[i].asteroide.x = randomico;
					asteroideVetor[i].asteroide.y = randomico;
					asteroideVetor[i].explodiuTotal = 1;
					asteroideVetor[i].asteroideCriado = 0;
				}
				atirar = 0;
				pontuacao += (asteroideVetor[i].tamanho)*800;
				dinheiro += (asteroideVetor[i].tamanho)*2.99;
			}
		}
		// Checar colisão da Nave com algum dos Asteroides.
		if(imunidade == 0){
			if(colisao_nave(x, y, asteroideVetor[i].asteroide, naveAngulo) == 1 &&
			   asteroideVetor[i].asteroideCriado == 1 &&
			   asteroideVetor[i].explodiuTotal == 0
			){
				explosao = IMG_Load("resources/explosion.png");
				SDL_SetColorKey(explosao, SDL_SRCCOLORKEY|SDL_RLEACCEL,(Uint32)SDL_MapRGB(explosao->format, 0,0,0));
				SDL_BlitSurface(explosao, NULL, janela_Jogo, &asteroideVetor[i].asteroide);
				SDL_Flip(janela_Jogo);
				SDL_Delay(7);
				if(asteroideVetor[i].tamanho == 3){
					asteroideVetor[i].tamanho -= 1;
					j = verificarAsteroides(asteroideVetor);
					criarAsteroide(randomico, randomico, 2, j);
				}
				else if(asteroideVetor[i].tamanho == 2){
					asteroideVetor[i].tamanho -= 1;
					j = verificarAsteroides(asteroideVetor);
					criarAsteroide(randomico, randomico, 1, j);
				}
				else if(asteroideVetor[i].tamanho == 1){
					asteroideVetor[i].tamanho -= 1;
					asteroideVetor[i].explodiuTotal = 1;
					asteroideVetor[i].asteroideCriado = 0;
				}
				if(aviso < 3){
				SDL_BlitSurface(bannerNotificacao, NULL, janela_Jogo, &imgBannerNotificacao);
				SDL_Flip(janela_Jogo);
				aviso++;
				sprintf(notificacao, "Você perdeu uma vida pela Colisão!");
				escreverTexto(1,imgBannerNotificacao.x+20,30,notificacao,255,255,255,18);
				}
 				else if(aviso == 3){
				SDL_BlitSurface(bannerNotificacao, NULL, janela_Jogo, &imgBannerNotificacao);
				sprintf(notificacao, "Você perdeu sua última vida!");
				escreverTexto(1,imgBannerNotificacao.x+20,30,notificacao,255,255,255,18);
				}
				SDL_Flip(janela_Jogo);
				vida -= 1;		
				x = 450;
				y = 300;
				angulo = 0;
				velocidade = 0;
				imunidade = 1;
				SDL_Delay(1000);
			}
		}
	}

	// -----------------------------------
	//  Condições de Movimentação da Nave
	// -----------------------------------
	combustivel -= velocidade/100;

	if(angulo >= 360){ angulo -= 360; }
	if(angulo < 0){ angulo += 360; }

	if(velocidade < 0){ velocidade = 0; }
	if(velocidade > 0){ velocidade -= 0.05; }

	int nave_Angulo;
	nave_Angulo = angulo;

	x-=sin(nave_Angulo*PI/180.0)*velocidade;
	y-=cos(nave_Angulo*PI/180.0)*velocidade;

	// -----------------------------------
	//          Condições de Tiro
	// -----------------------------------

	if(atirar == 1){
	  	tiroTotal.x-=sin(anguloTiro*PI/180.0)*velocidadeTiro;
	  	tiroTotal.y-=cos(anguloTiro*PI/180.0)*velocidadeTiro;
	}

	centroNave.x = x + (naveAngulo->w/2);
	centroNave.y = y + (naveAngulo->h/2);

	// -----------------------------------
	// Ultrapassar tela (Nave e Tiro)
	// -----------------------------------
	if(y < -(naveAngulo->h)){ y = ALTURA-naveAngulo->w; }
	if(x >= LARGURA){ x = 0; }
	if(y >= ALTURA){ y = 0; }
	if(x < -(naveAngulo->w)){ x = LARGURA-naveAngulo->w; }

	if((tiroTotal.x <= 0)||(tiroTotal.x >= LARGURA)){ tiroTotal.x = centroNaveX; atirar = 0; }
	if((tiroTotal.y <= 0)||(tiroTotal.y >= ALTURA)){ tiroTotal.y = centroNaveY; atirar = 0; }	

	// -----------------------------------
	//       Condições de Combustível
	// -----------------------------------
	if(combustivel <= 0){ combustivel = 0; }
	if(combustivel < 3000){
		sprintf(notificacao, "O seu combustível está acabando!");
		escreverTexto(1,25,640,notificacao,80,158,170,13);
		sprintf(notificacao, "Dica: Compre mais combustível com seu dinheiro, na Loja de Utilidades!");
		escreverTexto(1,25,660,notificacao,80,158,170,13);
	}
	if(combustivel <= 0 && vida > 0){
		vida -= 1;
		combustivel = COMBUSTIVEL_MAX;
		SDL_BlitSurface(bannerNotificacao, NULL, janela_Jogo, &imgBannerNotificacao);
		sprintf(notificacao, "Você perdeu uma vida por falta de Combustível!");
		escreverTexto(1,imgBannerNotificacao.x+15,30,notificacao,255,255,255,14);
		sprintf(notificacao, "O combustível será cheio novamente!");
		escreverTexto(1,imgBannerNotificacao.x+40,50,notificacao,255,255,255,14);
		SDL_Flip(janela_Jogo);
		x = 450;
		y = 300;
		angulo = 0;
		SDL_Delay(500);
		SDL_Flip(janela_Jogo);
	}

	// -----------------------------------
	//          Condições de Vida
	// -----------------------------------
	if(vida <= 0) {
		system("clear");
		SDL_Flip(janela_Jogo);
		SDL_Delay(100);
		SDL_BlitSurface(bannerNotificacao, NULL, janela_Jogo, &imgBannerNotificacao);
		sprintf(notificacao,"Infelizmente todas as suas vidas acabaram.");
		escreverTexto(1,imgBannerNotificacao.x+30,40,notificacao,255,255,255,14);
		SDL_Flip(janela_Jogo);
		SDL_Delay(500);
		sprintf(notificacao,"[GAME OVER]");
		escreverTexto(1,230,340,notificacao,255,0,0,80);
		SDL_Flip(janela_Jogo);
		SDL_Delay(1500);
		verificarRanking();
		ranking = 1;
	}

	// ---------------------------------------------------------------------------
	/* Chama janela do Jogador com todas suas informações */
	InformacoesJogador();
	// ---------------------------------------------------------------------------
	/* Desenha Botão da Loja de Utilidades */
	SDL_BlitSurface(imgUtilidades, NULL, janela_Jogo, &imagemUtilidades);

	// ---------------------------------------------------------------------------	
	/* Desenha Botão da Loja de Utilidades */
	SDL_BlitSurface(imgHabilidades, NULL, janela_Jogo, &imagemHabilidades);
}


// -----------------------------------------------------------------------------------------------------
// Função para Colisão da Nave com o Asteroide & Tiro com a Nave
//     ~ Feito por Gabriel Segobia
// -----------------------------------------------------------------------------------------------------
int colisao_nave(float x, float y, SDL_Rect B, SDL_Surface *C){

	int leftA = x; // Ponto x da imagem
	int leftB = B.x;
	int rightA = x + C -> w;
	int rightB = B.x + B.w;
	int topA = y;
	int topB = B.y;
	int bottomA = y + C -> h; 
	int bottomB = B.y + B.h;
	
	if( topA >= bottomB)
		return 0;
	
	if(bottomA <= topB)
		return 0;
		
	if(rightA <= leftB)
		return 0;
		
	if(leftA >= rightB)
		return 0;
		
	return 1;	
}

int colisao_tiro(SDL_Rect A, SDL_Rect B){
	
	int leftA = A.x;
	int leftB = B.x;
	int rightA = A.x + A.w;
	int rightB = B.x + B.w;
	int topA = A.y;
	int topB = B.y;
	int bottomA = A.y + A.h;
	int bottomB = B.y + B.h;
	
	if( topA >= bottomB)
		return 0;
	
	if(bottomA <= topB)
		return 0;
		
	if(rightA <= leftB)
		return 0;
		
	if(leftA >= rightB)
		return 0;
		
	return 1;	
	
} 

void criarAsteroide(float xAsteroide, float yAsteroide, int tamanho, int posicao_vetor){
	asteroideVetor[posicao_vetor].x_Asteroide = xAsteroide;
	asteroideVetor[posicao_vetor].y_Asteroide = yAsteroide;
	asteroideVetor[posicao_vetor].tamanho = tamanho;
	
	/* Desenha o Asteroide na tela */
	asteroideVetor[posicao_vetor].imgAsteroides = IMG_Load("resources/asteroides.png");
	asteroideVetor[posicao_vetor].asteroide.x = asteroideVetor[posicao_vetor].x_Asteroide;
	asteroideVetor[posicao_vetor].asteroide.y = asteroideVetor[posicao_vetor].y_Asteroide;

	asteroideVetor[posicao_vetor].anguloAsteroide += rand()%360;

	asteroideVetor[posicao_vetor].asteroideCriado = 1;
}

int verificarAsteroides(ASTEROIDE asteroideVetor[]){

	for(i = 0; i < ASTEROIDES_MAX; i++){
		if(asteroideVetor[i].asteroideCriado == 0){
			return i;
		}
	}
return 0;
}

void verificarRanking(){
	arquivoRanking = fopen("ranking.bin","r");
	while(!feof(arquivoRanking)){
		fread(&jogador, sizeof(RANKING), 1, arquivoRanking);
	}

	for(i = 0; i < POSICAO_MAX; i++){
		if(pontuacao > jogador[i].pontuacao){
			jogador[i].pontuacao = pontuacao;
			strncpy(jogador[i].nick, nick, sizeof(nick));
			fclose(arquivoRanking);
			arquivoRanking = fopen("ranking.bin","w");
			fwrite(&jogador[i], sizeof(RANKING), 1, arquivoRanking);
			fclose(arquivoRanking);
			i = POSICAO_MAX;
		}
	}
}

int Comprar(float valor){

	if(valor > dinheiro){
		sprintf(notificacao,"Você não possui dinheiro o suficiente!");
		escreverTexto(3,imgCombustivel.x+30,imgCombustivel.y+160,notificacao,255,0,0,16);
		SDL_Flip(janela_Utilidades);
		SDL_Delay(1000);
	} else {
		dinheiro -= valor;
		return 1;
	}
return 0;
}


void LogoASCII(){

	   system("clear");
	   printf("\t\t\t------------------------------------------------------------------------------------------------\n");
	   printf("\t\t\t|                                                                                              |\n");
	   printf("\t\t\t|               _______                                   _      _                             |\n");        
	   printf("\t\t\t|              (_______)         _                       (_)    | |                            |\n");             
	   printf("\t\t\t|               _______   ___  _| |_  _____   ____  ___   _   __| | _____   ___                |\n");
	   printf("\t\t\t|              |  ___  | /___)(_   _)| ___ | / ___)/ _ \\ | | / _  || ___ | /___)               |\n");
	   printf("\t\t\t|              | |   | ||___ |  | |_ | ____|| |   | |_| || |( (_| || ____||___ |               |\n");
	   printf("\t\t\t|              |_|   |_|(___/    \\__)|_____)|_|    \\___/ |_| \\____||_____)(___/                |\n");
	   printf("\t\t\t|                                         Projeto 2013                                         |\n");
	   printf("\t\t\t|                                                                                              |\n");
	   printf("\t\t\t|                     Trabalho de Laboratório de Computação 1 - IM-UFRRJ 2013                  |\n");
	   printf("\t\t\t|                          Participantes                                                       |\n");
	   printf("\t\t\t|				- Bianca Albuquerque                                           |\n");
	   printf("\t\t\t|				- Fellipe Bravo Ribeiro Pimentel                               |\n");
	   printf("\t\t\t|                                                                                              |\n");
	   printf("\t\t\t------------------------------------------------------------------------------------------------\n");

}


void RankingVisual(){
	if(ranking == 1){
		imgbotaoMenu4.x = imgbotaoMenu1.x;
		imgbotaoMenu4.y = imgbotaoMenu3.y+180;
		imgbotaoMenu4.h = 50;
		imgbotaoMenu4.w = 381;
	}
	// -----------------------------------------------------------------------------------------------------
	//                            Inicializações Fundamentais da Função Habilidades();
	// -----------------------------------------------------------------------------------------------------
	while(SDL_PollEvent(&evento)){ EventosRanking(evento); }
	   SDL_UpdateRect(janela_Ranking, 0, 0, 0, 0);

	// ---------------------------------------------------------------------------
	/* Desenha o Espaço por completo */
	SDL_BlitSurface(espaco, NULL, janela_Ranking, NULL);

	/* Desenha o PERGAMINHO (Background) */
	SDL_BlitSurface(pergaminho, NULL, janela_Ranking, &imagemPergaminho);
	/* Desenha o Banner do Ranking */
	SDL_BlitSurface(bannerRanking, NULL, janela_Ranking, &imagemRanking);

	/* Desenha imagens das Posicoes */
	SDL_BlitSurface(posicao1, NULL, janela_Ranking, &imgPosicao1);
	SDL_BlitSurface(posicao2, NULL, janela_Ranking, &imgPosicao2);
	SDL_BlitSurface(posicao3, NULL, janela_Ranking, &imgPosicao3);
	SDL_BlitSurface(posicao4, NULL, janela_Ranking, &imgPosicao4);

	/* Desenha Imagem SAIR (MENU) */
	SDL_BlitSurface(botaoMenu4, NULL, janela_Ranking, &imgbotaoMenu4);

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
	arquivoRanking = fopen("ranking.bin","r");
	while(!feof(arquivoRanking)){
		fread(&jogador, sizeof(RANKING), 1, arquivoRanking);
	for(i = 0; i < POSICAO_MAX; i++){
	   if(i == 0){
	   sprintf(notificacao,"%dº Lugar     [%s]   PONTOS: %d",i+1,jogador[i].nick,jogador[i].pontuacao);
	   escreverTexto(4,275,260,notificacao,102,51,0,16);}
	   else if(i == 1){
	   sprintf(notificacao,"%dº Lugar     [%s]   PONTOS: %d",i+1,jogador[i].nick,jogador[i].pontuacao);
	   escreverTexto(4,275,305,notificacao,102,51,0,16);}
	   else if(i == 2){
	   sprintf(notificacao,"%dº Lugar     [%s]   PONTOS: %d",i+1,jogador[i].nick,jogador[i].pontuacao);
	   escreverTexto(4,275,350,notificacao,102,51,0,16);}
	   else if(i == 3){
	   sprintf(notificacao,"%dº Lugar     [%s]   PONTOS: %d",i+1,jogador[i].nick,jogador[i].pontuacao);
	   escreverTexto(4,275,395,notificacao,102,51,0,16);}
	   else if(i == 4){
	   sprintf(notificacao,"%dº Lugar     [%s]   PONTOS: %d",i+1,jogador[i].nick,jogador[i].pontuacao);
	   escreverTexto(4,275,435,notificacao,102,51,0,16);}
	   else if(i == 5){
	   sprintf(notificacao,"%dº Lugar     [%s]   PONTOS: %d",i+1,jogador[i].nick,jogador[i].pontuacao);
	   escreverTexto(4,275,475,notificacao,102,51,0,16);}
	   else if(i == 6){
	   sprintf(notificacao,"%dº Lugar     [%s]   PONTOS: %d",i+1,jogador[i].nick,jogador[i].pontuacao);
	   escreverTexto(4,275,510,notificacao,102,51,0,16);}
	}
	}
	fclose(arquivoRanking);

}
