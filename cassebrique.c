  #include <SDL2/SDL.h>
#include <unistd.h>
#include "function.h"
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 1200 
#define WINDOW_HEIGHT 1000
#define FPS 60


//                                                                                  Variables


int bx = 400;//x balle 
int by = 850;//y balle
double j = 0; //direction x balle
double k = 0;// direction y balle
int rx = 150;// x raquette 
int ry = 900;//y raquette
int dans_le_menu = 1;
int programLaunched;
int tbx = 0;
int tby = 0;
int hauteur_brique = 50;
int largeur_brique = 96;
int tab_brique[10][4];
int fin_jeu = 0;
int check_rebond=0;
double inclinaison_bb;
int xbrique ;
int ybrique ;
int r=3;
int compteur_piece=0;
int nombre_vie=3;
int commencer_jeu=0;
int mouse_on_start = 0;
int apparition_sorciere = 0;
int move_sorciere = 0;
int xsorciere = 1000;
int compteur_briques = 0;


//                                                                                  reset variables
void reset_variable(){
    bx = 400;
    by = 850;
    double j = 0; //direction x balle
    double k = 0;// direction y balle
    rx = 150;// x raquette 
    ry = 900;//y raquette
    dans_le_menu = 1;
    tbx = 0; 
    tby = 0;
    hauteur_brique = 50;
    largeur_brique = 96;
    tab_brique[10][4];  
    fin_jeu = 0;
    check_rebond=0;
    r=3;
    compteur_piece=0;
    nombre_vie=3;
    commencer_jeu=0;
    mouse_on_start = 0;
    apparition_sorciere = 0;
    move_sorciere = 0;
    xsorciere = 1000;
    compteur_briques = 0;
   
}

//                                                                                    Menu

void menu(){
  
sprite(0,0,"maison_menu.bmp");
  switch (mouse_on_start){
    case 0:
      sprite (450,800, "start1.bmp");
      
      break;
    case 1:
      sprite (450,800, "start2.bmp");
    
      break;
  }
  
  actualize();
  usleep(1000000 / FPS); 
}

//                                                                         Initialisation du tableau


void init_tab(){
for (tbx=0;tbx<=9;tbx++){
    for (tby=1;tby<=4;tby++){ 
       tab_brique[tbx][tby] = 1;
    
     }
 }
}
//                                                                            Animation chaudron 


void animation_chaudron(){
int changement_frame;
for (changement_frame=0;changement_frame<=15;changement_frame++){
    clear();
    sprite(0,0,"maison_interieur15.bmp");
    sprite(xsorciere,650,"sorcière_gentille.bmp");
    sprite(0,600,"bulle_texte.bmp");
   switch (changement_frame){
    
    case 1:
    
     sprite(370,520,"bulle1.bmp");
     usleep(1000000 / FPS);
    break;

    case 2:
     sprite(370,520,"bulle2.bmp");
     usleep(1000000 / FPS);    

    break; 

    case 3:
     sprite(370,520,"bulle3.bmp");
     usleep(1000000 / FPS);
    break;

    case 4:
     sprite(370,520,"bulle4.bmp");
     usleep(1000000 / FPS);
    break; 

    case 5:
     sprite(370,520,"bulle5.bmp");
     usleep(1000000 / FPS);
    break; 

    case 6:
     sprite(370,520,"bulle6.bmp");
     usleep(1000000 / FPS);
    break; 

    case 7:
   
     sprite(370,520,"bulle7.bmp");
     usleep(1000000 / FPS);
    break; 

    case 8:
    
     sprite(370,520,"bulle8.bmp");
     usleep(1000000 / FPS);
    break;

    case 9:
  
     sprite(370,520,"bulle11.bmp");
     usleep(1000000 / FPS);
    break;

     case 12:
    
     sprite(370,520,"bulle12.bmp");
     usleep(1000000 / FPS);
    break;

     case 13:
     
     sprite(370,520,"bulle13.bmp");
     usleep(1000000 / FPS);
    break;

     case 14:
    
     sprite(370,520,"bulle14.bmp");
     usleep(1000000 / FPS);
    break;

     case 15:
    
     sprite(370,520,"bulle14.bmp");
     usleep(1000000 / FPS);
    break;

    default:
    break;
  }
  actualize();
  usleep(1000000 / FPS);
 } 
}
//                                                                                 Init_game


void init_game(){
init_tab();

}

//                                                                              balle immobile
void reset_balle(){
    k=0;
    j=0;
    bx= 400;
    by= 850;

}

//                                                                                 démarrer
void démarrer(){      
        k=2;
        j=2;
     clear();
     actualize();

    }
    

 
