#include <../Time/Time.h>
#include "SideralTime.h"

/**
 * Soit à calculer l'heure sidérale locale TSL en un lieu dont on connaît la longitude L, et à un jour J et une heure H (solaire) d'observation donnés1 :
 *
 * On se munit de l'heure sidérale au méridien de Greenwich à un instant de référence donné. Les éphémérides fournissent ce type d'information.
 * À défaut, on utilisera dans la suite le fait que, le 1er janvier 2000 à 12h (TUC), l'heure sidérale au méridien de Greenwich était 18,697374558 heures.
 *
 * On calcule combien de temps (en jours solaires et fractions de jour solaire) sépare l'instant observé de l'instant de référence.
 * Soit D cette durée2. Chaque jour solaire ayant une durée de 24,06570982441908 heures sidérales,
 * il en résulte que l'heure sidérale TSL0 au méridien de Greenwich à l'instant observé est, en heures sidérales :
 * TSL0 = 18,697374558 + 24,06570982441908*D.
 *
 * On ajoute à l'heure sidérale locale de Greenwich TSL0 à l'instant observé un décalage horaire dû à la longitude,
 * à savoir L/15 où L est donné en degrés décimaux, comptés positivement quand on se déplace vers l'Est et négativement vers l'Ouest.
 * En effet, les 360° d'un tour complet sont parcourus en 24h, soit 15° par heure : TSL = TSL0 + L/15 modulo 24
 * (ou modulo 24 signifie qu'on ramène le résultat final entre 0h et 24h par ajout ou différence d'un multiple entier de 24h)3.
 *
 * Le résultat est correct à la seconde près.
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


