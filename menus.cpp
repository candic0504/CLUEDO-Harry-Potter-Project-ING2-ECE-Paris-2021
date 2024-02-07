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

void Menu::menuPrincipal()
{
    int choix;
    Menu menuLP;

    BITMAP* aide;
    aide=load_bitmap("images/rules.bmp",NULL);

    // Page pour l'assemblage de la scène (invisible)
    BITMAP *page;
    // CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran
    page=create_bitmap(1200,650);

    do
    {
       do
    {
        std::cout << "Bienvenue a Poudlard " << std::endl << std::endl;
        std::cout << "Que voulez vous faire ? " << std::endl;
        std::cout << " 1 : Lancer une nouvelle partie " << std::endl;
        std::cout << " 2 : Reprendre une partie " << std::endl;
        std::cout << " 3 : Regles du jeu " << std::endl;
        std::cout << " 5 : Quitter " << std::endl;
        std::cin >> choix;
        setchoix(choix);

        if(getchoix()!=1 && getchoix() != 2 && getchoix() != 3 && getchoix() != 4 && getchoix()!=5)
        {
            std::cout<<"Erreur: " << std::endl;
        }
    }
    while(getchoix()!=1 && getchoix() != 2 && getchoix() != 3 && getchoix() != 4 && getchoix()!=5);

    switch(getchoix())
    {
    case 1 :
        menuLP.menuLancerPartie(false);
        break;
    case 2 :
        menuLP.menuLancerPartie(true);
        break;
    case 3 :
        //on affiche les regles sur jeu tant qu'on appuie pas sur espace
        while(!key[KEY_SPACE])
        {
            blit(aide,page,0,0,0,0,1200,650);
            blit(page,screen,0,0,0,0,1200,650);
        }
        break;
    case 4 :
        while(!key[KEY_SPACE])
        {

        }
        break;
    case 5:
        break;
    default :
        std::cout<<"Erreur: " << std::endl;
        break;
    }
    }while(choix!=5);

    destroy_bitmap(aide);
}

