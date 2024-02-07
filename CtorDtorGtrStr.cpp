#include "Cartes.h"
#include "User.h"
#include "CasePlateau.h"
#include "Suspect.h"
#include "Arme.h"
#include "Lieu.h"
#include "de.h"
#include "Save.h"
#include "Menu.h"

/// class User
User::User () : m_login(" "), m_mdp(" "), m_level(" "), m_hand(0), m_nbPartie(0), m_nbVictoire(0), m_pion(0), m_pionX(0), m_pionY(0), m_elimine(0) {}

User::User(std::string log, std::string mdp, std::string level, int pion, int pionX, int pionY, bool elimine)
    :m_login(log), m_mdp(mdp), m_level(level), m_pion(pion), m_pionX(pionX), m_pionY(pionY) , m_elimine(elimine){}

User::~User()
{
    int taille=m_hand.size();

    for(int i=0;i<taille;i++)
    {
        m_hand.clear();
    }
}

///setters et getters

void User::setLogin(std::string login)
{
    m_login=login;
}
void User::setMdp(std::string mdp)
{
    m_mdp=mdp;
}
//nouveau

void User::setVictoire(bool victoire)
{
    //si le joueur à gagné
    if(victoire == true)
    {
        m_nbVictoire=m_nbVictoire+1;
    }
    //si non le nb de victoire reste inchangé
    else
    {
        m_nbVictoire=0+m_nbVictoire;
    }

}
void User::setPartie(bool first)
{
    //si c'est la premiere partie du joueur
    if(first == true)
    {
        m_nbPartie=0;
    }
    //si non on incrémente le nombre de partie
    else
    {
        m_nbPartie++;
    }
}
//nouveau
void User::setLevel()
{
    //le joueur vient de se créer un compte
    if (getPartie() == 0)
    {
        m_level=" debutant";
    }
    //le joueur à fait au moins 1 partie
    else if (getPartie()>0)
    {
        //il a remporté au maximum 2 parties
        if(getVictoire()==0 && getVictoire() <=2)
        {
            m_level="amateur/trice";
        }
        //il a joué à 5 parties ou + et remporté au moins 3 parties
        else if (getPartie()>=5 && getPartie()<10 && getVictoire()>=3)
        {
            m_level="intermediaire";
        }
        //il a joué à 10 parties ou + et remporté 6 parties ou plus
        else if (getPartie()>=10 && getVictoire()>=6)
        {
            m_level="expert";
        }
    }

}

void User::setpion(int pion)
{
    m_pion=pion;
}

void User::setpionX(int pionX)
{
    //if(pionX < ...) etc
    m_pionX = pionX;
}

void User::setpionY(int pionY)
{
    //if(pionY < ...) etc
    m_pionY = pionY;
}

void User::setElimination(bool elimine)
{
    m_elimine=elimine;
}


std::string User::getLogin()const
{
    return m_login;
}
std::string User::getMdp()const
{
    return m_mdp;
}
std::string User::getLevel()const
{
    return m_level;
}

int User::getVictoire()const
{
    return m_nbVictoire;
}
int User::getPartie()const
{
    return m_nbPartie;
}

int User::getpion()const
{
    return m_pion;
}


int User::getpionX()const
{
    return m_pionX;
}

int User::getpionY()const
{
    return m_pionY;
}

std::vector<int> User::getHand()const
{
    return m_hand;
}

bool User::getElimination()const
{
    return m_elimine;
}

void User::setHand(std::vector<int> hand)
{
    m_hand = hand;
}



///case plateau

CasePlato::CasePlato() : m_presence(), m_posx(0), m_posy(0),m_passageSecret(false),m_indice(0){}

CasePlato::~CasePlato(){}

void CasePlato::setPresence(bool body)
{
    m_presence=body;
}
void CasePlato::setX(int posx)
{
    m_posx=posx;
}
void CasePlato::setY(int posy)
{
    m_posy=posy;
}
void CasePlato::setIndice(int indice)
{
    m_indice=indice;
}
void CasePlato::setSalle(std::string room)
{
    m_salle=room;
}
void CasePlato::setPassage(bool secret)
{
    m_passageSecret=secret;
}

bool CasePlato::getPresence()const
{
    return m_presence;
}
int CasePlato::getX()const
{
    return m_posx;
}
int CasePlato::getY()const
{
    return m_posy;
}

int CasePlato::getIndice()const
{
    return m_indice;
}
std::string CasePlato::getRoom()const
{
    return m_salle;
}
bool CasePlato::getPassage()const
{
    return m_passageSecret;
}


///classe abstraite Carte et ses classes fille suspect, arme, lieu
Carte::Carte() {}
Carte::~Carte() {
}
Suspect::Suspect(): Carte() {}
Lieu::Lieu() : Carte() {}
Arme::Arme():Carte() {}
Suspect::~Suspect()
{
destroy_bitmap(m_image);
}
Lieu::~Lieu()
{
destroy_bitmap(m_image);
}
Arme::~Arme()
{
destroy_bitmap(m_image);
}

//getter & setter
std::string Carte::getType()const
{
    return m_type;
}

std::string Carte::getNom() const
{
    return m_nom;
}
BITMAP* Carte::getImage()const
{
    return m_image;
}

void Suspect::setType()
{
    m_type="Suspect";
    //std::cout<<"TYPE :  "<<m_type<<std::endl;
}

void Suspect::setNom(std::string _name)
{
    m_nom=_name;
    //std::cout << "NOM :  " <<m_nom<<std::endl;
}
void Suspect::setImage(BITMAP* image)
{
    m_image=image;
}
void Lieu::setType()
{
    m_type="Lieu";
    //std::cout<<"TYPE :  "<<m_type<<std::endl;
}

void Lieu::setNom(std::string _name)
{
    m_nom=_name;
    //std::cout << "NOM :  " <<m_nom<<std::endl;
}
void Lieu::setImage(BITMAP* image)
{
    m_image=image;
}
void Arme::setType()
{
    m_type="Arme";
    //std::cout<<"TYPE :  "<<m_type<<std::endl;
}

void Arme::setNom(std::string _name)
{
    m_nom=_name;
    //std::cout << "NOM :  " <<m_nom<<std::endl;
}
void Arme::setImage(BITMAP* image)
{
    m_image=image;
}


//DE
De::De() : m_valeur(0){}
De::De(int _valeur) : m_valeur(_valeur){}

De::~De() {}


void De::setValeur(int valeur)
{
    m_valeur=valeur;
}

int De::getValeur()const
{
    return m_valeur;
}


//SAVE
Save::Save() : m_nomFichier(""){}
Save::Save(std::string _nomFichier) : m_nomFichier(_nomFichier){}

Save::~Save() {}


void Save::setnomF(std::string nomFichier)
{
    m_nomFichier=nomFichier;
}

std::string Save::getnomF()const
{
    return m_nomFichier;
}


//MENIU
Menu::Menu() : m_choix(0){}
Menu::Menu(int _choix) : m_choix(_choix){}

Menu::~Menu() {}


void Menu::setchoix(int choix)
{
    m_choix=choix;
}

int Menu::getchoix()const
{
    return m_choix;
}
