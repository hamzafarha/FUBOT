#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#define SCREEN_W 1050
#define SCREEN_H 453
typedef struct
{
    SDL_Rect position;
    SDL_Surface *avatar[6][10];
    int direction;
    int num;
    float vitesse;
    float acceleration;
    int floor;
    SDL_Rect pos_vie;
    SDL_Surface *afficher_vie[3];
    int score;
    SDL_Surface *afficher_score;
    int frappe;
    int vie,sens;
    int isjumping;
}Personne;
typedef struct
{
	SDL_Surface *fondScore;
   	SDL_Surface *texteScore;
   	SDL_Rect posFond;
   	SDL_Rect posScore;
   	int scoreActuel;
   	TTF_Font *police;
}Score;
void initperso(Personne *p);
void initperso2(Personne *p2);
void initialiserScore(  Score *score );
void afficherScore(SDL_Surface *screen, Score *score);
void afficheperso(Personne p,SDL_Surface *screen);
void afficheperso2(Personne p2,SDL_Surface *screen);
void affichiervie(Personne p, SDL_Surface *screen);
void animerperso(Personne *p );
void moveperso(Personne *p, Uint32 dt);

void saut(Personne *p,Uint32 dt);
//int gestionvie(Personne *p);
#endif
