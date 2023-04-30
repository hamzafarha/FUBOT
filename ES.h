#ifndef ES_H_INCLUDED
#define ES_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "header.h"
typedef struct Enemy
{
  SDL_Surface *image[2];
  SDL_Surface *imageIA[6];
  int etat;
  int vie;
  SDL_Rect pos;
  SDL_Rect pos_sp;
  int direction;

}Ennemi;

void initEnnemi(Ennemi*e,int x,int y);
void afficherEnnemi(Ennemi e, SDL_Surface * screen,int en);
void animerEnnemi( Ennemi * e,int en);
void move( Ennemi * e);
int collisionBB( SDL_Surface* p, SDL_Rect posp,Ennemi e);
void moveIA( Ennemi * e);
void liberer(Ennemi e);
void initEnnemiIA(Ennemi *e,int x,int y);
void updateEnnemiState (Ennemi* e, int distEH,Personne *p);

#endif
