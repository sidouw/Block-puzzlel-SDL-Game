#include"Game.h"


int PlacePieceRandomly(int T[][10], piece pieces[], int ChosenPiece, Colors BoxColor[][10], SDL_Rect rect[][10]) {

	int Placed = 0, x, y;
	srand(time(NULL));
	while (Placed == 0)
	{
		if (IsPlaceable(T, pieces[ChosenPiece]))
		{
			x = (rand() % 10)* BoxSize + XOffset, y = (rand() % 10)*BoxSize + YOffset;
			if (IsPossible(x, y, T, pieces[ChosenPiece]))
			{
				PlacePiece(x, y, pieces[ChosenPiece], T, BoxColor, rect);
				pieces[ChosenPiece] = Ar[rand() % 27];
				Placed = 1;
				return Placed;
			}

		}
		else
		{
			return Placed;
		}

	}

}

//Gets Piece Best placement
int PieceScore(int x, int y, int T[][10], piece P) {
	int score = 0;
	for (size_t i = 0; i < P.boxnumber; i++)
	{
		if (((x + P.X[i] - XOffset) / BoxSize) + 1 > 9 || T[((x + P.X[i] - XOffset) / BoxSize) + 1][((y + P.Y[i] - YOffset) / BoxSize)])
			score++;
		if (((x + P.X[i] - XOffset) / BoxSize) - 1 < 0 || T[((x + P.X[i] - XOffset) / BoxSize) - 1][((y + P.Y[i] - YOffset) / BoxSize)])
			score++;
		if (((y + P.X[i] - XOffset) / BoxSize) + 1 > 9 || T[((x + P.X[i] - XOffset) / BoxSize)][((y + P.Y[i] - YOffset) / BoxSize) + 1])
			score++;
		if (((y + P.X[i] - XOffset) / BoxSize) - 1 < 0 || T[((x + P.X[i] - XOffset) / BoxSize)][((y + P.Y[i] - YOffset) / BoxSize) - 1])
			score++;

	}
	return score;
}
Pausechoices CPausepropt() {
	int Quite = 1, Render = 1, w, h;
	SDL_GetWindowSize(Window, &w, &h);
	SDL_Rect rect = { w / 3,h / 6 ,400,350 };
	SDL_Event E;
	Size Bottun[TotalGChoi] = { 5 };
	while (Quite)
	{
		SDL_PollEvent(&E);
		if (E.type == SDL_QUIT) {
			return Exit;
		}
		else if (E.type == SDL_MOUSEBUTTONDOWN) {
			if (Isinside(w / 3 + 60, h / 6 + 60, Bottun[Resume].h, Bottun[Resume].w)) {
				return -1;
			}
			else if (Isinside(w / 3 + 60, h / 6 + 120, Bottun[Restart].h, Bottun[Restart].w))
			{
				return Restart;
			}
			else if (Isinside(w / 3 + 60, h / 6 + 180, Bottun[Menu].h, Bottun[Menu].w))
			{
				return Menu;
			}
			else if (Isinside(w / 3 + 60, h / 6 + 240, Bottun[Exit].h, Bottun[Exit].w))
			{
				return Exit;
			}

		}

		if (Render) {
			srand(time(NULL));
			SDL_SetRenderDrawColor(Rendere, 240, 230, 255, 160);
			SDL_SetRenderDrawBlendMode(Rendere, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(Rendere, &rect);
			RenderText(w / 3 + 60, h / 6, "Pause Menu", (rand() *SDL_GetTicks()) % TotalCols, 51);
			Bottun[Resume] = RenderText(w / 3 + 60, h / 6 + 60, "Resume", Red, 51);
			Bottun[Restart] = RenderText(w / 3 + 60, h / 6 + 120, "Restart", DeepBlue, 51);
			Bottun[Menu] = RenderText(w / 3 + 60, h / 6 + 180, "Main Menu", DeepGreen, 51);
			Bottun[Exit] = RenderText(w / 3 + 60, h / 6 + 240, "Exit", Black, 51);
			SDL_RenderPresent(Rendere);
			Render = 0;
		}
	}
}
void AIGame() {

	piece pieces[3];
	SDL_Rect rect[10][10] = { {{0}} };
	SDL_Event E;
	Colors BoxColor[10][10];
	stack * PotencialPlaces = NULL, *root = NULL, *ValidPlaces = NULL;
	int T[10][10] = { 0 }, x = 0, y = 0, score = 0, Gamelost = 0, ChosenPiece = 2;
	int Quite = 1;
	int Placed = 0;
	int Pscore = 0, Render = 1;
	char scoreT[10];
	srand(time(NULL));
	pieces[0] = Ar[rand() % 27];
	pieces[1] = Ar[rand() % 27];
	pieces[2] = Ar[rand() % 27];

	//AI Game Loop
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
				if (Isinside(BoxSize * 11 + XOffset + 30, 10, 60, 60))
				{

					switch (CPausepropt())
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


		}


		int Boxnumber = 0;
		for (size_t i = 0; i < 3; i++)
		{
			if (pieces[i].boxnumber > Boxnumber && IsPlaceable(T, pieces[i]))
			{
				Boxnumber = pieces[i].boxnumber;
				ChosenPiece = i;
			}
		}

		for (size_t i = 0; i < 10; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				if (T[i][j] == 0) {
					push(&PotencialPlaces,i,j);
				}
			}

		}


		Pscore = 0;
		while (!isEmpty(PotencialPlaces))
		{
			int Lx=0, Ly=0;
			char k;
			pop(&PotencialPlaces,&Lx,&k);
			Ly = k;
			Ly = Ly * BoxSize + YOffset;
			Lx = Lx * BoxSize + XOffset;
			for (size_t i = 0; i < 3; i++)
			{
				if (IsPlaceable(T, pieces[i]) && IsPossible(Lx,Ly,T,pieces[i]) )
				{
					if (Pscore < PieceScore(Lx, Ly, T, pieces[i])) {
						Pscore = PieceScore(Lx, Ly, T, pieces[i]);
						ChosenPiece = i;
						x = Lx; y = Ly;
					}
				}
			}
		}

		if (isEmpty(PotencialPlaces)) {
			SDL_Delay(800);
			PlacePiece(x, y, pieces[ChosenPiece], T, BoxColor, rect);
			score = score + (pieces[ChosenPiece].boxnumber * 10);
			pieces[ChosenPiece] = Ar[rand() % 27];
			CheckGrid(T, &root);
			score += removelines(&root, T, rect);
			Render = 1;

		}


		//Render the game
		if (Render)
		{

			SDL_SetRenderDrawColor(Rendere, 40, 40, 40, 255);
			SDL_RenderClear(Rendere);
			SDL_SetRenderDrawColor(Rendere, 255, 8, 255, 255);
			//draw lines
			for (size_t i = 0; i <= BoxSize * 10; i += BoxSize)
			{
				Setdrawcolor(pieces[ChosenPiece].Color);
				SDL_RenderDrawLine(Rendere, i + XOffset, YOffset, i + XOffset, BoxSize * 10 + YOffset);
				SDL_RenderDrawLine(Rendere, XOffset, i + YOffset, BoxSize * 10 + XOffset, i + YOffset);
			}
			//draw the boxs
			for (size_t i = 0; i <= 9; i++)
			{
				for (size_t j = 0; j <= 9; j++)
				{

					Setdrawcolor(BoxColor[i][j]);
					SDL_RenderFillRect(Rendere, &rect[i][j]);
				}

			}


			for (size_t i = 0; i < 3; i++)
			{
				DrawPiece(70 + (i * 145) + XOffset, (BoxSize * 11) + YOffset, pieces[i], IsPlaceable(T, pieces[i]), 0);
			}

			sprintf(scoreT, "%d", score);
			RenderText(XOffset * 4, 10, "Score:", White, 40);
			RenderText(XOffset * 5 + 30, 10, scoreT, pieces[ChosenPiece].Color, 40);
			RenderText(XOffset - 80, 10, "Best Score:", White, 40);
			RenderText(XOffset * 2 + 50, 10, Players[0].score, pieces[ChosenPiece].Color, 40);
			RenderText(BoxSize * 11 + XOffset + 30, 10, "||", White, 40);
			SDL_RenderPresent(Rendere);
		}





		//Checks if the Game is over
		if (!IsPlaceable(T, pieces[0]) && !IsPlaceable(T, pieces[1]) && !IsPlaceable(T, pieces[2]))
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
			if (isHigh) {
				Player P;
				strcpy(P.score, scoreT);
				strcpy(P.Date, __DATE__);
				strcpy(P.Name,"Cpu");
				AddPlayer(P, i - 1);
				SaveData();
			}
			char Temp[30] = "The Cpu Scored : ";
			strcat(Temp, scoreT);
			SDL_SetRenderDrawColor(Rendere, 255, 255, 255, 255);
			SDL_RenderClear(Rendere);
			RenderText(Width / 6, Hight / 5, "Game Over", Black, 51);
			RenderText(Width / 6, Hight / 5 + 100, Temp, Black, 51);
			SDL_RenderPresent(Rendere);
			SDL_Delay(2000);
			Quite = 0;
		}

	}




}
