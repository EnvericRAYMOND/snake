#ifndef COLLISION_H
#define COLLISION_H

#include"gameover.h"

typedef struct position
{
	int colonne; 
	int ligne;	
} POSITION;

#define LIGNE 40
#define COLONNE 60
#define CASE 20

void collision(POSITION dragon[COLONNE*LIGNE],int *not_echap, int longueur_dragon);
#endif