#include <../Time/Time.h>
#include "SideralTime.h"

/**
 * Soit � calculer l'heure sid�rale locale TSL en un lieu dont on conna�t la longitude L, et � un jour J et une heure H (solaire) d'observation donn�s1 :
 *
 * On se munit de l'heure sid�rale au m�ridien de Greenwich � un instant de r�f�rence donn�. Les �ph�m�rides fournissent ce type d'information.
 * � d�faut, on utilisera dans la suite le fait que, le 1er janvier 2000 � 12h (TUC), l'heure sid�rale au m�ridien de Greenwich �tait 18,697374558 heures.
 *
 * On calcule combien de temps (en jours solaires et fractions de jour solaire) s�pare l'instant observ� de l'instant de r�f�rence.
 * Soit D cette dur�e2. Chaque jour solaire ayant une dur�e de 24,06570982441908 heures sid�rales,
 * il en r�sulte que l'heure sid�rale TSL0 au m�ridien de Greenwich � l'instant observ� est, en heures sid�rales :
 * TSL0 = 18,697374558 + 24,06570982441908*D.
 *
 * On ajoute � l'heure sid�rale locale de Greenwich TSL0 � l'instant observ� un d�calage horaire d� � la longitude,
 * � savoir L/15 o� L est donn� en degr�s d�cimaux, compt�s positivement quand on se d�place vers l'Est et n�gativement vers l'Ouest.
 * En effet, les 360� d'un tour complet sont parcourus en 24h, soit 15� par heure : TSL = TSL0 + L/15 modulo 24
 * (ou modulo 24 signifie qu'on ram�ne le r�sultat final entre 0h et 24h par ajout ou diff�rence d'un multiple entier de 24h)3.
 *
 * Le r�sultat est correct � la seconde pr�s.
*/
#define TSMG 6.70078333333333333333333333333
#define TURF 1514764800
#define DJS  24.06570982441908
#define SEC_PER_DAY 86400.0
SideralTime::SideralTime(time_t time)
{
    double nbDays = (time - TURF)/SEC_PER_DAY;
    time_t TSE = (time_t) (DJS * nbDays)*SEC_PER_DAY;
    time_t TSU = (time_t)TSMG*SEC_PER_DAY + TSE;
    sideralTime = TSU%(int)(DJS*60*60);

}

SideralTime::~SideralTime()
{
    //dtor
}


