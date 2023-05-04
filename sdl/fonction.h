#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define PIC_WIDTH 3072
#define PIC_HEIGHT 746
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
