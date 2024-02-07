#ifndef DE_H_INCLUDED
#define DE_H_INCLUDED
#include <string>
#include <vector>
#include <allegro.h>
#include <iostream>
#include <map>


class De
{
private :
    int m_valeur;

public :
    //ctor & dtor
    De();
    De(int _valeur);
    ~De();
    //setters et getters
    void setValeur(int valeur);
    int getValeur()const;

    //méthodes
    void lancerDe();
    void affichageDE(BITMAP *page, int k);
};

#endif // DE_H_INCLUDED