void Menu::menuTour(int nbJoueur, std::vector<User> joueurs, std::vector<Carte*>enveloppe,std::map<int, Carte*> myMap)
{
    // Chargement musique de jeu
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    SAMPLE *musique;
    musique = load_sample("music.wav");
    play_sample(musique, 200, 128,1000, 0);

    SAMPLE *vic;
    vic= load_sample("victoire.wav");

    // Page pour l'assemblage de la scène (invisible)
    BITMAP *page;

    BITMAP *plat;
    BITMAP *accueil;
    BITMAP *bouton;
    BITMAP *accuser;
    BITMAP *victoiry;
    BITMAP *menu3;
    BITMAP *menu4;
    BITMAP *menu5;
    BITMAP *elimination;
    BITMAP *textFond1;
    BITMAP *textFond2;

    Save SavePartie("save.txt");


    //Tableau de couleurs
    int rouge=makecol(255,22,22);
    int vert=makecol(126,217,87);
    int bleu=makecol(0,115,221);
    int orange=makecol(255,145,77);
    int rose=makecol(255,102,196);
    int cyan=makecol(23,229,235);
    int tabColor[6];
    tabColor[0]=rouge;
    tabColor[1]=bleu;
    tabColor[2]=vert;
    tabColor[3]=rose;
    tabColor[4]=cyan;
    tabColor[5]=orange;

    // CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran
    page=create_bitmap(1200,650);

    plat=load_bitmap("images/plateauHP.bmp",NULL);
    bouton=load_bitmap("images/bouton.bmp",NULL);
    accuser=load_bitmap("images/accuser.bmp",NULL);
    victoiry=load_bitmap("images/victoire.bmp",NULL);
    accueil=load_bitmap("images/accueil.bmp",NULL);
    menu3=load_bitmap("images/menu3.bmp",NULL);
    menu4=load_bitmap("images/menu4.bmp",NULL);
    menu5=load_bitmap("images/menu5.bmp",NULL);
    elimination=load_bitmap("images/elimine.bmp",NULL);
    textFond1=load_bitmap("images/textFond1.bmp",NULL);
    textFond2=load_bitmap("images/textFond2.bmp",NULL);

    Menu menuHS, menuSPS, menuS;


    bool suite =false;

    ///affichage de l'image d'accueil
    while(suite!=true)
    {
        blit(accueil,page,0,0,0,0,1200,650);
        blit(page,screen,0,0,0,0,1200,650);
        if(mouse_b && mouse_x>=900 && mouse_x<=1090 && mouse_y>=350 && mouse_y<=800)
        {
            suite = true;
        }
    }
    bool victoire = false,fin=false;
    int salle=0;
    int b=0;
    std::string suspect, arme,lieu;

    //tant que la partie n'est pas gagné
    do
    {
        for(int i=0; i<nbJoueur ; i++)
        {
            if (joueurs[i].getElimination()==true) ///lorsque c'est le tour d'un joueur eliminé on affiche juste une image
            {
                rest(500);
                blit(elimination,page,0,0,0,0,1200,650);
                blit(page,screen,0,0,0,0,1200,650);
                rest(2000);
            }
            else ///pour chaque joueur qui n'est pas eliminé
            {
                b=0;
                stretch_blit(textFond1,plat,0,0,250,145, 0, 0,250,145);
                stretch_blit(textFond2,plat,0,0,197,27, 1004, 19,197,27);
                textprintf_ex(plat,font,30,15,tabColor[i],-1,"JEU DE %s :", joueurs[i].getLogin().c_str());
                ///on affiche le pseudo du joueur ainsi que son pion
                textprintf_ex(plat,font,1015,32,tabColor[i],-1," %s", joueurs[i].getLogin().c_str());
                blit(plat,page,0,0,0,0,1200,650);
                blit(page,screen,0,0,0,0,1200,650);

                //à chaque tour on regarde ou se situe le pion du joueur sur le plateau
                salle=joueurs[i].salleVerif();

                while(b!=1 && victoire!=true) //tant que la partie n'est pas gagnée et terminée
                {

                        if(key[KEY_SPACE])
{
    victoire =true;
    fin=true;

}
                        for(unsigned long int j=0; j<joueurs[i].getHand().size(); j++)
                        {
                            if(j>=4)
                            {

                                stretch_blit(myMap[joueurs[i].getHand()[j]]->getImage(),plat,0,0,59,88,10+(59*(j-4)),130,59,88);//on affichage la carte
                            }
                            else
                            {
                                stretch_blit(myMap[joueurs[i].getHand()[j]]->getImage(),plat,0,0,59,88,10+59*j,40,59,88);
                            }
                    }
                    if(salle == 0)    ///le joueur n'est pas dans une salle au début de son tour
                    {
                        draw_sprite(plat,menu3,945,200);
                        blit(page,screen,0,0,0,0,1200,650);
                        blit(plat,page,0,0,0,0,1200,650);
                        //affichage des pions des joueurs
                        for(int j=0; j<nbJoueur ; j++)
                        {
                            circlefill(page,((joueurs[j].getpionX()-1)*31.4)+270, ((joueurs[j].getpionY()-1)*27)+42, 10, joueurs[j].getpion());
                        }
                        blit(page,screen,0,0,0,0,1200,650);
                        fin=menuHS.menuHorsalle(page,plat,victoire,enveloppe,joueurs,i,nbJoueur, myMap, b);
                    }
                    else if(salle == 2 || salle == 3 || salle ==7|| salle ==9)  ///le joueur est dans une salle avec un PS au début de son tour
                    {
                        draw_sprite(plat,menu5,945,200);
                        blit(page,screen,0,0,0,0,1200,650);
                        blit(plat,page,0,0,0,0,1200,650);
                        for(int j=0; j<nbJoueur ; j++)
                        {
                            circlefill(page,((joueurs[j].getpionX()-1)*31.4)+270, ((joueurs[j].getpionY()-1)*27)+42, 10, joueurs[j].getpion());
                        }
                        blit(page,screen,0,0,0,0,1200,650);
                        fin=menuSPS.menuSallePS(b,page,plat,victoire,enveloppe,joueurs,i,nbJoueur,myMap,salle);
                    }
                    else   ///le joueur est dans une salle qui n'a pas de Passage Secret
                    {
                        draw_sprite(plat,menu4,945,200);
                        blit(page,screen,0,0,0,0,1200,650);
                        blit(plat,page,0,0,0,0,1200,650);
                        for(int j=0; j<nbJoueur ; j++)
                        {
                            circlefill(page,((joueurs[j].getpionX()-1)*31.4)+270, ((joueurs[j].getpionY()-1)*27)+42, 10, joueurs[j].getpion());
                        }
                        blit(page,screen,0,0,0,0,1200,650);
                        fin=menuS.menuSalle(b,page,plat,victoire,enveloppe,joueurs,i,nbJoueur,myMap,salle);
                    }
                }

                SavePartie.save1(nbJoueur, joueurs); //on sauvegarde le jeu
            }

            if(joueurs[i].getVictoire()==true)
            {
                victoire=true;
            }
        }
    }
    while(victoire != true && fin != true);
    ///si un joueur gagne affichage d'écran de victoire et musique de victoire
    if(victoire == true)
    {
        stop_sample(musique);
        play_sample(vic, 200, 128,1000, 0);
        blit(victoiry,page,0,0,0,0,1200,650);
        blit(page,screen,0,0,0,0,1200,650);
        rest(14005);
        fin=true;
    }

    if(victoire != true || fin!= true)
    {
        destroy_bitmap(page);
        destroy_bitmap(plat);
        destroy_bitmap(accuser);
        destroy_bitmap(bouton);
        destroy_bitmap(victoiry);
        destroy_bitmap(accueil);
        destroy_bitmap(menu3);
        destroy_bitmap(menu4);
        destroy_bitmap(menu5);
    }
}

