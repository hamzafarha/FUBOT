#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <errno.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "enigme.h"
#include "background.h"
#include "personne.h"
#define LOADING_BAR_WIDTH 300
#define LOADING_BAR_HEIGHT 20
#define MAX_TIME 4 

void genererEnigme(enigme *e, char *nomfichier) {

    FILE *f = fopen(nomfichier, "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomfichier);
        
    }

    int num_enigmes = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, f) != NULL) {
        if (strncmp(line, "Question: ", 10) == 0) {/ 
            num_enigmes++;
        }
    }

    if (num_enigmes == 0) {
        printf("Le fichier %s ne contient aucune enigme.\n", nomfichier);
        
    }
    


    srand(time(NULL));
    int enigme_num = rand() % num_enigmes + 1; 
    
    rewind(f); 

    int current_enigme = 0;
    while (fgets(line, MAX_LINE_LENGTH, f) != NULL) {
        if (strncmp(line, "Question: ", 10) == 0) {
            current_enigme++;
            if (current_enigme == enigme_num) { 
            
            sscanf(line + 10, "%[^\n]", e->question);
            sscanf(fgets(line, MAX_LINE_LENGTH, f) + 3, "%[^\n]", e->reponseA);
            sscanf(fgets(line, MAX_LINE_LENGTH, f) + 3, "%[^\n]", e->reponseB);
            sscanf(fgets(line, MAX_LINE_LENGTH, f) + 3, "%[^\n]", e->reponseC);
            sscanf(fgets(line, MAX_LINE_LENGTH, f) + 3, "%[^\n]", e->reponseD);
            e->correctAnswer = fgets(line, MAX_LINE_LENGTH, f)[8];
                break;
            }
        }
    }

    fclose(f);
    
    
    
    SDL_Color textColor = { 255, 255, 255, 255 };
    TTF_Init();
   
    e->fontquestion = TTF_OpenFont("font/questionfont.ttf", 29);
    e->fontanswers = TTF_OpenFont("font/answerfont.otf", 32);
    if (e->fontquestion == NULL) {
        printf("Error loading font: %s\n", TTF_GetError());
        return;
    }
    if (e->fontanswers == NULL) {
        printf("Error loading font: %s\n", TTF_GetError());
        return;
    }
    
    e->questionSurface  = TTF_RenderText_Blended(e->fontquestion, e->question, textColor);
    if (e->questionSurface == NULL) {
        printf("Error rendering question: %s\n", TTF_GetError());
        TTF_CloseFont(e->fontquestion);
        return;
    }

    
    e->answerSurfaceA = TTF_RenderText_Blended(e->fontanswers, e->reponseA, textColor);
    e->answerSurfaceB= TTF_RenderText_Blended(e->fontanswers, e->reponseB, textColor);
    e->answerSurfaceC = TTF_RenderText_Blended(e->fontanswers, e->reponseC, textColor);
    e->answerSurfaceD = TTF_RenderText_Blended(e->fontanswers, e->reponseD, textColor);
    if (e->answerSurfaceA == NULL || e->answerSurfaceB == NULL || e->answerSurfaceC == NULL || e->answerSurfaceD == NULL) {
        printf("Error rendering answer options: %s\n", TTF_GetError());
        SDL_FreeSurface(e->questionSurface);
        TTF_CloseFont(e->fontanswers);
        return;
    }
    
    e->Backgroundimg = IMG_Load("images/enigmebg.png");
    if (e->Backgroundimg == NULL) {
    printf("Failed to load background image: %s\n", IMG_GetError());
    }
    
    
    e->positionquestion.x = 200;
    e->positionquestion.y = 150;
    e->positionquestion.w = e->questionSurface->w;
    e->positionquestion.h = e->questionSurface->h; 
    
    e->positionReponse1.x = 300; 
    e->positionReponse1.y = 405;
    e->positionReponse1.w = 45;
    e->positionReponse1.h = 45;
    //
    e->positionReponse2.x = 700; 
    e->positionReponse2.y = 405;
    e->positionReponse2.w = 45;
    e->positionReponse2.h = 45;
    //
    e->positionReponse3.x = 300; 
    e->positionReponse3.y = 507;
    e->positionReponse3.w = 45;
    e->positionReponse3.h = 45;
    //
    e->positionReponse4.x = 700; 
    e->positionReponse4.y = 507;
    e->positionReponse4.w = 45;
    e->positionReponse4.h = 45; 
    //
    e->positionTemps.x = 1035;
    e->positionTemps.y = 15;
    //
    e->positionprogress.x = 40;
    e->positionprogress.y = 15;
    
    e->anima.posanim.x=0;
    e->anima.posanim.y=0;
    
    e->positionWait.x = 500;
    e->positionWait.y = 650;
}

