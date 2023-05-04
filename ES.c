#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include"ES.h"
#include "header.h"
void initEnnemi(Ennemi*e,int x,int y)
{
	e->image[0]=IMG_Load("RobSHARKR.png");
	e->image[1]=IMG_Load("RobSHARKL.png");
    	e->pos.y=y;
    	e->pos.x=x;
    	e->direction=0;
    	e->pos_sp.x=0;
    	e->pos_sp.y=0;
    	e->pos_sp.h=259;
    	e->pos_sp.w=182;
	e->vie=1;
}
void afficherEnnemi(Ennemi e, SDL_Surface * screen,int en)
{
	if ((en==1)&&(e.vie!=0))
		SDL_BlitSurface(e.image[e.direction],&e.pos_sp,screen,&e.pos);
	else if ((en==2)&&(e.vie>=-1))
		SDL_BlitSurface(e.imageIA[e.etat][e.direction],&e.pos_sp,screen,&e.pos);	
}
void animerEnnemi( Ennemi * e,int *en)
{
	int w;
	float f;
	if (*en==1)
		w=e->image[e->direction]->w;
	else
	{
		
		switch (e->etat)
		{
			case (0):
				f=21;
				break;
			case (1):
				f=25;
				break;
			case (2):
				f=21;
				break;
			case (3):
				f=22;
				break;
			case (4):
				f=27;
				break;
			case (5):
				f=41;
				break;
		}
		e->pos_sp.w=(int)round((double)e->imageIA[e->etat][e->direction]->w/f);
		w=e->imageIA[e->etat][e->direction]->w;
	}
	e->pos_sp.x += e->pos_sp.w ;
	if (e->pos_sp.x>=w-10)
    	{
    		if (e->etat==4)
    		{
    			e->vie=-1;
    			*en=-1;
    		}
    			
    		else
        		e->pos_sp.x=0;
    	}
}
void move( Ennemi * e)
{

	if (e->direction==0)
	{
	if (e->pos.x<800)
		e->pos.x+=5;
	else 
		e->direction=1;
	}
	if (e->direction==1)
	{
	if (e->pos.x>100)
		e->pos.x-=5;
	else 
		e->direction=0;
	}
}
int collisionBB( Personne P,Ennemi e,int en)
{
	int collision;
	SDL_Surface *p=P.avatar[P.direction][P.num]; 
	SDL_Rect posp=P.position;
	int up=0,xB=0;
	if ((en==2)&&(e.etat==2))
	{
		up=190;
		xB=100;
	}
	e.pos_sp.w-=xB;
	e.pos_sp.x-=xB;
	e.pos_sp.y-=up;
  	if (((posp.x + p->w) < e.pos.x) || (posp.x > (e.pos.x + e.pos_sp.w)) || ((posp.y + p->h) < e.pos.y) || (posp.y > (e.pos.y + e.pos_sp.h)))
  	{
    		collision=0;
  	} 
  	else 
  	{
    		collision=1;
  	}
  	return collision;
}
void liberer(Ennemi e)
{
	SDL_FreeSurface(e.image[0]);
	SDL_FreeSurface(e.image[1]);
	SDL_FreeSurface(e.imageIA[e.etat][e.direction]);
}
void initEnnemiIA(Ennemi *e,int x,int y)
{
	e->imageIA[0][0]=IMG_Load("RobTranIDLER.png");
	e->imageIA[1][0]=IMG_Load("RobTranWalkR.png");
	e->imageIA[2][0]=IMG_Load("RobTranAttackR.png");
	e->imageIA[3][0]=IMG_Load("RobTranHitR.png");
	e->imageIA[4][0]=IMG_Load("RobTranDeathR.png");
	e->imageIA[5][0]=IMG_Load("RobTranTiredR.png");
	e->imageIA[0][1]=IMG_Load("RobTranIDLE.png");
	e->imageIA[1][1]=IMG_Load("RobTranWalk.png");
	e->imageIA[2][1]=IMG_Load("RobTranAttack.png");
	e->imageIA[3][1]=IMG_Load("RobTranHit.png");
	e->imageIA[4][1]=IMG_Load("RobTranDeath.png");
	e->imageIA[5][1]=IMG_Load("RobTranTired.png");
	e->direction=1;
	e->etat=0;
    	e->pos.y=y;
    	e->pos.x=x;
    	e->pos_sp.x=0;
    	e->pos_sp.y=0;
    	e->pos_sp.h=350;
    	e->pos_sp.w=8526/21;
    	e->energie=150;
	e->vie=50;
}
void moveIA( Ennemi * e)
{
	if (e->direction==1)
	{
		if (e->etat==1)
			e->pos.x-=5;
		else if (e->etat==3)
			e->pos.x++;
		else if (e->etat==4)
			e->pos.x++;
	}
	if (e->direction==0)
	{
		if (e->etat==1)
			e->pos.x+=5;
		else if (e->etat==3)
			e->pos.x--;
		else if (e->etat==4)
			e->pos.x--;
	}
}
void updateEnnemiState (Ennemi* e, int distEH,Personne *p)
{
	int w=0;
	if (distEH<(-(e->pos_sp.w/2)))
	{
		e->direction=0;
		w=e->pos_sp.w/2;
	}	
	else
		e->direction=1;
	distEH=abs(distEH+w);
	if ((distEH>520)||(p->vie<=0))
	{
		e->etat=0;
		e->pos.y=350;
	}		
	else if (distEH>=130 && distEH<=520)
	{
		e->etat=1;
		e->pos.y=350;
	}
	else if (distEH<130)
	{
		e->etat=2;
		e->pos.y=230;
	}
	/*	
	if (p->attack==1)
	{
		p->attack=0;
		e->vie--;
		e->etat=3;
		e->pos.y=350;
		printf("%d\n",e->vie);
	}*/
	if (e->energie==0)
	{
		e->etat=5;
		e->pos.y=350;
	}
	if (e->vie<=0)
	{
		e->etat=4; 
		e->pos.y=350;
	} 
}
void init_health_bar(health_bar *HB)
{
	HB->enB=IMG_Load("enB.png");
	HB->enN=IMG_Load("enN.png");
	HB->bar=IMG_Load("HB.jpg");
	HB->p_en.x=920;
	HB->p_en.y=570;
	HB->p_bar.x=420;
	HB->p_bar.y=610;
	HB->p_vie.x=500;
	HB->p_vie.y=0;
	HB->p_vie.w=500;
	HB->p_vie.h=50;
}
void afficher_health_bar(Personne p,Ennemi e,health_bar HB,SDL_Surface * screen)
{
	if (e.etat==5)
		SDL_BlitSurface(HB.enB,NULL,screen,&HB.p_en);
	else 
		SDL_BlitSurface(HB.enN,NULL,screen,&HB.p_en);
	SDL_BlitSurface(HB.bar,&HB.p_vie,screen,&HB.p_bar);
}
