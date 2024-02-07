#include "Cartes.h"
#include "User.h"
#include "CasePlateau.h"
#include "Suspect.h"
#include "Arme.h"
#include "Lieu.h"
#include <fstream>


void User::position(int color, int posx, int posy)
{
    setpion(color);
    setpionX(posx);
    setpionY(posy);
}
void User::creation()
{
    ///connexion joueur

    std::map<std::string, std::string> myMap;


   /// enregistrer elements du fichier "log_mdp.txt" dans la mini base
    std::ifstream fichierL("log_mdp.txt");
    if(fichierL)
    {
        std::string log;
        std::string pass;

        while(getline(fichierL, log))
        {
            getline(fichierL, pass);
            // inserer log et pass dans la map
            myMap.insert(std::pair<std::string, std::string>(log,pass));
        }
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    }

    int CouP=2;

    //variables pour la CONNEXION
    bool good;
    std::string loginSaisi;
    std::string mdpSaisi;
    std::map<std::string, std::string>::iterator itr;

    //variables pour l'INSCRIPTION
    std::string logSaisi;
    std::string passSaisi;

    do
    {
        std::cout <<" Veuillez chosir" << std::endl;
        std::cout << "1-Connexion    2-Inscription" << std::endl << "--> ";
        std::cin >> CouP;
    }
    while(CouP < 1 || CouP > 2 );

    ///CONNEXION
    if(CouP == 1)
    {
        do
        {
            std::cout << std::endl << "CONNEXION" << std::endl << std::endl;
            std::cout << "Login: ";
            std::cin >> loginSaisi;
            std::cout << "Password: ";
            std::cin >> mdpSaisi;
            good=false;

            for (itr = myMap.begin(); itr != myMap.end(); ++itr)
            {
                if(loginSaisi == itr->first)
                {
                    if(mdpSaisi == itr->second)
                    {
                        good=true;
                    }
                    else
                    {} //password incorrect
                }
                else
                {} //login incorrect
            }

            if(good == false)
            {
                std::cout << "Login ou Password incorrect" << std::endl;
            }
            else
            {
                std::cout << "Connexion reussie, bonjour " <<  loginSaisi << " !" << std::endl << std::endl;
                setLogin(loginSaisi);
                setMdp(mdpSaisi);
            }
        }
        while(good == false);
    }
    else
    {
        ///INSCRIPTION
        std::cout << std::endl << "INSCRIPTION" << std::endl << std::endl;
        std::cout << "Login: ";
        std::cin >> logSaisi;
        std::cout << "Password: ";
        std::cin >> passSaisi;

        myMap.insert(std::pair<std::string, std::string>(logSaisi,passSaisi));

        std::ofstream fichierE("log_mdp.txt", std::ios::app);

        if(fichierE)
        {
            fichierE << logSaisi << std::endl;
            fichierE << passSaisi << std::endl;
            std::cout << "Inscription reussie, bonjour " << logSaisi << " !" << std::endl  << std::endl;

        }
        else
        {
            std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
        }

        setLogin(logSaisi);
        setMdp(passSaisi);
    }



    setPartie(true);
    setVictoire(false);
}

///ALLEGRO
// Regroupe les initialisations d'allegro, mode graphique, clavier, souris
void lancerToutAllegro(int largeur, int hauteur)
{
    allegro_init();
    install_keyboard();
    install_mouse();
set_uformat(U_ASCII);

    /// OUVERTURE MODE GRAPHIQUE (ouverture fenêtre allegro)
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,largeur,hauteur,0,0)!=0)
    {
        allegro_message("probleme mode graphique : %s", allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen); // Affiche pointeur de souris en mode allegro
}

void plateau(BITMAP *page)
{
    BITMAP *plat;

    plat=load_bitmap("images/plateauHP.bmp",NULL);

    /// Assemblage de la scène sur le BUFFER (invisible pour l'instant)
    //  En posant le décor sur le buffer on écrase son ancien contenu
    blit(plat,page,0,0,0,0,SCREEN_W,SCREEN_H);

}

