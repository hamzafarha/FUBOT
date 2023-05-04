#ifndef ENIGME_H_INCLUDED
#define ENIGME_H_INCLUDED
#include <SDL/SDL_ttf.h>
//
#define MAX_LINE_LENGTH 500
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 707
#include "background.h"
#include "personne.h"

typedef struct
{
SDL_Rect posanim;
}animation;

typedef struct enigme {
    char question[MAX_LINE_LENGTH];
    char reponseA[MAX_LINE_LENGTH];
    char reponseB[MAX_LINE_LENGTH];
    char reponseC[MAX_LINE_LENGTH];
    char reponseD[MAX_LINE_LENGTH];
    char correctAnswer;
    //
    SDL_Rect positionquestion;              
    SDL_Rect positionReponse1;              
    SDL_Rect positionReponse2;              
    SDL_Rect positionReponse3;              
    SDL_Rect positionReponse4;            
    //
    SDL_Surface *Backgroundimg;
    SDL_Surface *questionSurface;
    SDL_Surface *answerSurfaceA;
    SDL_Surface *answerSurfaceB;
    SDL_Surface *answerSurfaceC;    
    SDL_Surface *answerSurfaceD;
    //
    TTF_Font *fontquestion;
    TTF_Font *fontanswers;
    //
    SDL_Rect positionTemps;
    SDL_Rect positionprogress;
    SDL_Rect positionWait;
    //
    animation anima;
    //
    //
} enigme;



void afficherEnigme(enigme e, SDL_Surface *screen);
void genererEnigme(enigme *e, char *nomfichier);
void animerEnigme(enigme *e);
void afficherTemps(enigme e, SDL_Surface * screen, int timeLeft);
void afficherProgress(enigme e,SDL_Surface * screen, int progress);
void playMusic(const char* filename);
void PlaySoundEffect(const char* filename);
void free_all(enigme e);
void ImageGameOver(SDL_Surface *ecran);
void ImageGameWin(SDL_Surface *ecran);
void afficherWait(enigme e, SDL_Surface * screen, int timeLeft);
//
void sauvegarder(Personne p, background b, char *nomfichier);
void charger(Personne *p, background *b, char *nomfichier);


#endif // ENIGME_H_INCLUDED


