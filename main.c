#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "header.h"
int main(int argc, char *argv[])
{
    Personne p,p2;
    Score score;
    int x,var;
    int quitter=0;
    int posinit1=-10;
    int posinit2=-9;
    Uint32 dt, t_prev;
    SDL_Surface *screen=NULL;
    SDL_Surface *background=NULL;
    int appelperso=0;
    SDL_Rect positionFond;
    positionFond.x = 0;
    positionFond.y = 0;
    SDL_Event event;
    TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
    screen=SDL_SetVideoMode (SCREEN_W,SCREEN_H,32, SDL_HWSURFACE | SDL_DOUBLEBUF) ;
    SDL_WM_SetCaption("perso",NULL);
    background=IMG_Load("Level.jpg");
    initperso(&p);
    initperso2(&p2);
    initialiserScore(&score );
    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
    while(quitter==0)
    {
    t_prev = SDL_GetTicks();
    SDL_BlitSurface (background,NULL,screen,&positionFond);
    afficheperso(p2,screen);
    afficherScore(screen,&score);
    affichiervie(p,screen);
    printf("direction = %d",p2.direction);
    printf("    sens = %d\n",p2.sens);
    if (appelperso==1)
    {
    
    	afficheperso(p,screen);
    	printf("direction2 = %d",p.direction);
        printf("    sens2 = %d\n",p.sens);
    }
        while((SDL_PollEvent(&event)))
        {
        
        	switch (event.type)
		{
			
			case SDL_QUIT:
				quitter=1;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
        			{
            				case SDLK_UP:
            					if ((p.sens==1)||(p.sens==-1))
            					{
            					
            					p.direction=2;
            					//saut(&p,dt);
            					//animerperso(&p);
            					}
            					
            					if ((p.sens==2)||(p.sens==-2))
            					{p.direction=3;
            					//saut(&p,dt);
            					//animerperso(&p);
            					}
            					break;
            				case SDLK_RIGHT:				
            					p.sens=1;
            					p.direction=0;
           					//moveperso(&p,dt);
            					//animerperso(&p);
            					break;
            				case SDLK_LEFT:
            					p.sens=2;
            					p.direction=1;
            					//moveperso(&p,dt);
            					//animerperso(&p);
            					break;
            				case SDLK_d:
            					p2.sens=1;
            					p2.direction=0;
           					//moveperso(&p2,dt);
            					//animerperso(&p2);
            					break;
            				case SDLK_q:          					
            					p2.sens=2;
            					p2.direction=1;
           					//moveperso(&p2,dt);
            					//animerperso(&p2);
            					break;
            				case SDLK_z:
            					if ((p2.sens==1)||(p2.sens==-1))
            					{p2.direction=2;
            					//saut(&p2,dt);
            					//animerperso(&p2);
            					}
            					if ((p2.sens==2)||(p2.sens==-2)) 
            					{p2.direction=3;
            					//saut(&p2,dt);
            					//animerperso(&p2);
            					}
            					break;
            				case SDLK_m:
            					if ((p2.sens==1)||(p2.sens==-1))
            					{p2.direction=4;
            					//moveperso(&p2,dt);
            					//animerperso(&p2);
            					}
            					if ((p2.sens==2)||(p2.sens==-2)) 
            					{p2.direction=5;
            					//moveperso(&p2,dt);
            					//animerperso(&p2);
            					}
            					break;
           				
           				case SDLK_p: 
           					appelperso=1;
            					break;
            				case SDLK_SPACE:
            					p.acceleration=5;
            					if (p.sens==1)
            					
            					{p.direction=0;		
                 					
                					p.position.x+=((p.acceleration) * dt * dt) / 2 + (p.vitesse) * dt;
                					
                				}
                				else if (p.sens==2)
                				{p.direction=1;
                					
                					p.position.x-=((p.acceleration) * dt * dt) / 2 + (p.vitesse) * dt;
                				}
                				break;
                			
                				
                	}break;		
                case SDL_KEYUP:
                	switch(event.key.keysym.sym)
              		{
              			case SDLK_RIGHT:
              				p.direction=0;
              				p.sens=-1;
              				//moveperso(&p,dt);
            				//animerperso(&p);
            				
 				break;
 				case SDLK_LEFT:
 					p.direction=1;
              				p.sens=-2;
              				//moveperso(&p,dt);
            				animerperso(&p);
            			break;
            			case SDLK_d:
            				p2.direction=0;
              				p2.sens=-1;
              				//moveperso(&p2,dt);
            				//animerperso(&p2);
 				break;
 				case SDLK_q:
 					p2.direction=1;
              				p2.sens=-2;
              				//moveperso(&p2,dt);
            				//animerperso(&p2);
            			break;/*
            			case SDLK_UP:
            			if ((p.sens==1)||(p.sens==-1))
					var=1;
				if ((p.sens==2)||(p.sens==-2))
					var=-1;
            			while (p.isjumping!=0)
            			{
            				if((p).isjumping<0)
						{if ((p).isjumping >-5)
			 				(p).isjumping --;
						else 
							(p).isjumping=0;}
					(p).position.y-=10*((p).isjumping);
					x=var*((p).isjumping*(p).isjumping);
					(p).position.x+=x;
					//SDL_Delay(100);
				}
				break;*/
			}				
 		break;	
            	default:
			 break;		
              	}
              		
	}
	

	if ((p.direction == 2)||(p.direction == 3))
		{
			saut(&p,dt,posinit1);
			posinit1 += 1;
			if (posinit1 == 11)
			{
				if (p.direction == 2)
					p.direction = 0;
				if (p.direction == 3)
					p.direction = 1;
				posinit1 = -10;
			}
		}
	if ((p2.direction == 2)||(p2.direction == 3))
		{
			saut(&p2,dt,posinit2);
			posinit2 += 1;
			if (posinit2 == 10)
			{
				if (p2.direction == 2)
					p2.direction = 0;
				if (p2.direction == 3)
					p2.direction = 1;
				posinit2= -9;
			}
		}
	
	dt = SDL_GetTicks() - t_prev;
	
	animerperso(&p2);
	if ((p2.direction!=6)&&(p2.direction!=7))
		moveperso(&p2,dt);
			
	if (appelperso==1)
	{
		animerperso(&p);
		if ((p.direction!=6)&&(p.direction!=7)) 
			moveperso(&p,dt);
	
	}
			
	
	    	SDL_Flip(screen);
    	SDL_Delay(50);
    	    }
    
    SDL_FreeSurface(p2.avatar[p2.direction][p2.num]);
    SDL_FreeSurface(p.avatar[p.direction][p.num]);
    SDL_Quit();
return 0;
}