void initPlateau (CasePlato plateau [22][22])
{
    int i, j;

    ///salle de bain
    for(i=0; i<5; i++)
    {
        for(j=0; j<5; j++)
        {
            plateau[i][j].setSalle("salle de bain");
            plateau[i][j].setPassage(true);
            plateau[i][j].setIndice(1);
        }
    }
    ///grande salle
    for(i=7; i<15; i++)
    {
        for(j=0; j<6; j++)
        {
            plateau[i][j].setSalle("grande salle");
            plateau[i][j].setIndice(1);
        }
    }

    ///bibliothèque
    for(i=0; i<4; i++)
    {
        for(j=7; j<14; j++)
        {
            plateau[i][j].setSalle("bibliotheque");
            plateau[i][j].setIndice(1);
        }
    }
    for(i=4; i<7; i++)
    {
        for(j=8; j<14; j++)
        {
            plateau[i][j].setSalle("bibliotheque");
            plateau[i][j].setIndice(1);
        }
    }

    ///salle des potions
    for(i=0; i<6; i++)
    {
        for(j=17; j<22; j++)
        {
            plateau[i][j].setSalle("salle des potions");
            plateau[i][j].setPassage(true);
            plateau[i][j].setIndice(1);
        }
    }
    ///chambre des secrets
    for(i=8; i<14; i++)
    {
        for(j=16; j<22; j++)
        {
            plateau[i][j].setSalle("chambre des secrets");
            plateau[i][j].setIndice(1);
        }
    }
    ///tour d astronomie
    for(i=16; i<22; i++)
    {
        for(j=19; j<22; j++)
        {
            plateau[i][j].setSalle("tour d astronomie");
            plateau[i][j].setPassage(true);
            plateau[i][j].setIndice(1);
        }
    }
    ///salle sur demande
    for(i=17; i<22; i++)
    {
        for(j=12; j<17; j++)
        {
            plateau[i][j].setSalle("salle sur demande");
            plateau[i][j].setIndice(1);
        }
    }
    for(j=13; j<16; j++)
    {
        plateau[16][j].setSalle("bibliotheque");
        plateau[i][j].setIndice(1);
    }
    ///bureau dumbledore
    for(i=17; i<21; i++)
    {
        for(j=6; j<11; j++)
        {
            plateau[i][j].setSalle("bureau dumbledore");
            plateau[i][j].setIndice(1);
        }
    }
    ///serres
    for(i=17; i<22; i++)
    {
        for(j=0; j<3; j++)
        {
            plateau[i][j].setSalle("serres");
            plateau[i][j].setPassage(true);
            plateau[i][j].setIndice(1);
        }
    }
    for(i=17; i<22; i++)
    {
        plateau[i][3].setSalle("bibliotheque");
        plateau[i][j].setPassage(true);
        plateau[i][j].setIndice(1);
    }

}

///on met les cartes suspects, lieux et armes dans une seule pioche (un vector)
std::vector<Carte*> setPioche(std::vector<Carte*>suspect,std::vector<Carte*>lieu,std::vector<Carte*>arme)
{
    std::vector<Carte*> pioche;
    int size1,size2,size3;

    size1=suspect.size();
    size2=arme.size();
    size3=lieu.size();

    ///composition de la pioche :
    //5 cartes suspect
    for(int i=0; i<size1; i++)
    {
        pioche.push_back(suspect[i]);
    }
    //5 cartes arme
    for(int j=0; j<size2; j++)
    {
        pioche.push_back(arme[j]);
    }
    //8 cartes lieu
    for(int i=0; i<size3; i++)
    {
        pioche.push_back(lieu[i]);
    }

    return pioche;
}


std::map<int, Carte*> mappage(std::vector<Carte*> myPioche)
{
    std::map<int, Carte*> myHand; //int, Carte*

    ///composition de la pioche :
    for(unsigned long int i=0; i!=myPioche.size(); i++)
    {
        myHand.insert(std::pair<int, Carte*>(i,myPioche[i]));

    }

    return myHand;
}