void afficherEnigme(enigme e, SDL_Surface *screen) {
    SDL_BlitSurface(e.Backgroundimg, NULL, screen, NULL);
    
    SDL_BlitSurface(e.questionSurface, NULL, screen,&e.positionquestion);
    SDL_BlitSurface(e.answerSurfaceA, NULL, screen, &e.positionReponse1);
    SDL_BlitSurface(e.answerSurfaceB, NULL, screen, &e.positionReponse2);
    SDL_BlitSurface(e.answerSurfaceC, NULL, screen, &e.positionReponse3);
    SDL_BlitSurface(e.answerSurfaceD, NULL, screen, &e.positionReponse4);
    
}

void afficherTemps(enigme e, SDL_Surface * screen, int timeLeft) {
    char text[20];
    sprintf(text, "Temps : %d", timeLeft);

    SDL_Color color = { 255, 255, 255 }; 
    SDL_Surface * textSurface = TTF_RenderText_Solid(e.fontquestion, text, color);
    SDL_BlitSurface(textSurface, NULL, screen, &e.positionTemps);
    
    SDL_FreeSurface(textSurface);
}


void afficherWait(enigme e, SDL_Surface *screen, int timeLeft) {
  
    int loadingBarX = (SCREEN_WIDTH - LOADING_BAR_WIDTH) / 2;
    int loadingBarY = 660;


    float progress = (float)timeLeft / (float)MAX_TIME;

    
    SDL_Rect backgroundRect = {
        loadingBarX,
        loadingBarY,
        LOADING_BAR_WIDTH,
        LOADING_BAR_HEIGHT
    };
    SDL_FillRect(screen, &backgroundRect, SDL_MapRGB(screen->format, 255, 255, 255));


    SDL_Rect progressRect = {
        loadingBarX,
        loadingBarY,
        (int)(progress * LOADING_BAR_WIDTH),
        LOADING_BAR_HEIGHT
    };
    SDL_FillRect(screen, &progressRect, SDL_MapRGB(screen->format, 255, 0, 0)); 

    
    char text[20];
    sprintf(text, "%d", timeLeft);
    SDL_Color color = { 255, 255, 255 }; 
    SDL_Surface* textSurface = TTF_RenderText_Blended(e.fontquestion, text, color);
    SDL_Rect textRect = {
        loadingBarX + LOADING_BAR_WIDTH / 2 - textSurface->w / 2,
        loadingBarY - 40,
        textSurface->w,
        textSurface->h
    };
    SDL_BlitSurface(textSurface, NULL, screen, &textRect);
    SDL_FreeSurface(textSurface);

}






void afficherProgress(enigme e,SDL_Surface * screen, int progress) {
    char text[20];
    sprintf(text, "3/%d", progress);
    SDL_Color color = { 255, 255, 255 }; 
    SDL_Surface * textSurface = TTF_RenderText_Solid(e.fontquestion, text, color);
    SDL_Rect positionProgress;
    //
    SDL_BlitSurface(textSurface, NULL, screen,&e.positionprogress);
    
    SDL_FreeSurface(textSurface);
}


void animerEnigme(enigme *e)
{
    
    SDL_Surface *ecranAnimation = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

    
    if (ecranAnimation == NULL)
    {
        printf("Failed to initialize screen: %s\n", SDL_GetError());
        return;
    }

    SDL_Surface *Myimages_[500];

    int j;
    char ch[50];

    for(j=1; j<18; j++)
    {
        sprintf(ch,"animation/%d.png",j);
        Myimages_[j]=IMG_Load(ch);

        
        if (Myimages_[j] == NULL)
        {
            
            return;
        }
    }

    for(j=1; j<18; j++)
    {
        SDL_BlitSurface(Myimages_[j], NULL, ecranAnimation, &e->anima.posanim);
        SDL_Flip(ecranAnimation);
        
        SDL_Delay(120);
        SDL_FreeSurface(Myimages_[j]);
    } 
    
    SDL_Delay(1000);
}


