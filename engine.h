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
|				- Paulo Roberto Xavier                                         |
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
#define COMBUSTIVEL_MAX 20000 //Máximo de Combustível da Nave
#define ACELERACAO_MAX 5 //Máxima velocidade atingida com a nave
#define ASTEROIDES_MAX 16 //Máximo de asteroides no jogo.
// ----
/* Demais valores */
#define ACELERACAO 0.0 //Velocidade de movimentação da nave
#define ATRITO 15 //Reduz a velocidade de movimentação da nave
#define PI 3.14159265

/* Ints */
int i;
int menuAberto = 0;
int jogando = 0;
int utilidades = 0;
int habilidades = 0;
int ranking = 0;
int aviso = 1;
int vida = VIDA_MAX;
int combustivel = COMBUSTIVEL_MAX;
int angulo = 0;
int atirar;
int anguloTiro;
int velocidadeTiro = 12;
int centroNaveX;
int centroNaveY;
int pontuacao;
int criouAsteroide = 0;
int contarAsteroides;
int imunidade;
int tempoMaximo; // Tempo de Imunidade em SEGUNDOS (Tempo INICIAL da Nave)
/* Floats */
float dinheiro;
float velocidade = ACELERACAO;
float x,y;/* X e Y iniciais da Nave */
float Preco_Combustivel = 199.90;
float Preco_Vida = 999.99;
float Preco_Hab1 = 999.99;
float Preco_Hab2 = 999.99;
/* Chars */
char txtpontos[100],txtcombustivel[100],notificacao[400],txtvidas[100], nick[21];
/* Funções */
int colisao_nave(float x, float y, SDL_Rect B, SDL_Surface *C);
int colisao_tiro(SDL_Rect A, SDL_Rect B);
int Comprar(float valor);
int EventosRanking();
void criarAsteroide(float xAsteroide, float yAsteroide, int tamanho, int posicao_vetor);
void LogoASCII();
void Condicoes();
void ConfSDL();
void Sair();

/* Demais valores */
Uint32 start;
clock_t init_time; //Valor inicial 
clock_t last_time; //Valor atual 

typedef struct {
	float x_Asteroide;
	float y_Asteroide;
	int tamanho;
	int explodiu;
	SDL_Rect asteroide;
	SDL_Surface *imgAsteroides;
} ASTEROIDE;

ASTEROIDE asteroideVetor[ASTEROIDES_MAX];

SDL_Surface
 *janela_Menu,
 *janela_Jogo,
 *janela_Utilidades,
 *janela_Habilidades,
 *janela_Ranking,
 *logo,
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
 *alpha;

SDL_Rect
 PosicaoNave,
 imagemLogo,
 imgbotaoMenu1,
 imgbotaoMenu2,
 imgbotaoMenu3,
 imgbotaoMenu4,
 imgCombustivel,
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
 bgNotificacao;

TTF_Font *fonte;
SDL_Event evento;

/* Inicia a contagem */
int InitClock(void) { 
	init_time = clock(); 
	last_time = init_time; 
	return (int)init_time; 
} 

/* Atualiza o time */
int CheckClock(void) { 
	last_time = clock(); 
	if(((int)last_time)-((int)init_time) >= tempoMaximo){ return 1; } //O relogio atingiu o tempo de espera; 
	return 0; // o tempo de espera ainda não foi atingido; 
} 

// -----------------------------------------------------------------------------------------------------
// Função que contém todas as informações Iniciais do SDL
// -----------------------------------------------------------------------------------------------------
void ConfSDL(){

	/* Configurações das Janelas */
	SDL_WM_SetCaption(NOME, NULL); /* Nome, definido em engine.h */
	janela_Menu = SDL_SetVideoMode(LARGURA, ALTURA, 32, SDL_HWSURFACE);
	janela_Jogo = SDL_SetVideoMode(LARGURA, ALTURA, 32, SDL_HWSURFACE);
	janela_Utilidades = SDL_SetVideoMode(LARGURA, ALTURA, 32, SDL_HWSURFACE);
	janela_Habilidades = SDL_SetVideoMode(LARGURA, ALTURA, 32, SDL_HWSURFACE);
	janela_Ranking = SDL_SetVideoMode(LARGURA, ALTURA, 32, SDL_HWSURFACE);

	/* Repetição de tecla, para movimentação */
	SDL_EnableKeyRepeat(1, 10);

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
	nave = IMG_Load("resources/nave.png");
	/* Localização da Imagem */
	naveTotal.x = 0;
	naveTotal.y = 0;
	/* Cor nula na Nave */
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

	  SDL_FreeSurface(src);
	  TTF_CloseFont(fonte);

}

