#include <allegro.h>
#include "Cartes.h"
#include "User.h"
#include "CasePlateau.h"
#include "Suspect.h"
#include "Arme.h"
#include "Lieu.h"
#include "de.h"
#include <thread>
#include <chrono>
#include <fstream>
#include "Save.h"
#include "Menu.h"


void Save::save1(int nbj, std::vector<User> joueurs)
{
    std::ofstream fichierSave;
    fichierSave.open(getnomF(), std::ofstream::out | std::ofstream::trunc);

    if(fichierSave)
    {
        //nb joueurs
        fichierSave << nbj << std::endl;

        for(int k=0; k<nbj; k++)
        {
            fichierSave << joueurs[k].getLogin()<< std::endl;
            fichierSave << joueurs[k].getMdp()<< std::endl;
            //fichierSave << joueurs[k].getLevel()<< std::endl;
            fichierSave <<  joueurs[k].getpionX()<< std::endl;
            fichierSave <<  joueurs[k].getpionY()<< std::endl;
            for(unsigned long int h=0; h<joueurs[k].getHand().size(); h++)
            {
                fichierSave << joueurs[k].getHand()[h]<< std::endl;
            }
        }
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

    fichierSave.close();

}



void Save::save0(int n,int n1,int n2)
{
    std::ofstream fichierEnv;
    fichierEnv.open(getnomF(), std::ofstream::out | std::ofstream::trunc);

    if(fichierEnv)
    {
        fichierEnv << n << std::endl;
        fichierEnv << n1 << std::endl;
        fichierEnv << n2 << std::endl;
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

    fichierEnv.close();

}



void Save::load0(std::vector<Carte*>& enveloppe,std::vector<Carte*>& arme,std::vector<Carte*>& lieu,std::vector<Carte*>& suspect)
{
    int nFich, n1Fich, n2Fich, n,n1,n2;

    std::ifstream fichierEnv(getnomF(), std::ios::in);
    if(fichierEnv)
    {
        fichierEnv >> nFich;
        n=nFich;
        fichierEnv >> n1Fich;
        n1=n1Fich;
        fichierEnv >> n2Fich;
        n2=n2Fich;
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    }

    enveloppe.push_back(suspect[n]);
    enveloppe.push_back(arme[n1]);
    enveloppe.push_back(lieu[n2]);

    //on efface les cartes retirées de chaque paquet de cartes
    suspect.erase(suspect.begin()+n);
    arme.erase(arme.begin()+n1);
    lieu.erase(lieu.begin()+n2);
    ///reponse enigme a enlever
    std::cout<<"SUSPECT : "<<enveloppe[0]->getNom()<<std::endl;
    std::cout<<"ARME : "<<enveloppe[1]->getNom()<<std::endl;
    std::cout<<"LIEU : "<<enveloppe[2]->getNom()<<std::endl;

}

void Save::load(int& choixF, std::vector<User>& joueurs)
{
    int rouge,vert,bleu,orange,rose,cyan;
    //couleurs
    rouge=makecol(255,22,22);
    vert=makecol(126,217,87);
    bleu=makecol(0,115,221);
    orange=makecol(255,145,77);
    rose=makecol(255,102,196);
    cyan=makecol(23,229,235);

    User joueur;
    std::vector<int> myMain1,myMain2,myMain3,myMain4,myMain5,myMain6;
    int choiceFich,x1,x2,x3,x4,x5,x6,y1,y2,y3,y4,y5,y6,numCarte;
    std::string logFich, passFich,env0;
    //?levFich?


    std::ifstream fichierSaveL(getnomF(), std::ios::in);

    if(fichierSaveL)
    {
        fichierSaveL >> choiceFich;
        choixF=choiceFich;
        getline(fichierSaveL, env0);

        switch (choixF)
        {
        case 2 :
            for(int i=0 ; i<2; i++)
            {
                getline(fichierSaveL, logFich);
                joueur.setLogin(logFich);
                getline(fichierSaveL, passFich);
                joueur.setMdp(passFich);
                //getline(fichierSaveL, levFich);
                //joueur.setLevel(levFich);
                if(i==0)
                {
                    fichierSaveL >> x1;
                    fichierSaveL >> y1;
                    joueur.setpionX(x1);
                    joueur.setpionY(y1);
                    joueur.setpion(rouge);
                    for (int h= 0; h<9; h++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain1.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain1);
                }

                if(i==1)
                {
                    fichierSaveL >> x2;
                    fichierSaveL >> y2;
                    joueur.setpionX(x2);
                    joueur.setpionY(y2);
                    joueur.setpion(bleu);

                    for (int j=0; j<9; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain2.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain2);
                }
                //on l'ajoute à notre conteneurs de joueurs
                joueurs.push_back(joueur);
            }
            break;
        case  3:
            for(int i=0 ; i<3; i++)
            {
                getline(fichierSaveL, logFich);
                joueur.setLogin(logFich);
                getline(fichierSaveL, passFich);
                joueur.setMdp(passFich);
                //getline(fichierSaveL, levFich);
                //joueur.setLevel(levFich);
                if(i==0)
                {
                    fichierSaveL >> x1;
                    fichierSaveL >> y1;
                    joueur.setpionX(x1);
                    joueur.setpionY(y1);
                    joueur.setpion(rouge);
                    for (int h= 0; h<6; h++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain1.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain1);
                }

                if(i==1)
                {
                    fichierSaveL >> x2;
                    fichierSaveL >> y2;
                    joueur.setpionX(x2);
                    joueur.setpionY(y2);
                    joueur.setpion(bleu);

                    for (int j=0; j<6; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain2.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain2);
                }
                if(i==2)
                {
                    fichierSaveL >> x3;
                    fichierSaveL >> y3;
                    joueur.setpionX(x3);
                    joueur.setpionY(y3);
                    joueur.setpion(vert);

                    for (int j=0; j<6; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain3.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain3);
                }
                //on l'ajoute à notre conteneurs de joueurs
                joueurs.push_back(joueur);
            }
        case 4 :
            for(int i=0 ; i<4; i++)
            {
                getline(fichierSaveL, logFich);
                joueur.setLogin(logFich);
                getline(fichierSaveL, passFich);
                joueur.setMdp(passFich);
                //getline(fichierSaveL, levFich);
                //joueur.setLevel(levFich);
                if(i==0)
                {
                    fichierSaveL >> x1;
                    fichierSaveL >> y1;
                    joueur.setpionX(x1);
                    joueur.setpionY(y1);
                    joueur.setpion(rouge);
                    for (int h= 0; h<4; h++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain1.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain1);
                }

                if(i==1)
                {
                    fichierSaveL >> x2;
                    fichierSaveL >> y2;
                    joueur.setpionX(x2);
                    joueur.setpionY(y2);
                    joueur.setpion(bleu);

                    for (int j=0; j<4; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain2.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain2);
                }
                if(i==2)
                {
                    fichierSaveL >> x3;
                    fichierSaveL >> y3;
                    joueur.setpionX(x3);
                    joueur.setpionY(y3);
                    joueur.setpion(vert);

                    for (int j=0; j<5; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain3.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain3);
                }
                if(i==3)
                {
                    fichierSaveL >> x4;
                    fichierSaveL >> y4;
                    joueur.setpionX(x4);
                    joueur.setpionY(y4);
                    joueur.setpion(rose);

                    for (int j=0; j<5; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain4.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain4);
                }
                //on l'ajoute à notre conteneurs de joueurs
                joueurs.push_back(joueur);
            }
        case 5 :
            for(int i=0 ; i<5; i++)
            {
                getline(fichierSaveL, logFich);
                joueur.setLogin(logFich);
                getline(fichierSaveL, passFich);
                joueur.setMdp(passFich);
                //getline(fichierSaveL, levFich);
                //joueur.setLevel(levFich);
                if(i==0)
                {
                    fichierSaveL >> x1;
                    fichierSaveL >> y1;
                    joueur.setpionX(x1);
                    joueur.setpionY(y1);
                    joueur.setpion(rouge);
                    for (int h= 0; h<3; h++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain1.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain1);
                }

                if(i==1)
                {
                    fichierSaveL >> x2;
                    fichierSaveL >> y2;
                    joueur.setpionX(x2);
                    joueur.setpionY(y2);
                    joueur.setpion(bleu);

                    for (int j=0; j<3; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain2.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain2);
                }
                if(i==2)
                {
                    fichierSaveL >> x3;
                    fichierSaveL >> y3;
                    joueur.setpionX(x3);
                    joueur.setpionY(y3);
                    joueur.setpion(vert);

                    for (int j=0; j<4; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain3.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain3);
                }
                if(i==3)
                {
                    fichierSaveL >> x4;
                    fichierSaveL >> y4;
                    joueur.setpionX(x4);
                    joueur.setpionY(y4);
                    joueur.setpion(rose);

                    for (int j=0; j<4; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain4.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain4);
                }
                if(i==4)
                {
                    fichierSaveL >> x5;
                    fichierSaveL >> y5;
                    joueur.setpionX(x5);
                    joueur.setpionY(y5);
                    joueur.setpion(cyan);

                    for (int j=0; j<4; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain5.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain5);
                }
                //on l'ajoute à notre conteneurs de joueurs
                joueurs.push_back(joueur);
            }
        case 6 :
            for(int i=0 ; i<6; i++)
            {
                getline(fichierSaveL, logFich);
                joueur.setLogin(logFich);
                getline(fichierSaveL, passFich);
                joueur.setMdp(passFich);
                //getline(fichierSaveL, levFich);
                //joueur.setLevel(levFich);
                if(i==0)
                {
                    fichierSaveL >> x1;
                    fichierSaveL >> y1;
                    joueur.setpionX(x1);
                    joueur.setpionY(y1);
                    joueur.setpion(rouge);
                    for (int h= 0; h<3; h++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain1.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain1);
                }

                if(i==1)
                {
                    fichierSaveL >> x2;
                    fichierSaveL >> y2;
                    joueur.setpionX(x2);
                    joueur.setpionY(y2);
                    joueur.setpion(bleu);

                    for (int j=0; j<3; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain2.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain2);
                }
                if(i==2)
                {
                    fichierSaveL >> x3;
                    fichierSaveL >> y3;
                    joueur.setpionX(x3);
                    joueur.setpionY(y3);
                    joueur.setpion(vert);

                    for (int j=0; j<3; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain3.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain3);
                }
                if(i==3)
                {
                    fichierSaveL >> x4;
                    fichierSaveL >> y4;
                    joueur.setpionX(x4);
                    joueur.setpionY(y4);
                    joueur.setpion(rose);

                    for (int j=0; j<3; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain4.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain4);
                }
                if(i==4)
                {
                    fichierSaveL >> x5;
                    fichierSaveL >> y5;
                    joueur.setpionX(x5);
                    joueur.setpionY(y5);
                    joueur.setpion(cyan);

                    for (int j=0; j<3; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain5.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain5);
                }
                if(i==5)
                {
                    fichierSaveL >> x6;
                    fichierSaveL >> y6;
                    joueur.setpionX(x6);
                    joueur.setpionY(y6);
                    joueur.setpion(orange);

                    for (int j=0; j<3; j++)
                    {
                        fichierSaveL >> numCarte;
                        getline(fichierSaveL, env0);
                        myMain6.push_back(numCarte);
                    }
                    //joueur.setPartie(true);
                    //joueur.setVictoire(false);
                    joueur.setHand(myMain6);
                }
                //on l'ajoute à notre conteneurs de joueurs
                joueurs.push_back(joueur);
            }

        default :
            break;
        }
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    }
}