void Menu::menuLancerPartie(bool saveOrNot)
{
    std::vector<User> players;
    std::vector<Carte*> arme, lieu,suspect,enveloppe,pioche;
    std::map<int, Carte*> myHand;
    std::vector<int> myMain1,myMain2,myMain3,myMain4,myMain5,myMain6;
    int rouge,vert,bleu,orange,rose,cyan;
    Save SaveEnv("enveloppe.txt");
    Save SavePartie("save.txt");

    Menu menuT;

    //couleurs
    rouge=makecol(255,22,22);
    vert=makecol(126,217,87);
    bleu=makecol(0,115,221);
    orange=makecol(255,145,77);
    rose=makecol(255,102,196);
    cyan=makecol(23,229,235);

    User joueur;

    int choice;

    //creation d'un paquet de cartes arme,lieu et suspect
    arme=creationArme();
    lieu=creationLieu();
    suspect=creationSuspect();

    if(saveOrNot==false)
    {
        int n,n1,n2;

        //on ajoute aléatoirement une carte suspect, lieu et arme dans l'enveloppe de l'énigme
        n=rand()%suspect.size();
        n1=rand()%arme.size();
        n2=rand()%lieu.size();
        SaveEnv.save0(n,n1,n2);

        enveloppe.push_back(suspect[n]);
        enveloppe.push_back(arme[n1]);
        enveloppe.push_back(lieu[n2]);
        std::cout<<"SUSPECT : "<<enveloppe[0]->getNom()<<std::endl;
        std::cout<<"ARME : "<<enveloppe[1]->getNom()<<std::endl;
        std::cout<<"LIEU : "<<enveloppe[2]->getNom()<<std::endl;

        //on efface les cartes retirées de chaque paquet de cartes
        suspect.erase(suspect.begin()+n);
        arme.erase(arme.begin()+n1);
        lieu.erase(lieu.begin()+n2);

        //on met les cartes restantes dans une pioche
        pioche=setPioche(suspect,lieu,arme);
        //on mélange la pioche
        //pioche=melange(pioche);
        myHand = mappage(pioche);

        do
        {
            std::cout<<" Combien de joueurs etes-vous ?"<<std::endl;
            std::cout<<"2, 3, 4, 5 ou 6 ?"<<std::endl;
            std::cin>>choice;
            setchoix(choice);
            if(getchoix() !=2 && getchoix() !=3 && getchoix() !=4 && getchoix() !=5 && getchoix() !=6)
            {
                std::cout << "Erreur: saisi" << std::endl;
            }
        }
        while(getchoix() !=2 && getchoix() !=3 && getchoix() !=4 && getchoix() !=5 && getchoix() !=6);

        switch (getchoix())
        {
        case 2 :
        {
            for(int i=0 ; i<2; i++)
            {
                //on créé les joueurs
                joueur.creation();
                if(i==0)
                {
                    joueur.position(rouge,1,6);
                }

                if(i==1)
                {
                    joueur.position(bleu,15,22);
                }

                //on l'ajoute à notre conteneurs de joueurs
                players.push_back(joueur);
            }

            //on créer un vector de int pour chaque joueurs
            //on va y mettre le reste des cartes indices divisé par 2 (car 2 joueurs)
            for (int i = 0; i<9; i++)
            {
                myMain1.push_back(i);
            }

            for (int i = 9; i<18; i++)
            {
                myMain2.push_back(i);
            }


            //on attribut aux joueurs les vector de int respectifs
            players[0].setHand(myMain1);
            players[1].setHand(myMain2);
            SaveEnv.save0(n,n1,n2);
            SavePartie.save1(2, players);
            break;
        }
        case  3 :
            for(int i=0 ; i<3; i++)
            {
                joueur.creation();
                if(i==0)
                {
                    joueur.position(rouge,1,6);
                }

                if(i==1)
                {
                    joueur.position(bleu,15,22);
                }

                if(i==2)
                {
                    joueur.position(vert,22,6);
                }
                players.push_back(joueur);
            }

            for (int i = 0; i<6; i++)
            {
                //premier joueur va prendre les chiffres de 0 à 6 dans son vector
                myMain1.push_back(i);
            }

            for (int i=6; i<12; i++)
            {
                //deuxième joueur va prendre les chiffres de 6 à 12 dans son vector
                myMain2.push_back(i);
            }
            for (int i=12; i<18; i++)
            {
                //deuxième joueur va prendre les chiffres de 12 à 18 dans son vector
                myMain3.push_back(i);
            }

            //on attribut aux joueurs les vector de int respectifs aux joueurs
            players[0].setHand(myMain1);
            players[1].setHand(myMain2);
            players[2].setHand(myMain3);
            SavePartie.save1(3, players);
            break;
        case 4 :
            for(int i=0; i<4; i++)
            {
                joueur.creation();
                if(i==0)
                {
                    joueur.position(rouge,1,6);
                }

                if(i==1)
                {
                    joueur.position(bleu,15,22);
                }

                if(i==2)
                {
                    joueur.position(vert,22,6);
                }
                if(i==3)
                {
                    joueur.position(rose,1,16);
                }
                players.push_back(joueur);
            }
            for (int i = 0; i<4; i++)
            {
                //premier joueur va prendre les chiffres de 0 à 6 dans son vector
                myMain1.push_back(i);
            }

            for (int i=4; i<8; i++)
            {
                //deuxième joueur va prendre les chiffres de 6 à 12 dans son vector
                myMain2.push_back(i);
            }
            for (int i=8; i<13; i++)
            {
                //deuxième joueur va prendre les chiffres de 12 à 18 dans son vector
                myMain3.push_back(i);
            }
            for (int i=13; i<18; i++)
            {
                //deuxième joueur va prendre les chiffres de 12 à 18 dans son vector
                myMain4.push_back(i);
            }
            players[0].setHand(myMain1);
            players[1].setHand(myMain2);
            players[2].setHand(myMain3);
            players[3].setHand(myMain4);
            SavePartie.save1(4, players);
            break;
        case 5 :
            for(int i=0; i<5; i++)
            {
                joueur.creation();
                if(i==0)
                {
                    joueur.position(rouge,1,6);
                }

                if(i==1)
                {
                    joueur.position(bleu,15,22);
                }

                if(i==2)
                {
                    joueur.position(vert,22,6);
                }
                if(i==3)
                {
                    joueur.position(rose,1,16);
                }
                if(i==4)
                {
                    joueur.position(cyan,17,1);
                }
                players.push_back(joueur);
            }

            for (int i = 0; i<3; i++)
            {
                //premier joueur va prendre les chiffres de 0 à 6 dans son vector
                myMain1.push_back(i);
            }

            for (int i=3; i<6; i++)
            {
                //deuxième joueur va prendre les chiffres de 6 à 12 dans son vector
                myMain2.push_back(i);
            }
            for (int i=6; i<10; i++)
            {
                //deuxième joueur va prendre les chiffres de 12 à 18 dans son vector
                myMain3.push_back(i);
            }
            for (int i=10; i<14; i++)
            {
                //deuxième joueur va prendre les chiffres de 12 à 18 dans son vector
                myMain4.push_back(i);
            }
            for (int i=14; i<18; i++)
            {
                //deuxième joueur va prendre les chiffres de 12 à 18 dans son vector
                myMain5.push_back(i);
            }

            players[0].setHand(myMain1);
            players[1].setHand(myMain2);
            players[2].setHand(myMain3);
            players[3].setHand(myMain4);
            players[4].setHand(myMain5);
            SavePartie.save1(5, players);
            break;
        case 6 :
            for(int i=0; i<6; i++)
            {
                joueur.creation();
                if(i==0)
                {
                    joueur.position(rouge,1,6);
                }

                if(i==1)
                {
                    joueur.position(bleu,15,22);
                }

                if(i==2)
                {
                    joueur.position(vert,22,6);
                }
                if(i==3)
                {
                    joueur.position(rose,1,16);
                }
                if(i==4)
                {
                    joueur.position(cyan,17,1);
                }
                if(i==5)
                {
                    joueur.position(orange,22,18);
                }
                players.push_back(joueur);
            }
            for (int i = 0; i<3; i++)
            {
                //premier joueur va prendre les chiffres de 0 à 6 dans son vector
                myMain1.push_back(i);
            }

            for (int i=3; i<6; i++)
            {
                //deuxième joueur va prendre les chiffres de 6 à 12 dans son vector
                myMain2.push_back(i);
            }
            for (int i=6; i<9; i++)
            {
                //deuxième joueur va prendre les chiffres de 12 à 18 dans son vector
                myMain3.push_back(i);
            }
            for (int i=9; i<12; i++)
            {
                //deuxième joueur va prendre les chiffres de 12 à 18 dans son vector
                myMain4.push_back(i);
            }
            for (int i=12; i<15; i++)
            {
                //deuxième joueur va prendre les chiffres de 12 à 18 dans son vector
                myMain5.push_back(i);
            }
            for (int i=15; i<18; i++)
            {
                //deuxième joueur va prendre les chiffres de 12 à 18 dans son vector
                myMain6.push_back(i);
            }
            players[0].setHand(myMain1);
            players[1].setHand(myMain2);
            players[2].setHand(myMain3);
            players[3].setHand(myMain4);
            players[4].setHand(myMain5);
            players[5].setHand(myMain6);
            SavePartie.save1(6, players);
            break;
        default :
            break;
        }
    }
    else if(saveOrNot==true)
    {
        int choixF=0;
        SaveEnv.load0(enveloppe, arme, lieu, suspect);
        SavePartie.load(choixF, players);
        setchoix(choixF);
        //on met les cartes restantes dans une pioche
        pioche=setPioche(suspect,lieu,arme);
        //on mélange la pioche
        //pioche=melange(pioche);
        myHand = mappage(pioche);
    }

    std::cout << "Cliquez sur le plateau avant de continuer" << std::endl;
    menuT.menuTour(getchoix(),players, enveloppe,myHand);

    /*for(unsigned long int i=0; i<myHand.size(); i++)
    {
        delete myHand[i];
        myHand[i]=NULL;
    }

    for(unsigned long int i=0; i<enveloppe.size(); i++)
    {
        delete enveloppe[i];
        enveloppe[i]=NULL;
    }
    for(unsigned long int i=0; i<arme.size(); i++)
    {
        delete arme[i];
        arme[i]=NULL;
    }
    for(unsigned long int i=0; i<suspect.size(); i++)
    {
        delete suspect[i];
        suspect[i]=NULL;
    }
    for(unsigned long int i=0; i<lieu.size(); i++)
    {
        delete lieu[i];
        lieu[i]=NULL;
    }
    for(unsigned long int i =0; i<pioche.size(); i++)
    {
        delete pioche[i];
        pioche[i]=NULL;
    }*/

}

