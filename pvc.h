#include"AI.h"
#define POffset 650


void PVCResetgame(int T[][10], piece pieces[], SDL_Rect rect[][10], int * score, int TP[][10], piece Ppieces[], SDL_Rect Prect[][10], int * Pscore) {

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			T[i][j] = 0;
			rect[i][j].h = 0;
			rect[i][j].w = 0;
			TP[i][j] = 0;
			Prect[i][j].h = 0;
			Prect[i][j].w = 0;
		}

	}
	*score = 0;
	*Pscore = 0;
	for (size_t i = 0; i < 3; i++)
	{
		Ppieces[i] =pieces[i] = Ar[rand() % 26];
	}
}


int IsPossibleP(int x, int y, int T[10][10], piece p) {

	for (size_t i = 0; i < p.boxnumber; i++)
	{
		if ((x + p.X[i]) < 0 +  POffset
			|| (x + p.X[i]) >= BoxSize * 10 +  POffset
			|| (y + p.Y[i]) < 0 + YOffset
			|| (y + p.Y[i]) >= BoxSize * 10 + YOffset
			|| T[(x + p.X[i] -  POffset) / BoxSize][(y + p.Y[i] - YOffset) / BoxSize] == 1
			)
			return 0;
	}

	return 1;
}
void PPlacePiece(int x, int y, piece P, int t[10][10], Colors BoxCol[][10], SDL_Rect rect[][10]) {

	for (size_t i = 0; i < P.boxnumber; i++)
	{
		rect[(x + P.X[i] - POffset) / BoxSize][(y + P.Y[i] - YOffset) / BoxSize].x = x + P.X[i] + 2;
		rect[(x + P.X[i] - POffset) / BoxSize][(y + P.Y[i] - YOffset) / BoxSize].y = y + P.Y[i] + 2;
		rect[(x + P.X[i] -POffset) / BoxSize][(y + P.Y[i] - YOffset) / BoxSize].h = BoxSize - 4;
		rect[(x + P.X[i] - POffset) / BoxSize][(y + P.Y[i] - YOffset) / BoxSize].w = BoxSize - 4;
		t[(x + P.X[i] - POffset) / BoxSize][(y + P.Y[i] - YOffset) / BoxSize] = 1;
		BoxCol[(x + P.X[i] - POffset) / BoxSize][(y + P.Y[i] - YOffset) / BoxSize] = P.Color;
	}
}

