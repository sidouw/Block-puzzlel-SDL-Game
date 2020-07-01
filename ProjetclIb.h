#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

#define Width 800
#define Hight 720
typedef struct {
	char Name[50];
	char Date[16];
	char score[15];
}Player;
typedef struct
{
	int index;
	char type;
	struct stack  * next;
}stack;
typedef enum
{
	Play,Load,PVC,CPU,HallOfFame,Quit, TotalB
}Choice;
typedef struct { int h, w; }Size;
typedef enum
{
	Red, LightGreen, DarkBlue, Yellow, Orange, DeepPink,Black,DeepBlue,DeepGreen,WBlue,Brown,White,TotalCols
}Colors;

SDL_Color GColor[TotalCols] = { {138, 0, 0, 255},
{154, 205, 50, 255},{53, 53, 240, 255},{204, 204, 30, 255},{240, 150, 6, 255},
{138, 0, 57, 255},{30,30,30,255},{ 0, 63, 111 ,255},{57, 138, 0,255},{0, 138, 138,255},{117, 68, 0,255},{255,255,255,255} };

SDL_Window * Window;
SDL_Renderer * Rendere;
Player Players[5] = { {" ",0} };
int GameQuiteFlag = 1;


void Initialize() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("failed to initialize SDL !! : %s", SDL_GetError());
	}

	else
	{
		Window = SDL_CreateWindow("Block Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Hight, SDL_WINDOW_SHOWN);
		if (Window == NULL)
		{
			printf("failed to Create Window !! : %s", SDL_GetError());
		}
		else
		{
			TTF_Init();
			///SDL_RENDERER_ACCELERATED ||
			Rendere = SDL_CreateRenderer(Window, -1, SDL_RENDERER_PRESENTVSYNC);

		}


	}
}
SDL_Texture * CreateTextTexture(const char text[], SDL_Color TextColor, Size * dem,int size) {
	SDL_Surface * CreatedText = NULL;
	SDL_Texture * Texture = NULL;
	 TTF_Font * TFont = TTF_OpenFont("F.ttf", size);

	if (TFont == NULL) {
		printf("failed to Load Font !! : %s", TTF_GetError());
	}

		CreatedText = TTF_RenderText_Blended(TFont, text, TextColor);


	if (CreatedText == NULL) {
		printf("failed to Create Text !! : %s\n", TTF_GetError());
	}
	else
	{
		Texture = SDL_CreateTextureFromSurface(Rendere, CreatedText);
		if (Texture == NULL) {
			printf("failed to Create Texture !! : %s", SDL_GetError());
		}
		else
		{
			dem->h = CreatedText->h;
			dem->w = CreatedText->w;
			SDL_FreeSurface(CreatedText);
		}
	}
	TTF_CloseFont(TFont);
	return Texture;
}
Size RenderText(int x, int y, const char Text[], Colors TextColor,int size) {

	Size Dem;
	SDL_Texture * TextT = NULL;
	TextT = CreateTextTexture(Text, GColor[TextColor],&Dem,size);
	SDL_Rect Scorerect = { x,y,Dem.w,Dem.h };
	SDL_RenderCopy(Rendere, TextT, NULL, &Scorerect);
	SDL_DestroyTexture(TextT);
	return Dem;
}
stack* newNode(int index,char type)
{
	stack * stackNode = malloc(sizeof(stack));
	stackNode->index = index;
	stackNode->type = type;
	stackNode->next = NULL;
	return stackNode;
}
int isEmpty(stack * root) {
	return !root;
}
int Isinside(int x ,int y ,int h, int w) {
	int Mx, My;
	SDL_GetMouseState(&Mx, &My);

		if (Mx <x+w  && Mx >x  && My <y+h && My >y  )
			return 1;

	return 0;
}
void push(stack** root, int index,char type)
{
	stack* stackNode = newNode(index,type);
	stackNode->next = *root;
	*root = stackNode;
}
void pop(stack** root,int * index,char * type)
{
	stack* temp = NULL;
	temp = *root;
	*root = temp->next;
	*index = temp->index;
	*type = temp->type;
	free(temp);
}
void SaveData() {
	FILE * fp=NULL;
	fp = fopen("Data.bin", "wb");
	if (fp !=NULL) {
		fwrite(Players, sizeof(Player), 4, fp);
		fclose(fp);
	}
	else
	{
		printf(" Failed to create file");
	}
}
void LoadData() {
	FILE * fp = NULL;
	fp = fopen("Data.bin", "rb");

	if (fp) {
		fread(Players, sizeof(Player), 4, fp);
		fclose(fp);
	}
	else
	{
		printf(" Failed to create file");
	}
}
void HallOfFameM() {
	SDL_Event E;
	SDL_SetRenderDrawColor(Rendere, 60, 60, 60, 255);
	SDL_RenderClear(Rendere);
	RenderText(Width / 10, Hight / 5 -50, "Name", Black, 51);
	RenderText(Width / 10+225, Hight / 5 - 50, "Score", Orange, 51);
	RenderText(Width / 10+400, Hight / 5 - 50, "Date", WBlue, 51);
	for (size_t i = 0; i < 5; i++)
	{
		RenderText(Width / 10-50 , Hight / 5 + (i*50) +50, Players[i].Name, Black, 40);
		RenderText(Width / 10 + 230, Hight / 5 + (i * 50) +50, Players[i].score, Orange, 40);
		RenderText(Width / 10 + 370, Hight / 5 + (i * 50) +50, Players[i].Date, WBlue, 40);
	}
	Size dem = RenderText(20, 10, "Back", Black, 51);
	//draws the table
	SDL_SetRenderDrawColor(Rendere, 255, 255, 255, 255);
	SDL_RenderDrawLine(Rendere, 15, 90, 720, 90);
	SDL_RenderDrawLine(Rendere, 15, 170, 720, 170);
	SDL_RenderDrawLine(Rendere, 15, 90, 15, 500);
	SDL_RenderDrawLine(Rendere, 720, 90, 720, 500);
	SDL_RenderDrawLine(Rendere, 15, 500, 720, 500);
	//**************
	for (size_t i = 0; i <= 140; i=i+140)
	{
		SDL_RenderDrawLine(Rendere, 300+i, 90, 300+i, 500);
	}
	SDL_RenderPresent(Rendere);
	while (1)
	{
		SDL_PollEvent(&E);
		if (E.type == SDL_QUIT) {
			GameQuiteFlag = 0;
				return;
		}
		else if (E.type == SDL_MOUSEBUTTONDOWN) {
			if (Isinside(20,10,dem.h, dem.w)) {
				return;
			}
		}
	}
}
void Close() {

	SDL_DestroyRenderer(Rendere);
	SDL_DestroyWindow(Window);
	SDL_Quit();
	TTF_Quit();
}