bool Menu::menuHorsalle(BITMAP* page, BITMAP* plat,bool& victoire, std::vector<Carte*> &solution, std::vector<User> &joueurs, int perso, int nbJoueur,std::map<int, Carte*> myMap, int& fin)
{
    std::string suspect, arme, lieu;
    int salle, caseM=0;
    bool M1=true, M2=true, M3=true, M4=true, M5=true;
    bool endGame=false;

    De dice;

    SAMPLE *swoosh;
    swoosh = load_sample("swoosh.wav");

    SAMPLE *scream;
    scream = load_sample("screamer.wav");

    BITMAP *screamer;
    screamer=load_bitmap("images/screamer.bmp",NULL);

    if(mouse_b&1 && mouse_x>= 980 && mouse_x<1150 && mouse_y>=230 && mouse_y<300)  ///le joueur choisit d'accuser
    {
        joueurs[perso].accusation(suspect,arme,lieu,page);
        victoire=joueurs[perso].verification(suspect,lieu,arme,solution);
        fin=1;
    }
    if(mouse_b&1 && mouse_x>= 980 && mouse_x<1150 && mouse_y>=312 && mouse_y<382)  ///le joueur choisit de lancer le dé
    {
        dice.lancerDe();  //lancer le dé
        for(int k=0; k<dice.getValeur(); k++)
        {
            if(salle==0 || k==0) //tant quil reste un déplacement possible et que le joueur n'est pas dans une salle
            {
                dice.affichageDE(page, k);
                joueurs[perso].deplacement(perso,nbJoueur,joueurs);//sousprogramme du deplacement du joueur
                play_sample(swoosh, 15, 128,1000, 0);
                blit(plat,page,0,0,0,0,1200,650);
                for(int j=0; j<nbJoueur ; j++)
                {
                    circlefill(page,((joueurs[j].getpionX()-1)*31.4)+270, ((joueurs[j].getpionY()-1)*27)+42, 10, joueurs[j].getpion());
                }
                blit(page,screen,0,0,0,0,1200,650);
            }
            salle=joueurs[perso].salleVerif();  //on verifie si le joueur est dans une salle ou pas

            caseM=joueurs[perso].caseMverif();
            if(caseM==1 && M1==true)
            {
                k=0;
                dice.lancerDe();
                M1=false;
            }
            else if(caseM==2 && M2==true)
            {
                dice.setValeur(5);
                M2=false;
            }
            else if(caseM==3 && M3==true)
            {
                dice.setValeur(dice.getValeur()-2);
                M3=false;
            }
            else if(caseM==4 && M4==true)
            {
                k=dice.getValeur();
                M4=false;
            }
            else if(caseM==5 && M5==true)
            {
                play_sample(scream, 1000, 128,1000, 0);
                blit(screamer,page,0,0,0,0,1200,650);
                blit(page,screen,0,0,0,0,1200,650);

                rest(1500);
                dice.affichageDE(page, k);
                blit(plat,page,0,0,0,0,1200,650);
                for(int j=0; j<nbJoueur ; j++)
                {
                    circlefill(page,((joueurs[j].getpionX()-1)*31.4)+270, ((joueurs[j].getpionY()-1)*27)+42, 10, joueurs[j].getpion());
                }
                blit(page,screen,0,0,0,0,1200,650);
                M5=false;
            }
            else if(caseM==0)
            {
            }
        }

        switch(salle)
        {
        ///on demande au joueur d'émettre une hypothèse selon la pièce dans laquelle il est
        case 0 : //rien a faire
            break;
        case 1 :   ///bureau de dumbledore
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);  ///le joueur fait une hypothèse quand il rentre dans une salle
            joueurs[perso].verifHypo("bureau de dumbledore", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 2 :  ///salle des potions
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("salle de classe des potions", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 3 :  ///salle de bain
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("salle de bain", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 4 :   ///grande salle
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("grande salle", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 5 :   ///biblio
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("bibliotheque", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 6 :   ///chambre des secrets
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("chambre des secrets", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 7 :   ///tour d'astronomie
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("tour d astronomie", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 8 :  ///salle sur demande
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("salle sur demande", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 9 :  ///les serres
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("les serres", arme,suspect,joueurs,myMap,plat,perso);
            break;
        default :
            break;
        }
        fin=1;
    }
    if(mouse_b&1 && mouse_x>= 980 && mouse_x<1150 && mouse_y>=395 && mouse_y<465)  ///le joueur choisit de quitter la partie
    {
        endGame=true;
    }
    return endGame;
}

bool Menu::menuSallePS(int& fin, BITMAP* page, BITMAP* plat,bool& victoire, std::vector<Carte*> &solution, std::vector<User> &joueurs, int perso, int nbJoueur,std::map<int, Carte*> myMap, int salle)
{
    std::string suspect, arme, lieu;

    bool endGame;

    SAMPLE *swoosh;
    swoosh = load_sample("swoosh.wav");

    De dice2;


    //affichage des pions des joueurs
    for(int j=0; j<nbJoueur ; j++)
    {
        circlefill(page,((joueurs[j].getpionX()-1)*31.4)+270, ((joueurs[j].getpionY()-1)*27)+42, 10, joueurs[j].getpion());
    }
    blit(page,screen,0,0,0,0,1200,650);

    if(mouse_b&1 && mouse_x>= 1010 && mouse_x<1120 && mouse_y>=209 && mouse_y<250)  ///le joueur choisit d'accuser
    {
        joueurs[perso].accusation(suspect,arme,lieu,page);
        victoire=joueurs[perso].verification(suspect,lieu,arme,solution);
        fin=1;
    }
    if(mouse_b&1 && mouse_x>= 1010 && mouse_x<1120 && mouse_y>=270 && mouse_y<309)  ///le joueur choisit de faire une hypothese
    {
        switch(salle)
        {
        ///on demande au joueur d'émettre une hypothèse selon la pièce dans laquelle il est
        case 0 : //rien a faire
            break;
        case 1 :   ///bureau de dumbledore
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);  //le joueur fait une hypothèse quand il rentre dans une salle
            joueurs[perso].verifHypo("bureau de dumbledore", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 2 :  ///salle des potions
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("salle de classe des potions", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 3 :  ///salle de bain
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("salle de bain", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 4 :   ///grande salle
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("grande salle", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 5 :   ///biblio
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("bibliotheque", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 6 :   ///chambre des secrets
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("chambre des secrets", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 7 :   ///tour d'astronomie
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("tour d astronomie", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 8 :  ///salle sur demande
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("salle sur demande", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 9 :  ///les serres
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("les serres", arme,suspect,joueurs,myMap,plat,perso);
            break;
        default :
            break;
        }
        fin=1;
    }
    if(mouse_b&1 && mouse_x>= 1010 && mouse_x<1120 && mouse_y>=323 && mouse_y<364)  ///le joueur choisit de lancer le dé
    {
        dice2.lancerDe();  //lancer le dé
        for(int k=0; k<dice2.getValeur(); k++)
        {
            if(salle==0 || k==0) //tant quil reste un déplacement possible et que le joueur n'est pas dans une salle
            {
                dice2.affichageDE(page, k);
                joueurs[perso].deplacement(perso,nbJoueur,joueurs);//sousprogramme du deplacement du joueur
                play_sample(swoosh, 15, 128,1000, 0);
                blit(plat,page,0,0,0,0,1200,650);
                for(int j=0; j<nbJoueur ; j++)
                {
                    circlefill(page,((joueurs[j].getpionX()-1)*31.4)+270, ((joueurs[j].getpionY()-1)*27)+42, 10, joueurs[j].getpion());
                }
                blit(page,screen,0,0,0,0,1200,650);
            }
            salle=joueurs[perso].salleVerif();  //on verifie si le joueur est dans une salle ou pas
        }

        switch(salle)
        {
        ///on demande au joueur d'émettre une hypothèse selon la pièce dans laquelle il est
        case 0 : //rien a faire
            break;
        case 1 :   ///bureau de dumbledore
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);  //le joueur fait une hypothèse quand il rentre dans une salle
            joueurs[perso].verifHypo("bureau de dumbledore", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 2 :  ///salle des potions
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("salle de classe des potions", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 3 :  ///salle de bain
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("salle de bain", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 4 :   ///grande salle
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("grande salle", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 5 :   ///biblio
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("bibliotheque", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 6 :   ///chambre des secrets
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("chambre des secrets", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 7 :   ///tour d'astronomie
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("tour d astronomie", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 8 :  ///salle sur demande
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("salle sur demande", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 9 :  ///les serres
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("les serres", arme,suspect,joueurs,myMap,plat,perso);
            break;
        default :
            break;
        }
        fin=1;
    }
    if(mouse_b&1 && mouse_x>= 1010 && mouse_x<1120 && mouse_y>=378 && mouse_y<416)  ///le joueur decide d'emprunter le passage secret
    {
        switch(salle)
        {
        case 2 :  ///salle des potions
            joueurs[perso].setpionX(18);
            joueurs[perso].setpionY(3);
            circlefill(page,((joueurs[perso].getpionX()-1)*31.4)+270, ((joueurs[perso].getpionY()-1)*27)+42, 10, joueurs[perso].getpion());
            blit(page,screen,0,0,0,0,1200,650);
            rest(1000);
            break;

        case 3 :  ///salle de bain
            joueurs[perso].setpionX(17);
            joueurs[perso].setpionY(22);
            circlefill(page,((joueurs[perso].getpionX()-1)*31.4)+270, ((joueurs[perso].getpionY()-1)*27)+42, 10, joueurs[perso].getpion());
            blit(page,screen,0,0,0,0,1200,650);
            rest(1000);
            break;

        case 7 :   ///tour d'astronomie
            joueurs[perso].setpionX(3);
            joueurs[perso].setpionY(5);
            circlefill(page,((joueurs[perso].getpionX()-1)*31.4)+270, ((joueurs[perso].getpionY()-1)*27)+42, 10, joueurs[perso].getpion());
            blit(page,screen,0,0,0,0,1200,650);
            rest(1000);
            break;

        case 9 :  ///les serres
            joueurs[perso].setpionX(6);
            joueurs[perso].setpionY(21);
            circlefill(page,((joueurs[perso].getpionX()-1)*31.4)+270, ((joueurs[perso].getpionY()-1)*27)+42, 10, joueurs[perso].getpion());
            blit(page,screen,0,0,0,0,1200,650);
            rest(1000);
            break;
        default :
            break;
        }
    }
    if(mouse_b&1 && mouse_x>= 1010 && mouse_x<1120 && mouse_y>=432 && mouse_y<471)  ///le joueur decide de quitter la partie
    {
        endGame=true;
        fin=1;
    }
    return endGame;
}

bool Menu::menuSalle(int& fin, BITMAP* page, BITMAP* plat,bool& victoire, std::vector<Carte*> &solution, std::vector<User> &joueurs, int perso, int nbJoueur,std::map<int, Carte*> myMap, int salle)
{
    std::string suspect, arme, lieu;
    bool endGame=false;

    SAMPLE *swoosh;
    swoosh = load_sample("swoosh.wav");

    De dice3;

    //affichage des pions des joueurs
    for(int j=0; j<nbJoueur ; j++)
    {
        circlefill(page,((joueurs[j].getpionX()-1)*31.4)+270, ((joueurs[j].getpionY()-1)*27)+42, 10, joueurs[j].getpion());
    }
    blit(page,screen,0,0,0,0,1200,650);

    if(mouse_b&1 && mouse_x>= 997 && mouse_x<1132 && mouse_y>=219 && mouse_y<269)  ///le joueur decide d'accuser
    {
        joueurs[perso].accusation(suspect,arme,lieu,page);
        victoire=joueurs[perso].verification(suspect,lieu,arme,solution);
        fin=1;
    }
    if(mouse_b&1 && mouse_x>= 997 && mouse_x<1132 && mouse_y>=282 && mouse_y<338)  ///le joueur decide de refaire une hypothese ds la salle
    {
        switch(salle)
        {
        ///on demande au joueur d'émettre une hypothèse selon la pièce dans laquelle il est
        case 0 : //rien a faire
            break;
        case 1 :   ///bureau de dumbledore
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);  //le joueur fait une hypothèse quand il rentre dans une salle
            joueurs[perso].verifHypo("bureau de dumbledore", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 2 :  ///salle des potions
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("salle de classe des potions", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 3 :  ///salle de bain
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("salle de bain", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 4 :   ///grande salle
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("grande salle", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 5 :   ///biblio
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("bibliotheque", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 6 :   ///chambre des secrets
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("chambre des secrets", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 7 :   ///tour d'astronomie
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("tour d astronomie", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 8 :  ///salle sur demande
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("salle sur demande", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 9 :  ///les serres
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("les serres", arme,suspect,joueurs,myMap,plat,perso);
            break;
        default :
            break;
        }
        fin=1;
    }
    if(mouse_b&1 && mouse_x>= 997 && mouse_x<1132 && mouse_y>=350 && mouse_y<395)  ///le joueur decide de lancer le dé
    {
        int scancode;
        int touche;
        bool finChoix=false;

        set_keyboard_rate(1000,200);

        while(finChoix==false)
        {
            textprintf_ex(plat,font,963,110,makecol(0,0,0),-1,"UTILISER LES FLECHES:");
            textprintf_ex(plat,font,963,125,makecol(0,0,0),-1,"(pour choisir la porte");
            textprintf_ex(plat,font,958,140,makecol(0,0,0),-1,"      <- ou ->");
            blit(plat,page,0,0,0,0,1200,650);

            if(keypressed())
            {
                touche=readkey();

                // a partir de l'info de touche on obtient le scancode sur le 2ème octet
                // permet d'obtenir les touches non caractères (directions, effacer ...)
                scancode=touche>>8;
                switch (scancode)
                {
                case KEY_LEFT :
                    if(salle==4)
                    {
                        joueurs[perso].setpionX(8);
                        joueurs[perso].setpionY(4);
                        finChoix=true;
                    }
                    else if(salle==5)
                    {
                        joueurs[perso].setpionX(2);
                        joueurs[perso].setpionY(14);
                        finChoix=true;
                    }
                    break;
                case KEY_RIGHT :
                    if(salle==4)
                    {
                        joueurs[perso].setpionX(13);
                        joueurs[perso].setpionY(6);
                        finChoix=true;
                    }
                    else if(salle==5)
                    {
                        joueurs[perso].setpionX(6);
                        joueurs[perso].setpionY(9);
                        finChoix=true;
                    }
                    break;
                default:
                    break;
                }
            }
            for(int j=0; j<nbJoueur ; j++)
            {
                circlefill(page,((joueurs[j].getpionX()-1)*31.4)+270, ((joueurs[j].getpionY()-1)*27)+42, 10, joueurs[j].getpion());
            }
            blit(page,screen,0,0,0,0,1200,650);
        }

        dice3.lancerDe();  //lancer le dé
        for(int k=0; k<dice3.getValeur(); k++)
        {
            if(salle==0 || k==0) //tant quil reste un déplacement possible et que le joueur n'est pas dans une salle
            {
                dice3.affichageDE(page, k);
                joueurs[perso].deplacement(perso,nbJoueur,joueurs);//sousprogramme du deplacement du joueur
                play_sample(swoosh, 15, 128,1000, 0);
                blit(plat,page,0,0,0,0,1200,650);
                for(int j=0; j<nbJoueur ; j++)
                {
                    circlefill(page,((joueurs[j].getpionX()-1)*31.4)+270, ((joueurs[j].getpionY()-1)*27)+42, 10, joueurs[j].getpion());
                }
                blit(page,screen,0,0,0,0,1200,650);
            }
            salle=joueurs[perso].salleVerif();  //on verifie si le joueur est dans une salle ou pas
        }

        switch(salle)
        {
        ///on demande au joueur d'émettre une hypothèse selon la pièce dans laquelle il est
        case 0 : //rien a faire
            break;
        case 1 :   ///bureau de dumbledore
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);  //le joueur fait une hypothèse quand il rentre dans une salle
            joueurs[perso].verifHypo("bureau de dumbledore", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 2 :  ///salle des potions
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("salle de classe des potions", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 3 :  ///salle de bain
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            //joueurs[perso].verifHypo("salle de bain", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 4 :   ///grande salle
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("grande salle", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 5 :   ///biblio
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("bibliotheque", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 6 :   ///chambre des secrets
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("chambre des secrets", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 7 :   ///tour d'astronomie
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("tour d astronomie", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 8 :  ///salle sur demande
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("salle sur demande", arme,suspect,joueurs,myMap,plat,perso);
            break;
        case 9 :  ///les serres
            rest(1000);
            joueurs[perso].hypothese(suspect,arme, page);
            joueurs[perso].verifHypo("les serres", arme,suspect,joueurs,myMap,plat,perso);
            break;
        default :
            break;
        }
        fin=1;
    }
    if(mouse_b&1 && mouse_x>= 997 && mouse_x<1132 && mouse_y>=411 && mouse_y<460)  ///le joueur decide de quitter la partie
    {
        endGame=true;
        fin=1;
    }
    return endGame;
}
