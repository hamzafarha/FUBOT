#ifndef ES_H_INCLUDED
#define ES_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>
#include "header.h"
typedef struct Enemy
{
  SDL_Surface *image[2];
  SDL_Surface *imageIA[7][2];
  int etat;
  int vie;
  SDL_Rect pos;
  SDL_Rect pos_sp;
  int direction;
  int energie;
}Ennemi;
typedef struct
{
	SDL_Surface *enN,*enB,*bar;
	SDL_Rect p_en,p_bar,p_vie;
}health_bar;
void initEnnemi(Ennemi*e,int x,int y);
void afficherEnnemi(Ennemi e, SDL_Surface * screen,int en);
void animerEnnemi( Ennemi * e,int *en);
void move( Ennemi * e);
int collisionBB( Personne P,Ennemi e,int en);
void moveIA( Ennemi * e);
void liberer(Ennemi e);
void initEnnemiIA(Ennemi *e,int x,int y);
void updateEnnemiState (Ennemi* e, int distEH,Personne *p);
void init_health_bar(health_bar *HB);
void afficher_health_bar(Personne p,Ennemi e,health_bar HB,SDL_Surface * screen);
#endif
