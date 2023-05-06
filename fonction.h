#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define PIC_WIDTH 3072
#define PIC_HEIGHT 746
/**
* @struct background
* @brief struct for background:
* image1: image du fond 1
* image2: image du fond 2
* image3: image du fond 3
* music1: champ du musique1
* music2: champ du musique2
* music3: champ du musique3
* camerapos: position du caméra 
* screenpos: position du background
* musicplaying : verifier la musique du jeu
* direction : direction de déplacement  
*/
typedef struct 
{
       SDL_Rect camerapos;
       SDL_Rect screenpos;
       int direction;
       SDL_Surface *image1; 
       SDL_Surface *image2; 
       SDL_Surface *image3;
       Mix_Music *music1; 
       Mix_Music *music2; 
       Mix_Music *music3;
       int musicplaying;
}background;
/**
* @struct scoreinfo
* @brief struct for scoreinfo:
* score : the score of the player
* temps : time token
* playername : name of the player
*/
typedef struct
{
	int score;
	int temps;
	char playername[20];
	SDL_Surface *surface1;
	SDL_Surface *surface2;
	SDL_Surface *surface3;
	SDL_Rect position1;
	SDL_Rect position2;
	SDL_Rect position3;
}scoreinfo;
void init_background(background *bg);
void init_background2(background *bg2);
void afficher_background(background *bg,SDL_Surface *screen,int difficulte);
void partage_ecran(background *bg2, SDL_Surface *screen,int difficulte2);
void animerback(background *bg,SDL_Surface *screen);
void animerback2(background *bg2,SDL_Surface *screen);
void scrolling(background *bg , int direction,int pas);
void scrolling2(background *bg2,int direction,int pas);
void savescore(scoreinfo s1,char *filename);
void bestscore(char *filename, scoreinfo trois[]);
void afficherbest(SDL_Surface *screen, scoreinfo trois[]);	