std::vector<Carte*> creationArme()
{
    BITMAP *crochet;
    BITMAP *epee;
    BITMAP *avada;
    BITMAP *poison;
    BITMAP *collier;
    BITMAP *philtre;

    crochet=load_bitmap("images/cartes/armes/crochet.bmp",NULL);
    epee=load_bitmap("images/cartes/armes/epee.bmp",NULL);
    avada=load_bitmap("images/cartes/armes/avada.bmp",NULL);
    poison=load_bitmap("images/cartes/armes/poison.bmp",NULL);
    collier=load_bitmap("images/cartes/armes/collier.bmp",NULL);
    philtre=load_bitmap("images/cartes/armes/philtre.bmp",NULL);


    std::vector<Carte*> arme;
    Carte* CrochetBasilic;
    Carte* EpeeGryffondor;
    Carte* AvadaKedavra;
    Carte* Poison;
    Carte* CollierDopale;
    Carte* PhiltreMortVivant;

    CrochetBasilic = new Arme();
    EpeeGryffondor = new Arme();
    AvadaKedavra = new Arme();
    Poison = new Arme();
    CollierDopale = new Arme();
    PhiltreMortVivant = new Arme();

    //type et nom carte arme
    CrochetBasilic->setType();
    CrochetBasilic->setNom("crochet basilic");
    CrochetBasilic->setImage(crochet);

    EpeeGryffondor->setType();
    EpeeGryffondor->setNom("epee gryffondor");
    EpeeGryffondor->setImage(epee);

    AvadaKedavra->setType();
    AvadaKedavra->setNom("avada kedavra");
    AvadaKedavra->setImage(avada);

    Poison->setType();
    Poison->setNom("poison");
    Poison->setImage(poison);

    CollierDopale->setType();
    CollierDopale->setNom("collier d opale");
    CollierDopale->setImage(collier);

    PhiltreMortVivant->setType();
    PhiltreMortVivant->setNom("philtre mort vivant");
    PhiltreMortVivant->setImage(philtre);

    arme.push_back(CrochetBasilic);
    arme.push_back(EpeeGryffondor);
    arme.push_back(AvadaKedavra);
    arme.push_back(Poison);
    arme.push_back(CollierDopale);
    arme.push_back(PhiltreMortVivant);

    return arme;

}
std::vector<Carte*> creationSuspect()
{
    std::vector<Carte*> suspect;
    BITMAP *HP;
    BITMAP *HG;
    BITMAP *RW;
    BITMAP *GW;
    BITMAP *DM;
    BITMAP *LL;

    HP=load_bitmap("images/cartes/suspects/HP.bmp",NULL);
    HG=load_bitmap("images/cartes/suspects/HG.bmp",NULL);
    RW=load_bitmap("images/cartes/suspects/RW.bmp",NULL);
    GW=load_bitmap("images/cartes/suspects/GW.bmp",NULL);
    DM=load_bitmap("images/cartes/suspects/DM.bmp",NULL);
    LL=load_bitmap("images/cartes/suspects/LL.bmp",NULL);

    Carte* HarryPotter;
    Carte* HermioneGranger;
    Carte* RonWeasley;
    Carte* GinnyWeasley;
    Carte* DragoMalefoy;
    Carte* LunaLovegood;

    HarryPotter = new Suspect();
    HermioneGranger = new Suspect();
    RonWeasley = new Suspect();
    GinnyWeasley = new Suspect();
    DragoMalefoy = new Suspect();
    LunaLovegood = new Suspect();

    //type et nom carte suspect
    HarryPotter->setType();
    HarryPotter->setNom("harry potter");
    HarryPotter->setImage(HP);

    HermioneGranger->setType();
    HermioneGranger->setNom("hermione granger");
    HermioneGranger->setImage(HG);

    RonWeasley->setType();
    RonWeasley->setNom("ron weasley");
    RonWeasley->setImage(RW);

    GinnyWeasley->setType();
    GinnyWeasley->setNom("ginny weasley");
    GinnyWeasley->setImage(GW);

    DragoMalefoy->setType();
    DragoMalefoy->setNom("drago malefoy");
    DragoMalefoy->setImage(DM);

    LunaLovegood->setType();
    LunaLovegood->setNom("luna lovegood");
    LunaLovegood->setImage(LL);

    suspect.push_back(HarryPotter);
    suspect.push_back(HermioneGranger);
    suspect.push_back(GinnyWeasley);
    suspect.push_back(RonWeasley);
    suspect.push_back(LunaLovegood);
    suspect.push_back(DragoMalefoy);

    return suspect;


}

