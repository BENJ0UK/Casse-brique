#include <SDL2/SDL.h>
#include <unistd.h>
#include <SDL2/SDL_ttf.h>
#include "sdl_helper/function.h"
#include "sdl_helper/text_functions.h"
#include "sdl_helper/audio_functions.h"
#include "sdl_helper/constants.h"
#include <time.h>


/* to do list :
 -texte sorcière
 -changer vitesse de balle
*/

//                                                                                  Variables
int bx = 400;//x balle 
int by = 850;//y balle
int v_x = 0; //direction x balle
int v_y = 0;// direction y balle
int rx = 150;// x raquette 
int ry = 900;//y raquette
int start_game=0;
int vitesse_balle;
int collision_balle_raquette;
int dans_le_menu = 1;
int programLaunched;
int tbx = 0;
int tby = 0;
int hauteur_brique = 50;
int largeur_brique = 96;
int tab_brique[9][4];
int fin_jeu = 0;
int xbrique ;
int ybrique ;
int r=3;
int nombre_vie=3;
int commencer_jeu=0;
int press_h_to_start_apparition=0;
int mouse_on_start = 0;
int move_sorciere = 0;
int xsorciere = 1000;
int compteur_briques = 0;
int case_tab_ingred = 0;
int ingred =0;
int compteur_tab_ingred=0;
int score = 0;
int  case_tab_score=0;
int case_tab_score_2=0;
int mouse_on_door = 0;
int mouse_on_restart = 0;
int mouse_on_exit =0;
int ingredient_is_falling=0;
typedef struct iNGREDIENT{
    int apparition_ingredient;
    int x_ingred;
    int y_ingred;
    int num_sprite;//sprite les différents ingrédients
} iNGREDIENT;

iNGREDIENT tableau_ingredients [100];

int stop_ingred = 0;
int compteur_frame=0;

int x_score=1049;//position x de la barre violette de score
int y_score=745;//position y de la barre violette de score
int score_total; 

   

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
   
 // fantome_start();

}

//                                                                            sorcière menu de fin
void sorciere_menu_fin(){

 while (xsorciere != 800){
          
           sprite(0,0,"sprite/maison_interieur_fin.bmp");
           xsorciere = xsorciere - 2;
           if (nombre_vie==0){
            sprite(xsorciere,650,"sprite/sorciere_pleure.bmp"); 
            
           }else{
            sprite(xsorciere,650,"sprite/sorciere_contente.bmp"); 
           }          
           actualize();
        }
}

//                                                                                menu de fin
void menu_fin(){       

//sprite menu + bulle + text
         sprite(0,0,"sprite/maison_interieur_fin.bmp");
         if (nombre_vie==0){
            sprite(xsorciere,650,"sprite/sorciere_pleure.bmp"); 
            sprite (400, 100, "sprite/game_over.bmp");
            sprite(0,600,"sprite/bulle_texte.bmp");
            textChangeColor (224, 127, 36,0);
            textDrawText("dommage, merci ",120,790,texte_sorciere_16);
            textDrawText("quand meme...",120,815,texte_sorciere_16);
            
           }else{
            sprite(xsorciere,650,"sprite/sorciere_contente.bmp"); 
            sprite (320, 60, "sprite/Victory.bmp");
            sprite(0,600,"sprite/bulle_texte.bmp");
            textChangeColor (224, 127, 36,0);
            textDrawText("Super ! ",120,790,texte_sorciere_16);
            textDrawText("Merci beaucoup",120,815,texte_sorciere_16);
            
           }   

// bouton interactif exit / restart
       switch (mouse_on_restart){
                    case 0:
                        sprite (500,650,"sprite/bouton_restart.bmp");
                        break;
                    case 1:
                        sprite (500,650,"sprite/bouton_restart_pushed.bmp");
                        break;
             }
       switch (mouse_on_exit){
                    case 0:
                        sprite (520,800,"sprite/exit1.bmp");
                        break;
                    case 1:
                        sprite (520,800,"sprite/exit2.bmp");
                        break;
             }

// sprite des étoiles
            if (score_total*20<400){
                sprite(520,500,"sprite/etoile_grise.bmp");
                sprite(580,500,"sprite/etoile_grise.bmp");
                sprite(640,500,"sprite/etoile_grise.bmp");
            }
            if (score_total*20>=400 && score_total*20<560){
                sprite(520,500,"sprite/etoile_jaune.bmp");
                sprite(580,500,"sprite/etoile_grise.bmp");
                sprite(640,500,"sprite/etoile_grise.bmp");
            }
            if (score_total*20>=560 && score_total*20<700){
                sprite(520,500,"sprite/etoile_jaune.bmp");
                sprite(580,500,"sprite/etoile_jaune.bmp");
                sprite(640,500,"sprite/etoile_grise.bmp");
            }
            if (score_total*20>=700){
                sprite(520, 500, "sprite/etoile_jaune.bmp");
                sprite(580,500,"sprite/etoile_jaune.bmp");
                sprite(640,500,"sprite/etoile_jaune.bmp");
                
            }
   

}

