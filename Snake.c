#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define X 48//344
#define Y 36//144
#define DELAI 100
#define GROW 3

int rand_ab(int a, int b);

int main(int argc, char *argv[]){
	int grille[Y][X];
	int i = 0, j = 0;
	int posSX = 25, posSY = 25;
	int posEX = 23, posEY = 25;
	int dirS = 6, dirE = 6;
	int a = 1;
	char eatApple = 0, spawnedApple = 0;
	char eatScissor = 0; //, spawnedScissor = 0;

	int score = 0, lenght = 0;


	srand(time(NULL));

	SDL_Event event;
	SDL_Rect pos, posApple, posScissor;
	SDL_Surface *ecran = NULL;

	SDL_Surface *tete_8 = NULL, *tete_6 = NULL, *tete_2 = NULL, *tete_4 = NULL;

	SDL_Surface *corps_h = NULL, *corps_v = NULL;

	SDL_Surface *queue_4 = NULL, *queue_8 = NULL, *queue_6 = NULL, *queue_2 = NULL;

	SDL_Surface *virage_48 = NULL, *virage_86 = NULL, *virage_62 = NULL, *virage_24 = NULL;

	SDL_Surface *pomme = NULL, *noir = NULL, *game_over = NULL, *scissor = NULL;

	//SDL_Surface *menu = NULL;

	tete_4 = IMG_Load("tete_4_10.png");
	tete_8 = IMG_Load("tete_8_10.png");
	tete_6 = IMG_Load("tete_6_10.png");
	tete_2 = IMG_Load("tete_2_10.png");

	corps_h = IMG_Load("corps_h_10.png");
	corps_v = IMG_Load("corps_v_10.png");

	queue_4 = IMG_Load("queue_4_10.png");
	queue_8 = IMG_Load("queue_8_10.png");
	queue_6 = IMG_Load("queue_6_10.png");
	queue_2 = IMG_Load("queue_2_10.png");

	virage_48 = IMG_Load("virage_48_10.png");
	virage_86 = IMG_Load("virage_86_10.png");
	virage_62 = IMG_Load("virage_62_10.png");
	virage_24 = IMG_Load("virage_24_10.png");

	pomme = IMG_Load("pomme_10.png");
	noir = IMG_Load("noir_10.png");
	game_over = IMG_Load("game_over.png");
	scissor = IMG_Load("queue_2_10.png");

	//menu = IMG_Load("Quelque pars !");


	SDL_SetColorKey(tete_4, SDL_SRCCOLORKEY, SDL_MapRGB(tete_4->format, 0, 0, 255));
	SDL_SetColorKey(tete_8, SDL_SRCCOLORKEY, SDL_MapRGB(tete_8->format, 0, 0, 255));
	SDL_SetColorKey(tete_6, SDL_SRCCOLORKEY, SDL_MapRGB(tete_6->format, 0, 0, 255));
	SDL_SetColorKey(tete_2, SDL_SRCCOLORKEY, SDL_MapRGB(tete_2->format, 0, 0, 255));

	SDL_SetColorKey(corps_h, SDL_SRCCOLORKEY, SDL_MapRGB(corps_h->format, 0, 0, 255));
	SDL_SetColorKey(corps_v, SDL_SRCCOLORKEY, SDL_MapRGB(corps_v->format, 0, 0, 255));

	SDL_SetColorKey(queue_4, SDL_SRCCOLORKEY, SDL_MapRGB(queue_4->format, 0, 0, 255));
	SDL_SetColorKey(queue_8, SDL_SRCCOLORKEY, SDL_MapRGB(queue_8->format, 0, 0, 255));
	SDL_SetColorKey(queue_6, SDL_SRCCOLORKEY, SDL_MapRGB(queue_6->format, 0, 0, 255));
	SDL_SetColorKey(queue_2, SDL_SRCCOLORKEY, SDL_MapRGB(queue_2->format, 0, 0, 255));

	SDL_SetColorKey(virage_48, SDL_SRCCOLORKEY, SDL_MapRGB(virage_48->format, 0, 0, 255));
	SDL_SetColorKey(virage_86, SDL_SRCCOLORKEY, SDL_MapRGB(virage_86->format, 0, 0, 255));
	SDL_SetColorKey(virage_62, SDL_SRCCOLORKEY, SDL_MapRGB(virage_62->format, 0, 0, 255));
	SDL_SetColorKey(virage_24, SDL_SRCCOLORKEY, SDL_MapRGB(virage_24->format, 0, 0, 255));

	SDL_SetColorKey(pomme, SDL_SRCCOLORKEY, SDL_MapRGB(pomme->format, 0, 0, 255));



	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER);
	SDL_WM_SetIcon(IMG_Load("pomme_64.png"), NULL);
	ecran = SDL_SetVideoMode(X * 10, Y * 10, 32, SDL_HWSURFACE);// | SDL_FULLSCREEN);
	SDL_WM_SetCaption("Snake !", NULL);

	//Insérez le menu ici !

	pos.x = 0;
	pos.y = 0;

	/*SDL_BlitSurface(menu, NULL, ecran, &pos);

	while (a == 1){

	}*/

	for (i = 0; i < Y; i++){
		for(j = 0; j < X; j++){
			grille[i][j] = 0;
		}
	}

	grille[25][25] = 66;
	grille[25][24] = 66;
	grille[25][23] = 66;
	/*grille[25][22] = 66;
	grille[25][21] = 66;
	grille[25][20] = 66;
	grille[25][19] = 66;*/

	do{
		posApple.x = rand_ab(0, X);
		posApple.y = rand_ab(0, Y);
	}while(grille[posApple.y][posApple.x] != 0);
	eatApple = 0;
	spawnedApple = 1;
	grille[posApple.y][posApple.x] = 1;
	posApple.x = posApple.x * 10;
	posApple.y = posApple.y * 10;


	while(a == 1){

		// Bloc de commande

		// Queue
		do{
			if (!eatApple){
				switch (dirE){
					case 2:
						posEY += 1;
						grille[posEY - 1][posEX] = 0;

						pos.y = (posEY - 1) * 10;
						pos.x = posEX * 10;
						SDL_BlitSurface(noir, NULL, ecran, &pos);

						if (posEY == Y)
							posEY = 0;
						break;
					case 4:
						posEX -= 1;
						grille[posEY][posEX + 1] = 0;

						pos.y = posEY * 10;
						pos.x = (posEX + 1) * 10;
						SDL_BlitSurface(noir, NULL, ecran, &pos);

						if (posEX == -1)
							posEX = X - 1;
						break;
					case 8:
						posEY -= 1;
						grille[posEY + 1][posEX] = 0;

						pos.y = (posEY + 1) * 10;
						pos.x = posEX * 10;
						SDL_BlitSurface(noir, NULL, ecran, &pos);

						if (posEY == -1)
							posEY = Y - 1;
						break;
					case 6:
						posEX += 1;
						grille[posEY][posEX - 1] = 0;

						pos.y = posEY * 10;
						pos.x = (posEX - 1) * 10;
						SDL_BlitSurface(noir, NULL, ecran, &pos);

						if (posEX == X)
							posEX = 0;
						break;
				}
				dirE = grille[posEY][posEX] % 10;
				if (!eatScissor)
					eatScissor--;
			}
		}while (!eatScissor);

		if (!spawnedApple){
			do{
				posApple.x = rand_ab(0, X);
				posApple.y = rand_ab(0, Y);
			}while(grille[posApple.y][posApple.x] != 0);
			grille[posApple.y][posApple.x] = 1;
			spawnedApple = 1;
			posApple.x = posApple.x * 10;
			posApple.y = posApple.y * 10;
		}

		/*if(!spawnedScissor && rand_ab(0, 50) == 25){
			do{
				posScissor.x = rand_ab(0, X);
				posScissor.y = rand_ab(0, Y);
			}while(grille[posScissor.y][posScissor.x] != 0);
			spawnedScissor = 1;
			grille[posScissor.y][posScissor.x] = 2;
			posScissor.x = posScissor.x * 10;
			posScissor.y = posScissor.y * 10;
		}*/

		if (eatApple > 0)
			eatApple--;

		// Tête
		switch (dirS){
			case 2:
				posSY += 1;

				if (posSY == Y){
					posSY = 0;

					if (grille[posSY][posSX] == 1){
						eatApple += GROW;
						spawnedApple = 0;
						score++;
						lenght += GROW;
						printf("Score : %d\nLongueur : %d\n\n", score, lenght);
						grille[posSY][posSX] = 0;
					}

					/*if (grille[posSY][posSX] == 2){
						eatScissor += GROW;
						spawnedApple = 0;
						score++;
						lenght += GROW;
						printf("Score : %d\nLongueur : %d\n\n", score, lenght);
						grille[posSY][posSX] = 0;
					}*/

					if (grille[posSY][posSX] != 0)
						a = 2;

					grille[Y - 1][posSX] = ((grille[Y - 1][posSX] * 10) % 100 + 2);
					grille[posSY][posSX] = 22;
				}else{
					if (grille[posSY][posSX] == 1){
						eatApple += GROW;
						spawnedApple = 0;
						score++;
						lenght += GROW;
						printf("Score : %d\nLongueur : %d\n\n", score, lenght);
						grille[posSY][posSX] = 0;
					}

					if (grille[posSY][posSX] != 0)
						a = 2;

					grille[posSY - 1][posSX] = ((grille[posSY - 1][posSX] * 10) % 100 + 2);
					grille[posSY][posSX] = 22;
				}
				break;

			case 4:
				posSX -= 1;

				if (posSX == -1){
					posSX = X - 1;

					if (grille[posSY][posSX] == 1){
						eatApple += GROW;
						spawnedApple = 0;
						score++;
						lenght += GROW;
						printf("Score : %d\nLongueur : %d\n\n", score, lenght);
						grille[posSY][posSX] = 0;
					}

					if (grille[posSY][posSX] != 0)
						a = 2;

					grille[posSY][0] = ((grille[posSY][0] * 10) % 100 + 4);
					grille[posSY][posSX] = 44;
				}else{
					if (grille[posSY][posSX] == 1){
						eatApple += GROW;
						spawnedApple = 0;
						score++;
						lenght += GROW;
						printf("Score : %d\nLongueur : %d\n\n", score, lenght);
						grille[posSY][posSX] = 0;
					}

					if (grille[posSY][posSX] != 0)
						a = 2;

					grille[posSY][posSX + 1] = ((grille[posSY][posSX + 1] * 10) % 100 + 4);
					grille[posSY][posSX] = 44;
				}
				break;

			case 8:
				posSY -= 1;

				if (posSY == -1){
					posSY = Y - 1;

					if (grille[posSY][posSX] == 1){
						eatApple += GROW;
						spawnedApple = 0;
						score++;
						lenght += GROW;
						printf("Score : %d\nLongueur : %d\n\n", score, lenght);
						grille[posSY][posSX] = 0;
					}

					if (grille[posSY][posSX] != 0)
						a = 2;

					grille[0][posSX] = ((grille[0][posSX] * 10) % 100 + 8);
					grille[posSY][posSX] = 88;
				}else{
					if (grille[posSY][posSX] == 1){
						eatApple += GROW;
						spawnedApple = 0;
						score++;
						lenght += GROW;
						printf("Score : %d\nLongueur : %d\n\n", score, lenght);
						grille[posSY][posSX] = 0;
					}

					if (grille[posSY][posSX] != 0)
						a = 2;

					grille[posSY + 1][posSX] = ((grille[posSY + 1][posSX] * 10) % 100 + 8);
					grille[posSY][posSX] = 88;
				}
				break;

			case 6:
				posSX += 1;

				if (posSX == X){
					posSX = 0;

					if (grille[posSY][posSX] == 1){
						eatApple += GROW;
						spawnedApple = 0;
						score++;
						lenght += GROW;
						printf("Score : %d\nLongueur : %d\n\n", score, lenght);
						grille[posSY][posSX] = 0;
					}

					if (grille[posSY][posSX] != 0)
						a = 2;

					grille[posSY][X - 1] = ((grille[posSY][X - 1] * 10) % 100 + 6);
					grille[posSY][posSX] = 66;
				}else{
					if (grille[posSY][posSX] == 1){
						eatApple += GROW;
						spawnedApple = 0;
						score++;
						lenght += GROW;
						printf("Score : %d\nLongueur : %d\n\n", score, lenght);
						grille[posSY][posSX] = 0;
					}

					if (grille[posSY][posSX] != 0)
						a = 2;

					grille[posSY][posSX - 1] = ((grille[posSY][posSX - 1] * 10) % 100 + 6);
					grille[posSY][posSX] = 66;
				}
				break;
		}

		// Bloc de traçage
		for (i = 0; i < Y; i++){
			for(j = 0; j < X; j++){

				pos.y = i * 10;
				pos.x = j * 10;

				switch (grille[i][j]){
					case 1:
						SDL_BlitSurface(pomme, NULL, ecran, &posApple);
						break;

					case 2:
						SDL_BlitSurface(scissor, NULL, ecran, &posScissor);
						break;

					case 66:
					case 44:
						SDL_BlitSurface(corps_h, NULL, ecran, &pos);
						break;

					case 88:
					case 22:
						SDL_BlitSurface(corps_v, NULL, ecran, &pos);
						break;

					case 68:
					case 24:
						SDL_BlitSurface(virage_48, NULL, ecran, &pos);
						break;

					case 26:
					case 48:
						SDL_BlitSurface(virage_86, NULL, ecran, &pos);
						break;

					case 42:
					case 86:
						SDL_BlitSurface(virage_62, NULL, ecran, &pos);
						break;

					case 84:
					case 62:
						SDL_BlitSurface(virage_24, NULL, ecran, &pos);
						break;
				}
			}
		}

		// Traçage tête
		pos.y = posSY * 10;
		pos.x = posSX * 10;
		switch (dirS){
			case 6:
				SDL_BlitSurface(tete_6, NULL, ecran, &pos);
				break;

			case 2:
				SDL_BlitSurface(tete_2, NULL, ecran, &pos);
				break;

			case 4:
				SDL_BlitSurface(tete_4, NULL, ecran, &pos);
				break;

			case 8:
				SDL_BlitSurface(tete_8, NULL, ecran, &pos);
				break;
		}

		// Traçage queue
		pos.y = posEY * 10;
		pos.x = posEX * 10;
		switch (dirE){
			case 6:
				SDL_BlitSurface(queue_6, NULL, ecran, &pos);
				break;

			case 2:
				SDL_BlitSurface(queue_2, NULL, ecran, &pos);
				break;

			case 4:
				SDL_BlitSurface(queue_4, NULL, ecran, &pos);
				break;

			case 8:
				SDL_BlitSurface(queue_8, NULL, ecran, &pos);
				break;
		}

		SDL_PollEvent(&event);

		switch (event.type){

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){

					case SDLK_ESCAPE: //Touche echap
						a = 0;
						break;
					case SDLK_UP: //Flèche haut
						if(dirS != 2)
						dirS = 8;
						break;
					case SDLK_DOWN: //Flèche bas
						if(dirS != 8)
						dirS = 2;
						break;
					case SDLK_RIGHT: //Flèche droite
						if(dirS != 4)
						dirS = 6;
						break;
					case SDLK_LEFT: //Flèche gauche
						if(dirS != 6)
						dirS = 4;
					break;
				default:
					break;
				}
				break;
		}


		//Autoplay

		//if (posSX < posApple.x)



		/*if (posSY != posApple.y / 10 && (dirS != 8 && dirS != 2)){
			if (posSY > posApple.y / 10 && (grille[posSY - 1][posSX] == 0 || grille[posSY - 1][posSX] == 1)){
				dirS = 8;
			}else if (grille[posSY + 1][posSX] == 0 || grille[posSY + 1][posSX] == 1){
				dirS = 2;
			}
		}else{
			if (posSX != posApple.x / 10 && (dirS != 4 && dirS != 6)){
				if (posSX > posApple.x / 10 && (grille[posSY][posSX - 1] == 0 || grille[posSY][posSX - 1] == 1)){
					dirS = 4;
				}else if (grille[posSY][posSX + 1] == 0 || grille[posSY][posSX + 1] == 1){
					dirS = 6;
				}
			}
		}*/
		SDL_Flip(ecran);
		SDL_Delay(DELAI);
	}

	if (a == 2){
		pos.x = 0;
		pos.y = 0;

		for(i = 0; i< 255; i++){
			SDL_SetAlpha(game_over, SDL_SRCALPHA, i);
			SDL_BlitSurface(game_over, NULL, ecran, &pos);
			SDL_Flip(ecran);
			SDL_Delay(10);
		}
		SDL_Delay(1000);
	}
	SDL_Quit();
	return 0;
}

int rand_ab(int a, int b){
	return rand() % (b - a) + a;
}
