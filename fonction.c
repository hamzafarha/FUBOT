/**
* @file fonction.c
* @brief Testing Program.
* @author C Team
* @version 0.1
* @date Apr 01, 2015
*
* Testing program for background scrollilng
*/
/**

* @file background.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"
/**
* @brief To initialize the background bg .
* @param b the background
* @return Nothing
*/
void init_background(background *bg)
{
	bg->image1=IMG_Load("easy.png");
	if(!bg->image1)
	{
		fprintf(stderr,"Impossible de charger l'image du fond %s :%s\n","background.png",IMG_GetError());
		exit(EXIT_FAILURE);
	}
	bg->image2=IMG_Load("medium.png");
	if(!bg->image2)
	{
		fprintf(stderr,"Impossible de charger l'image du fond %s :%s\n","background.png",IMG_GetError());
		exit(EXIT_FAILURE);
	}
	bg->image3=IMG_Load("hard.png");
	if(!bg->image3)
	{
		fprintf(stderr,"Impossible de charger l'image du fond %s :%s\n","background.png",IMG_GetError());
		exit(EXIT_FAILURE);
	}

        bg->music1= Mix_LoadMUS("easy.mp3");
        bg->music2= Mix_LoadMUS("medium.mp3");
        bg->music3= Mix_LoadMUS("hard.mp3");

	
	bg->camerapos.x=0;
	bg->camerapos.y=1726-SCREEN_HEIGHT;
	bg->camerapos.w=SCREEN_WIDTH;
	bg->camerapos.h=SCREEN_HEIGHT;
	bg->screenpos.x=0;
	bg->screenpos.y=0;
	bg->screenpos.w=SCREEN_WIDTH;
	bg->screenpos.h=SCREEN_HEIGHT;
	bg->direction=1;
	bg->musicplaying=0;
}
/**
* @brief To initialize the background bg2 .
* @param bg2 the background
* @return Nothing
*/
void init_background2(background *bg2)
{

	bg2->image1=IMG_Load("easy.png");
	if(!bg2->image1)
	{
		fprintf(stderr,"Impossible de charger l'image du fond %s :%s\n","background.png",IMG_GetError());
		exit(EXIT_FAILURE);
	}
	bg2->image2=IMG_Load("medium.png");
	if(!bg2->image2)
	{
		fprintf(stderr,"Impossible de charger l'image du fond %s :%s\n","background.png",IMG_GetError());
		exit(EXIT_FAILURE);
	}
	bg2->image3=IMG_Load("hard.png");
	if(!bg2->image3)
	{
		fprintf(stderr,"Impossible de charger l'image du fond %s :%s\n","background.png",IMG_GetError());
		exit(EXIT_FAILURE);
	}
        bg2->music1= Mix_LoadMUS("easy.mp3");
        bg2->music2= Mix_LoadMUS("medium.mp3");
        bg2->music3= Mix_LoadMUS("hard.mp3");
	bg2->camerapos.x=0;
	bg2->camerapos.y=1726;
	bg2->camerapos.w=SCREEN_WIDTH;
	bg2->camerapos.h=SCREEN_HEIGHT;
	/*bg2->screenpos.x=SCREEN_WIDTH/2;
	bg2->screenpos.y=0;
	bg2->screenpos.w=2+SCREEN_WIDTH/2;
	bg2->screenpos.h=SCREEN_HEIGHT;*/

	bg2->direction=1;
	bg2->musicplaying=0;
}
/**
* @brief To show the background bg .
* @param screen the screen
* @param bg the background
* @return Nothing
*/
void afficher_background(background *bg,SDL_Surface *screen,int difficulte)
{
	
	switch(difficulte)
	{
		case 1:
			  
			  SDL_BlitSurface(bg->image1,&bg->camerapos,screen,NULL);
			   if(bg->music1!=NULL&&bg->musicplaying==0)
			  {
			  	Mix_PlayMusic(bg->music1,-1);
			  	bg->musicplaying=1;
			  }
                        
			
		          break;
		case 2:
      	                 
			  SDL_BlitSurface(bg->image2,&bg->camerapos,screen,NULL);	 
			  if(bg->music2!=NULL&&bg->musicplaying==0)
			  {
			  	 Mix_PlayMusic(bg->music2,-1);
			  	 bg->musicplaying=1;
			  }
		           break;
		case 3:
		       
      			
			  SDL_BlitSurface(bg->image3,&bg->camerapos,screen,NULL);
			  if(bg->music3!=NULL&&bg->musicplaying==0)
			  {
			  	 Mix_PlayMusic(bg->music3,-1);
			  	 bg->musicplaying=1;
			  }
			  
		           break;
	}
	
}
/**
* @brief To show the background bg2 .
* @param screen the screen
* @param bg2 the background
* @return Nothing
*/
void partage_ecran(background *bg2, SDL_Surface *screen,int difficulte2)
{
    
    switch(difficulte2)
    {
        case 1:
            SDL_BlitSurface(bg2->image1, &bg2->camerapos, screen, &bg2->screenpos);
            if(bg2->music1!=NULL&&bg2->musicplaying==0)
			  {
			  	Mix_PlayMusic(bg2->music1,-1);
			  	bg2->musicplaying=1;
			  }
            break;
        case 2:
            SDL_BlitSurface(bg2->image2, &bg2->camerapos, screen, &bg2->screenpos);
            if(bg2->music2!=NULL&&bg2->musicplaying==0)
			  {
			  	 Mix_PlayMusic(bg2->music2,-1);
			  	 bg2->musicplaying=1;
			  }
            break;
        case 3:
            SDL_BlitSurface(bg2->image3, &bg2->camerapos, screen, &bg2->screenpos);
            if(bg2->music3!=NULL&&bg2->musicplaying==0)
			  {
			  	 Mix_PlayMusic(bg2->music3,-1);
			  	 bg2->musicplaying=1;
			  }
            break;
    }
}
/**
* @brief To scroll the background to o 4 directions .
* @param bg2 the background
* @param direction integer
* @param pas integer 
* @return Nothing
*/
void scrolling(background *bg,int direction,int pas)
{
	
	switch(direction)
	{
		case 0:
			if(bg->camerapos.x>100){
				bg->camerapos.x=100;
			}
			else
				bg->camerapos.x+=pas;
			break;
		case 1:
			if(bg->camerapos.x<=0){
				bg->camerapos.x=0;
			}
			else
				bg->camerapos.x-=pas;
			break;
		case 2:
			if(bg->camerapos.y<=0){
				bg->camerapos.y=0;
			}
			else
				bg->camerapos.y-=pas;
			break;
		case 3:
			if(bg->camerapos.y>=1726-SCREEN_HEIGHT){
				bg->camerapos.y=1726-SCREEN_HEIGHT;
			}
			else
				bg->camerapos.y+=pas;
			break;
		default :
			break;	
	}
}
/**
* @brief To scroll the background to 4 directions.
* @param bg2 the background
* @param direction integer
* @param pas integer 
* @return Nothing
*/
void scrolling2(background *bg2,int direction,int pas)
{
	switch(direction)
	{
		case 0:
			if(bg2->camerapos.x>100){
				bg2->camerapos.x=100;
			}
			else
				bg2->camerapos.x+=pas;
			break;
		case 1:
			if(bg2->camerapos.x<=0){
				bg2->camerapos.x=0;
			}
			else
				bg2->camerapos.x-=pas;
			break;
		case 2:
			if(bg2->camerapos.y<=3){
				bg2->camerapos.y=0;
			}
			else
				bg2->camerapos.y-=pas;
			break;
		case 3:
			if(bg2->camerapos.y>7){
				bg2->camerapos.y=7;
			}
			else
				bg2->camerapos.y+=pas;
			break;
		default :
			break;	
	}
}
/**
* @brief To animate the background .
* @param bg the background
* @param screen the screen
* @return Nothing
*/
void animerback(background *bg,SDL_Surface *screen)
{
    static int x = 0;
    static int y = 0;
    static int dx = 2;
    static int dy = 2;
    static SDL_Surface *nuage = NULL;
    

    if (nuage == NULL) {
        nuage = IMG_Load("nuage.png");
    }

    x += dx;
    y += dy;

    if (x + nuage->w >= bg->camerapos.w || x <= 0) {
        dx = -dx;
    }

    SDL_Rect nuagePos = { x, 50, nuage->w, nuage->h };
    SDL_BlitSurface(nuage, NULL, screen, &nuagePos);
    
    static int x1 = 0;
    static int y1 = 250;
    static int dx1 = 2;
    static int dy1 = 2;
    static SDL_Surface *ballon = NULL;
   
    if (ballon == NULL) {
        ballon = IMG_Load("ballon.png");
    }

    x1 += dx1;
    y1 += dy1;

    if (y1 + ballon->w >= 400 || y1 <= 200) {
        dy1 = -dy1;
    }

    SDL_Rect ballonPos = { 200, y1, ballon->w, ballon->h };
    SDL_BlitSurface(ballon, &bg->camerapos, screen, &ballonPos);
}
/**
* @brief To animate the background .
* @param bg2 the background
* @param screen the screen
* @return Nothing
*/
void animerback2(background *bg2,SDL_Surface *screen)
{
    static int x = 0;
    static int y = 0;
    static int dx = 2;
    static int dy = 2;
    static SDL_Surface *nuage = NULL;
    

    if (nuage == NULL) {
        nuage = IMG_Load("nuage.png");
    }

    x += dx;
    y += dy;

    if (x + nuage->w >= bg2->camerapos.w || x <= 0) {
        dx = -dx;
    }

    SDL_Rect nuagePos = { x+bg2->camerapos.w, 50, nuage->w, nuage->h };
    SDL_BlitSurface(nuage, NULL, screen, &nuagePos);
    
    static int x1 = 0;
    static int y1 = 250;
    static int dx1 = 2;
    static int dy1 = 2;
    static SDL_Surface *ballon = NULL;
   
    if (ballon == NULL) {
        ballon = IMG_Load("ballon.png");
    }

    x1 += dx1;
    y1 += dy1;

    if (y1 + ballon->w >= 400 || y1 <= 200) {
        dy1 = -dy1;
    }

    SDL_Rect ballonPos = { 200+bg2->camerapos.w, y1, ballon->w, ballon->h };
    SDL_BlitSurface(ballon, &bg2->camerapos, screen, &ballonPos);
}
/**
* @brief To save the score .
* @param s1 the scoreinfo .
* @param filename string .
* @return Nothing
*/
void savescore(scoreinfo s1,char *filename)
{
	FILE *file=fopen(filename,"a+");
	if(file==NULL){
		printf("Erreur lors de l'ouverture du fichier %s \n",filename);
	}
	fprintf(file,"score: %d temps: %d playername:%s \n",s1.score,s1.temps,s1.playername);
	fclose(file);
}
/**
* @brief To find the best 3 scores .
* @param trois table of scoreinfo .
* @param filename string .
* @return Nothing
*/
void bestscore(char *filename, scoreinfo trois[]) {
    scoreinfo *scores = NULL;
    int nbScores = 0;
    scoreinfo s;
    scoreinfo tmp;
    int i,j,z;
    TTF_Font *police;
    SDL_Color couleurNoire={255,255,255};
    SDL_Surface *texte;
    SDL_Rect position;
    char ch[100];
  
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", filename);
        return;
    }  
  
        
        while (fscanf(file, "%d %d %s\n", &scores[nbScores].score,&scores[nbScores].temps,scores[nbScores].playername) == 3) {
   
            nbScores++;
        }

    fclose(file);


    for (i = 0; i < nbScores - 1; i++) {
        for (j = i + 1; j < nbScores; j++) {
            if (scores[i].score < scores[j].score || (scores[i].score == scores[j].score && scores[i].temps > scores[j].temps)) {
              
                tmp = scores[i];
                scores[i] = scores[j];
                scores[j] = tmp;
            }
        }
    }

    


    free(scores);
    TTF_Init();
	police=TTF_OpenFont("times.ttf",65);
	
	for(z=0;z<3;z++)
	{
	sprintf(ch,"%d ",trois[z].score);
	trois[z].surface1=TTF_RenderText_Blended(police,ch,couleurNoire);
	
	sprintf(ch," %d",trois[z].temps);
	trois[z].surface2=TTF_RenderText_Blended(police,ch,couleurNoire);
	
	trois[z].surface3=TTF_RenderText_Blended(police,trois[z].playername,couleurNoire);

	}
	TTF_CloseFont(police);
}
/**
* @brief To show the best 3 scores .
* @param trois table of scoreinfo .
* @param screen the screen
* @return Nothing
*/
void afficherbest(SDL_Surface *screen, scoreinfo trois[]) {
    int z;
    for(z=0;z<3;z++)
	{
	if(trois[z].surface1!=NULL && trois[z].surface2!=NULL && trois[z].surface3!=NULL)
		{trois[1].position1.y=250;
		trois[1].position2.y=250;
		trois[1].position3.y=250;
		
		trois[2].position1.y+=300;
		trois[2].position2.y+=300;
		trois[2].position3.y=300;
		
		trois[3].position1.y+=350;
		trois[3].position2.y+=350;
		trois[3].position3.y=350;
		
		
		
		
		
		SDL_BlitSurface(trois[z].surface1,NULL,screen,&(trois[z].position1));
		SDL_BlitSurface(trois[z].surface2,NULL,screen,&(trois[z].position2));
		SDL_BlitSurface(trois[z].surface3,NULL,screen,&(trois[z].position3));
		
		
		printf("\n aaa");
		
		
		}
		}
}
