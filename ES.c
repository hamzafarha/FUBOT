#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
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
		SDL_BlitSurface(e.imageIA[e.etat],&e.pos_sp,screen,&e.pos);	
}
void animerEnnemi( Ennemi * e,int en)
{
	int w,f;
	if (en==1)
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
		}
		e->pos_sp.w=e->imageIA[e->etat]->w/f;
		w=e->imageIA[e->etat]->w;
	}
	e->pos_sp.x += e->pos_sp.w ;
	if (e->pos_sp.x>=w-10)
    	{
    		if (e->etat==4)
    			e->vie=-1;
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
int collisionBB( SDL_Surface* p, SDL_Rect posp,Ennemi e)
{
	int collision;
  	if (((posp.x + p->w) < e.pos.x) || (posp.x > (e.pos.x + e.pos_sp.w)) || ((e.pos.y + p->h) < e.pos.y) || (posp.y > (e.pos.y + e.pos_sp.h)))
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
	SDL_FreeSurface(e.imageIA[e.etat]);
}
void initEnnemiIA(Ennemi *e,int x,int y)
{
	e->imageIA[0]=IMG_Load("RobTranIDLE.png");
	e->imageIA[1]=IMG_Load("RobTranWalk.png");
	e->imageIA[2]=IMG_Load("RobTranAttack.png");
	e->imageIA[3]=IMG_Load("RobTranHit.png");
	e->imageIA[4]=IMG_Load("RobTranDeath.png");
	e->etat=0;
    	e->pos.y=y;
    	e->pos.x=x;
    	e->pos_sp.x=0;
    	e->pos_sp.y=0;
    	e->pos_sp.h=350;
    	e->pos_sp.w=8526/21;
	e->vie=3;
}
void moveIA( Ennemi * e)
{
	if (e->etat==1)
		e->pos.x-=5;
	else if (e->etat==3)
		e->pos.x++;
	else if (e->etat==4)
		e->pos.x++;
}
void updateEnnemiState (Ennemi* e, int distEH,Personne *p)
{
	if (distEH>520)
		e->etat=0;
	else if (distEH>=130 && distEH<=520)
		e->etat=1;
	else if (distEH<130)
		e->etat=2;
	if (p->attack==1)
	{
		p->attack=0;
		e->vie--;
		e->etat=3;
		printf("%d\n",e->vie);
	}
	if (e->vie<=0)
		e->etat=4;  
}