//                                                                         Initialisation du tableau
void init_tab(){
for (case_tab_ingred = 0; case_tab_ingred <= 100; case_tab_ingred ++){
            tableau_ingredients [case_tab_ingred].num_sprite= rand()%4;
           
 }

for (tby=0;tby<=3;tby++){ 
    for (tbx=0;tbx<=8;tbx++){
       tab_brique[tbx][tby] = 1;
     }
      
 }
}

//                                                                            Animation chaudron 
void animation_chaudron(){

  int animeframe;
  char bulle [300];
  for (animeframe = 1; animeframe<=14;animeframe++){
     clear();
     sprite(0,0,"sprite/maison_interieur15.bmp");
     sprite(1001,0,"sprite/chaudron_score_test.bmp");
     sprite(xsorciere,650,"sprite/sorcière_gentille.bmp");
     sprite(0,600,"sprite/bulle_texte_700.bmp");
     textChangeColor (224, 127, 36,0);
     textDrawText("je n'arrive plus a",180,740,texte_sorciere_16);
     textDrawText("retrouver les",180,765,texte_sorciere_16);
     textDrawText("ingredients de ma ",180,790,texte_sorciere_16);
     textDrawText("recette.",180,815,texte_sorciere_16);
     textDrawText("tu dois m'aider",180,840,texte_sorciere_16);
     textDrawText("a les retrouver !",180,865,texte_sorciere_16);
     textDrawText("clique sur le ",180,890,texte_sorciere_16);
     textDrawText("chaudron pour lancer  ",180,915,texte_sorciere_16);
     textDrawText("les recherches.",180,940,texte_sorciere_16);
     sprintf(bulle,"bullebulle/bulle%d.bmp",animeframe);
     sprite (370,520,bulle);
     actualize();
     usleep(50000);
     }

 
}

//                                                                                 Init_game
void init_game(){
srand(time(NULL));
init_tab();
audioLoadAndPlay("sdl_helper/sound/theme_sorciere.wav",3);
}

//                                                                              reset variables
void reset_variable(){
    bx = 400;
    by = 850;
    v_x = 0; //direction x balle
    v_y = 0;// direction y balle
    dans_le_menu = 1;
    init_tab();
    fin_jeu = 0;
    nombre_vie=3;
    commencer_jeu=0;
    move_sorciere = 0;
    xsorciere = 1200;
    compteur_briques = 0;
    score = 0;
    score_total=0;
    for (int reset_tab=0;reset_tab <= 99;reset_tab++){
        tableau_ingredients[reset_tab].apparition_ingredient=0;
    }
    
 
}

//                                                                              balle immobile
void reset_balle(){
    v_y=0;
    v_x=0;
    bx= 400;
    by= 850;
    vitesse_balle = 0;
    start_game =0;

}

//                                                                                 démarrer
void démarrer(){  
    // seulement si h pressed
    
    v_y=2;
    v_x=2;
/*if (score_total< 20 && start_game==1){
       v_y=2;
       v_x=2;
    } 
    if (score_total>=20 && score_total <28 && start_game==1 ){
       v_y=4;
       v_x=4;
    }
    if (score_total>=28 && start_game==1 ){
       v_y=8;
       v_x=8;
    }
    start_game=1;*/
}

//                                                                            Bordure de fenêtre
void sortie_map(){
    // bordure balle x
    if(bx >= 990){
      v_x=-v_x;
      
    }else if (bx <= 10 ){
      v_x=-v_x;
    
    }
    
    // bordure balle y
    if (by >= 990){//perdu
     audioLoadAndPlay("sdl_helper/sound/son_verre1.wav",1);
     nombre_vie-=1;
     stop_ingred = 1;
     reset_balle();
     for (case_tab_ingred = 0; case_tab_ingred <= 100; case_tab_ingred ++){
        tableau_ingredients [case_tab_ingred].apparition_ingredient = 0;
     }
    
    }else if (by <= 10){ 
     v_y=-v_y;
     
    }
    
    // bordure raquette en x
    if (rx <0){
       rx=0;
       
    }else if (rx > 880){
        rx=880;  
   
    }
}

