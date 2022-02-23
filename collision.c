#include "collision.h"


void collision(POSITION dragon[COLONNE*LIGNE],int *not_echap, int longueur_dragon)
{
	int i;
/* --------------------------------------  gestion de la collision avec les bordures du terrain de jeux  ---------------------------------- */
	if ((dragon[0].colonne*CASE < 0) || (dragon[0].colonne*CASE >= 1200) || (dragon[0].ligne*CASE < 0) || (dragon[0].ligne*CASE >= 800))
	{
		gameover();
		*not_echap=0;
	}

/* --------------------------------  fin de la gestion de la collision avec les bordures du terrain de jeux  ------------------------------ */

/* ----------------------------------------------  gestion de la collision son corps  ----------------------------------------------------- */
	for(i=1; i<longueur_dragon; i++)
	{
		if ((dragon[0].ligne*CASE == dragon[i].ligne*CASE) && (dragon[0].colonne*CASE == dragon[i].colonne*CASE))
		{
			gameover();
			*not_echap=0;
		}
	}

/* ------------------------------------  gestion de la collision avec les buildings (obstacle fixe)  -------------------------------------- */
	/* 1er building */
    if (dragon[0].ligne*CASE >= 640 && dragon[0].ligne*CASE <= 800 && dragon[0].colonne*CASE >= 180 && dragon[0].colonne*CASE <= 240 )
    {
	    gameover();
	    *not_echap=0;
	}
	/*2 eme building*/
	else if (dragon[0].ligne*CASE >= 680 && dragon[0].ligne*CASE <= 800 && dragon[0].colonne*CASE >= 700 && dragon[0].colonne*CASE <= 760 )
    {
	    gameover();
	    *not_echap=0;
	}
}