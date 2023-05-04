#ifndef minimap_H
#define minimap_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <time.h>
/**
* @struct tic
* @brief struct for background
*/
typedef struct 
{
    SDL_Surface* background; 
    SDL_Rect posback ; 
    SDL_Surface* playerX;   
    SDL_Surface* playerO; 
    int tabsuivi[9]; 
    SDL_Rect firstpos ;
    int currentPlayer; 
    int currentTurn; 
    SDL_Surface *t ;
    TTF_Font* font; 
    SDL_Color textColor; 
    char endGameText[20]; 
    SDL_Rect textPos; 
}tic;
/**
* @struct minimap
* @brief struct for background
*/
typedef struct
{
    SDL_Surface *map;
    SDL_Surface *minijoueur;
    SDL_Surface *engime;
    SDL_Rect positionmap;
    SDL_Rect positionminijoueur;
    SDL_Rect positionengime;
} minimap;
/**
* @struct temps
* @brief struct for background
*/
typedef struct 
{
   SDL_Surface *texte; 
   SDL_Surface * score;
   int s;
   SDL_Rect position;  
   TTF_Font *police;
   char entree[100]; 
   int secondesEcoulees;   
   SDL_Color color; 
   time_t t1, t2;            
   int min, sec;             
} temps;

/**
* @struct personne
* @brief struct for background
*/
typedef struct
{
    SDL_Surface *perso;
    SDL_Rect pos;
    int dir;
} personne;

void init_map(minimap *m);

void MAJMinimap(SDL_Rect posJoueur, minimap *m, int redimensionnement);

void afficherminimap(minimap m, SDL_Surface *screen);

void animerminimap( minimap  *m , int *i);

void initialiser_temps(temps *t);

void afficher_temps(temps *t, SDL_Surface *ecran);

void free_temps(temps *t);

SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y);

int collisionPP( personne p, SDL_Surface * Masque);

void initialiserTic(tic *t) ;

void afficherTic(tic t,SDL_Surface *ecran);

int atilganer(int tabsuivi[]);

void Resultat(tic *t, SDL_Surface *screen) ;

int minimax(int tabsuivi[],int joueur);

void calcul_coup(int tabsuivi[]);


#endif

