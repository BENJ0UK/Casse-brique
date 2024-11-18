#include <SDL2/SDL.h>
#include <unistd.h>
#include <SDL2/SDL_ttf.h>
#include "sdl_helper/function.h"
#include "sdl_helper/text_functions.h"
#include "sdl_helper/audio_functions.h"
#include "sdl_helper/constants.h"
#include <time.h>


/*
  printf("test");
  printf("%d",);
  printf("\n",);
*/
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
int tab_brique[9][4];
int fin_jeu = 0;
double inclinaison_bb;
int xbrique ;
int ybrique ;
int r=3;
int compteur_piece=0;
int nombre_vie=3;
int commencer_jeu=0;
int mouse_on_start = 0;

int move_sorciere = 0;
int xsorciere = 1000;
int compteur_briques = 0;
int case_tab_ingred = 0;
int ingred =0;
int ingred_fall=0;
int compteur_tab_ingred=0;
int score = 0;
int  case_tab_score=0;
int case_tab_score_2=0;
int mouse_on_door = 0;

typedef struct iNGREDIENT{
    int apparition_ingredient;
    int x_ingred;
    int y_ingred;
} iNGREDIENT;

iNGREDIENT tableau_ingredients [100];



int x_score=1049;//position x de la barre violette de score
int y_score=745;//position y de la barre violette de score
int coef_score=0;// 
int score_total; // le nombre de barre de score à imprimer à chaque fois que les bonus touchent la raquette

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
    tab_brique[9][4];  
    fin_jeu = 0;
    r=3;
    compteur_piece=0;
    nombre_vie=3;
    commencer_jeu=0;
    mouse_on_start = 0;
    
    move_sorciere = 0;
    xsorciere = 1200;
    compteur_briques = 0;
    
 
}


//                                                                                    Menu

void menu(){
  
sprite(0,0,"sprite/maison_menu.bmp");
  switch (mouse_on_start){
    case 0:
      sprite (450,800, "sprite/start1.bmp");
      
      break;
    case 1:
      sprite (450,800, "sprite/start2.bmp");
    
      break;
  }
  
 

}

//                                                                         Initialisation du tableau


void init_tab(){

for (tby=1;tby<=4;tby++){ 
    for (tbx=0;tbx<=8;tbx++){
       tab_brique[tbx][tby] = 1;
    
     }
 }
}

//                                                                            Animation chaudron 


void animation_chaudron(){

  int animeframe=14;
  char bulle [300];
  for (animeframe = 1; animeframe<=14;animeframe++){
     clear();
     sprite(0,0,"sprite/maison_interieur15.bmp");
     sprite(1001,0,"sprite/chaudron_score_test.bmp");
     sprite(xsorciere,650,"sprite/sorcière_gentille.bmp");
     sprite(0,600,"sprite/bulle_texte.bmp");
     sprintf(bulle,"bullebulle/bulle%d.bmp",animeframe);
     sprite (370,520,bulle);
     actualize();
     usleep(50000);
 
    }

 
}
//                                                                                 Init_game


void init_game(){
init_tab();

srand(time(NULL));
audioLoadAndPlay("sdl_helper/sound/theme_sorciere.wav",3);
}

//                                                                              balle immobile
void reset_balle(){
    k = 0;
    j = 0;
    bx= 400;
    by= 850;

}

//                                                                                 démarrer
void démarrer(){      
        k = 2;
        j = 2;
    }
    

//                                                                            Bordure de fenêtre


void sortie_map(){
    // bordure balle x
    if(bx >= 990){
      j = -j;
      
    }else if (bx <= 10 ){
      j = -j;
    
    }
    
    // bordure balle y
    if (by >= 990){//perdu
     audioLoadAndPlay("sdl_helper/sound/son_mort.wav",1);
     nombre_vie-=1;
     reset_balle();
    
    }else if (by <= 10){ 
     k = -k;
     
    }
    
    // bordure raquette en x
    if (rx < (-20)){
       rx=rx+30;
       
    }else if (rx > 880){
        rx= rx-30;  
   
    }
}

//                                                                          Déplacements de balle


void deplacement_balle(){ 
bx=bx+j;
by=by+k;
}



//                                                                              Draw briques


void briques(){    

for (tby=1;tby<=4;tby++){ 
    for (tbx=0;tbx<=8;tbx++){
         
        if (tab_brique[tbx][tby] == 1){
            if (tbx==0){
        drawRect(tbx*(largeur_brique+2)+60,tby*(hauteur_brique+2),largeur_brique,hauteur_brique);
            }else{
  //+2 pour l'écart entre les briques     
           drawRect(tbx*(largeur_brique+2)+60,tby*(hauteur_brique+2),largeur_brique,hauteur_brique);
            }
         }
      }
  }
}



//                                                                              Sorcière


