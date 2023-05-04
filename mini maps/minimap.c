/**
* @file minimap.c
* @brief Testing Program.
* @author C Team
* @version 0.1
* @date Apr 01, 2015
*
* Testing program for minimap scrollilng
*/

/**

* @file minimap.c
*/
#include "minimap.h"
#include <string.h> 

/**
* @brief To initialize the minimap m .
* @param m the minimap
* @param url the url of the image
* @return Nothing
*/
void init_map(minimap *m)
{

    m->map = IMG_Load("fond1.jpg");
    m->minijoueur = IMG_Load("robot.ico");
    m->engime = IMG_Load("outils/signe 1.png");
    m->positionmap.x = 250;
    m->positionmap.y = 19;
    m->positionminijoueur.x = 250;
    m->positionminijoueur.y = 40;
    m->positionengime.x = 390;
    m->positionengime.y = 50;
}

/**
* @brief To calcul la positin du bonhomme the minimap m .
* @param m the minimap
* @return Nothing
*/
void MAJMinimap(SDL_Rect posJoueur, minimap *m,int redimensionnement)
{
    SDL_Rect posJoueurABS;
    posJoueurABS.x = 0;
    posJoueurABS.y = 0;
    posJoueurABS.x = posJoueur.x ;
    posJoueurABS.y = posJoueur.y ;
    m->positionminijoueur.x = (posJoueurABS.x * redimensionnement / 95) +250;
    m->positionminijoueur.y = (posJoueurABS.y * redimensionnement / 95)+21;
}

/**
* @brief To show the minimap m .
* @param m the minimap
* @param screen the screen
* @return Nothing
*/
void afficherminimap(minimap m, SDL_Surface *screen)
{
    SDL_BlitSurface(m.map, NULL, screen, &m.positionmap);
    SDL_BlitSurface(m.minijoueur, NULL, screen, &m.positionminijoueur);
    SDL_BlitSurface(m.engime, NULL, screen, &m.positionengime);
}

/**
* @brief To animate the enigme  .
* @param m the minimap
* @param url the url of the image
* @return Nothing
*/
void animerminimap(minimap * m ,int *i)
{
 char ch[40];
    sprintf(ch, "outils/signe %d.png",*i);
    if ((*i)==3)
        (*i)=0;
    (*i)++;
    m->engime=IMG_Load(ch);
    
        m->positionengime.x = 390;
        m->positionengime.y = 50;
}

/**
* @brief To initialize the time t  .
* @param t the time
* @return Nothing
*/
void initialiser_temps(temps *t)
{
  t->texte = NULL; 
  t->s = 0;
  t->position.x = 10;
  t->position.y = 50;
  t->police = NULL;
  t->police = TTF_OpenFont("outils/avocado.ttf", 40);
  if (t->police == NULL)
  {
    printf("error loading font \n ");
  }
  t->color.r = 0 ; 
  t->color.g = 0 ; 
  t->color.b = 0 ; 

  strcpy(t->entree, "");
  (t->secondesEcoulees) = 0;
  time(&(t->t1)); 
}

/**
* @brief To show the time t  .
* @param t the time
* @param ecran the ecran
* @return Nothing
*/
void afficher_temps(temps *t, SDL_Surface *ecran)
{ 
  time(&(t->t2)); 
  t->secondesEcoulees = t->t2 - t->t1;
  t->min = ((t->secondesEcoulees / 60) % 60);
  t->sec = ((t->secondesEcoulees) % 60);
  sprintf(t->entree, "%02d:%02d", t->min, t->sec); 
  t->texte = TTF_RenderText_Blended(t->police, t->entree, t->color);
  SDL_BlitSurface(t->texte, NULL, ecran, &(t->position)); 
  t->s = (t->sec * 10 + t->min * 600);
}

/**
* @brief To free the time t  .
* @param t the time
* @return Nothing
*/
void free_temps(temps *t)
{
  SDL_FreeSurface(t->texte);
  TTF_CloseFont(t->police);
}

/**
* @brief To show the masque .
* @param psurface the psurface
* @return color of pixel
*/
SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y)
{
SDL_Color color;
Uint32 col=0;
char* pPosition=(char* )pSurface->pixels;
pPosition+=(pSurface->pitch *y);
pPosition+=(pSurface->format->BytesPerPixel *x);
memcpy (&col,pPosition,pSurface->format->BytesPerPixel);

SDL_GetRGB(col,pSurface->format,&color.r,&color.g,&color.b);
return(color);
}

/**
* @brief To show the collision .
* @param masque the masque
* @param p the person
* @return intiger
*/
 int collisionPP( personne p, SDL_Surface * Masque)
{
    SDL_Color Couleur_Obstacle = {0, 0, 0};
    SDL_Color cal ;
 int X,Y,H,W;
     X = p.pos.x;
     Y = p.pos.y;
  W = p.pos.w=96;
  H = p.pos.h=96;
if (p.dir==2 || p.dir==3 || p.dir==4)
{
    W = p.pos.w=96;
 	 H = p.pos.h=96;
}
    int pos[8][2];
    pos[0][0]=X;
    pos[0][1]=Y;
    pos[1][0]=X+W/2;
    pos[1][1]=Y;
    pos[2][0]=X+W;
    pos[2][1]=Y;
    pos[3][0]=X;
    pos[3][1]=Y+H/2;
    pos[4][0]=X;
    pos[4][1]=Y+H;
    pos[5][0]=X+W/2;
    pos[5][1]=Y+H;
    pos[6][0]=X+W;
    pos[6][1]=Y+H;
    pos[7][0]=X+W;
    pos[7][1]=Y+H/2;
    int collision=0,i=0;
    while ((i<8)&&(collision==0))
    {
        cal = GetPixel(Masque, pos[i][0], pos[i][1]);
        if((cal.r == Couleur_Obstacle.r) && (cal.g == Couleur_Obstacle.g) && (cal.b == Couleur_Obstacle.b))
        {
            collision = 1;
        }
          i++;
    }
    return collision;
}
/**
* @brief To calculate score .
* @param tabsuivi tableau de 9 case
* @return intiger
*/