// -----------------------------------------------------------------------------------------------------
// Função para verificar todas as condições de Jogo.
// -----------------------------------------------------------------------------------------------------
void Condicoes(){
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

	if(imunidade == 1){
		tempoMaximo = 1;
		InitClock();
		if(CheckClock() == 1){ imunidade = 0; SDL_Flip(janela_Jogo);}
	}

	// -----------------------------------
	//   Informações Gerais - Asteroides
	// -----------------------------------
	// Criação dos Quatro Asteroides Iniciais
	if(criouAsteroide == 0){ criarAsteroide(50, 50, 3, 0); }
	else if(criouAsteroide == 1){  criarAsteroide(LARGURA-250, 50, 3, 1);  }
	else if(criouAsteroide == 2){  criarAsteroide(50, ALTURA-250, 3, 2);  }
	else if(criouAsteroide == 3){  criarAsteroide(LARGURA-250, ALTURA-250, 3, 4);  }

	for(i = 0; i < ASTEROIDES_MAX; i++){
		// Ultrapassar tela
		if(asteroideVetor[i].asteroide.y <= 0){ asteroideVetor[i].asteroide.y = ALTURA-250; }
		else if(asteroideVetor[i].asteroide.x >= LARGURA){ asteroideVetor[i].asteroide.x = 0; }
		else if(asteroideVetor[i].asteroide.y >= ALTURA){ asteroideVetor[i].asteroide.y = 0; }
		else if(asteroideVetor[i].asteroide.x <= 0){ asteroideVetor[i].asteroide.x = LARGURA-250; }

		// Movimentação do Asteroide na Tela
		asteroideVetor[i].asteroide.x += 1;
		asteroideVetor[i].asteroide.y -= 1;
		if(pontuacao > 20000){
		asteroideVetor[i].asteroide.x += 3;
		asteroideVetor[i].asteroide.y -= 3;
		}

		// Criação dos Asteroides Secundários
 		if(asteroideVetor[i].tamanho < 0){
			criarAsteroide(rand()%LARGURA, rand()%ALTURA, 3, i);
		}
 		else if(asteroideVetor[i].tamanho == 3){
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
				SDL_Delay(35);
				asteroideVetor[i].tamanho -= 1;
				atirar = 0;
				pontuacao += (asteroideVetor[i].tamanho)*800;
			}
		}
		// Checar colisão da Nave com algum dos Asteroides.
		if(imunidade == 0){
			if(colisao_nave(x, y, asteroideVetor[i].asteroide, naveAngulo) == 1){
				sprintf(notificacao, "Você perdeu uma vida pela Colisão!");
				escreverTexto(1,270,260,notificacao,78,126,150,22);
				SDL_Flip(janela_Jogo);
				vida -= 1;		
				x = rand()%LARGURA;
				y = rand()%ALTURA;
				angulo = 90;
				velocidade = 0;
				SDL_Delay(4000);
			}
		}
	}

	// -----------------------------------
	//  Condições de Movimentação da Nave
	// -----------------------------------
	naveAngulo = rotozoomSurface(nave,angulo,1.0,0);

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
		escreverTexto(1,25,540,notificacao,80,158,170,13);
		sprintf(notificacao, "Dica: Compre mais combustível com seu dinheiro, na Loja de Utilidades!");
		escreverTexto(1,25,560,notificacao,80,158,170,13);
	}
	if(combustivel <= 0 && vida > 0){
		vida -= 1;
		combustivel = COMBUSTIVEL_MAX;
		if(aviso < 3){
			aviso += 1;
			sprintf(notificacao, "Você perdeu uma vida por falta de Combustível!");
			escreverTexto(1,200,260,notificacao,78,126,150,18);
			sprintf(notificacao, "O tanque será cheio novamente, [ %s ]!",nick);
			escreverTexto(1,220,280,notificacao,78,126,150,18);
			SDL_Flip(janela_Jogo);
			x = 350;
			y = 350;
			SDL_Delay(4000);
			SDL_Flip(janela_Jogo);
		} else if(aviso == 3){
			sprintf(notificacao, "Você perdeu sua última vida por falta de Combustível!");
			escreverTexto(1,200,260,notificacao,78,126,150,18);
			SDL_Flip(janela_Jogo);
		}
	}

	// -----------------------------------
	//          Condições de Vida
	// -----------------------------------
	if(vida <= 0) {
		system("clear");
		SDL_Flip(janela_Jogo);
		SDL_Delay(500);
		sprintf(notificacao,"Infelizmente todas as suas vidas acabaram.");
		escreverTexto(1,200,290,notificacao,148,126,150,20);
		SDL_Delay(2000);
		SDL_Flip(janela_Jogo);
		sprintf(notificacao,"[GAME OVER]");
		escreverTexto(1,300,350,notificacao,20,40,60,42);
		SDL_Flip(janela_Jogo);
		SDL_Delay(3000);
		Sair();
	}
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

	criouAsteroide += 1;
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
	   printf("------------------------------------------------------------------------------------------------\n");
	   printf("|                                                                                              |\n");
	   printf("|               _______                                   _      _                             |\n");        
	   printf("|              (_______)         _                       (_)    | |                            |\n");             
	   printf("|               _______   ___  _| |_  _____   ____  ___   _   __| | _____   ___                |\n");
	   printf("|              |  ___  | /___)(_   _)| ___ | / ___)/ _ \\ | | / _  || ___ | /___)               |\n");
	   printf("|              | |   | ||___ |  | |_ | ____|| |   | |_| || |( (_| || ____||___ |               |\n");
	   printf("|              |_|   |_|(___/    \\__)|_____)|_|    \\___/ |_| \\____||_____)(___/                |\n");
	   printf("|                                         Projeto 2013                                         |\n");
	   printf("|                                                                                              |\n");
	   printf("|                     Trabalho de Laboratório de Computação 1 - IM-UFRRJ 2013                  |\n");
	   printf("|                          Participantes                                                       |\n");
	   printf("|				- Bianca Albuquerque                                           |\n");
	   printf("|				- Fellipe Bravo Ribeiro Pimentel                               |\n");
	   printf("|				- Paulo Roberto Xavier                                         |\n");
	   printf("|                                                                                              |\n");
	   printf("------------------------------------------------------------------------------------------------\n");

}


