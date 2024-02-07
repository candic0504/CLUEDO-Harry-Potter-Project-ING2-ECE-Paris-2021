#ifndef CARTES_H_INCLUDED
#define CARTES_H_INCLUDED
#include <string>
#include <allegro.h>

class Carte
{
protected :
    std::string m_type;
    std::string m_nom;
    BITMAP* m_image;
public :
    Carte();
    virtual ~Carte();
    std::string getType()const;
    std::string getNom() const;
    BITMAP* getImage()const;

    virtual void setType() =0;
    virtual void setNom(std::string _name) = 0;
    virtual void setImage(BITMAP* image) = 0;

};

#endif // CARTES_H_INCLUDED
