#ifndef SAVE_H_INCLUDED
#define SAVE_H_INCLUDED
#include <string>
#include <vector>
#include <allegro.h>
#include <iostream>
#include <map>
#include <fstream>
#include "Menu.h"

class Save
{
private :
    std::string m_nomFichier;

public :
    //ctor & dtor
    Save();
    Save(std::string _nomFichier);
    ~Save();
    //setters et getters
    void setnomF(std::string nomFichier);
    std::string getnomF()const;

    //méthodes
    void save1(int nbj, std::vector<User> joueurs);
    void save0(int n, int n1,int n2);
    void load0(std::vector<Carte*>& enveloppe,std::vector<Carte*>& arme,std::vector<Carte*>& lieu,std::vector<Carte*>& suspect);
    void load(int& choixF, std::vector<User>& joueurs);

};

#endif // SAVE_H_INCLUDED