//                                                                          Déplacements de balle
void deplacement_balle(){ 

/*if (start_game == 1){
   if (score_total< 20 ){
       v_y=2;
       v_x=2;
       start_game =0;
    } 
    if (score_total>=20 && score_total <28 ){
       v_y=4;
       v_x=4;
       start_game =0;
    }
    if (score_total>=28 ){
       v_y=8;
       v_x=8;
       start_game =0;
    }
 
 }  */
  bx=bx+v_x;
  by=by+v_y;
}

//                                                                               Draw briques
void briques(){    

    for (tby=0;tby<=3;tby++){ 
        for (tbx=0;tbx<=8;tbx++){
         
             if (tab_brique[tbx][tby] == 1){
             sprite(tbx*(largeur_brique+2)+60,tby*(hauteur_brique+2),"sprite/briques.bmp");
            }
        }
    }    
}

//                                                                                 Sorcière
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
            sprite(0,600,"sprite/bulle_texte_700.bmp");
            textChangeColor (224, 127, 36,0);
            textDrawText("hey! j'ai besoin",190,740,texte_sorciere_16);
            textDrawText("de ton aide",190,765,texte_sorciere_16);
            textDrawText("pour concocter",190,790,texte_sorciere_16);
            textDrawText("une toute",190,815,texte_sorciere_16);
            textDrawText("nouvelle potion!",190,840,texte_sorciere_16);
            textDrawText("clique sur la",190,865,texte_sorciere_16);
            textDrawText("porte pour venir",190,890,texte_sorciere_16);
            textDrawText("m'aider.",190,915,texte_sorciere_16);

       } else if (mouse_on_door == 1){
            sprite(0,0,"sprite/maison_menu_porte_ouverte.bmp");
            sprite(xsorciere,650,"sprite/sorcière_gentille.bmp");
            sprite(0,600,"sprite/bulle_texte_700.bmp");
            textChangeColor (224, 127, 36,0);
            textDrawText("hey! j'ai besoin",190,740,texte_sorciere_16);
            textDrawText("de ton aide",190,765,texte_sorciere_16);
            textDrawText("pour concocter",190,790,texte_sorciere_16);
            textDrawText("une toute",190,815,texte_sorciere_16);
            textDrawText("nouvelle potion!",190,840,texte_sorciere_16);
            textDrawText("clique sur la",190,865,texte_sorciere_16);
            textDrawText("porte pour venir",190,890,texte_sorciere_16);
            textDrawText("m'aider.",190,915,texte_sorciere_16);
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

//                                                                              Press H to start
void press_h_to_start(){
    compteur_frame ++;

    if (v_x == 0 && v_y == 0){
        if (compteur_frame <= 60){
    textChangeColor(255,255,255,0);
    textDrawText ("Press h to start",250,600,texte_sorciere_28);
        }
    }
    if (compteur_frame>= 120){
        compteur_frame =0;
    }
}

//                                                                        Collisions balle-raquettes
void collision(){
//rx-2 car si non la balle traversait la raquette au niveau du bord gauche
//balle raquette
 

 if (( (v_y>0) && (bx-10>=(rx-3)) && (bx+10<=(rx+153))) && (by+10>=ry) && (by+10<=ry+20)){
  v_y=-v_y;
  
  collision_balle_raquette = 1;
 } else {
    collision_balle_raquette = 0;
 }
 
}  

//                                                                                ingrédients
void ingrédients(){
  
   for (case_tab_ingred = 0; case_tab_ingred <= 100; case_tab_ingred ++){
        if (tableau_ingredients [case_tab_ingred].apparition_ingredient == 1){
            ingredient_is_falling = 1;
            
            
            switch (tableau_ingredients [case_tab_ingred].num_sprite){
            case 0:
         sprite(tableau_ingredients[case_tab_ingred].x_ingred,tableau_ingredients[case_tab_ingred].y_ingred,"sprite/crane.bmp");
                break;

             case 1:
         sprite(tableau_ingredients[case_tab_ingred].x_ingred,tableau_ingredients[case_tab_ingred].y_ingred,"sprite/viande.bmp");
                break;

             case 2:
         sprite(tableau_ingredients[case_tab_ingred].x_ingred,tableau_ingredients[case_tab_ingred].y_ingred,"sprite/oeil.bmp");
                break;

             case 3:
         sprite(tableau_ingredients[case_tab_ingred].x_ingred,tableau_ingredients[case_tab_ingred].y_ingred,"sprite/plume.bmp");
                break;

            default:
                break;
            }
         
           if (tableau_ingredients[case_tab_ingred].y_ingred > 995 ){
              tableau_ingredients[case_tab_ingred].apparition_ingredient = 0;
              ingredient_is_falling = 0;
             
            }
        
           if (((tableau_ingredients[case_tab_ingred].x_ingred+25>=rx) && (tableau_ingredients[case_tab_ingred].x_ingred+25<=(rx+150))) && ((tableau_ingredients[case_tab_ingred].y_ingred+50>=ry) && (tableau_ingredients[case_tab_ingred].y_ingred+50<=ry+20))){
             tableau_ingredients[case_tab_ingred].apparition_ingredient = 0;
             ingredient_is_falling = 0;
             score_total++;    
            }
            
            
         tableau_ingredients[case_tab_ingred].y_ingred = tableau_ingredients[case_tab_ingred].y_ingred+1;
           
        }
          
    }



 



    }   

//                                                                          collisions balle-brique
void collision_bb(){
//balle brique




// v_y<0 haut v_y>0 bas v_x<0 gauche v_x>0 droite
    for (tby=0;tby<=3;tby++){
       for (tbx=0;tbx<=8;tbx++){ 
            xbrique = tbx*(largeur_brique+2)+60;
            ybrique = tby*hauteur_brique;
                  //transforme les coordonnées de tableau en coordonnées de fenêtre de jeu:
          

                    // Bas
          if (((v_y<0) && (bx-10>=xbrique-1) && (bx+10<=(xbrique)+largeur_brique+1) && (by-10>=ybrique) && (by-10<=ybrique+hauteur_brique))){
                if (tab_brique[tbx][tby] == 1) {
                   tab_brique[tbx][tby]=0;
                   v_y=-v_y;
                   compteur_briques+=1;
                   tableau_ingredients[compteur_tab_ingred].x_ingred = (tbx*largeur_brique)+48;
                   tableau_ingredients[compteur_tab_ingred].y_ingred = (tby*hauteur_brique)+50;
                   tableau_ingredients [compteur_tab_ingred].apparition_ingredient= 1;
                   compteur_tab_ingred++;
                   
                                  
                   
                }
            }


                    // Haut
           if (((v_y>0) && (bx-10>=xbrique-1) && (bx+10<=xbrique+largeur_brique+1) && (by+10>=ybrique) && (by+10<=ybrique+hauteur_brique))){
                if (tab_brique[tbx][tby] == 1) {
                   tab_brique[tbx][tby]=0;
                   v_y=-v_y;
                   compteur_briques+=1;
                   tableau_ingredients[compteur_tab_ingred].x_ingred = (tbx*largeur_brique)+48;
                   tableau_ingredients[compteur_tab_ingred].y_ingred = (tby*hauteur_brique)+50;
                   tableau_ingredients [compteur_tab_ingred].apparition_ingredient= 1;
                   compteur_tab_ingred++;
                   
     
                }
            }


                    //droite
           if ((v_x<0) && (bx-10<=xbrique+largeur_brique) && (bx-10>=xbrique) && (by+10<=ybrique+hauteur_brique+1) && (by-10>=ybrique-1)){
                if (tab_brique[tbx][tby] == 1) {
                   tab_brique[tbx][tby]=0;
                   v_x=-v_x;
                   compteur_briques+=1;
                   tableau_ingredients[compteur_tab_ingred].x_ingred = (tbx*largeur_brique)+48;
                   tableau_ingredients[compteur_tab_ingred].y_ingred = (tby*hauteur_brique)+50;
                   tableau_ingredients [compteur_tab_ingred].apparition_ingredient= 1;
                   compteur_tab_ingred++;
                  
                }
            }


                    // gauche
           if ((v_x>0)  && (bx+10<=xbrique+largeur_brique) && (bx+10>=xbrique) && (by+10<=ybrique+hauteur_brique+1) && (by-10>=ybrique-1)){
                if (tab_brique[tbx][tby] == 1) {
                   tab_brique[tbx][tby]=0;
                   v_x=-v_x;
                   compteur_briques+=1;
                   tableau_ingredients[compteur_tab_ingred].x_ingred = (tbx*largeur_brique)+48;
                   tableau_ingredients[compteur_tab_ingred].y_ingred = (tby*hauteur_brique)+50;
                   tableau_ingredients [compteur_tab_ingred].apparition_ingredient= 1;
                   compteur_tab_ingred++;
                   
             
                } 
              
            }
           
        }
    }
          
}

//                                                                                   vie
void vie(){
   switch (nombre_vie){
       case 3 :
        sprite (1010,895,"sprite/potion.bmp");
        sprite (1075,895,"sprite/potion.bmp");
        sprite (1140,895,"sprite/potion.bmp"); 
          break;
       case 2 :
        sprite (1010,895,"sprite/potion.bmp");
        sprite (1075,895,"sprite/potion.bmp");
          break;

       case 1 :
          
        sprite (1010,895,"sprite/potion.bmp");
          break;
        
       default:
          break;
    }

   if (nombre_vie == 0 || (compteur_briques == 36 && collision_balle_raquette == 1 && ingredient_is_falling == 0) ){
        dans_le_menu = 4;
    }
    
}
 
//                                                                             fenêtre de score
void score_fonction(){   
  

  y_score = 770 ; // évite que la première barre monte toute seule

            for (int x=0;x<=score_total;x++){
                    if (score_total <= 35){
                     changeColor(88,38,112);
                     drawRect(x_score,y_score,103,score_total*(-20));
                    }else if (score_total == 36){
                     changeColor(88,38,112);
                     drawRect(x_score,y_score,103,-701);
                    }
            }
    if (score_total == 20){
        start_game = 1;
    }
    if (start_game == 28){
        start_game = 1;
    }
}

//                                                                                 DrawGame
void drawGame(){
   
    if (compteur_frame == 600){
        compteur_frame = 0;
    }
    switch (dans_le_menu){ 
    
    case 1 :
        clear();
        menu();
        actualize();
        usleep(100000 / FPS); 
       break;
       
    case 2:
        
        histoire_debut();
        
        break;
  
    
    case 3 : 
        clear(); 
        changeColor(224,127,36);
        sprite(0,0,"sprite/maison_interieur_jeu.bmp");
        sprite(1001,0,"sprite/chaudron_score_test.bmp");
        sprite(bx-10,by-10,"sprite/particule_magie.bmp");
        sprite (rx,ry,"sprite/raquette_chaudron.bmp");
        press_h_to_start();
        vie(); 
        briques();
        collision();
        collision_bb(); 
        ingrédients();
        score_fonction();
        deplacement_balle();
        sortie_map();
        actualize();
        usleep(100000 / FPS); 
       break;

    case 4 :
        clear();
        sorciere_menu_fin(); 
        dans_le_menu++;
       break;

    case 5:
        clear();
        menu_fin();
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

        case SDLK_u:
           if (dans_le_menu==4){
            score_total-=1;
           }
        
            break;
        case SDLK_y:
           if (dans_le_menu==4){
            score_total+=1;
           }
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
            v_y=-v_y;
            break;
        case SDLK_m:
            v_x=-v_x;
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
                    if (dans_le_menu == 1 ){
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
                    
                    if ((dans_le_menu == 5) && (event.motion.x >= 500) && (event.motion.x <= 700) && (event.motion.y >= 650) && (event.motion.y <= 700)){
                             mouse_on_restart=1;
                        }else{
                             mouse_on_restart=0;
                        }
                    if ((dans_le_menu == 5) && (event.motion.x >= 520) && (event.motion.x <= 720) && (event.motion.y >= 800) && (event.motion.y <= 850)){
                             mouse_on_exit=1;
                        }else{
                             mouse_on_exit=0;
                        }
           

                    if (dans_le_menu == 3){
                        if ((event.motion.x<rx+75) && (event.motion.x > 0) ){
                            rx=rx-10;
                        }else if((event.motion.x>rx+75) && (event.motion.x <940)){
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

                    if ((dans_le_menu==5) && (event.motion.x >= 500) && (event.motion.x <= 700) && (event.motion.y >= 650) && (event.motion.y <= 700)){
                        reset_variable();
                        dans_le_menu =1;
                    }
                    if ((dans_le_menu==5) && (event.motion.x >= 520) && (event.motion.x <= 720) && (event.motion.y >= 800) && (event.motion.y <= 850)){
                       freeAndTerminate();
                    }

                break;

                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
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



