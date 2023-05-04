#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <string.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include"ES.h"
#include "header.h"
int main()
{
	SDL_Event event;
	SDL_Surface *screen,*fond;
	int col,en=2,distEH,etat,energ=0,c;
	health_bar HB;
	Uint32 DebT=0,FinT,T;
	//printf("%u\n",DebT);
	Personne p;
	fond=IMG_Load("fond.jpeg");
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	screen=SDL_SetVideoMode (1050,700,32, SDL_HWSURFACE | SDL_DOUBLEBUF) ;
	int quitter=0;
	Ennemi e,eIA;
	initEnnemiIA(&eIA,650,350);
	init_health_bar(&HB);
	initperso(&p);
	p.position.x=10;
	p.position.y=450;
	initEnnemi(&e,200,320);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
	while (quitter!=1)
	{
		
		SDL_BlitSurface(fond,NULL,screen,NULL);
		affichiervie(p,screen);
		if (p.vie>0)
			afficheperso(p,screen);
		if (en==1)
		{
			afficherEnnemi(e,screen,en);
			move(&e);
			animerEnnemi(&e,&en);
			SDL_Delay(75);
			col=collisionBB(p,e,en);
			printf("%d\n",col);
		}
		else if (en==2)
		{
			afficherEnnemi(eIA,screen,en);
			afficher_health_bar(p,eIA,HB,screen);
			if ((collisionBB(p,eIA,2))&&(eIA.etat==2))
			{
			if (DebT==0)
			{
				p.vie--;
				if (eIA.direction==1)
					p.position.x-=100;
				else
					p.position.x+=100;
				DebT=SDL_GetTicks();
			}
			else
			{
				FinT=SDL_GetTicks();
				T=FinT-DebT;
				if (T>=4200)
				{
					p.vie--;
					if (eIA.direction==1)
						p.position.x-=100;
					else
						p.position.x+=100;
					DebT=SDL_GetTicks();
				}
				//printf("%u\n",T);
			}
			}
			switch(eIA.etat)
			{
				case (0):
					animerEnnemi(&eIA,&en);
					break;
				case (1):
					animerEnnemi(&eIA,&en);
					moveIA(&eIA);
					eIA.energie--;
					break;
				case (2):
					animerEnnemi(&eIA,&en);
					moveIA(&eIA);
					eIA.energie--;
					break;
				case (3):
					animerEnnemi(&eIA,&en);
					moveIA(&eIA);
					break;
				case (4):
					animerEnnemi(&eIA,&en);
					moveIA(&eIA);
					break;
				case (5):
					animerEnnemi(&eIA,&en);
					c++;
					if (c>200)
					{
						eIA.energie=150;
						c=0;	
					}
					break;
			}
			
			distEH=eIA.pos.x-p.position.x;
			//printf("%d\n",distEH);
			etat=eIA.etat;
			updateEnnemiState (&eIA,distEH,&p);
			if (eIA.etat!=etat)
				eIA.pos_sp.x=0;
			//printf("%d\n",eIA.etat);
			SDL_Delay(75);
			col=collisionBB(p,eIA,en);
			//printf("%d\n",col);
			if ((eIA.etat==5)&&(p.attack==1)&&(col==1))
			{
				p.attack=0;
				eIA.vie--;
				HB.p_vie.x-=((float)1/50)*500;
				printf("%d\n",eIA.vie);
			}
			printf("%d\n",eIA.energie);
		}
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
				case SDLK_f:
					screen=SDL_SetVideoMode (1050,700,32, SDL_HWSURFACE | SDL_DOUBLEBUF|SDL_FULLSCREEN) ;
					break;
				case SDLK_n:
					screen=SDL_SetVideoMode (1050,700,32, SDL_HWSURFACE | SDL_DOUBLEBUF) ;
					break;
				case SDLK_q:
					quitter=1;
					break;
				case SDLK_a:
					en=1;
					break;
				case SDLK_z:
					en=2;
					break;
				case SDLK_UP:
            				if (p.sens==0)
            				{p.direction=2;
            				moveperso(&p);
            				animerperso(&p,&event);}
           				if (p.sens==1) 
            				{p.direction=3;
            				moveperso(&p);
            				animerperso(&p,&event);}
            				break;
            			case SDLK_RIGHT:
            				p.direction=0;
            				p.sens=0;
           				moveperso(&p);
            				animerperso(&p,&event);
            				break;
            			case SDLK_LEFT:
            				p.direction=1;
            				p.sens=1;
            				moveperso(&p);
            				animerperso(&p,&event);
            				break;
            			
            				
            			case SDLK_SPACE:
            				if (p.direction==0)
            				{		
                 			p.acceleration = 70;
                			p.position.x+=p.vitesse+p.acceleration;
                					
                			}
                			else if (p.direction==1)
                			{
                			p.acceleration = 70;
                			p.position.x-=p.vitesse+p.acceleration;
                			}
                			break;
                		case SDLK_s:
                			printf("attack\n");
                			p.attack=1;
                			break;/*
                		case SDLK_w:
                			eIA.etat=0;
                			eIA.pos_sp.x=0;
                			break;
                		case SDLK_x:
                			eIA.etat=1;
                			eIA.pos_sp.x=0;
                			break;
                		case SDLK_c:
                			eIA.etat=2;
                			eIA.pos_sp.x=0;
                			break;
                		case SDLK_v:
                			eIA.etat=3;
                			eIA.pos_sp.x=0;
                			break;
                		case SDLK_b:
                			eIA.etat=4;
                			eIA.pos_sp.x=0;
                			break;*/	
			}
			}
		}
		SDL_Flip(screen);	
	}
	SDL_FreeSurface(p.avatar[p.direction][p.num]);
	liberer(eIA);
	SDL_Quit();
	return 0;
}
