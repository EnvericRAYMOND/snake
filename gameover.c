#include "gameover.h"

void gameover()
{
	/* écran de fin de jeux s'affiche lorque le joueur meurt (collision avec une bordure)*/
	int touche;
	ChoisirCouleurDessin(CouleurParNom("black"));
    RemplirRectangle(0,0,1200,800);
    ChoisirCouleurDessin(CouleurParNom("red"));
    EcrireTexte(480,370,"GAME OVER",2);
    ChoisirCouleurDessin(CouleurParNom("white"));
    EcrireTexte(260,750,"Temps",2);
    EcrireTexte(735,750,"Score",2);
    EcrireTexte(443,500,"echap pour quitter",2);
    touche = Touche();
    while(touche != XK_Escape)
    {
    	touche = Touche();
    }
}