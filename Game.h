#include"ProjetclIb.h"
#define BoxSize 50
#define XOffset 100
#define YOffset 100


typedef enum
{
	Resume,Restart,Save, LoadG, Menu, Exit,TotalGChoi
}Pausechoices;

typedef struct
{
	int boxnumber;
	int X[10];
	int Y[10];
	Colors Color;
}piece;

int LoadFlag = 0;


piece Ar[27] =
{ { 1,{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},DarkBlue },
 { 2,{0,BoxSize,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},Orange },
 { 2,{0,0,0,0,0,0,0,0,0},{0,BoxSize,0,0,0,0,0,0,0},Orange },
 { 3,{0,BoxSize,-BoxSize,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},LightGreen },
 { 3,{0,0,0,0,0,0,0,0,0},{0,BoxSize,-BoxSize,0,0,0,0,0,0} ,LightGreen},
 { 3,{-BoxSize,0,0,0,0,0,0,0,0},{0,-BoxSize,0,0,0,0,0,0,0} ,Brown},
 { 3,{0,BoxSize,0,0,0,0,0,0,0},{0,0,BoxSize,0,0,0,0,0,0} ,Brown},
 { 3,{0,-BoxSize,0,0,0,0,0,0,0},{BoxSize,0,0,0,0,0,0,0,0},Brown },
 { 3,{0,BoxSize,0,0,0,0,0,0,0},{-BoxSize,0,0,0,0,0,0,0,0} ,Brown},
 { 4, {0,BoxSize,0,BoxSize,0,0,0,0,0},{0,0,BoxSize,BoxSize,0,0,0,0,0},Yellow },
 { 4, {0,BoxSize,-BoxSize,0,0,0,0,0,0},{0,0,0,BoxSize,0,0,0,0,0},DeepPink },
 { 4, {0,0,0,-BoxSize,0,0,0,0,0},{0,BoxSize,-BoxSize,0,0,0,0,0,0},DeepPink },
 { 4, {0,BoxSize,-BoxSize,0,0,0,0,0,0},{0,0,0,-BoxSize,0,0,0,0,0} ,DeepPink},
 { 4, {0,BoxSize,0,0,0,0,0,0,0},{0,0,BoxSize,-BoxSize,0,0,0,0,0} ,DeepPink},
 { 4, {0,BoxSize,-BoxSize * 2,-BoxSize,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},Yellow },
 { 4, {0,0,0,0,0,0,0,0,0},{0,BoxSize,BoxSize * 2,-BoxSize,0,0,0,0,0} ,Yellow},
 { 5, {0,BoxSize,BoxSize * 2,-BoxSize * 2,-BoxSize,0,0,0,0},{0,0,0,0,0,0,0,0,0},DeepBlue },
 { 5, {0,0,0,0,0,0,0,0,0},{0,BoxSize,-BoxSize,BoxSize * 2,-BoxSize * 2,0,0,0,0} ,DeepBlue},
 { 5, {0,-BoxSize,0,0,-BoxSize * 2,0,0,0,0},{0,0,BoxSize,BoxSize * 2,0,0,0,0,0} ,WBlue},//18
 { 5, {0,BoxSize,BoxSize * 2,0,0,0,0,0,0,0},{0,0,0,BoxSize,BoxSize * 2,BoxSize * 3,0,0,0,0},WBlue },//19
 { 5, {0,BoxSize,BoxSize * 2,0,0,0,0,0,0,0},{0,0,0,-BoxSize,-BoxSize * 2,-BoxSize * 3,0,0,0,0} ,WBlue},//20
 { 5, {0,-BoxSize,0,0,-BoxSize * 2,0,0,0,0},{0,0,-BoxSize,-BoxSize * 2,0,0,0,0,0} ,WBlue},//21
 { 5, {0,-BoxSize,-BoxSize,0,0,0,0,0,0},{0,BoxSize,-BoxSize,BoxSize,-BoxSize,0,0,0,0} ,DeepGreen},//22
 { 5, {0,BoxSize,-BoxSize,BoxSize,-BoxSize,0,0,0,0},{0,-BoxSize,-BoxSize,0,0,0,0,0,0},DeepGreen },//23
 { 5, {BoxSize,BoxSize,0,0,0,0,0,0,0},{BoxSize,-BoxSize,BoxSize,-BoxSize,0,0,0,0,0} ,DeepGreen},
 { 5, {0,BoxSize,-BoxSize,BoxSize,-BoxSize,0,0,0,0},{0,BoxSize,BoxSize,0,0,0,0,0,0}  ,DeepGreen},//25
 { 9, {0,0,0,BoxSize,-BoxSize,BoxSize,-BoxSize,-BoxSize,BoxSize},{0,BoxSize,-BoxSize,-BoxSize,0,BoxSize,BoxSize,-BoxSize,0},Red} };//26