void histoire_debut(){

  

switch (move_sorciere){

case 0:
       clear();
       while (xsorciere != 800){
         
               clear();
               sprite(0,0,"sprite/maison_menu.bmp");
               xsorciere = xsorciere - 1;
               sprite(xsorciere,650,"sprite/sorcière_gentille.bmp");
               actualize();
               
        } 
        
        move_sorciere = move_sorciere + 1;
       
    break;
case 1:

       clear();
       if (mouse_on_door == 0){
            sprite(0,0,"sprite/maison_menu.bmp");
            sprite(xsorciere,650,"sprite/sorcière_gentille.bmp");
            sprite(0,600,"sprite/bulle_texte.bmp");
       textChangeColor (224,127,36);
       textDrawText("Hello,world !",150,740,texte_sorciere_28);
       } else if (mouse_on_door == 1){
            sprite(0,0,"sprite/maison_menu_porte_ouverte.bmp");
            sprite(xsorciere,650,"sprite/sorcière_gentille.bmp");
            sprite(0,600,"sprite/bulle_texte.bmp");
       
       textDrawText("Hello,world !",150,740,texte_sorciere_28);
       }

       actualize();
      
      
    break;

case 2:
        clear();
        audioLoadAndPlay("sdl_helper/sound/grincement_porte.wav",2);
       while (xsorciere != 1300){
         
               clear();
               sprite(0,0,"sprite/maison_menu_porte_ouverte.bmp");
               xsorciere = xsorciere + 1;
               sprite(xsorciere,650,"sprite/sorcière_gentille.bmp");
               actualize();
            
       }
       
       move_sorciere = move_sorciere + 1;
    
    break;
case 3:
       clear();
       
      while (xsorciere != 800){
         
               clear();
               sprite(0,0,"sprite/maison_interieur15.bmp");
               sprite(1001,0,"sprite/chaudron_score_test.bmp");
               xsorciere = xsorciere - 1;
               sprite(xsorciere,650,"sprite/sorcière_gentille.bmp");
               actualize();
               
       }
       
       move_sorciere = move_sorciere + 1;
    break;
case 4:

       clear();
       animation_chaudron();
       actualize();
     

    break;

case 5:
      
   while (xsorciere != 1300){
               clear();
               sprite(0,0,"sprite/maison_interieur15.bmp");
               sprite(1001,0,"sprite/chaudron_score_test.bmp");
               xsorciere = xsorciere + 1;
               sprite(xsorciere,650,"sprite/sorcière_gentille.bmp");
               actualize();   
       }
       
       move_sorciere = move_sorciere + 1;
    break;
case 6:
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
 

 if (( (k>0) && (bx-10>=(rx-3)) && (bx+10<=(rx+153))) && (by+10>=ry) && (by+10<=ry+20)){
  k = -k;
  score_total = score_total+coef_score;
  coef_score=0;
 
 }
 
}  

//                                                                                ingrédients

void ingrédients(){
   for (case_tab_ingred = 0; case_tab_ingred <= 100; case_tab_ingred ++){
        if (tableau_ingredients [case_tab_ingred].apparition_ingredient == 1){
         drawCircle(tableau_ingredients[case_tab_ingred].x_ingred,tableau_ingredients[case_tab_ingred].y_ingred,10);
         
           if (tableau_ingredients[case_tab_ingred].y_ingred > 995){
              tableau_ingredients[case_tab_ingred].apparition_ingredient = 0;
            }
        
           if (((tableau_ingredients[case_tab_ingred].x_ingred-10>=(rx-3)) && (tableau_ingredients[case_tab_ingred].x_ingred+10<=(rx+153))) && ((tableau_ingredients[case_tab_ingred].y_ingred+10>=ry) && (tableau_ingredients[case_tab_ingred].y_ingred+10<=ry+20))){
             tableau_ingredients[case_tab_ingred].apparition_ingredient = 0;
             score++;
            
                 
               
            }
         tableau_ingredients[case_tab_ingred].y_ingred = tableau_ingredients[case_tab_ingred].y_ingred+3;
        }
          
    }



 



}


//                                                                          collisions balle-brique


void collision_bb(){
//balle brique




// k<0 haut k>0 bas j<0 gauche j>0 droite
    for (tby=1;tby<=4;tby++){
       for (tbx=0;tbx<=8;tbx++){ 
            xbrique = tbx*(largeur_brique+2)+60;
            ybrique = tby*hauteur_brique;
                  //transforme les coordonnées de tableau en coordonnées de fenêtre de jeu:
          

                    // Bas
          if (((k<0) && (bx-10>=xbrique-1) && (bx+10<=(xbrique)+largeur_brique+1) && (by-10>=ybrique) && (by-10<=ybrique+hauteur_brique))){
                if (tab_brique[tbx][tby] == 1) {
                   tab_brique[tbx][tby]=0;
                   compteur_piece+=1;
                   k = -k;
                   compteur_briques+=1;
                   tableau_ingredients[compteur_tab_ingred].x_ingred = (tbx*largeur_brique)+48;
                   tableau_ingredients[compteur_tab_ingred].y_ingred = (tby*hauteur_brique)+50;
                   tableau_ingredients [compteur_tab_ingred].apparition_ingredient= 1;
                   compteur_tab_ingred++;
                   coef_score+=1;
                
                   
                }
            }


                    // Haut
           if (((k>0) && (bx-10>=xbrique-1) && (bx+10<=xbrique+largeur_brique+1) && (by+10>=ybrique) && (by+10<=ybrique+hauteur_brique))){
                if (tab_brique[tbx][tby] == 1) {
                   tab_brique[tbx][tby]=0;
                   compteur_piece+=1;
                   k = -k;
                   compteur_briques+=1;
                   tableau_ingredients[compteur_tab_ingred].x_ingred = (tbx*largeur_brique)+48;
                   tableau_ingredients[compteur_tab_ingred].y_ingred = (tby*hauteur_brique)+50;
                tableau_ingredients [compteur_tab_ingred].apparition_ingredient= 1;
                   compteur_tab_ingred++;
                   coef_score+=1;
                }
            }


                    //droite
           if ((j<0) && (bx-10<=xbrique+largeur_brique) && (bx-10>=xbrique) && (by+10<=ybrique+hauteur_brique+1) && (by-10>=ybrique-1)){
                if (tab_brique[tbx][tby] == 1) {
                   tab_brique[tbx][tby]=0;
                   compteur_piece+=1;
                   j = -j;
                   compteur_briques+=1;
                   tableau_ingredients[compteur_tab_ingred].x_ingred = (tbx*largeur_brique)+48;
                   tableau_ingredients[compteur_tab_ingred].y_ingred = (tby*hauteur_brique)+50;
                   tableau_ingredients [compteur_tab_ingred].apparition_ingredient= 1;
                   compteur_tab_ingred++;
                   coef_score+=1;
                }
            }


                    // gauche
           if ((j>0)  && (bx+10<=xbrique+largeur_brique) && (bx+10>=xbrique) && (by+10<=ybrique+hauteur_brique+1) && (by-10>=ybrique-1)){
                if (tab_brique[tbx][tby] == 1) {
                   tab_brique[tbx][tby]=0;
                   compteur_piece+=1;
                   j = -j;
                   compteur_briques+=1;
                   tableau_ingredients[compteur_tab_ingred].x_ingred = (tbx*largeur_brique)+48;
                   tableau_ingredients[compteur_tab_ingred].y_ingred = (tby*hauteur_brique)+50;
                   tableau_ingredients [compteur_tab_ingred].apparition_ingredient= 1;
                   compteur_tab_ingred++;
                   coef_score+=1;
                } 
              
            }
           
        }
    }
          
}



//                                                                                  vie


void vie(){
switch (nombre_vie){
       case 2 :
        
          sprite (0,0,"sprite/avant_derniere_vie.bmp");
          break;

       case 1 :
          
          sprite (0,0,"sprite/derniere_vie.bmp");
          break;
        
       

       default:
          break;
    }
    
}
 
//                                                                             fenêtre de score
void score_fonction(){
int score_for=0;// variable incrémentée dans le premier for
y_score = 745 ; // évite que la première barre monte toute seule



       for(score_for=0;score_for<=score;score_for++){
            for (int x=0;x<=score_total;x++){
                    if (y_score >= 45){
                     sprite (x_score,y_score,"sprite/barre_score.bmp");
                     y_score-=1;
                    }

            }
        }
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
        sprite(0,0,"sprite/maison_interieur_jeu.bmp");
        sprite(1001,0,"sprite/chaudron_score_test.bmp");
        changeColor(255,255,0);
        sprite(bx-10,by-10,"sprite/particule_magie.bmp");
        vie();
        sprite (rx,ry,"sprite/raquette_chaudron.bmp");
        briques();
        
        collision();
        collision_bb(); 
        ingrédients();
        score_fonction();
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
        case SDLK_l:
            k = -k;
            break;
        case SDLK_m:
            j = -j;
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
                if ((dans_le_menu == 2) && (move_sorciere == 1) && (event.motion.x >= 510) && (event.motion.x <= 580) && (event.motion.y >= 495) && (event.motion.y <= 595)){
                    mouse_on_door = 1;
                }else{
                    mouse_on_door = 0;
                }
                if (dans_le_menu == 3){

                    if ((event.motion.x<rx+75) && (event.motion.x > 0) ){
                      rx=rx-10;
                    }else if((event.motion.x>rx+75) && (event.motion.x <1000)){
                      rx=rx+10;
                    }
                }
                
                    break;

                case SDL_MOUSEBUTTONUP:
                 if ((dans_le_menu==1) && (event.motion.x >= 450) && (event.motion.x <= 550) && (event.motion.y >= 800) && (event.motion.y <= 900)){
                  dans_le_menu = 2;
               
                 }     
                 if ((dans_le_menu==2) && (move_sorciere == 1) && (event.motion.x >= 510) && (event.motion.x <= 580) && (event.motion.y >= 495) && (event.motion.y <= 595)){
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



