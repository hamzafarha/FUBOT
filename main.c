#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <time.h>
#include <stdbool.h>
#include <SDL/SDL_mixer.h>
#include "enigme.h"
#include "background.h"
#include "personne.h"
#define COUNTDOWN_TIME 20 // in seconds
#define DELAY_AFTER_INCORRECT_RESPONSE 5000 // 5 seconds

int main() {
  int quit = 1;
  int countCorrect=0;
  char selectedAnswer[2] = {0}; // this variable will hold the user's selected answer
  // add a boolean flag to keep track of whether the win sound has been played
  bool hasPlayedWinSound = false;
  bool hasPlayedLoseSound = false;
  bool hasWon = false;
  bool gameover = false;
  SDL_Event event;
  SDL_Surface * screen = NULL;
  if (SDL_Init(SDL_INIT_VIDEO) != 0) { printf("SDL_Init failed: %s\n", SDL_GetError());return 1;}
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (screen == NULL){printf("Unable to set video mode: %s\n", SDL_GetError());return 1;}
   // initialize SDL
  SDL_Init(SDL_INIT_AUDIO);
  // initialize SDL_mixer
  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {printf("Failed to initialize SDL mixer: %s\n", Mix_GetError());return 1;}
    //
    playMusic("sound/music.mp3");
    enigme e;
    genererEnigme(&e, "enigme.txt");
    animerEnigme(&e);  
    printf("The correct answer is %c\n", e.correctAnswer);
    Uint32 startTime = SDL_GetTicks();
    //
    Uint32 lastIncorrectTime = 0;
    bool canClick = true; // track whether the user is allowed to click on an answer or not
    Uint32 clickTimer = 0; // track the time since the user last clicked on an answer
    bool canClickNow = false;
    //
    // Initialize the personnage Forn function sauvegarder()
    Personne p;
    p.position.x = 0;
    p.position.y = 0;
    p.direction = 0;
    p.num = 0;
    p.vitesse = 0.0;
    p.acceleration = 0.1;
    p.floor = 400;
    p.pos_vie.x = 0;
    p.pos_vie.y = 0;
    p.score = 0;
    p.frappe = 0;
    p.vie = 3;
    p.sens = 0;
    p.isjumping = 0;
    // Initialize the background
    background b;
    b.camerapos.x = 0;
    b.camerapos.y = 0;
    b.camerapos.w = 640;
    b.camerapos.h = 480;
    b.direction = 1;
    /*b.image1 = IMG_Load("bg1.png");
    b.image2 = IMG_Load("bg2.png");
    b.image3 = IMG_Load("bg3.png");
    b.music1 = Mix_LoadMUS("music1.mp3");
    b.music2 = Mix_LoadMUS("music2.mp3");
    b.music3 = Mix_LoadMUS("music3.mp3");*/
    b.musicplaying = 0;

    ///////////////////////////////// Save and load the data    (.bin file to prevent user --> modify data)
    //sauvegarder(p, b, "game.bin");
    //////////////////////////////// Charger 
    Personne pppp;
    background bbbb;
    charger(&pppp, &bbbb, "game.bin");

    printf("Player Score = %d\n", pppp.score);
    printf("Player Vie = %d\n", pppp.vie);
    printf("Background.x = %d\n", bbbb.camerapos.x);
    printf("Background.y = %d\n", bbbb.camerapos.y);
    printf("Background.w = %d\n", bbbb.camerapos.w);
    printf("Background.h = %d\n", bbbb.camerapos.h);
    printf("Player Position x = %d\n", pppp.position.x);
    printf("Player Position y = %d\n", pppp.position.y);

    
    //
    //  
  while (quit) {
  
        if(!hasWon && !gameover)
        {
        afficherEnigme(e, screen);
        }
        //
        Uint32 currentTime = SDL_GetTicks();
        int timeLeft = COUNTDOWN_TIME - (currentTime - startTime) / 1000;
        if (timeLeft < 0 && !hasWon && !gameover) {
            printf("Time's up! Game over.\n");
            //quit = 0;
            //break;
            timeLeft=0;
            gameover=true;
        }

        if (!hasWon && !hasPlayedLoseSound) {
        afficherTemps(e, screen, timeLeft); // Timer
        afficherProgress(e,screen,countCorrect); //  3/0
        }
        
        if(gameover && !hasPlayedLoseSound)
        {
         ImageGameOver(screen);
         playMusic("sound/gameover.mp3");
         hasPlayedLoseSound = true; // set the flag to true so the sound won't play again
        }
        
        if(countCorrect==3 && !hasPlayedWinSound)
        {
        startTime = SDL_GetTicks(); // reset the countdown timer
        ImageGameWin(screen);
        playMusic("sound/win.mp3");
        hasPlayedWinSound = true; // set the flag to true so the sound won't play again
        }
        //
        if(canClickNow && !hasWon && !gameover)
        {
           Uint32 currentTimeee = SDL_GetTicks();
           //printf("Please wait %d seconds before trying again.\n", (clickTimer + 5000 - currentTimeee) / 1000);
           int waitTime = (clickTimer + 5000 > currentTimeee) ? ((clickTimer + 5000 - currentTimeee) / 1000) : 0;
           afficherWait(e, screen, waitTime);            
        }      
        //
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN: {
                    if (canClickNow) {
                        break;
                    }
                // Check if the mouse click is inside one of the answer rectangles
       if (!gameover && !hasWon && event.button.button == SDL_BUTTON_LEFT) {
         if (event.button.x >= e.positionReponse1.x && event.button.x <= (e.positionReponse1.x + 290) && event.button.y >= e.positionReponse1.y && event.button.y <= e.positionReponse1.y+45)  {
                        printf("A\n");
                        strcpy(selectedAnswer, "A"); // the user selected A
                    }
          else if (event.button.x >= e.positionReponse2.x && event.button.x <= (e.positionReponse2.x + 290) && event.button.y >= e.positionReponse2.y && event.button.y <=(e.positionReponse2.y + 45)) {
                        printf("B\n");
                        strcpy(selectedAnswer, "B"); // the user selected B
                    }
           else if (event.button.x >= e.positionReponse3.x && event.button.x <= (e.positionReponse3.x + 290) && event.button.y >= e.positionReponse3.y && event.button.y <= (e.positionReponse3.y + 45)){
                        printf("C\n");
                        strcpy(selectedAnswer, "C"); // the user selected C
                    }
           else if (event.button.x >= e.positionReponse4.x && event.button.x <= (e.positionReponse4.x + 290) && event.button.y >= e.positionReponse4.y && event.button.y <= (e.positionReponse4.y + 45)) {
                        printf("D\n");
                        strcpy(selectedAnswer, "D"); // the user selected D
                    }
              else {
                        // The click was outside of any answer rectangle, so don't attempt to answer
                        continue;
                    }
                    
                        if (strcmp(selectedAnswer, &e.correctAnswer) == 0) {
                            printf("Congratulations, your answer is correct!\n");
                            if(!hasWon) 
                            {
                            genererEnigme(&e, "enigme.txt");
                            }
                            //afficherEnigme(e, screen);
                            if(countCorrect<3)
                            {
                            countCorrect++;
                            }
                            if(countCorrect==3 && !hasWon) {
                            // User has won
                            hasWon = true;
                            }
                            //printf("Count Correct %d \n",countCorrect);
                            //startTime = SDL_GetTicks(); // reset the countdown timer
                            PlaySoundEffect("sound/correct.wav");
                        } else {
                            PlaySoundEffect("sound/wrong.wav");
                            Uint32 currentTimesss = SDL_GetTicks();
                            printf("Sorry, your answer is incorrect. The correct answer is %c\n", e.correctAnswer);
                            lastIncorrectTime = currentTimesss;
                            canClickNow= true;
                            clickTimer = currentTimesss;
                        }
                        strcpy(selectedAnswer, ""); // reset selectedAnswer for next round
                }

                break;
            }
            case SDL_QUIT: {
                quit = 0;
                break;
            }
            
            case SDL_KEYDOWN:
            if(gameover)
            {
             if (event.key.keysym.sym == SDLK_RETURN) {
                printf("Enter key pressed.\n");
                hasPlayedWinSound = false;
                hasPlayedLoseSound = false;
                hasWon = false;
                gameover = false;
                countCorrect=0;
                startTime = SDL_GetTicks(); // reset the countdown timer
                playMusic("sound/music.mp3");
                //clickTimer = SDL_GetTicks(); // reset click timer
                canClickNow=false;
              }
            }
              break;
            
            default: {
                break;
            }
        }
    }  
        // check if the delay after an incorrect answer has passed
        if (canClickNow) {
            Uint32 currentTimemm = SDL_GetTicks();
            if (currentTimemm - lastIncorrectTime >= DELAY_AFTER_INCORRECT_RESPONSE) {
                canClickNow=false;
            }
        }
        SDL_Flip(screen);
}
  free_all(e);
  SDL_FreeSurface(screen);// free the memory
  SDL_Quit();
  return 0;
}
