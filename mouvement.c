#include "mouvement.h"
#define GAUCHE 0
#define DROITE 1
#define HAUT 2
#define BAS 3

void mouvement(int *Direction,int *pause,int *touche,int *not_echap){
	*touche = Touche();
	if ((*touche == XK_Up) && (*Direction != BAS ) && (*pause != 1)) 
	{
		*Direction = HAUT;
	}
	else if ((*touche == XK_Right) && (*Direction != GAUCHE) && (*pause != 1))
	{
		*Direction = DROITE;
	}
	else if((*touche == XK_Left) && (*Direction != DROITE) && (*pause != 1))
	{
		*Direction = GAUCHE;
	}
	else if ((*touche == XK_Down) && (*Direction != HAUT) && (*pause != 1))
	{
		*Direction = BAS;
	}
	else if (*touche == XK_Escape)
	{
		*not_echap = 0;
	}
	else if ((*touche == XK_space) && (*pause == 0))
	{
	    *pause = 1;
    }
    else if((*touche == XK_space) && (*pause == 1))
    {
    	*pause = 0;
    }
}