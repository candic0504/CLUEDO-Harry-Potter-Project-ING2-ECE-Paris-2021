#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <string>
#include <vector>
#include <allegro.h>
#include <iostream>
#include <map>
#include <fstream>


class Menu
{
private :
    int m_choix;

public :
    //ctor & dtor
    Menu();
    Menu(int _choix);
    ~Menu();
    //setters et getters
    void setchoix(int choix);
    int getchoix()const;

    //méthodes
    void menuPrincipal();
    void menuLancerPartie(bool saveOrNot);
    bool menuHorsalle(BITMAP* page, BITMAP* plat,bool& victoire, std::vector<Carte*> &solution, std::vector<User> &joueurs, int perso, int nbJoueur,std::map<int, Carte*> myMap, int& fin);
    bool menuSallePS(int& fin, BITMAP* page, BITMAP* plat,bool& victoire, std::vector<Carte*> &solution, std::vector<User> &joueurs, int perso, int nbJoueur,std::map<int, Carte*> myMap, int salle);
    bool menuSalle(int& fin, BITMAP* page, BITMAP* plat,bool& victoire, std::vector<Carte*> &solution, std::vector<User> &joueurs, int perso, int nbJoueur,std::map<int, Carte*> myMap, int salle);
    void menuTour(int nbJoueur, std::vector<User> joueurs, std::vector<Carte*>enveloppe,std::map<int, Carte*> myMap);


};


#endif // MENU_H_INCLUDED
