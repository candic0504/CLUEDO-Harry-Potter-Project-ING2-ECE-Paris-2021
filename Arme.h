#ifndef ARME_H_INCLUDED
#define ARME_H_INCLUDED
#include <iostream>
#include <allegro.h>

class Arme : public Carte
{
public :
    Arme();
    ~Arme();

    void setType();
    void setNom(std::string _name);
    void setImage(BITMAP* image);
};

#endif // ARME_H_INCLUDED