void RankingVisual(){

	// -----------------------------------------------------------------------------------------------------
	//                            Inicializações Fundamentais da Função Habilidades();
	// -----------------------------------------------------------------------------------------------------
	while(SDL_PollEvent(&evento)){ EventosRanking(evento); }
	   SDL_UpdateRect(janela_Ranking, 0, 0, 0, 0);

	// ---------------------------------------------------------------------------
	/* Desenha o Espaço por completo */
	SDL_BlitSurface(espaco, NULL, janela_Ranking, NULL);

	/* Desenha LOGO */
	SDL_BlitSurface(logo, NULL, janela_Menu, &imagemLogo);

	/* Desenha Imagem SAIR (MENU) */
	SDL_BlitSurface(botaoMenu4, NULL, janela_Menu, &imgbotaoMenu4);

	   sprintf(notificacao,"-----------------------------------------------------------------------------------");
	   escreverTexto(4,150,200,notificacao,0,0,0,18);
	   sprintf(notificacao,"|                           Ranking de Jogadores                      |");
	   escreverTexto(4,150,220,notificacao,0,0,0,18);
	   sprintf(notificacao,"-----------------------------------------------------------------------------------");
	   escreverTexto(4,150,240,notificacao,0,0,0,18);
	   sprintf(notificacao,"|     COLOCAÇÃO  |    NICKNAME    |     PONTUAÇÃO     |");
	   escreverTexto(4,150,260,notificacao,0,0,0,18);
	   sprintf(notificacao,"-----------------------------------------------------------------------------------");
	   escreverTexto(4,150,280,notificacao,0,0,0,18);
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
	   sprintf(notificacao,"| 1º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |",PONTUACAO_MAX);
	   escreverTexto(4,150,300,notificacao,0,0,0,16);
	   sprintf(notificacao,"-----------------------------------------------------------------------------------");
	   escreverTexto(4,150,320,notificacao,0,0,0,18);
	   sprintf(notificacao,"| 2º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |",PONTUACAO_MAX);
	   escreverTexto(4,150,340,notificacao,0,0,0,16);
	   sprintf(notificacao,"-----------------------------------------------------------------------------------");
	   escreverTexto(4,150,360,notificacao,0,0,0,18);
	   sprintf(notificacao,"| 3º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |",PONTUACAO_MAX);
	   escreverTexto(4,150,380,notificacao,0,0,0,16);
	   sprintf(notificacao,"-----------------------------------------------------------------------------------");
	   escreverTexto(4,150,400,notificacao,0,0,0,18);
	   sprintf(notificacao,"| 4º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |",PONTUACAO_MAX);
	   escreverTexto(4,150,420,notificacao,0,0,0,16);
	   sprintf(notificacao,"-----------------------------------------------------------------------------------");
	   escreverTexto(4,150,440,notificacao,0,0,0,18);
	   sprintf(notificacao,"| 5º Lugar -   NOMEDEATE21CARACTERES   PONTOS: %u |",PONTUACAO_MAX);
	   escreverTexto(4,150,460,notificacao,0,0,0,16);
	   sprintf(notificacao,"-----------------------------------------------------------------------------------");
	   escreverTexto(4,150,480,notificacao,0,0,0,18);

}