//                                                                            Bordure de fenêtre


void sortie_map(){
    // bordure balle x
    if(bx >= 990){
      j=-j;
      
    }else if (bx <= 10 ){
      j=-j;
    
    }
    
    // bordure balle y
    if (by >= 990){//perdu
     
     nombre_vie-=1;
     reset_balle();
    
    }else if (by <= 10){ 
     k=-k;
     
    }
    
    // bordure raquette en x
    if (rx < (-20)){
       rx=rx+30;
       
    }else if (rx > 850){
        rx=rx-30;;    
   
    }
}

//                                                                          Déplacements de balle


void deplacement_balle(){ 
bx=bx+j;
by=by+k;
}




//                                                                                Raquette


//                                                                              Draw briques


void briques(){
for (tbx=0;tbx<=9;tbx++){
    for (tby=1;tby<=4;tby++){ 

        if (tab_brique[tbx][tby] == 1){
  
  //+2 pour l'écart entre les briques     
           drawRect(tbx*(largeur_brique+2),tby*(hauteur_brique+2),largeur_brique,hauteur_brique);
         }
      }
  }
}





//                                                                              Sorcière


void histoire_debut(){

  

switch (move_sorciere){

case 0:
       clear();
       for (int xp = 0; xp<=350; xp++ ){
         
               clear();
               sprite(0,0,"maison_menu.bmp");
               xsorciere = xsorciere - 1;
               sprite(xsorciere,650,"sorcière_gentille.bmp");
               actualize();
               usleep(100000 / FPS);
               
        } 
        
        move_sorciere = move_sorciere + 1;
       
    break;
case 1:

       clear();
       
       sprite(0,0,"maison_menu.bmp");
       sprite(xsorciere,650,"sorcière_gentille.bmp");
       sprite(0,600,"bulle_texte.bmp");
       actualize();
       usleep(100000 / FPS);
      
    break;

case 2:
        clear();
       for (int xp2 = 0; xp2<=350; xp2++ ){
         
               clear();
               sprite(0,0,"maison_menu_porte_ouverte.bmp");
               xsorciere = xsorciere + 1;
               sprite(xsorciere,650,"sorcière_gentille.bmp");
               actualize();
               usleep(100000 / FPS);
       }
       
       move_sorciere = move_sorciere + 1;
    
    break;
case 3:
       clear();
       
       for (int xp2 = 0; xp2<=350; xp2++ ){
         
               clear();
               sprite(0,0,"maison_interieur15.bmp");
               xsorciere = xsorciere - 1;
               sprite(xsorciere,650,"sorcière_gentille.bmp");
               actualize();
               usleep(100000 / FPS);
       }
       
       move_sorciere = move_sorciere + 1;
    break;
case 4:

       clear();
       animation_chaudron();
       actualize();
       usleep(100000 / FPS);

    break;

case 5:
       dans_le_menu=3;
  
    break;

default:
    break;
}
 


}
//                                                                        Collisions balle-raquettes


void collision(){
//rx-2 car si non la balle traversait la raquette au niveau du bord gauche
//balle raquette
 

 if (( (k>0) && (bx>=(rx-3)) && (bx+20<=(rx+153))) && (by+20>=ry) && (by+20<=ry+20)){
  k=-k;
  if (compteur_briques >0){
    
  }
 }
 
}  
//                                                                          collisions balle-brique


void collision_bb(){
//balle brique




// k<0 haut k>0 bas j<0 gauche j>0 droite
    for (tbx=0;tbx<=9;tbx++){ 
       for (tby=1;tby<=4;tby++){
            xbrique = tbx*largeur_brique;
            ybrique = tby*hauteur_brique;
                  //transforme les coordonnées de tableau en coordonnées de fenêtre de jeu:
            check_rebond =0;

         

                    // Bas
          if (((k<0) && (check_rebond==0) && (bx>=xbrique) && (bx<=(xbrique)+largeur_brique) && (by>=ybrique+r) && (by<=ybrique+hauteur_brique+r))){
                if (tab_brique[tbx][tby] == 1) {
                   tab_brique[tbx][tby]=0;
                   compteur_piece+=1;
                   k=-k;
                   compteur_briques+=1;
                   
                   
                   check_rebond =1;
                }
            }


                    // Haut
           if (((k>0) && (check_rebond==0) && (bx>=xbrique) && (bx<=xbrique+largeur_brique) && (by>=ybrique-r) && (by<=ybrique+hauteur_brique-r))){
                if (tab_brique[tbx][tby] == 1) {
                   tab_brique[tbx][tby]=0;
                   compteur_piece+=1;
                   k=-k;
                   compteur_briques+=1;
                 
                   check_rebond =1;
                }
            }


                    //droite
           if ((j<0) && (check_rebond==0) && (bx<=xbrique+largeur_brique+3) && (bx>=xbrique+3) && (by<=ybrique+hauteur_brique) && (by>=ybrique)){
                if (tab_brique[tbx][tby] == 1) {
                   tab_brique[tbx][tby]=0;
                   compteur_piece+=1;
                   j=-j;
                   compteur_briques+=1;
               
                   check_rebond =1;
                }
            }


                    // gauche
           if ((j>0) && (check_rebond==0) && (bx<=xbrique+largeur_brique-3) && (bx>=xbrique-3) && (by<=ybrique+hauteur_brique) && (by>=ybrique)){
                if (tab_brique[tbx][tby] == 1) {
                   tab_brique[tbx][tby]=0;
                   compteur_piece+=1;
                   j=-j;
                   compteur_briques+=1;
                 
                   check_rebond =1;
                 
                } 
            }
  
        }
    }
        actualize();
}