int minimax(int tabsuivi[], int joueur) {
    //How is the position like for player (their turn) on board?
    int gagnant=atilganer(tabsuivi);
    if(gagnant != 0)
     return gagnant*joueur;

    int coup = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(tabsuivi[i] == 0) {//If legal,
            tabsuivi[i] = joueur;//Try the move
            int mmscore = -minimax(tabsuivi, joueur*-1);
            if(mmscore > score) {
                score = mmscore;
                coup = i;
            }//Pick the one that's worst for the opponent
            tabsuivi[i] = 0;//Reset board after try
        }
    }
    if(coup == -1) 
    return 0;
    return score;
}

/**
* @brief To update le tableau .
* @param tabsuivi tableau de 9 case
* @return nothing
*/
void calcul_coup(int tabsuivi[9]) {
    int coup = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) 
    {
        if(tabsuivi[i] == 0) 
        {
            tabsuivi[i] = 1;
            int mmscore = -minimax(tabsuivi, -1);
           tabsuivi[i] = 0;
            if(mmscore > score) 
            {
                score = mmscore;
                coup = i;
            }
        }
    }
    tabsuivi[coup] = 1;
}

/**
* @brief To show the winner .
* @param tabsuivi tableau de 9 case
* @return intiger
*/
int atilganer(int tabsuivi[]) {
    // Les lignes gagnantes
    int lignes_gagnantes[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    // Vérification de chaque ligne gagnante
    for (int i = 0; i < 8; i++) {
        int first_value = tabsuivi[lignes_gagnantes[i][0]];
        if (first_value != 0 && first_value == tabsuivi[lignes_gagnantes[i][1]] && first_value == tabsuivi[lignes_gagnantes[i][2]]) {
            // La même valeur est présente sur les 3 cases de la ligne gagnante
            if (first_value == 1) {
                return 1; // Machine gagne
            } else if (first_value == -1) {
                return -1; // Humain gagne
            }
        }
    }
    // Aucun gagnant trouvé
    return 0;
}

/**
* @brief To initialize the tic t .
* @param t the tic
* @param url the url of the image
* @return Nothing
*/
void initialiserTic(tic *t) 
{
    t->background = IMG_Load("XO.jpg");
    t->playerX = IMG_Load("playerX.png");
    t->playerO = IMG_Load("playerO.png");  
    
    for(int i = 0; i < 9; i++) 
    {
    t->tabsuivi[i]=0 ;
    }

    
    t->firstpos.x = 0;
    t->firstpos.y = 0;
    t->firstpos.w = 300;
    t->firstpos.h = 300;   
    t->currentPlayer = 1;
    t->currentTurn = 0;
    TTF_Init();
    t->font = TTF_OpenFont("arial.ttf", 25);
    t->textColor.r = 255;
    t->textColor.g = 255;
    t->textColor.b = 255;
   strcpy(t->endGameText, ""); 
    t->textPos.x = 700;
    t->textPos.y = 0;
}

/**
* @brief To show the tic t .
* @param t the tic
* @param ecran the ecran
* @return Nothing
*/
void afficherTic(tic t, SDL_Surface *ecran) 
{   
    SDL_BlitSurface(t.background, NULL, ecran,NULL);
    int i, x, y ;
    for(i = 0; i < 9; i++) 
    {
 	t.firstpos.x = (t.firstpos.w ) * (i % 3) ;
        t.firstpos.y = (t.firstpos.h ) * (i / 3) ;
   
        if(t.tabsuivi[i] == 1) 
        {            
            SDL_BlitSurface(t.playerX, NULL, ecran, &(t.firstpos));            
        } 
        else if(t.tabsuivi[i] == -1) 
        {            
            SDL_BlitSurface(t.playerO, NULL, ecran, &(t.firstpos));            
        }
    }   
}

/**
* @brief To show the results of tic t .
* @param t the tic
* @param screen the screen
* @return Nothing
*/
void Resultat(tic *t, SDL_Surface *screen)
{
    int resultat;
    resultat = atilganer(t->tabsuivi);
    if (resultat == 1)
    {
        strcpy(t->endGameText, "Victoire");
        t->t = TTF_RenderText_Blended(t->font, t->endGameText, t->textColor);
        SDL_BlitSurface(t->t, NULL, screen, &t->textPos);
    }
    if (resultat == -1)
    {
        strcpy(t->endGameText, "Defaite");
        t->t = TTF_RenderText_Blended(t->font, t->endGameText, t->textColor);
        SDL_BlitSurface(t->t, NULL, screen, &t->textPos);
    }
    if (resultat == 0)
    {
        strcpy(t->endGameText, "Nul");
        t->t = TTF_RenderText_Blended(t->font, t->endGameText, t->textColor);
        SDL_BlitSurface(t->t, NULL, screen, &t->textPos);
    }
}



