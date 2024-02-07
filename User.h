#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include <string>
#include <vector>
#include <allegro.h>
#include <iostream>
#include "Cartes.h"
#include <map>


class User
{
private :
    std::string m_login;
    std::string m_mdp;
    std::string m_level;
    std::vector <int> m_hand;
    int m_nbVictoire=0;
    int m_nbPartie=0;
    ///rajout
    int m_pion;
    int m_pionX;
    int m_pionY;
    bool m_elimine;

public :
    //ctor & dtor
    User();
    User(std::string log, std::string mdp, std::string level, int m_pion, int pionX, int pionY,bool elimine);
    ~User();
    //setters et getters
    void setLogin(std::string log);
    void setMdp(std::string mdp);
    void setLevel();
    void setHand(std::vector<int> hand);
    void setVictoire(bool victoire);
    void setPartie(bool first);
    void setpion(int pion);
    void setpionX(int pionX);
    void setpionY(int pionY);
    void setElimination(bool elimin);

    std::string getLogin()const;
    std::string getMdp()const;
    std::string getLevel()const;
    std::vector<int> getHand()const;
    int getVictoire()const;
    int getPartie()const;
    int getpion()const;
    int getpionX()const;
    int getpionY()const;
    bool getElimination()const;

    //méthodes
    void deplacement(int iJ, int njoueurs, std::vector<User> players);
    void creation();
    void position(int color, int posx, int posy);

    void hypothese(std::string&suspect, std::string&arme, BITMAP *page);
    void accusation(std::string& suspect, std::string& arme, std::string& lieu, BITMAP *page);
    bool verification(std::string suspect, std::string lieu, std::string arme, std::vector<Carte*>enveloppe);
    void affichageCartes(std::map<int, Carte*> myMap, BITMAP* page);
    void verifHypo(std::string lieu, std::string arme, std::string suspect, std::vector<User>player, std::map<int, Carte*> cartes, BITMAP* page, unsigned long int joueur);
    bool posverif(std::string keyPres, int iJ, int nbjoueurs, std::vector<User>& players); ///A MODIFIER - BUG
    int salleVerif();
    int caseMverif();
};

//classe save + allegro + plateau + pioche(ou + de methodes dans cartes)  + classe menu + classe musique

#endif // USER_H_INCLUDED
