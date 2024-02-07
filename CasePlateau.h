#ifndef CASEPLATEAU_H_INCLUDED
#define CASEPLATEAU_H_INCLUDED
#include "User.h"
#include "Cartes.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <allegro.h>


/* indice casePlato
   1 : dans une salle
   2 : sur une case du plateau random
*/

class CasePlato
{
private :
    bool m_presence;
    bool m_passageSecret;
    int m_posx;
    int m_posy;
    int m_indice;//savoir si on est dans une salle ou sur des cases random
    std::string m_salle;

public :
    // ctor & dtor
    CasePlato();
    ~CasePlato();
    void setPresence(bool body);
    void setPassage(bool secret);
    void setX(int posx);
    void setY(int posy);
    void setIndice(int indice);
    void setSalle(std::string room);

    //setters et getters
    bool getPresence()const;
    bool getPassage()const;
    int getX()const;
    int getY()const;
    int getIndice()const;
    std::string getRoom()const;

};

///ALLEGRO
void lancerToutAllegro(int largeur, int hauteur);
BITMAP *chargerImage(std::string nomFichierImage);
void plateau(BITMAP *page);

void initPlateau (CasePlato plateau [22][22]);

std::vector<Carte*> creationArme();
std::vector<Carte*> creationLieu();
std::vector<Carte*> creationSuspect();
std::vector<Carte*> melange(std::vector<Carte*>pioche);
std::vector<Carte*> setPioche(std::vector<Carte*>suspect,std::vector<Carte*>lieu,std::vector<Carte*>arme );
std::map<int, Carte*> mappage(std::vector<Carte*> myPioche);


#endif // CASEPLATEAU_H_INCLUDED
