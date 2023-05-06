
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "header.h"
void initperso(Personne *p)
{
	p->position.x=10;
	p->position.y=300;
	p->pos_vie.x=800;
	p->pos_vie.y=30;
	p->vie=3;
	p->direction=6;
	p->num=0;
	p->sens=1;
	p->vitesse=3;
	p->acceleration=0.5;
	p->floor=300;
	p->isjumping=0;
	p->afficher_vie[0]=IMG_Load("vie0.png");
	p->afficher_vie[1]=IMG_Load("vie1.png");
	p->afficher_vie[2]=IMG_Load("vie2.png");
	p->afficher_vie[3]=IMG_Load("vie3.png");
	p->avatar[0][0]=IMG_Load("r1.png");
	p->avatar[0][1]=IMG_Load("r2.png");
	p->avatar[0][2]=IMG_Load("r3.png");
	p->avatar[0][3]=IMG_Load("r4.png");
	p->avatar[0][4]=IMG_Load("r5.png");
	p->avatar[1][0]=IMG_Load("l1.png");
	p->avatar[1][1]=IMG_Load("l2.png");
	p->avatar[1][2]=IMG_Load("l3.png");
	p->avatar[1][3]=IMG_Load("l4.png");
	p->avatar[1][4]=IMG_Load("l5.png");
	p->avatar[2][0]=IMG_Load("u1.png");
	p->avatar[2][1]=IMG_Load("u2.png");
	p->avatar[2][2]=IMG_Load("u3.png");
	p->avatar[3][0]=IMG_Load("l1.png");
	p->avatar[3][1]=IMG_Load("l2.png");
	p->avatar[3][2]=IMG_Load("l3.png");
	p->avatar[4][0]=IMG_Load("d1.png");
	p->avatar[4][1]=IMG_Load("d2.png");
	p->avatar[4][2]=IMG_Load("d3.png");
	p->avatar[5][0]=IMG_Load("d1.png");
	p->avatar[5][1]=IMG_Load("d2.png");
	p->avatar[5][2]=IMG_Load("d3.png");
	p->avatar[6][0]=IMG_Load("a.png");
	p->avatar[7][0]=IMG_Load("b.png");
}
void initialiserScore(  Score *score )
{
	char chaine[20];
	SDL_Color couleurNoire ={255,255,255};
	
	score->posScore.x=50 ;
	score->posScore.y=50;
	score->posFond.x=score->posScore.x-20;
	score->posFond.y=score->posScore.y-20;	

	score->fondScore = IMG_Load("bois.png");
	score->police = TTF_OpenFont("Colleged.ttf", 50);

	score->scoreActuel=0;
	sprintf(chaine,"%d", score->scoreActuel);

	score->texteScore=TTF_RenderText_Blended(score->police ,chaine, couleurNoire);		

}
void afficherScore(SDL_Surface *screen, Score *score)
{
	SDL_Color couleurNoire ={255,255,255};
	
	char chaine[20];
	
	score->scoreActuel+=1;
	sprintf(chaine,"%d", score->scoreActuel);
	
	score->texteScore =TTF_RenderText_Blended(score->police,chaine, couleurNoire);
	
	SDL_BlitSurface(score->fondScore, NULL, screen, &score->posFond);
	SDL_BlitSurface(score->texteScore, NULL, screen, &score->posScore);
}
void afficheperso(Personne p,SDL_Surface *screen)
{
	SDL_BlitSurface (p.avatar[p.direction][p.num],NULL,screen,&p.position);
	
}
void affichiervie(Personne p, SDL_Surface *screen){
	
	SDL_BlitSurface(p.afficher_vie[p.vie],NULL,screen,&p.pos_vie);
}

