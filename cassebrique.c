#include <SDL2/SDL.h>
#include <unistd.h>
#include "function.h"

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700
#define FPS 60


int x = 0;
int y = 0;
int bx = 350;//x balle
int by = 462;//y balle
int j = 1; //redirectionner x balle
int k = 1;// redirectionner y balle
int rx = 300;// x raquette
int ry = 460;//y raquette
int dans_le_menu = 1;
int choix_raquette;
int programLaunched =1;
int tbx=0;
int tby=0;
int tab_brique[7][4];



void menu(){
  clear();
  sprite(0,0,"menu_cassebrique.bmp");
 actualize();
  usleep(1000000 / FPS); 
}


void init_tab(){
for (tbx=0;tbx<=6;tbx++){
    for (tby=1;tby<=4;tby++){ 
       tab_brique[tbx][tby] = 1;
             printf("%d %d %d \n", tbx, tby, tab_brique[tbx][tby]);
     }
 }
}

void init_game(){
init_tab();
menu();
}



void sortie_map(){
    // bordure balle x
    if(bx >= 700){
      j=1;
      printf("error sortie de map\n");
    }else if (bx <= 0 ){
      j=2;     
      printf("error sortie de map\n");
    }
    
    // bordure balle y
    if (by <= 0){
       k=2;        
       printf("error sortie de map\n");
    }else if (by >= 700){ //perdu
      k=2;
      
       
    }
    
    // bordure raquette en x
    if (rx <= (-10)){
       rx=rx+10;
        printf("error sortie de map\n");
    }else if (rx >= 610){
        rx=rx-10;;    
        printf("error sortie de map\n");
    }
}


void deplacement_balle(){ 
if(j==1){ // gauche
    bx=bx-1; 
  }else if (j==2){ // droite
    bx=bx+1;
  }
 if(k==1){ // haut
    by=by-1;
  }else if (k==2){ // bas
    by=by+1;
  }
}


void raquette(){
  switch (choix_raquette){
      case 1:
      sprite (rx,ry,"raquette_ile_volante.bmp"); 
      break;
      case 2:
      sprite (rx,ry,"raquette_violette.bmp");
      break;
  }
}

void briques(){
for (tbx=0;tbx<=6;tbx++){
    for (tby=1;tby<=4;tby++){ 

        if (tab_brique[tbx][tby] == 1){
       
           drawRect(tbx*102,tby*12,100,10);
         }
      }
  }
}

void collision(){
//rx-2 car si non la balle traversait la raquette au niveau du bord gauche
//balle raquette
  if ((rx-2<=bx) && (bx<=rx+100) && (ry==by)){
    k=1; 
  }
}

void collision_bb(){
//balle brique

for (tbx=0;tbx<=6;tbx++){ 
    for (tby=1;tby<=4;tby++){
       if ((tab_brique[tbx][tby]== 1) && ((bx>=tbx*101) && (bx<=(tbx*101)+100)) && ((by>= (tby*11)+10) && (by<= tby*11))){
         tab_brique[tbx][tby]=0;
          if (by>= (tby*11)+10){
               k=2;
               briques();
          }else if (by<= tby*11){
               k=1;
               briques();
          }
        }
      }
   
 }
 actualize();
 
}

 
void drawGame(){
    
    clear();
    changeColor(255,255,0);
    drawCircle(bx,by,5);  
    raquette();
    briques();
    collision();
    collision_bb();
    deplacement_balle();
    sortie_map();
    actualize();
    usleep(100000 / FPS); 
}



void KeyPressed(SDL_Keycode touche){
    switch (touche) {
        case SDLK_q:
           rx=rx-10;
           printf("Q\n");
            
            break;
        case SDLK_d:
           rx=rx+10;
           printf("D\n"); 
            break;
        case SDLK_b:
            dans_le_menu = 0;
            break;
           
        case SDLK_ESCAPE:
            freeAndTerminate();
            break;
        default:
            break;
    }
}




void gameLoop() {
  // menu début
  dans_le_menu = 1;
    while (dans_le_menu == 1) {
    
      SDL_Event event;
        while (SDL_PollEvent(&event)) {
        
            switch (event.type) {
              
                case SDL_QUIT:
                    programLaunched = 0;
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
                    break;
               
                default:
                    break;
            }
        }
    }
       // jeu 
    int programLaunched = 1;
    while (programLaunched == 1) {
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            
            switch (event.type) {
               
                case SDL_QUIT:
                   
                    programLaunched = 0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    
                    printf("position de la souris x : %d , y : %d\n", event.motion.x, event.motion.y);
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
                    break;
                case SDL_JOYBUTTONDOWN:
                    break;
                default:
                    break;
            }
        }
       
        drawGame();
    }
}





int main(){
    printf("quelle raquette souhaitez-vous ?\n 1 = Flying Island\n 2= Purple Rock\n");
   scanf("%d",&choix_raquette);
    init(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_game();
    gameLoop();
    printf("Fin du programme\n");
    freeAndTerminate();
}
