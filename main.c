/**
* @file main.c
* @brief Testing Program.
* @author C Team
* @version 0.1
* @date Apr 01, 2015
*
* Testing program for background scrollilng
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"
int main(int argc,char *argv[]){
	SDL_Surface *screen;
	Mix_Music *music;
	background bg,bg2;
	SDL_Event event;
	int difficulte=1;
	int difficulte2=1;
	scoreinfo s1;
	scoreinfo trois[3];
	int running=1;
	
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
	TTF_Init();
	screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32,SDL_HWSURFACE);
	init_background(&bg);
	/*init_background2(&bg2);*/
	
	while(running&&difficulte<4&&difficulte2<4){
		
		while(SDL_PollEvent(&event)){
			if(event.type==SDL_QUIT){
				running=0;
			}
			else if(event.type==SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					case SDLK_RIGHT:
						scrolling(&bg,0,5);
						break;
					case SDLK_LEFT:
						scrolling(&bg,1,5);
						break;
					case SDLK_UP:
						scrolling(&bg,2,5);
						break;
					case SDLK_DOWN:
						scrolling(&bg,3,5);
						break;

			               // Ajout des entrées pour le deuxième joueur
                                      case SDLK_d:
                        	       	scrolling2(&bg2,0,5);
                                      	break;
                                      case SDLK_q:
                                      	scrolling2(&bg2,1,5);
                                      	break;
                                      case SDLK_z:
                                      	scrolling2(&bg2,2,5);
                                      	break;
                                      case SDLK_s:
                                      	scrolling2(&bg2,3,5);
                                      	break;

				}
				}
				else if(event.type==SDL_KEYUP){
				switch(event.key.keysym.sym){
					case SDLK_RIGHT:
						scrolling(&bg,0,0);
						break;
					case SDLK_LEFT:
						scrolling(&bg,1,0);
						break;
					case SDLK_UP:
						scrolling(&bg,2,0);
						break;
					case SDLK_DOWN:
						scrolling(&bg,3,0);
						break;
                                      case SDLK_d:
                        	       	scrolling2(&bg2,0,0);
                                      	break;
                                      case SDLK_q:
                                      	scrolling2(&bg2,1,0);
                                      	break;
                                      case SDLK_z:
                                      	scrolling2(&bg2,2,0);
                                      	break;
                                      case SDLK_s:
                                      	scrolling2(&bg2,3,0);
                                      	break;

				}
			}
			
		}
		
	        
	        if(bg.camerapos.x>100)
	        {
	        	init_background(&bg);
	        	bg.musicplaying=0;
	        	difficulte++;
	        	afficher_background(&bg,screen,difficulte);
	        	SDL_Flip(screen);
	        }
	        /*if(bg2.camerapos.x>100)
	        {
	        	init_background2(&bg2);
	        	bg2.musicplaying=0;
	        	difficulte2++;
	        	partage_ecran(&bg2, screen,difficulte2);
	        	SDL_Flip(screen);
	        }*/
	        afficher_background(&bg,screen,difficulte);
		/*animerback(&bg,screen);
		/*partage_ecran(&bg2,screen,difficulte2);
		animerback2(&bg2,screen);*/
		/*savescore(s1,"score");
	        bestscore("score",trois);
                afficherbest(screen,trois);*/	
		SDL_Flip(screen);

	}
	SDL_FreeSurface(bg.image1);
	SDL_FreeSurface(bg.image2);
	SDL_FreeSurface(bg.image3);
	Mix_FreeMusic(bg.music1);
	Mix_FreeMusic(bg.music2);
	Mix_FreeMusic(bg.music3);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
