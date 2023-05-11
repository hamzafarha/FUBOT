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
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"
/**
* @brief To initialize the background bg .
* @param b the background b.
* @return Nothing
*/
/*void init_background(background *bg)
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
	bg->images[0] = IMG_Load("yeux_ouverts.png");
       bg->images[1] = IMG_Load("yeux_demi_fermes.png");
       bg->images[2] = IMG_Load("yeux_fermes.png");
       bg->pos.x=-4000;
       printf("%d",bg->pos.x);
       bg->pos.y=-100;
       bg->pos.w=bg->images[0]->w;
       bg->pos.h=bg->images[0]->h;
}*/
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
	bg->camerapos.w=SCREEN_WIDTH/2;
	bg->camerapos.h=SCREEN_HEIGHT;
	bg->screenpos.x=0;
	bg->screenpos.y=0;
	bg->screenpos.w=SCREEN_WIDTH/2;
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
	bg2->camerapos.x=0;
	bg2->camerapos.y=1726-SCREEN_HEIGHT;
	bg2->camerapos.w=2+SCREEN_WIDTH/2;
	bg2->camerapos.h=SCREEN_HEIGHT;
	bg2->screenpos.x=2+SCREEN_WIDTH/2;
	bg2->screenpos.y=0;
	bg2->screenpos.w=SCREEN_WIDTH/2;
	bg2->screenpos.h=SCREEN_HEIGHT;
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
* @brief To scroll the background to 4 directions .
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

/**
* @brief To save the score .
* @param s1 the scoreinfo .
* @param filename string .
* @return Nothing
*/
void animerback(SDL_Surface *screen) {
    SDL_Surface *images[3];
    images[0] = IMG_Load("yeux_ouverts.png");
    images[1] = IMG_Load("yeux_demi_fermes.png");
    images[2] = IMG_Load("yeux_fermes.png");
    SDL_Rect pos={-2000,0,images[0]->w,images[0]->h};
    for (int i = 0; i < 3; i++) {
     
        SDL_BlitSurface(images[i], NULL, screen,NULL);
        SDL_Flip(screen);
        SDL_Delay(10);
    }
}
void animerback2(SDL_Surface *screen)
{
    SDL_Surface *images[3];
    images[0] = IMG_Load("yeux_ouverts.png");
    images[1] = IMG_Load("yeux_demi_fermes.png");
    images[2] = IMG_Load("yeux_fermes.png");
    SDL_Rect pos={2+SCREEN_WIDTH/2,0,images[0]->w,images[0]->h};
    for (int i = 0; i < 3; i++) {
     
        SDL_BlitSurface(images[i], NULL, screen,&pos);
        SDL_Flip(screen);
        SDL_Delay(10);
    }
} 
void savescore(scoreinfo s1,char *filename)
{
	FILE *file=fopen(filename,"a+");
	s1.score=rand()% 100+1;
	s1.temps=rand()% 100+1;
	strncpy(s1.playername,"hamza",sizeof("hamza"));
	printf("\n aaaaaa");
	if(file==NULL){
		printf("Erreur lors de l'ouverture du fichier %s \n",filename);
	}
	else
		fprintf(file,"%d %d %s \n",s1.score,s1.temps,s1.playername);
	fclose(file);
}
/**
* @brief To find the best 3 scores .
* @param trois table of scoreinfo .
* @param filename string .
* @return Nothing
*/
void bestscore(char *filename, scoreinfo trois[]) {
    int nbScores = 0;
    scoreinfo s;
    scoreinfo tmp;
    int i,j,z;
    TTF_Font *police;
    SDL_Color couleurNoire={0,0,0};
    char ch[100];
    s.position1.x=400;
    s.position2.x=500;
    s.position3.x=600;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", filename);
        return;
    }  
  
        
       while (!feof(file)) {
             fscanf(file, "%d %d %s \n", &s.score,&s.temps,s.playername);
   	     trois[nbScores]=s;
             nbScores++;
        }
    fclose(file);
    for (i = 0; i < nbScores - 1; i++) {
        for (j = i + 1; j < nbScores; j++) {
            if (trois[i].score < trois[j].score || (trois[i].score == trois[j].score && trois[i].temps > trois[j].temps)) {
              
                tmp = trois[i];
                trois[i] = trois[j];
                trois[j] = tmp;
     
  
    }
}
}
	TTF_Init();
	police=TTF_OpenFont("times.ttf",40);
	
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
void afficherbest(SDL_Surface *screen, scoreinfo trois[]) 
{
    int z,i;
    for(i=0;i<3;i++)
    {
    	printf("%d %d %s",trois[i].score,trois[i].temps,trois[i].playername);
    }
    for(z=0;z<3;z++)
	{
	if(trois[z].surface1!=NULL && trois[z].surface2!=NULL && trois[z].surface3!=NULL)
		{trois[0].position1.y=230;
		trois[0].position2.y=230;
		trois[0].position3.y=230;
		
		trois[1].position1.y=300;
		trois[1].position2.y=300;
		trois[1].position3.y=300;
		
		trois[2].position1.y=370;
		trois[2].position2.y=370;
		trois[2].position3.y=370;
		
		SDL_BlitSurface(trois[z].surface1,NULL,screen,&(trois[z].position1));
		SDL_BlitSurface(trois[z].surface2,NULL,screen,&(trois[z].position2));
		SDL_BlitSurface(trois[z].surface3,NULL,screen,&(trois[z].position3));
		printf("\n afficche");
		}
		}
}
