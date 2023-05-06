#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"
int main(int argc, char *argv[])
{
	int quitter=0,f=0;
	int i,d=1920/1050,k=-1;
	int v=7,xR=30,yR=30;
	image rob1,rob2;
	text t,t1,t2,tF,t1F,t2F;
	SDL_Event event;
	button B[20];
	image logo;
	SDL_Surface *ecran=NULL; 
	image menu;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	TTF_Init();
	initText(&t,500,490,255,255,255,"Gameplay.ttf",30);
	initText(&tF,500*d,490*d,255,255,255,"Gameplay.ttf",30*d);
	initText(&t1,500,540,255,255,255,"Gameplay.ttf",30);
	initText(&t1F,500*d,540*d,255,255,255,"Gameplay.ttf",30*d);
	initText(&t2,500,590,255,255,255,"Gameplay.ttf",30);
	initText(&t2F,500*d,590*d,255,255,255,"Gameplay.ttf",30*d);
	initImage(&logo,"LOGO.png",146,104);
	SDL_WM_SetIcon(IMG_Load("robot.ico"),NULL);
	ecran=SDL_SetVideoMode (SCREEN_W,SCREEN_H,32, SDL_HWSURFACE | SDL_DOUBLEBUF) ;
	SDL_WM_SetCaption("Fubot",NULL);
	initBackground(&menu,"background.jpg");
	initButton(&B[0],"PLAY.png","PLAY2.png","PLAY3.png",30,455);
	initButton(&B[1],"OPTIONS.png","OPTIONS2.png","OPTIONS3.png",30,538);
	initButton(&B[2],"QUIT.png","QUIT2.png","QUIT3.png",30,621);
	if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
	{
		printf("%s",Mix_GetError());
	}
	Mix_Music *music;
	Mix_Chunk *clic,*effet;
	music=Mix_LoadMUS("rbmu.mp3");
	clic=Mix_LoadWAV("button.wav");
	effet=Mix_LoadWAV("effet.wav");
	Mix_PlayMusic(music,-1);
	Mix_VolumeMusic((MIX_MAX_VOLUME/10)*v);
	while (quitter==0)
	{
	switch (k)
	{
		case -1:
		B[0].etat=0;
		B[1].etat=0;
		B[2].etat=0;
		break;
		case 0:
		B[0].etat=1;
		B[1].etat=0;
		B[2].etat=0;
		break;
		case 1:
		B[0].etat=0;
		B[1].etat=1;
		B[2].etat=0;
		break;
		case 2:
		B[0].etat=0;
		B[1].etat=0;
		B[2].etat=1;
		break;
	}
	afficher(menu,ecran,f);
	afficher(logo,ecran,f);
	for (i=0;i<3;i++)
		afficherButton(B[i],ecran,f);
	if (f==0)
	{
		displayText(t,ecran,"Press 'j' to play");
		displayText(t1,ecran,"Press 'o' for options");
		displayText(t2,ecran,"Press 'q' to quit");
	}
	else
	{
		displayText(tF,ecran,"Press 'j' to play");
		displayText(t1F,ecran,"Press 'o' for options");
		displayText(t2F,ecran,"Press 'q' to quit");
	}
	RobotAnim(ecran,&rob1,&rob2,1050,700,&xR,&yR,30);
	while (SDL_PollEvent(&event))
	{
	switch (event.type)
	{
		case SDL_QUIT:
			quitter=1;
			break;
		case SDL_KEYDOWN:
		switch(event.key.keysym.sym)
		{
			case SDLK_ESCAPE:
				quitter=1;
				break;
			case SDLK_j:
				jouer(ecran,v,f);
				break;
			case SDLK_o:
				options(ecran,&v,&f);
				break;
			case SDLK_q:
				quitter=1;
				break;
			case SDLK_DOWN:
				k++;
				Mix_PauseMusic();
				Mix_PlayChannel(0,effet,0);
				Mix_ResumeMusic();
				if (k==3)
		 			k=0;
		 		break;
		 	case SDLK_UP:
				k--;
				Mix_PauseMusic();
				Mix_PlayChannel(0,effet,0);
				Mix_ResumeMusic();
				if (k==-1)
					k=2;
				break;	
			case SDLK_RETURN:
				if (k==0)
				{
					Mix_PauseMusic();
					Mix_PlayChannel(0,clic,0);
					B[k].etat=2;
					afficherButton(B[k],ecran,f);
					Mix_ResumeMusic();
					SDL_Delay(800);
					jouer(ecran,v,f);
				}
				else if (k==1)
				{
					Mix_PauseMusic();
					Mix_PlayChannel(0,clic,0);
					B[k].etat=2;
					afficherButton(B[k],ecran,f);
					Mix_ResumeMusic();
					SDL_Delay(800);
					options(ecran,&v,&f);
				}
				else if (k==2)
				{
					Mix_PauseMusic();
					Mix_PlayChannel(0,clic,0);
					B[k].etat=2;
					afficherButton(B[k],ecran,f);
					Mix_ResumeMusic();
					SDL_Delay(800);
					quitter=1;
				}
					break;	
		}
		break;
		case SDL_MOUSEMOTION:
		//printf("Souris en position %d %d\n",event.motion.x, event.motion.y);
			if (MousePos(B[0],event,f))
			{	
				Mix_PauseMusic();
				Mix_PlayChannel(0,effet,0);
				Mix_ResumeMusic();
				k=0;
			}
			else if (MousePos(B[1],event,f))
			{
				Mix_PauseMusic();
				Mix_PlayChannel(0,effet,0);
				Mix_ResumeMusic();
				k=1;
			}
			else if (MousePos(B[2],event,f))
			{
				Mix_PauseMusic();
				Mix_PlayChannel(0,effet,0);
				Mix_ResumeMusic();
				k=2;
			}
			else 
			{
				k=-1;
			}
			
			break;
		case SDL_MOUSEBUTTONDOWN:
			if ((MousePos(B[0],event,f))&&(event.button.button==SDL_BUTTON_LEFT))
			{
				Mix_PauseMusic();
				Mix_PlayChannel(0,clic,0);
				B[0].etat=2;
				afficherButton(B[k],ecran,f);
				Mix_ResumeMusic();
				SDL_Delay(800);
				jouer(ecran,v,f);
			}
			else if ((MousePos(B[1],event,f))&&(event.button.button==SDL_BUTTON_LEFT))
			{
				Mix_PauseMusic();
				Mix_PlayChannel(0,clic,0);
				B[1].etat=2;
				afficherButton(B[k],ecran,f);
				Mix_ResumeMusic();
				SDL_Delay(800);
				options(ecran,&v,&f);
			}
			else if ((MousePos(B[2],event,f))&&(event.button.button==SDL_BUTTON_LEFT))
			{
				Mix_PauseMusic();
				Mix_PlayChannel(0,clic,0);
				B[k].etat=2;
				afficherButton(B[2],ecran,f);
				Mix_ResumeMusic();
				SDL_Delay(800);
				quitter=1;
			}
			break;
			
	}
	}
		SDL_Flip(ecran);
	}
	liberer(&menu,f);
	if (f==0)
		freeText(&t);
	else
		freeText(&tF);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