void pvc() {
	piece pieces[3],Ppieces[3];
	SDL_Rect rect[10][10] = { {{0}} }, Prect[10][10] = { {{0}} };
	SDL_Event E;
	Colors BoxColor[10][10], PBoxColor[10][10];
	stack * LinesNdColums = NULL;
	stack * PotencialPlaces = NULL, *root = NULL, *ValidPlaces = NULL;
	int T[10][10] = { 0 }, x = 0, y = 0, score = 0, CurrentP = 0, Gamelost = 0, ChosenPiece = 2, Pscore=0, TP[10][10] = { 0 },PlayerScore =0;
	int Quite = 1,PTurn =0;
	int MoveFlag = 0, SaveFlag = 0, Render = 1;
	char scoreT[10];
	srand(time(NULL));
	Ppieces[0] =pieces[0] = Ar[rand() % 27];
	Ppieces[1] =pieces[1] = Ar[rand() % 27];
	Ppieces[2] =pieces[2] = Ar[rand() % 27];
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
					if (IsInsideP(70 + (i * 145) + POffset, (BoxSize * 11) + YOffset, Ppieces[i]) && IsPlaceable(TP, Ppieces[i]) && PTurn)
					{
						MoveFlag = 1;
						CurrentP = i;
						Render = 1;
					}
				}
				if (Isinside(BoxSize * 10, 10, 60, 60))
				{
					switch (CPausepropt())
					{
					case Restart:
						PVCResetgame(T, pieces, rect, &score, TP, Ppieces, Prect, &Pscore);
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
				if (IsPossibleP(x, y, TP, Ppieces[CurrentP]) && MoveFlag) {

					PPlacePiece(x, y, Ppieces[CurrentP], TP, PBoxColor, Prect);
					Ppieces[CurrentP] = pieces[ChosenPiece];
					PTurn = 0;
					PlayerScore = PlayerScore + (Ppieces[CurrentP].boxnumber * 10);
					srand(time(NULL));
					CheckGrid(TP, &LinesNdColums);
					PlayerScore = PlayerScore + removelines(&LinesNdColums, TP, Prect);
					Gamelost = 1;
				}

				MoveFlag = 0;
				Render = 1;
			}
			else if (E.type == SDL_KEYDOWN)
			{

				if (E.key.keysym.sym == SDLK_x)
					score += 119;
				Render = 1;
			}
		}


		//AI Gameplay
		//*******************************************************************************************
		if (!PTurn) {
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
						push(&PotencialPlaces, i, j);
					}
				}

			}

			Pscore = 0;
			while (!isEmpty(PotencialPlaces))
			{
				int Lx = 0, Ly = 0;
				char k;
				pop(&PotencialPlaces, &Lx, &k);
				Ly = k;
				Ly = Ly * BoxSize + YOffset;
				Lx = Lx * BoxSize + XOffset;
				for (size_t i = 0; i < 3; i++)
				{
					if (IsPlaceable(T, pieces[i]) && IsPossible(Lx, Ly, T, pieces[i]))
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
				PlacePiece(x, y, pieces[ChosenPiece], T, BoxColor, rect);
				pieces[ChosenPiece]  = Ar[rand() % 27];
				PTurn = 1;
				Gamelost = 1;
				score = score + (pieces[ChosenPiece].boxnumber * 10);
				CheckGrid(T, &root);
				score += removelines(&root, T, rect);
				Render = 1;

			}
		}
		//***********************************************************************************************


		//Render the Game
		if (Render || MoveFlag) {
			SDL_SetRenderDrawColor(Rendere,40,40,40, 255);
			SDL_RenderClear(Rendere);
			SDL_SetRenderDrawColor(Rendere, 255, 8, 255, 255);
			//draw lines
			for (size_t i = 0; i <= BoxSize * 10; i += BoxSize)
			{
				Setdrawcolor(pieces[ChosenPiece].Color);
				SDL_RenderDrawLine(Rendere, i + XOffset, YOffset, i + XOffset, BoxSize * 10 + YOffset);
				Setdrawcolor(Ppieces[CurrentP].Color);
				SDL_RenderDrawLine(Rendere, i + POffset, YOffset, i + POffset, BoxSize * 10 + YOffset);

			}
			for (size_t i = 0; i <= BoxSize * 10; i += BoxSize)
			{
				Setdrawcolor(pieces[ChosenPiece].Color);
				SDL_RenderDrawLine(Rendere, XOffset, i + YOffset, BoxSize * 10 + XOffset, i + YOffset);
				Setdrawcolor(Ppieces[CurrentP].Color);
				SDL_RenderDrawLine(Rendere, POffset, i + YOffset, BoxSize * 10 + POffset, i + YOffset);

			}

			//draw the boxs
			for (size_t i = 0; i <= 9; i++)
			{
				for (size_t j = 0; j <= 9; j++)
				{

					Setdrawcolor(BoxColor[i][j]);
					SDL_RenderFillRect(Rendere, &rect[i][j]);
					Setdrawcolor(PBoxColor[i][j]);
					SDL_RenderFillRect(Rendere, &Prect[i][j]);
				}

			}

			//AIPieces
			for (size_t i = 0; i < 3; i++)
			{
				if( !(i == ChosenPiece && PTurn) || score == 0)
				DrawPiece(70 + (i * 145) + XOffset, (BoxSize * 11) + YOffset, pieces[i], IsPlaceable(T, pieces[i]), 0);
			}
			if (MoveFlag)
			{
				DrawPiece(E.motion.x - (BoxSize / 2), E.motion.y - (BoxSize / 2), Ppieces[CurrentP], IsPlaceable(TP, Ppieces[CurrentP]), 1);
				for (size_t i = 0; i < 3; i++)
				{
					if (i != CurrentP)
						DrawPiece(70 + (i * 145) +POffset, (BoxSize * 11) + YOffset, Ppieces[i], IsPlaceable(TP, Ppieces[i]), 0);
				}
			}
			else
			{
				for (size_t i = 0; i < 3; i++)
				{
					DrawPiece(70 + (i * 145) + POffset, (BoxSize * 11) + YOffset, Ppieces[i], IsPlaceable(TP, Ppieces[i]), 0);
				}
			}

			//AIScore
			sprintf(scoreT, "%d", score);
			RenderText(XOffset, 10, "score:", White, 50);
			RenderText(XOffset * 2+50 , 10, scoreT, pieces[ChosenPiece].Color, 50);
			RenderText(BoxSize * 10, 10, "||", Red, 51);
			//Player Score
			sprintf(scoreT, "%d", PlayerScore);
			RenderText(POffset , 10, "score:", White, 50);
			RenderText( POffset+150 , 10, scoreT, Ppieces[CurrentP].Color, 50);
			SDL_RenderPresent(Rendere);
			Render = 0;

		}

		//Checks if the Game is over
		if (Gamelost)
		{
			if (!IsPlaceable(T, pieces[0]) && !IsPlaceable(T, pieces[1]) && !IsPlaceable(T, pieces[2])) {

				char Temp[30] = " You Scored : ";
				strcat(Temp, scoreT);
				SDL_SetRenderDrawColor(Rendere, 255, 255, 255, 255);
				SDL_RenderClear(Rendere);
				RenderText(Width / 6, Hight / 5, "Game Over You Won ", Black, 100);
				RenderText(Width / 6, Hight / 5 + 200, Temp, Black, 51);
				SDL_RenderPresent(Rendere);
				SDL_Delay(2000);
				Quite = 0;
			}
			if (!IsPlaceable(TP, Ppieces[0]) && !IsPlaceable(TP, Ppieces[1]) && !IsPlaceable(TP, Ppieces[2])) {

				char Temp[30] = " You Scored : ";
				strcat(Temp, scoreT);
				SDL_SetRenderDrawColor(Rendere, 255, 255, 255, 255);
				SDL_RenderClear(Rendere);
				RenderText(Width / 6, Hight / 5, "Game Over You Lost ", Black, 100);
				RenderText(Width / 6, Hight / 5 + 200, Temp, Black, 51);
				SDL_RenderPresent(Rendere);
				SDL_Delay(2000);
				Quite = 0;
			}
			Gamelost = 0;
		}

	}


}
