/**
* @file main.c
* @brief Testing Program.
* @author C Team
* @version 0.1
* @date Apr 01, 2015
*
* Testing program for background scrollilng
*/
#include "minimap.h"
int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Surface *screen,* back,*Masque ;
    screen = SDL_SetVideoMode(1082, 701, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); 
    SDL_Rect  posminijoueur; 
    SDL_Event event; 
    minimap m;  
    temps t;   
    tic ti ;
    personne p;
    p.perso = IMG_Load("robot.png");
    back = IMG_Load("fond.jpeg");
    Masque = IMG_Load("fond masque.jpg");
    int coup ;
    int continuer = 1;
    init_map(&m);  
    int x,y ;
    p.pos.x = 0;
    p.pos.y = 400;
    SDL_EnableKeyRepeat(100, 10); 
    initialiser_temps(&t); 
    
    initialiserTic(&ti) ;
    int i=2,c;
    
    while (continuer)
    {
    		  ////////////////////////////////////////////////
	   //SDL_BlitSurface(Masque, NULL, screen, NULL);
	  	 ////////////////////////////////////////////////
	   
       SDL_BlitSurface(back, NULL, screen, NULL);
       
        afficherTic(ti,screen);
        
        printf( " %d | %d | %d | %d | %d | %d | %d | %d | %d \n",ti.tabsuivi[0],ti.tabsuivi[1],ti.tabsuivi[2],ti.tabsuivi[3],ti.tabsuivi[4],ti.tabsuivi[5],ti.tabsuivi[6],ti.tabsuivi[7],ti.tabsuivi[8]);

        
        if(ti.currentTurn<9 && atilganer(ti.tabsuivi)==0){
        
          if((ti.currentTurn+ti.currentPlayer)%2==0){
          calcul_coup(ti.tabsuivi);
          ti.currentTurn ++ ;
          }
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONUP :
            
                        x=event.button.x/ti.firstpos.w ;
 			y=event.button.y/ti.firstpos.h ;
 			coup=3*y+x ;
 			ti.tabsuivi[coup]=-1 ;
 			ti.currentTurn ++ ;
 		    break ;    
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                        p.pos.x -= 5;
                        p.dir=3;
                    break;
                case SDLK_RIGHT:
                        p.pos.x += 5;
                        p.dir=4;
                    break;
                case SDLK_UP:
                        p.pos.y -= 5;
                        p.dir=1;
                    break;
                case SDLK_DOWN:
                        p.pos.y += 5;
                        p.dir=2;
                    break;                   
                }
                break;
            }
        }
        Resultat(&ti,screen) ;
        SDL_BlitSurface(p.perso, NULL, screen, &p.pos);        
        afficher_temps(&t, screen);  
        animerminimap(&m,&i);
        MAJMinimap(p.pos, &m, 20); 
        afficherminimap(m, screen); 
        c= collisionPP(p,Masque);
       
      // printf("%d\n",c);
       if(c==1){
       p.pos.x = 0;
       p.pos.y = 400;
       }      
////////////////////////////////////////////////
        SDL_Flip(screen);  
        SDL_Delay(20);       
    }     
    SDL_FreeSurface(p.perso);
    SDL_FreeSurface(back);
    SDL_FreeSurface(m.minijoueur);
    SDL_FreeSurface(m.map);
    SDL_FreeSurface(m.engime);
    SDL_FreeSurface(ti.playerX);
    SDL_FreeSurface(ti.playerO);
    SDL_FreeSurface(ti.background);
    free_temps(&t);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
