#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include "fonctions_fichiers.h"
#include "constante.h"
#include <stdbool.h>
#include "world.h"
#include "graphic.h"
#include "message.h"
#include"jeu.h"
#include "sound.h"



int main(int argc, char *argv[]){
	
	SDL_Window* fenetre;  // Déclaration de la fenêtre
	SDL_Event evenements; // Événements liés à la fenêtre
	SDL_Renderer* ecran ;
	jeu_t jeu;
	world_t world;
	init_SDL();
	init_world(&world,1,0);
	fenetre = creer_window(HAUTEUR_ECRAN,LARGEUR_ECRAN);
	ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
	TTF_Init();
	TTF_Font *font = TTF_OpenFont("./arial.ttf",35);
	message_t msg;
	init_jeux(&jeu);
	init_message(&msg,ecran,font,jeu.tab_score,world.niveau);
	//Charger l’image
	init_textures(&jeu,&world,ecran);
	init_mixer();
	bruitages_t *bruits = init_bruitages();
	//play_music(bruits->background);
	printf("nbr ennemy %i\n",world.ennemies.nbr_ennemies);
	printf("ligne   %i colonne %i \n",world.ligne , world.colonne);
    printf("hello %i %i %i\n",jeu.tab_score[0],jeu.tab_score[1],jeu.tab_score[2]);

	while(!world.terminer)
	{
		handle_events(&jeu,&world,&evenements,ecran,font,&msg,bruits);
		update_world(&world,bruits);
		//world.ennemy.DestR_sprite.x++;
		refresh_graphic(&jeu,&world,ecran,font,&msg,bruits);
		pause(15);// une pause du programe pendant 10 ms  
	}
	update_best_score("score.txt",jeu.tab_score,world.score);
	clean_world(&world);
	clear_textures(&jeu,&world);
	clean_message(&msg);
	clean_bruitage(bruits);
	//clean_jeu(&jeu);
	// Fermer la police et quitter SDL_ttf
	TTF_CloseFont( font );
	TTF_Quit();
	// Libération de l’écran (renderer)
	SDL_DestroyRenderer(ecran);
	// Quitter SDL 
	SDL_DestroyWindow(fenetre);
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}
