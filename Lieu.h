#ifndef LIEU_H_INCLUDED
#define LIEU_H_INCLUDED
#include <iostream>
#include <allegro.h>


class Lieu : public Carte
{
    public :
    Lieu();
    ~Lieu();

    void setType();
    void setNom(std::string _name);
    void setImage(BITMAP* image);

};


#endif // LIEU_H_INCLUDED