void moveperso(Personne *p,Uint32 dt)
{
	int x,var;
	/*if (p->sens==1)
		var=1;
	if (p->sens==2)
		var=-1;*/
	switch(p->sens)
	{
	case 1:
		var=1;
		x=var*((p->acceleration) * dt * dt) / 2 + (p->vitesse) * dt;
		p->position.x+=x;
		p->acceleration+=0.1;
		break;
	case -1:
		var=1;
		x=var*((p->acceleration) * dt * dt) / 2 + (p->vitesse) * dt;
		p->position.x+=x;
		p->acceleration-=0.5;
		if(p->acceleration<0.5)
			{p->vitesse=0;
			p->direction=6;
			p->acceleration=0;}
			
		break;
	case 2:
		var=-1;
		x=var*((p->acceleration) * dt * dt) / 2 + (p->vitesse) * dt;
		if (p->position.x+x<0)
			p->position.x=0;
		else
			p->position.x+=x;	
		p->acceleration+=0.1;
		break;
	case -2:
		var=-1;
		x=var*((p->acceleration) * dt * dt) / 2 + (p->vitesse) * dt;
		p->position.x+=x;
		p->acceleration-=0.5;
		if(p->acceleration<0.5)
			{p->vitesse=0;
			p->direction=7;
			p->acceleration=0;}
			
		break;
		
		
		
	}
	//x=var*(p->vitesse);
	//x=var*((p->acceleration) * dt * dt) / 2 + (p->vitesse) * dt;
	//p->position.x+=x;		
	/*if (p->direction==0)
		p->position.x+=p->vitesse;
	else if (p->direction==1)
		p->position.x-=p->vitesse;
*/


}
void animerperso(Personne *p )
{
	
			if (p->direction==0)
			{if (p->num<4)
			{
				p->num++;
				
			}
			else
				p->num=0;}
				
				
		
			if (p->direction==1)
			{if (p->num<4)
			{
				p->num++;
				
			}
				else
				p->num=0;}
				
		
			if (p->sens==1)
			{if(p->direction==2)
			{if (p->num<2)
			{
				p->num++;
				}
			else
			{
				p->num=0;
				}
				}
			if (p->direction==4)
			{
			if (p->num<2)
				p->num++;
			else
				p->num=0;
				}
				}
			if (p->sens==2)
			{if(p->direction==3)
			{if (p->num<2)
			{
				p->num++;
				
				}
			else
			{
				p->num=0;
				
				}
			}
			if (p->direction==5)
			{
			if (p->num<2)
				p->num++;
			else
				p->num=0;
			}
			}
			if (p->direction==6)
			{
			
				p->num=0;
			}
			if (p->direction==7)
			{
			
				p->num=0;
			}
			
			
			
	
				
			

}
void saut(Personne *p, Uint32 dt, int posinit)
{

	p->position.y = (posinit) * (posinit)+ 200;
}
/*void saut(Personne *p,Uint32 dt)
{
	int var,x;
	//printf("direction = %d",p->direction);
	if (p->sens==1)
		var=1;
	if (p->sens==2)
		var=-1;
	
	if((*p).isjumping==0)
	 	(*p).isjumping = 1;
	if((*p).isjumping>0)
		{if ((*p).isjumping <5)
			 (*p).isjumping ++;
			 
		else 
			(*p).isjumping=-1;}
	(*p).position.y-=10*((*p).isjumping);
	//printf("x = %d, var=%d",x,var);
	x=var*((*p).isjumping*(*p).isjumping);
	(*p).position.x+=x;
	//(*p).position.x+=(*p).isjumping*(*p).isjumping+10;
}*/
void initperso2(Personne *p)
{
	
	p->position.x=10;
	p->position.y=280;
	p->pos_vie.x=800;
	p->pos_vie.y=30;
	p->vie=3;
	p->direction=6;
	p->num=0;
	p->sens=1;
	p->vitesse=3;
	p->acceleration=0.5;
	p->floor=280;
	p->isjumping=0;
	p->afficher_vie[0]=IMG_Load("vie0.png");
	p->afficher_vie[1]=IMG_Load("vie1.png");
	p->afficher_vie[2]=IMG_Load("vie2.png");
	p->afficher_vie[3]=IMG_Load("vie3.png");
	p->avatar[0][0]=IMG_Load("R1.png");
	p->avatar[0][1]=IMG_Load("R2.png");
	p->avatar[0][2]=IMG_Load("R3.png");
	p->avatar[0][3]=IMG_Load("R4.png");
	p->avatar[0][4]=IMG_Load("R5.png");
	p->avatar[1][0]=IMG_Load("L1.png");
	p->avatar[1][1]=IMG_Load("L2.png");
	p->avatar[1][2]=IMG_Load("L3.png");
	p->avatar[1][3]=IMG_Load("L4.png");
	p->avatar[1][4]=IMG_Load("L5.png");
	p->avatar[2][0]=IMG_Load("JR1.png");
	p->avatar[2][1]=IMG_Load("JR2.png");
	p->avatar[2][2]=IMG_Load("JR3.png");
	p->avatar[3][0]=IMG_Load("JL1.png");
	p->avatar[3][1]=IMG_Load("JL2.png");
	p->avatar[3][2]=IMG_Load("JL3.png");
	p->avatar[4][0]=IMG_Load("AR1.png");
	/*if (p->avatar[0]==NULL)
	{
		printf("Erreur:%s\n",SDL_GetError());
		return;
	}*/
	p->avatar[4][1]=IMG_Load("AR2.png");
	p->avatar[4][2]=IMG_Load("AR3.png");
	p->avatar[5][0]=IMG_Load("AL1.png");
	p->avatar[5][1]=IMG_Load("AL2.png");
	p->avatar[5][2]=IMG_Load("AL3.png");
	p->avatar[6][0]=IMG_Load("R1.png");
	p->avatar[7][0]=IMG_Load("L1.png");

}
void afficheperso2(Personne p,SDL_Surface *screen)
{
	SDL_BlitSurface (p.avatar[p.direction][p.num],NULL,screen,&p.position);
	
}

 		

 	



