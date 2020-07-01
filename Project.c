///Chaouadi sidahmed / Mallem Sofiane
#include"pvc.h"


int main(int arg , char * argc []) {

	Initialize();
	TTF_Font * Font;
	LoadData();
	SDL_Event E;
	Size Bottun[TotalB] = { { 0} };
	int index=0,Render = 1,change = 1,col=0;
	int BC[TotalB] = { 6,6,6,6,6,6 }, BCL[TotalB] = { 1,1,1,1,1,1 };

	while (GameQuiteFlag)
	{
		while (SDL_PollEvent(&E) != 0)
		{
			if (E.type == SDL_QUIT) {
				GameQuiteFlag = 0;
			}
			else if (E.type == SDL_MOUSEBUTTONDOWN)
			{

					if (Isinside(Width / 8, Hight / 9-50, Bottun[Play].h, Bottun[Play].w)) {
						LoadFlag = 0;
						Game();
						Render = 1;

					}
					else if (Isinside(Width / 8, Hight / 9+50 , Bottun[Load].h, Bottun[Load].w))
					{
						LoadFlag = 1;
						Game();
						Render = 1;

					}
					else if (Isinside(Width / 8, Hight / 9 + 150, Bottun[PVC].h, Bottun[PVC].w))
					{
						SDL_SetWindowSize(Window, 1200, 720);
						SDL_SetWindowPosition(Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
						pvc();
						SDL_SetWindowSize(Window, Width, Hight);
						SDL_SetWindowPosition(Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
						Render = 1;

					}
					else if (Isinside(Width / 8, Hight / 9 + 250, Bottun[CPU].h, Bottun[CPU].w))
					{
						AIGame();
						Render = 1;
					}
					else if (Isinside(Width / 8, Hight / 9 + 350, Bottun[HallOfFame].h, Bottun[HallOfFame].w))
					{
						HallOfFameM();
						Render = 1;
					}
					else if (Isinside(Width / 8, Hight / 9 +450, Bottun[Quit].h, Bottun[Quit].w))
					{
						GameQuiteFlag = 0;
						Render = 1;
					}


			}
		}

		if (E.motion.x != 0 && E.motion.y != 0)
		{
			if (Isinside(Width / 8, Hight / 9 - 50, Bottun[Play].h, Bottun[Play].w)) {
				if (BCL[Play]) {
					col++;
					BC[Play] = col % TotalCols;
					BCL[Play] = 0;
					Render = 1;
					BCL[Load] = BCL[PVC] = BCL[CPU] = BCL[HallOfFame] = BCL[Quit] = 1;
				}
			}
			else if (Isinside(Width / 8, Hight / 9 +50, Bottun[Load].h, Bottun[Load].w))
			{
				if (BCL[Load]) {
					col++;
					BC[Load] = col % TotalCols;
					BCL[Load] = 0;
					Render = 1;
					BCL[Play] = BCL[PVC] = BCL[CPU] = BCL[HallOfFame] = BCL[Quit] = 1;
				}

			}
			else if (Isinside(Width / 8, Hight / 9 + 150, Bottun[PVC].h, Bottun[PVC].w) )
			{
				if (BCL[PVC]) {
					col++;
					BC[PVC] = col % TotalCols;
					BCL[PVC] = 0;
					Render = 1;
					BCL[Load] = BCL[Play] = BCL[CPU] = BCL[HallOfFame] = BCL[Quit] = 1;
				}

			}
			else if (Isinside(Width / 8, Hight / 9 + 250, Bottun[CPU].h, Bottun[CPU].w) )
			{
				if (BCL[CPU]) {
					col++;
					BC[CPU] = col % TotalCols;
					BCL[CPU] = 0;
					Render = 1;
					BCL[Load] = BCL[PVC] = BCL[Play] = BCL[HallOfFame] = BCL[Quit] = 1;
				}

			}
			else if (Isinside(Width / 8, Hight / 9 + 350, Bottun[HallOfFame].h, Bottun[HallOfFame].w) )
			{
				if (BCL[HallOfFame]) {
					col++;
					BC[HallOfFame] = col % TotalCols;
					BCL[HallOfFame] = 0;
					Render = 1;
					BCL[Load] = BCL[PVC] = BCL[CPU] = BCL[Play] = BCL[Quit] = 1;
				}
			}
			else if (Isinside(Width / 8, Hight / 9 + 450, Bottun[Quit].h, Bottun[Quit].w) )
			{
				if (BCL[Quit]) {
					col++;
					BC[Quit] = col % TotalCols;
					BCL[Quit] = 0;
					Render = 1;
					BCL[Load] = BCL[PVC] = BCL[CPU] = BCL[HallOfFame] = BCL[Play] = 1;
				}
			}
		}
		if (Render) {
			SDL_SetRenderDrawColor(Rendere, 130, 130, 130, 255);
			SDL_RenderClear(Rendere);
			Bottun[Play] = RenderText(Width / 8, Hight / 9-50, "Start Game", BC[Play],90);
			Bottun[Load] = RenderText(Width / 8, Hight / 9+50 , "Load Game", BC[Load],90);
			Bottun[PVC] = RenderText(Width / 8, Hight / 9 + 150, "PVC", BC[PVC], 90);
			Bottun[CPU] = RenderText(Width / 8, Hight / 9 + 250, "Cpu", BC[CPU], 90);
			Bottun[HallOfFame] = RenderText(Width / 8, Hight / 9 + 350, "Hall Of Fame", BC[HallOfFame],90);
			Bottun[Quit] = RenderText(Width / 8, Hight / 9 + 450, "Quit", BC[Quit],90);
			SDL_RenderPresent(Rendere);
			Render = 0;
		}
	}


	Close();
	return 0;
}