void PlacePiece(int x, int y, piece P, int t[10][10], Colors BoxCol[][10], SDL_Rect rect[][10]) {

	for (size_t i = 0; i < P.boxnumber; i++)
	{
		rect[(x + P.X[i] - XOffset) / BoxSize][(y + P.Y[i] - YOffset) / BoxSize].x = x + P.X[i]+2;
		rect[(x + P.X[i] - XOffset) / BoxSize][(y + P.Y[i] - YOffset) / BoxSize].y = y + P.Y[i]+2;
		rect[(x + P.X[i] - XOffset) / BoxSize][(y + P.Y[i] - YOffset) / BoxSize].h = BoxSize-4;
		rect[(x + P.X[i] - XOffset) / BoxSize][(y + P.Y[i] - YOffset) / BoxSize].w = BoxSize-4;
		t[(x + P.X[i] - XOffset) / BoxSize][(y + P.Y[i] - YOffset) / BoxSize] = 1;
		BoxCol[(x + P.X[i] - XOffset) / BoxSize][(y + P.Y[i] - YOffset) / BoxSize] = P.Color;
	}
}
void Setdrawcolor(Colors color)
{
	switch (color)
	{
	case Red:
		SDL_SetRenderDrawColor(Rendere, 138, 0, 0, 255);
		break;
	case LightGreen:
		SDL_SetRenderDrawColor(Rendere, 154, 205, 50, 255);
		break;
	case DeepGreen:
		SDL_SetRenderDrawColor(Rendere, 57, 138, 0, 255);
		break;
	case DeepBlue:
		SDL_SetRenderDrawColor(Rendere, 0, 63, 111, 255);
		break;
	case WBlue:
		SDL_SetRenderDrawColor(Rendere, 0, 138, 138, 255);
		break;
	case DarkBlue:
		SDL_SetRenderDrawColor(Rendere, 53, 53, 240, 255);
		break;
	case Yellow:
		SDL_SetRenderDrawColor(Rendere, 204, 204, 30, 255);
		break;
	case Orange:
		SDL_SetRenderDrawColor(Rendere, 240, 150, 6, 255);
		break;
	case DeepPink:
		SDL_SetRenderDrawColor(Rendere, 138, 0, 57, 255);
		break;
	case Brown:
		SDL_SetRenderDrawColor(Rendere, 117, 68, 0, 255);
		break;
	case White:
		SDL_SetRenderDrawColor(Rendere, 255, 255,255, 255);
		break;
	}

}
void DrawPiece(int x, int y, piece P, int Placealbe, int chosen) {

	if (Placealbe)
	{
		Setdrawcolor(P.Color);
	}
	else
	{
		SDL_SetRenderDrawColor(Rendere, 66, 66, 69, 255);
	}

	for (size_t i = 0; i < P.boxnumber; i++)
	{
		if (chosen) {
			SDL_Rect rect = { x + P.X[i]+2,y + P.Y[i]+2,BoxSize-4,BoxSize-4 };
			SDL_RenderFillRect(Rendere, &rect);
		}
		else
		{
			piece smallp = P;
			for (size_t j = 0; j < smallp.boxnumber; j++)
			{
				int temp;
				if (smallp.X[j] != 0) {
					temp = smallp.X[j] / BoxSize;
					smallp.X[j] = temp *20;
				}

				if (smallp.Y[j] != 0) {
					temp = smallp.Y[j] / BoxSize;
					smallp.Y[j] = temp *20 ;
				}
			}
			SDL_Rect rect = { x + smallp.X[i]+1,y + smallp.Y[i]+1,20-1,20-1 };
			SDL_RenderFillRect(Rendere, &rect);
		}



	}
}
int IsInsideP(int x, int y, piece p) {
	int Mx, My;
	SDL_GetMouseState(&Mx, &My);
	for (size_t i = 0; i < p.boxnumber; i++)
	{
		if (Mx <(x + p.X[i] + BoxSize) && Mx >(x + p.X[i]) && My <(y + p.Y[i] + BoxSize) && My >(y + p.Y[i]))
			return 1;
	}
	return 0;
}
int IsPossible(int x, int y, int T[10][10], piece p) {

	for (size_t i = 0; i < p.boxnumber; i++)
	{
		if ((x + p.X[i]) < 0 + XOffset
			|| (x + p.X[i]) >= BoxSize * 10 + XOffset
			|| (y + p.Y[i]) < 0 + YOffset
			|| (y + p.Y[i]) >= BoxSize * 10 + YOffset
			|| T[(x + p.X[i]- XOffset) / BoxSize][(y + p.Y[i] - YOffset) / BoxSize] == 1
			)
			return 0;
	}

	return 1;
}
int IsPlaceable (int T[10][10], piece p) {

	for (int i = 0; i < 10; i = i + 1)
	{
		for (size_t t = 0; t < 10; t++)
		{
			if (IsPossible(i * BoxSize+XOffset, t * BoxSize+YOffset, T, p)) {
				return 1;
			}

		}
	}
	return 0;
}
int  removelines(stack **root, int  T[10][10], SDL_Rect  rect[10][10]) {
	int index;
	char type;
	int score =0;

	while (!isEmpty(*root))
	{
		pop(root, &index, &type);
		if (type == 'l') {
			for (size_t i = 0; i <= 9; i++)
			{
				T[index][i] = 0;
				rect[index][i].h = 0;
				rect[index][i].w = 0;
			}
			score++;
		}
		if (type == 'c') {
			for (size_t i = 0; i <= 9; i++)
			{
				T[i][index] = 0;
				rect[i][index].h = 0;
				rect[i][index].w = 0;
			}
			score++;
		}
	}
	switch (score)
	{
	case 1: return 100;
		break;
	case 2: return 300;
		break;
	case 3: return 600;
		break;
	case 4: return 1000;
		break;
	case 5: return 1500;
		break;
	default: return 0;
		break;
	}

}
void Savegame(int T[][10], Colors BoxColor[][10], piece pieces[], SDL_Rect rect[][10], int score) {
	FILE * fp;
	fp = fopen("save.bin", "wb");
	if (!fp) {
		printf("Failed to Create file");
		return;
	}
	for (int i = 0; i < 10; i++) {
		fwrite(T[i], sizeof(int), 10, fp);
	}
	for (int i = 0; i < 10; i++) {
		fwrite(BoxColor[i], sizeof(Colors), 10, fp);
	}
	for (int i = 0; i < 10; i++) {
		fwrite(rect[i], sizeof(SDL_Rect), 10, fp);
	}
	fwrite(pieces, sizeof(piece), 3, fp);
	fwrite(&score, sizeof(int), 1, fp);
	fclose(fp);
}
void Loadgame(int T[][10], Colors BoxColor[][10], piece pieces[], SDL_Rect rect[][10], int * score) {
	FILE * fp;
	fp = fopen("save.bin", "rb");
	if (!fp) {
		printf("Failed to open file");
		return;
	}
	for (int i = 0; i < 10; i++) {
		fread(T[i], sizeof(int), 10, fp);
	}
	for (int i = 0; i < 10; i++) {
		fread(BoxColor[i], sizeof(Colors), 10, fp);
	}
	for (int i = 0; i < 10; i++) {
		fread(rect[i], sizeof(SDL_Rect), 10, fp);
	}
	fread(pieces, sizeof(piece), 3, fp);
	fread(score, sizeof(int), 1, fp);
	fclose(fp);
}
void Resetgame(int T[][10],piece pieces[], SDL_Rect rect[][10], int * score) {

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			T[i][j] = 0;
			rect[i][j].h = 0;
			rect[i][j].w = 0;
		}
	}
	*score = 0;
	for (size_t i = 0; i < 3; i++)
	{
		pieces[i] = Ar[rand()%26];
	}
}
void TakeScreen() {
	SDL_Surface* pScreenShot = SDL_CreateRGBSurface(0, Width, Hight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	if (pScreenShot)
	{
		// Read the pixels from the current render target and save them onto the surface
		SDL_RenderReadPixels(Rendere, NULL, 0, pScreenShot->pixels, pScreenShot->pitch);

		// Create the bmp screenshot file
		SDL_SaveBMP(pScreenShot, "sdio.bmp");

		// Destroy the screenshot surface
		SDL_FreeSurface(pScreenShot);
	}
}
Pausechoices Pausepropt() {
	int Quite = 1, Render = 1;
	SDL_Rect rect = { (Width /5+50), (Hight / 5-20) ,400,450};
	SDL_Event E;
	Size Bottun[TotalGChoi] = { 5 };
	while (Quite)
	{
		SDL_PollEvent(&E);
		if (E.type == SDL_QUIT) {
			return Exit;
		}else if (E.type == SDL_MOUSEBUTTONDOWN) {
			if (Isinside((Width / 4) + 60, (Hight / 5) + 60, Bottun[Resume].h, Bottun[Resume].w)) {
				return -1;
			}
			else if (Isinside((Width / 4) + 60, (Hight / 5) + 120, Bottun[Restart].h, Bottun[Restart].w))
			{
				return Restart;
			}
			else if (Isinside((Width / 4) + 60, (Hight / 5) + 180, Bottun[Save].h, Bottun[Save].w))
			{
				return Save;
			}
			else if (Isinside((Width / 4) + 60, (Hight / 5) + 240, Bottun[LoadG].h, Bottun[LoadG].w))
			{
				return LoadG;
			}
			else if (Isinside((Width / 4) + 60, (Hight / 5) + 300, Bottun[Menu].h, Bottun[Menu].w))
			{
				return Menu;
			}
			else if (Isinside((Width / 4) + 60, (Hight / 5) + 360, Bottun[Exit].h, Bottun[Exit].w))
			{
				return Exit;
			}

		}

		if (Render) {
			srand(time(NULL));
			SDL_SetRenderDrawColor(Rendere, 240, 230, 255, 160);
			SDL_SetRenderDrawBlendMode(Rendere, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(Rendere, &rect);
			RenderText(Width / 3, Hight / 6, "Pause Menu", (rand() *SDL_GetTicks()) % TotalCols, 51);
			Bottun[Resume] = RenderText((Width / 4) + 60, (Hight / 5) + 60, "Resume", Red, 51);
			Bottun[Restart] = RenderText((Width / 4) + 60, (Hight / 5) + 120, "Restart",DeepBlue, 51);
			Bottun[Save] = RenderText((Width / 4) + 60, (Hight / 5) + 180, "Save",Orange, 51);
			Bottun[LoadG] = RenderText((Width / 4) + 60, (Hight / 5) + 240, "Load Game", DeepPink, 51);
			Bottun[Menu] = RenderText((Width / 4) + 60, (Hight / 5) + 300, "Main Menu", DeepGreen, 51);
			Bottun[Exit] = RenderText((Width / 4) + 60, (Hight / 5) + 360, "Exit",Black, 51);

			SDL_RenderPresent(Rendere);
			Render = 0;
		}
	}
}
void AddPlayer(Player P,int index) {
	for (size_t i = 4; i > index; i--)
	{
		Players[i] = Players[i-1];
	}
	Players[index] = P;
}
char * GetText (int x ,int y,int F) {

	SDL_Event e;
	char * text= NULL;
	text = malloc( 10 * sizeof(char));
	for( int i = 0 ; i<=10;i++)
        text[i] = '\0';

	SDL_Rect TextB = { x,y,500,60};
	int i = 0,Render = 1;
	SDL_Color c = { 19,94,143,255 };
	while (1)
	{

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) {
				GameQuiteFlag = 0;
				return " ";
			}
			else if (e.type == SDL_KEYDOWN)
			{
				//Handle backspace
				if (e.key.keysym.sym == SDLK_BACKSPACE && strlen(text) > 0)
				{
					if (i > 0) {
						text[i - 1] = '\0';
						i--;
					}
					else if (i == 0)
					{
						text[0] = ' ';
					}
					Render = 1;

				}
				else if (e.key.keysym.sym == SDLK_RETURN)
				{
					return text;
				}
			}
			else if (e.type == SDL_TEXTINPUT)
			{
				//Not copy or pasting
				if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
				{
					if (i < 10) {
						text[i] = *e.text.text;
						i++;
						Render = 1;
					}

				}
			}

		}
		if (Render) {
			SDL_SetRenderDrawColor(Rendere, 255, 255, 255, 255);
			SDL_RenderFillRect(Rendere, &TextB);
			RenderText(x, y, text, Black, F);
			SDL_RenderPresent(Rendere);
			Render = 0;
		}

	}
}
void CheckGrid(int T[][10],stack ** root) {
	for (size_t i = 0; i < 10; i++)
	{
		int flagl = 1, flagc = 1;
		for (size_t l = 0; l < 10; l++)
		{
			if (T[l][i] != 1) { flagc = 0; }
			if (T[i][l] != 1) { flagl = 0; }
		}
		if (flagl) {
			push(root, i, 'l');
			flagl = 0;
		}
		if (flagc) {
			push(root, i, 'c');
			flagc = 0;
		}
	}
}
void Game() {

	piece pieces[3];
	SDL_Rect rect[10][10] = { {{0}} };
	SDL_Event E;
	Colors BoxColor[10][10];
	stack * LinesNdColums = NULL;
	int T[10][10] = { 0 }, x = 0, y = 0, score = 0, CurrentP = 0, Gamelost = 0;
	int Quite = 1;
	int MoveFlag = 0, SaveFlag = 0,Render = 1;
	char scoreT[10];
	srand(time(NULL));
	pieces[0] = Ar[rand() % 27];
	pieces[1] = Ar[rand() % 27];
	pieces[2] = Ar[rand() % 27];
	//checks to load the game or not
	if (LoadFlag)
	{
		Loadgame(T, BoxColor, pieces, rect, &score);
	}
	//Game Loop
	while (Quite == 1)
	{
		while (SDL_PollEvent(&E) != 0)
		{
			if (E.type == SDL_QUIT)
			{
				GameQuiteFlag = 0;
				return;
			}
			else if (E.type == SDL_MOUSEBUTTONDOWN)
			{
				for (size_t i = 0; i < 3; i++)
				{
					if (IsInsideP(70 + (i * 145) + XOffset, (BoxSize * 11) + YOffset, pieces[i]) && IsPlaceable(T, pieces[i]))
					{
						MoveFlag = 1;
						CurrentP = i;
						Render = 1;
					}

				}
				if (Isinside(BoxSize * 11 + XOffset+30, 10,60,60))
				{

					switch (Pausepropt())
					{
					case Save:
						Savegame(T, BoxColor, pieces, rect, score);
						break;
					case Restart:
						Resetgame(T, pieces, rect, &score);
						break;
					case LoadG:
						Loadgame(T, BoxColor, pieces, rect, &score);
						break;
					case Menu:
						Quite = 0;
						break;
					case Exit:
						GameQuiteFlag = 0;
						Quite = 0;
						return;
						break;
					}
				}
			}
			else if (E.type == SDL_MOUSEBUTTONUP)
			{
				SDL_GetMouseState(&x, &y);
				x = floor(x / BoxSize) * BoxSize;
				y = floor(y / BoxSize) * BoxSize;
				if (IsPossible(x, y, T, pieces[CurrentP]) && MoveFlag)  {
					PlacePiece(x, y, pieces[CurrentP], T, BoxColor, rect);
					score = score + (pieces[CurrentP].boxnumber * 10);
					srand(time(NULL));
					pieces[CurrentP] = Ar[rand() % 27];
					CheckGrid(T, &LinesNdColums);
					score = score + removelines(&LinesNdColums, T, rect);
					Gamelost = 1;
				}

				MoveFlag = 0;
				Render = 1;
			}
			else if (E.type == SDL_KEYDOWN )
			{

				if (E.key.keysym.sym == SDLK_x)
					score += 119;
				Render = 1;
			}
		}

		//Render the Game
		if (Render ||MoveFlag) {
			SDL_SetRenderDrawColor(Rendere, 40, 40, 40, 255);
			SDL_RenderClear(Rendere);
			SDL_SetRenderDrawColor(Rendere, 255, 8, 255, 255);
			//draw lines
			for (size_t i = 0; i <= BoxSize * 10; i += BoxSize)
			{
				Setdrawcolor(White);
				SDL_RenderDrawLine(Rendere, i + XOffset, YOffset, i + XOffset, BoxSize * 10 + YOffset);
				SDL_RenderDrawLine(Rendere, XOffset, i + YOffset, BoxSize * 10 + XOffset, i + YOffset);

			}
			//draw boxes
			for (size_t i = 0; i <= 9; i++)
			{
				for (size_t j = 0; j <= 9; j++)
				{

					Setdrawcolor(BoxColor[i][j]);
					SDL_RenderFillRect(Rendere, &rect[i][j]);
				}

			}
			if (MoveFlag)
			{
				DrawPiece(E.motion.x - (BoxSize / 2), E.motion.y - (BoxSize / 2), pieces[CurrentP], IsPlaceable (T, pieces[CurrentP]), 1);
				for (size_t i = 0; i < 3; i++)
				{
					if (i != CurrentP)
						DrawPiece(70 + (i * 145) + XOffset, (BoxSize * 11) + YOffset, pieces[i], IsPlaceable (T, pieces[i]), 0);
				}
			}
			else
			{
				for (size_t i = 0; i < 3; i++)
				{
					DrawPiece(70 + (i * 145) + XOffset, (BoxSize * 11) + YOffset, pieces[i], IsPlaceable (T, pieces[i]), 0);
				}
			}
			sprintf(scoreT, "%d", score);
			RenderText(XOffset *4,10, "Score:", White, 40);
			RenderText(XOffset *5+30,10, scoreT, pieces[CurrentP].Color, 40);
			RenderText(XOffset-80 , 10,"Best Score:", White, 40);
			RenderText(XOffset*2 +50, 10, Players[0].score, pieces[CurrentP].Color, 40);
			RenderText(BoxSize * 11 + XOffset+30, 10, "||", White,40);
			SDL_RenderPresent(Rendere);
			Render = 0;

		}

		//Checks if the Game is over
		if (Gamelost)
		{
			if (!IsPlaceable (T, pieces[0]) && !IsPlaceable (T, pieces[1]) && !IsPlaceable (T, pieces[2]))
			{

				int isHigh = 0, i = 0;
				while (i < 5 && !isHigh)
				{
					if (score > atoi(Players[i].score))
					{
						isHigh = 1;
					}
					i++;
				}

				char Temp[30] = " You Scored : ";
				strcat(Temp, scoreT);
				SDL_SetRenderDrawColor(Rendere, 255, 255, 255, 255);
				SDL_RenderClear(Rendere);
				RenderText(Width / 6-50, Hight / 8, Temp, Black, 65);
				SDL_RenderPresent(Rendere);
				if (isHigh) {
					RenderText(Width / 6, Hight / 8 + 200, "Enter Your Name", Black, 51);
					Player P;
					strcpy(P.score, scoreT);
					strcpy(P.Date, __DATE__);
					strcpy(P.Name,GetText(Width / 6 , Hight / 8 + 270, 45));
					AddPlayer(P, i - 1);
					SaveData();
				}
				SDL_Delay(800);
				Quite = 0;
			}
			Gamelost = 0;
		}

	}

}




