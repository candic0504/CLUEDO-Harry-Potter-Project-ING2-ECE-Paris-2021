#ifndef SUSPECT_H_INCLUDED
#define SUSPECT_H_INCLUDED
#include <iostream>
#include <allegro.h>

class Suspect : public Carte
{
public :
    Suspect();
    ~Suspect();

    void setType();
    void setNom(std::string _name);
    void setImage(BITMAP* image);
};

#endif // SUSPECT_H_INCLUDED