std::vector<Carte*> creationLieu()
{
    std::vector<Carte*>lieu;

    BITMAP *bain;
    BITMAP *grande;
    BITMAP *serres;
    BITMAP *dumbledore;
    BITMAP *demande;
    BITMAP *tour;
    BITMAP *chambre;
    BITMAP *potions;
    BITMAP *bibli;

    bain=load_bitmap("images/cartes/lieux/salledeBAIN.bmp",NULL);
    grande=load_bitmap("images/cartes/lieux/grandeSALLE.bmp",NULL);
    serres=load_bitmap("images/cartes/lieux/lesSERRES.bmp",NULL);
    dumbledore=load_bitmap("images/cartes/lieux/bureauDUMBLEDORE.bmp",NULL);
    demande=load_bitmap("images/cartes/lieux/sallesurDEMANDE.bmp",NULL);
    tour=load_bitmap("images/cartes/lieux/tourASTRONOMIE.bmp",NULL);
    chambre=load_bitmap("images/cartes/lieux/chambredesSECRETS.bmp",NULL);
    potions=load_bitmap("images/cartes/lieux/sallePOTIONS.bmp",NULL);
    bibli=load_bitmap("images/cartes/lieux/bibliotheque.bmp",NULL);

    Carte* sdb;
    Carte* gs;
    Carte* ls;
    Carte* bdd;
    Carte* ssd;
    Carte* ta;
    Carte* cds;
    Carte* sdp;
    Carte* biblio;

    sdb=new Lieu();
    gs=new Lieu();
    ls=new Lieu();
    bdd=new Lieu();
    ssd = new Lieu();
    ta =new Lieu();
    cds= new Lieu();
    sdp = new Lieu();
    biblio = new Lieu();

    //type t nom carte lieu
    sdb->setType();
    sdb->setNom("salle de bain");
    sdb->setImage(bain);

    gs->setType();
    gs->setNom("grande salle");
    gs->setImage(grande);

    ls->setType();
    ls->setNom("les serres");
    ls->setImage(serres);

    bdd->setType();
    bdd->setNom("bureau de dumbledore");
    bdd->setImage(dumbledore);

    ssd->setType();
    ssd->setNom("salle sur demande");
    ssd->setImage(demande);

    ta->setType();
    ta->setNom("tour d astronomie");
    ta->setImage(tour);

    cds->setType();
    cds->setNom("chambre des secrets");
    cds->setImage(chambre);

    sdp->setType();
    sdp->setNom("salle de classe des potions");
    sdp->setImage(potions);

    biblio->setType();
    biblio->setNom("bibliotheque");
    biblio->setImage(bibli);

    lieu.push_back(sdb);
    lieu.push_back(gs);
    lieu.push_back(ls);
    lieu.push_back(bdd);
    lieu.push_back(ta);
    lieu.push_back(cds);
    lieu.push_back(sdp);
    lieu.push_back(ssd);
    lieu.push_back(biblio);


    return lieu;
}

std::vector<Carte*> melange(std::vector<Carte*>pioche)
{

    Carte* tmp;
    int n=pioche.size();
    int j;

    for(int i=0; i<n; i++)
    {
        j=(rand()%(n+1));
        tmp= pioche[j];
        pioche[j]=pioche[i];
        pioche[i]=tmp;
    }
    return pioche;

}
