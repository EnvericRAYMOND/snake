#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <time.h>
#include <unistd.h>
#include "mouvement.h"
#include "collision.h"

#define CYCLE 1000000L
#define CASE 20
#define NOURRITURE_MAX 5
#define LIGNE 40
#define COLONNE 60
#define L 1200
#define H 800


#define GAUCHE 0
#define DROITE 1
#define HAUT 2
#define BAS 3


int main(void)
{
	srand(time(0));
	POSITION dragon[COLONNE*LIGNE], oiseaux[5];

	int oiseau_x,oiseau_y,longueur_dragon = 10,nbr; /*défini la longueur du dragon à son apparition*/
	int a,x,y,i,j , pos =1;
	int tableaux[6], tableau[6];
	int Direction = GAUCHE; /*le dragon va avancer à gauche dès le début*/
	int not_echap = 1;
	int pause = 0;
	int touche;
	char score[100]="0";
	int scor = 0;
	char minutes[100];
	char secondes[100];
	unsigned long sec=0,temps,min=0;
	temps=Microsecondes()+CYCLE;


	/* Création de la fenetre avec ses différentes couleurs et ajout du nom du jeux */

	InitialiserGraphique();
	CreerFenetre(300,50,1200,880);
    ChoisirCouleurDessin(CouleurParComposante(7,38,48));
    RemplirRectangle(0,0,1200,800);
    ChoisirCouleurDessin(CouleurParNom("green"));
    RemplirRectangle(0,800,1200,80);
    ChoisirTitreFenetre("Dragon Chinois(Romain LEOTURE et Enveric RAYMOND)");


/* ---------------------------------------------On fait spawn les oiseaux ------------------------------------------ */
	for(nbr = 0; nbr < NOURRITURE_MAX; nbr++) 
	{
		do
		{
			pos = 1;
			oiseaux[nbr].ligne = rand()%LIGNE;
			oiseaux[nbr].colonne = rand()%COLONNE;
			for(j=0; j<longueur_dragon; j++)
			{
				if(oiseaux[nbr].ligne==dragon[j].ligne && oiseaux[nbr].colonne==dragon[j].colonne)
				{
					pos = 0;
				}
			}
		} while(((oiseaux[nbr].ligne*CASE>=640 && oiseaux[nbr].ligne*CASE<=800) && (oiseaux[nbr].colonne*CASE>=180 && oiseaux[nbr].colonne*CASE<=240)) || ((oiseaux[nbr].ligne*CASE>=680 && oiseaux[nbr].ligne*CASE<=800) && (oiseaux[nbr].colonne*CASE>=700 && oiseaux[nbr].colonne*CASE<=760)) || pos==0);
	}
/* --------------------------------------------------- dragon ---------------------------------------------------- */
	for(int i = 0; i < 10; i++) 
	{
		dragon[i].ligne = 20;
		dragon[i].colonne = i+30;
	}

	while(not_echap) 
	{
	
		usleep(89999);

/* -------------------------------------------- gestion des mouvement du dragon -------------------------------------- */
		if (ToucheEnAttente()) 
		{
			mouvement(&Direction, &pause, &touche, &not_echap);
		}

		if(pause != 1 && not_echap != 0)
		{
			for(a=longueur_dragon;a > 0; a--) 
			{
				dragon[a].colonne=dragon[a-1].colonne;
				dragon[a].ligne=dragon[a-1].ligne;
			}
/* ----------------------------------------------- Empêche le dragon de retourner sur ses pas  ------------------------------------- */
			if (Direction == HAUT) 
			{
				dragon[0].ligne = dragon[0].ligne-1;
			}
			else if (Direction == DROITE)
			{
				dragon[0].colonne = dragon[0].colonne+1;
			}
			else if (Direction == GAUCHE)
			{
				dragon[0].colonne = dragon[0].colonne-1;
			}
			else if (Direction == BAS)
			{
				dragon[0].ligne = dragon[0].ligne+1;
			}

			EffacerEcran(CouleurParComposante(7,38,48));
			/* sprites building (la règle suplémentaire dans notre cas un obstacle fixe représenté par 2 buildings) */
		    /* 1er building */
		    ChargerSprite("1building.png");
		    AfficherSprite(2,180,760);
		    AfficherSprite(2,180,720);
		    AfficherSprite(2,180,680);
		    AfficherSprite(2,180,640);
		    /* 2eme building */
		    ChargerSprite("2building.png");
		    AfficherSprite(3,700,760);
		    AfficherSprite(3,700,720);
		    AfficherSprite(3,700,680);

		    if (Microsecondes()>temps)
		    {
				sec++;
				temps=Microsecondes()+CYCLE;
				/* Convertion des secondes en minutes */
				if (sec==60) 
				{
					sec = 0;
					min++;
				}
			}
/*---------------------------------- affiche un encart en  bas de la fenêtre avec le chronomètre et le score ------------------------------*/
			sprintf(secondes,"%02d",sec);
			sprintf(minutes,"%02d",min);
			ChoisirCouleurDessin(CouleurParNom("black"));
			RemplirRectangle(0,800,1200,80);
			ChoisirCouleurDessin(CouleurParNom("purple"));
			EcrireTexte(200,850,"chrono",2);
			EcrireTexte(320,850, minutes,2);
			EcrireTexte(370,850,":",2);
			EcrireTexte(400,850, secondes,2);
			sprintf(score,"%08d",scor);
			ChoisirCouleurDessin(CouleurParNom("blue"));
			EcrireTexte(713,850, score,2);
			/* fonction qui s'occupe des collisions */
			collision(dragon, &not_echap, longueur_dragon);
/* ------------------------------  fin de la gestion de la collision avec les buildings (obstacle fixe)  ---------------------------------- */
		}

		if(not_echap != 0)
		{
/*------------------------------------------ afficher le dragon ------------------------------------*/
			ChoisirCouleurDessin(CouleurParNom("yellow"));
			for(int i = 0; i < longueur_dragon; i++)
			{
				RemplirRectangle(dragon[i].colonne*CASE, dragon[i].ligne*CASE, CASE, CASE);
			}

/*------------------------------------------ afficher les oiseaux ------------------------------------*/
			ChoisirCouleurDessin(CouleurParNom("white"));
			for(int i = 0; i < NOURRITURE_MAX; i++)
			{
				RemplirRectangle(oiseaux[i].colonne*CASE, oiseaux[i].ligne*CASE, CASE, CASE);
			}
			for (i = 0; i < NOURRITURE_MAX; i++)
			{
				/*on recupère la position des oiseaux*/
				oiseau_x = oiseaux[i].colonne;
				oiseau_y = oiseaux[i].ligne;

/*------------------------------------- Si le dragon mange un oiseau---------------------------------*/
				if (dragon[0].colonne == oiseau_x && dragon[0].ligne == oiseau_y)
				{
					do
					{
						pos = 1;
						oiseaux[i].ligne = rand()%LIGNE;
						oiseaux[i].colonne = rand()%COLONNE;
						for(j=0; j<longueur_dragon; j++)
						{
							if((oiseaux[i].ligne==dragon[j].ligne) && (oiseaux[i].colonne==dragon[j].colonne))
							{
								pos = 0;
							}
						}
					} while((((oiseaux[i].ligne*CASE>=640 && oiseaux[i].ligne*CASE<=800) && (oiseaux[i].colonne*CASE>=180 && oiseaux[i].colonne*CASE<=240)) || ((oiseaux[i].ligne*CASE>=680 && oiseaux[i].ligne*CASE<=800) && (oiseaux[i].colonne*CASE>=700 && oiseaux[i].colonne*CASE<=760))) || pos==0);

					ChoisirCouleurDessin(CouleurParNom("white"));
					RemplirRectangle(oiseaux[i].colonne*CASE, oiseaux[i].ligne*CASE,CASE,CASE);
/*--------------------------------------- gestion du score -------------------------------------------*/
					scor = scor +5;
					longueur_dragon = longueur_dragon+2;
				}
			}
		}
	}

	FermerGraphique();
	return 0;

}