void playMusic(const char* filename)
{
    
    Mix_Music *music = Mix_LoadMUS(filename);

    if (music == NULL) {
        printf("Failed to load music file: %s\n", Mix_GetError());
        return;
    }
    
    Mix_VolumeMusic(MIX_MAX_VOLUME); 

    
    if (Mix_PlayMusic(music, 1) == -1) {
        printf("Failed to play music: %s\n", Mix_GetError());
        return;
    }
       
        if (music != NULL) {
        if (Mix_PlayingMusic() == 0) {
            
            Mix_FreeMusic(music);
            music = NULL;           
           
            Mix_CloseAudio();
        }
    }
}

void PlaySoundEffect(const char* filename) {  
    Mix_Chunk *sfx; 
    sfx = Mix_LoadWAV(filename);
    if (sfx==NULL)
    {
     printf("Fichier sound wav Not Found \n");
    }
    Mix_PlayChannel(1, sfx, 0);
}



void free_all(enigme e)
{ 
    if (e.Backgroundimg != NULL) {
        SDL_FreeSurface(e.Backgroundimg);
       
    }

    if (e.questionSurface != NULL) {
        SDL_FreeSurface (e.questionSurface) ;
       
    }

    if (e.answerSurfaceA != NULL) {
        SDL_FreeSurface(e.answerSurfaceA);
       
    }

    if (e.answerSurfaceB != NULL) {
        SDL_FreeSurface(e.answerSurfaceB);
      
    }

    if (e.answerSurfaceC != NULL) {
        SDL_FreeSurface(e.answerSurfaceC);
      
    }

    if (e.answerSurfaceD != NULL) {
        SDL_FreeSurface(e.answerSurfaceD);
      
    }
    
    TTF_CloseFont(e.fontquestion);
    TTF_CloseFont(e.fontanswers); 
    TTF_Quit();
}


void ImageGameOver(SDL_Surface *ecran)
{    
    SDL_Surface* image = NULL;
    
    image = IMG_Load("images/over.jpg");
    
    SDL_BlitSurface(image, NULL, ecran, NULL);
    
    SDL_FreeSurface(image);
}

void ImageGameWin(SDL_Surface *ecran)
{    
    SDL_Surface* image = NULL;
   
    image = IMG_Load("images/win.jpg");
    
    SDL_BlitSurface(image, NULL, ecran, NULL);
    
    SDL_FreeSurface(image);
}


void sauvegarder(Personne p, background b, char *nomfichier)
{
    FILE *fichier = fopen(nomfichier, "wb"); 
    if (fichier == NULL) {
        fprintf(stderr, "Error: Cannot open file '%s' for writing\n", nomfichier);
        return;
    }

    
    if (fwrite(&p, sizeof(Personne), 1, fichier) != 1) {
        fprintf(stderr, "Error: Failed to write to file '%s'\n", nomfichier);
        fclose(fichier);
        return;
    }
    if (fwrite(&b, sizeof(background), 1, fichier) != 1) {
        fprintf(stderr, "Error: Failed to write to file '%s'\n", nomfichier);
        fclose(fichier);
        return;
    }

    if (fclose(fichier) != 0) {
        fprintf(stderr, "Error: Failed to close file '%s'\n", nomfichier);
    }
}

void charger(Personne *p, background *b, char *nomfichier)
{
    FILE *fichier = fopen(nomfichier, "rb"); 
    if (fichier == NULL) {
        fprintf(stderr, "Error: Cannot open file '%s' for reading\n", nomfichier);
        return;
    }

    
    if (fread(p, sizeof(Personne), 1, fichier) != 1) {
        fprintf(stderr, "Error: Failed to read from file '%s'\n", nomfichier);
        fclose(fichier);
        return;
    }
    if (fread(b, sizeof(background), 1, fichier) != 1) {
        fprintf(stderr, "Error: Failed to read from file '%s'\n", nomfichier);
        fclose(fichier);
        return;
    }

    if (fclose(fichier) != 0) {
        fprintf(stderr, "Error: Failed to close file '%s'\n", nomfichier);
    }
}