//                                                                                pièces

void pieces(){

}

//                                                                                  vie


void vie(){
switch (nombre_vie){
       case 2 :
          sprite (0,0,"avant_derniere_vie.bmp");
          break;

       case 1 :
          sprite (0,0,"derniere_vie.bmp");
          break;
        
       

       default:
          break;
    }
    
}
 
//                                                                             fenêtre de score
void score(){
    int y_barre_score = 740;
sprite(1001,0,"chaudron_score_test.bmp");


}
//                                                                                DrawGame


void drawGame(){
    switch (dans_le_menu){ 
    
    case 1 :
        clear();
        menu();
        actualize();
        usleep(100000 / FPS); 
   
       break;
       
    case 2:
        clear();
        histoire_debut();
        actualize();
        usleep(100000 / FPS); 
       
        break;
    
    case 3 : 

        clear();
        sprite(0,0,"maison_interieur_jeu.bmp");
        score();
        changeColor(255,255,0);
        sprite(bx,by,"particule_magie.bmp");
        vie();
        sprite (rx,ry,"raquette_chaudron.bmp");
        briques();
        collision();
        collision_bb();
        
        pieces();
        deplacement_balle();
        sortie_map();
        if (nombre_vie==0){
            reset_variable();
            dans_le_menu = 1;
        }
        
        actualize();
        usleep(100000 / FPS); 

       
       break;
  
    default:
       break;
    }
}

//                                                                                KeyPressed


void KeyPressed(SDL_Keycode touche){
    switch (touche) {
        case SDLK_q:
           rx=rx-10;
           
            
            break;
        case SDLK_d:
           rx=rx+10;
           
            break;
            
        case SDLK_ESCAPE:
            freeAndTerminate();
            break;
        
        case SDLK_h:
            démarrer();
            break;

        default:
            break;
    }
}



//                                                                                 Gameloop


void gameLoop() {
  
       // jeu 
    
    programLaunched = 1;
    while (programLaunched == 1) {
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            
            switch (event.type) {
               
                case SDL_QUIT:
                   
                    programLaunched = 0;
                    break;
                case SDL_MOUSEMOTION:
                if (dans_le_menu == 1){
                  if ((event.motion.x >= 450) && (event.motion.x <= 600) && (event.motion.y >= 800) && (event.motion.y <= 860)){
                    
                    mouse_on_start = 1;
                    }else{
                    mouse_on_start = 0;
                    }
                }
                if (dans_le_menu == 3){

                    if (event.motion.x<rx+50){
                      rx=rx-10;
                    }else if(event.motion.x>rx+50){
                      rx=rx+10;
                    }
                }
                
                    break;

                case SDL_MOUSEBUTTONUP:
                 if ((dans_le_menu==1) && (event.motion.x >= 450) && (event.motion.x <= 550) && (event.motion.y >= 800) && (event.motion.y <= 900)){
                  dans_le_menu = 2;
                  apparition_sorciere=1;
                 }     
                 if ((dans_le_menu==2) && (move_sorciere == 1) && (event.motion.x >= 440) && (event.motion.x <= 495) && (event.motion.y >= 515) && (event.motion.y <= 615)){
                     move_sorciere = move_sorciere + 1;
                 }
                if (move_sorciere==4){
                    move_sorciere = move_sorciere + 1;
                }
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




//                                                                                 int main


int main(){
    
    init(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_game();
    gameLoop();
    freeAndTerminate();
}



