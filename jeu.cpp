#include "Cartes.h"
#include "User.h"
#include "CasePlateau.h"
#include "Suspect.h"
#include "Arme.h"
#include "Lieu.h"
#include "de.h"


///choix de l'hypothèse en mode graphique
void User::hypothese(std::string& suspect, std::string& arme, BITMAP *page)
{
    bool susp=false;
    bool arm=false;
    bool fini=false;

    BITMAP *hypofond;
    BITMAP *verif;

    hypofond=load_bitmap("images/hypofond.bmp",NULL);
    verif=load_bitmap("images/verif.bmp",NULL);

    clear(screen);
    clear(page);

    blit(hypofond,page,0,0,0,0,SCREEN_W,SCREEN_H);

    while (fini==false)  ///tant que le joueur n'a pas choisi deux cartes et valider son choix
    {
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(20);

        if ( mouse_x>=284 && mouse_x<=384 && mouse_y>=194 && mouse_y<=294 && arm==false)
        {

            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 300, 214, 72, 92);              ///le joueur choisi d'abord l'arme qu'il suspecte
                arme="avada kedavra";
                arm=true;
            }

        }

        else if (mouse_x>=404 && mouse_x<=504 && mouse_y>=194 && mouse_y<=294 && arm==false)
        {

            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 420, 214, 72, 92);
                arme="collier d opale";
                arm=true;
            }
        }

        else if ( mouse_x>=524 && mouse_x<=624 && mouse_y>=194 && mouse_y<=294 && arm==false)
        {

            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 540, 214, 72, 92);
                arme="crochet basilic";
                arm=true;
            }
        }

        else if ( mouse_x>=644 && mouse_x<=744 && mouse_y>=194 && mouse_y<=294 && arm==false)
        {

            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 660, 214, 72, 92);
                arme="epee gryffondor";
                arm=true;
            }
        }

        else if (mouse_x>=764 && mouse_x<=864 && mouse_y>=194 && mouse_y<=294 && arm==false)
        {

            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 780, 214, 72, 92);
                arme="philtre mort vivant";
                arm=true;
            }

        }

        else if ( mouse_x>=884 && mouse_x<=984 && mouse_y>=194 && mouse_y<=294 && arm==false)
        {

            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 900, 214, 72, 92);
                arme="poison";
                arm=true;
            }

        }

        else if(mouse_x>=350 && mouse_x<=450 && mouse_y>=384 && mouse_y<=484 && arm==true && susp==false)
        {

            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 366, 404, 72, 92);                      ///puis choix du suspect
                suspect="harry potter";
                susp=true;
            }
        }

        else if(mouse_x>=470 && mouse_x<=570 && mouse_y>=384 && mouse_y<=484 && arm==true && susp==false)
        {

            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 486, 404, 72, 92);
                suspect="ron weasley";
                susp=true;
            }
        }

        else if(mouse_x>=590 && mouse_x<=690 && mouse_y>=384 && mouse_y<=484 && arm==true && susp==false)
        {

            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 606, 404, 72, 92);
                suspect="hermione granger";
                susp=true;
            }
        }

        else if(mouse_x>=710 && mouse_x<=810 && mouse_y>=384 && mouse_y<=484 && arm==true && susp==false)
        {

            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 726, 404, 72, 92);
                suspect="ginny weasley";
                susp=true;
            }
        }

        else if(mouse_x>=830 && mouse_x<=930 && mouse_y>=384 && mouse_y<=484 && arm==true && susp==false)
        {

            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 846, 404, 72, 92);
                suspect="luna lovegood";
                susp=true;
            }
        }

        else if(mouse_x>=950 && mouse_x<=1050 && mouse_y>=384 && mouse_y<=484 && arm==true && susp==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 966, 404, 72, 92);
                suspect="drago malefoy";
                susp=true;
            }

        }

        if(mouse_x>=950 && mouse_x<=1160 && mouse_y>=540 && mouse_y<=627 && susp==true && arm==true) //valider hypothese
        {
            if(mouse_b&1)
            {
                fini=true;
            }

        }
    }
    destroy_bitmap(hypofond);
    destroy_bitmap(verif);
}


bool User::verification(std::string suspect, std::string lieu, std::string arme, std::vector<Carte*>enveloppe)
{
    bool verif=false;
    std::cout<<suspect<<std::endl;
    std::cout<<arme<<std::endl;
    std::cout<<lieu<<std::endl;
    fflush(stdin);
    if(suspect == enveloppe[0]->getNom() && arme == enveloppe[1]->getNom() && lieu == enveloppe[2]->getNom())
    {
        verif = true;//l'hypothèse est la bonne, victoire
        std::cout<<std::endl;
        std::cout<<"VOUS AVEZ TROUVE LA BONNE HYPOTHESE "<<std::endl;
        setVictoire(true);
        //system("CLS");
    }
    else
    {
        verif = false;
        std::cout<<std::endl;
        std::cout<<" Votre hypothese n'est pas la bonne, mauvais... "<<std::endl;
        std::cout<<std::endl;
        setElimination(true);
    }
    return verif;
}


void User::deplacement(int iJ, int nbjoueurs, std::vector<User> players)
{
    bool err;
    int fin=0;
    int scancode;
    int touche;
    CasePlato plateau [22][22];
    initPlateau(plateau);      ///a modifier - mettre dans une classe

    set_keyboard_rate(1000,200);

    ///A REVOIR
    while(!fin)
    {
        if(keypressed())
        {
            touche=readkey();

            // a partir de l'info de touche on obtient le scancode sur le 2ème octet
            // permet d'obtenir les touches non caractères (directions, effacer ...)
            scancode=touche>>8;
            switch (scancode)
            {
            case KEY_UP :
                err=this->posverif("up", iJ, nbjoueurs, players);
                if(err==false)
                {
                    fin=1;
                    setpionY(getpionY()-1);
                }
                else
                {}
                break;

            case KEY_DOWN :
                err=this->posverif("down", iJ, nbjoueurs, players);
                if(err==false)
                {
                    fin=1;
                    setpionY(getpionY()+1);
                }
                else
                {}
                break;

            case KEY_LEFT :
                err=this->posverif("left", iJ, nbjoueurs, players);
                if(err==false)
                {
                    fin=1;
                    setpionX(getpionX()-1);
                }
                else
                {}
                break;

            case KEY_RIGHT :
                err=this->posverif("right", iJ, nbjoueurs, players);
                if(err==false)
                {
                    fin=1;
                    setpionX(getpionX()+1);
                }
                else
                {}
                break;
            default:
                break;
            }
        }
    }
}

void User::accusation(std::string& suspect, std::string& arme, std::string& lieu, BITMAP *page)
{
    bool susp=false;
    bool arm=false;
    bool salle=false;
    bool fini=false;

    BITMAP *accufond;
    BITMAP *verif;

    accufond=load_bitmap("images/accufond.bmp",NULL);
    verif=load_bitmap("images/verif.bmp",NULL);

    clear(screen);
    clear(page);

    blit(accufond,page,0,0,0,0,SCREEN_W,SCREEN_H);


    while (fini!=true)
    {
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(20);
        if(mouse_x>=125 && mouse_x<=218 && mouse_y>=16 && mouse_y<=153 && salle==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif,page,0,0,200,200,137,31,70,91);
                lieu="chambre des secrets";
                salle=true;
            }
        }
        if(mouse_x>=250 && mouse_x<=340 && mouse_y>=16 && mouse_y<=153 && salle==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif,page,0,0,200,200,257,31,70,91);
                lieu="bureau dumbledore";
                salle=true;
            }
        }
        if(mouse_x>=375 && mouse_x<=452 && mouse_y>=16 && mouse_y<=153 && salle==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif,page,0,0,200,200,377,31,70,91);
                lieu="grande salle";
                salle=true;
            }
        }
        if(mouse_b && mouse_x>=500 && mouse_x<=593 && mouse_y>=16 && mouse_y<=153 && salle==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif,page,0,0,200,200,497,31,70,91);
                lieu="les serres";
                salle=true;
            }
        }
        if(mouse_x>=625 && mouse_x<=718 && mouse_y>=16 && mouse_y<=153 && salle==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif,page,0,0,200,200,617,31,70,91);
                lieu="salle de bain";
                salle=true;
            }
        }
        if(mouse_x>=750 && mouse_x<=843 && mouse_y>=16 && mouse_y<=153 && salle==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif,page,0,0,200,200,737,31,70,91);
                lieu="salle de classe des potions";
                salle=true;
            }
        }
        if(mouse_x>=875 && mouse_x<=968 && mouse_y>=16 && mouse_y<=153 && salle==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif,page,0,0,200,200,857,31,70,91);
                lieu="salle sur demande";
                salle=true;
            }
        }
        if(mouse_x>=1000 && mouse_x<=1093 && mouse_y>=16 && mouse_y<=153 && salle==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif,page,0,0,200,200,977,31,70,91);
                lieu="tour d astronomie";
                salle=true;
            }
        }
        if(mouse_x>=1125 && mouse_x<=1218 && mouse_y>=16 && mouse_y<=153 && salle==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif,page,0,0,200,200,1097,31,71,90);
                lieu="bibliotheque";
                salle=true;
            }
        }
        if (mouse_x>=284 && mouse_x<=384 && mouse_y>=194 && mouse_y<=294 && salle==true && arm==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 300, 214, 72, 92);
                arme="avada kedavra";
                arm=true;
            }
        }

        if (mouse_x>=404 && mouse_x<=504 && mouse_y>=194 && mouse_y<=294 && salle==true && arm==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 420, 214, 72, 92);
                arme="collier d opale";
                arm=true;
            }
        }

        if (mouse_x>=524 && mouse_x<=624 && mouse_y>=194 && mouse_y<=294 && salle==true && arm==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 540, 214, 72, 92);
                arme="crochet basilic";
                arm=true;
            }
        }

        if (mouse_x>=644 && mouse_x<=744 && mouse_y>=194 && mouse_y<=294 && salle==true && arm==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 660, 214, 72, 92);
                arme="epee gryffondor";
                arm=true;
            }
        }

        if (mouse_x>=764 && mouse_x<=864 && mouse_y>=194 && mouse_y<=294 && salle==true && arm==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 780, 214, 72, 92);
                arme="philtre mort vivant";
                arm=true;
            }
        }

        if (mouse_x>=884 && mouse_x<=984 && mouse_y>=194 && mouse_y<=294 && salle==true && arm==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 900, 214, 72, 92);
                arme="poison";
                arm=true;
            }
        }

        if(mouse_x>=350 && mouse_x<=450 && mouse_y>=384 && mouse_y<=484 && salle==true && arm==true && susp==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 366, 404, 72, 92);
                suspect="harry potter";
                susp=true;
            }
        }

        if(mouse_x>=470 && mouse_x<=570 && mouse_y>=384 && mouse_y<=484 && salle==true && arm==true && susp==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 486, 404, 72, 92);
                suspect="ron weasley";
                susp=true;
            }
        }

        if(mouse_x>=590 && mouse_x<=690 && mouse_y>=384 && mouse_y<=484 && salle==true && arm==true && susp==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 606, 404, 72, 92);
                suspect="hermione granger";
                susp=true;
            }
        }

        if(mouse_x>=710 && mouse_x<=810 && mouse_y>=384 && mouse_y<=484 && salle==true && arm==true && susp==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 726, 404, 72, 92);
                suspect="ginny weasley";
                susp=true;
            }
        }

        if(mouse_x>=830 && mouse_x<=930 && mouse_y>=384 && mouse_y<=484 && salle==true && arm==true && susp==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 846, 404, 72, 92);
                suspect="luna lovegood";
                susp=true;
            }
        }

        if(mouse_x>=950 && mouse_x<=1050 && mouse_y>=384 && mouse_y<=484 && salle==true && arm==true && susp==false)
        {
            if( mouse_b&1)
            {
                stretch_blit(verif, page, 0, 0, 200, 200, 966, 404, 72, 92);
                suspect="drago malefoy";
                susp=true;
            }
        }

        if(mouse_x>=800 && mouse_x<=2000 && mouse_y>=500 && mouse_y<=650 && salle==true && susp==true && arm==true) //valider hypothese
        {
            if( mouse_b&1)
            {
                fini=true;
            }
        }
    }
    destroy_bitmap(accufond);
    destroy_bitmap(verif);
}


void De::lancerDe()
{
    //on génère un nb aléatoire entre 1 et 6
    int resultat;
    resultat=rand()%6+1;
    setValeur(resultat);
}


bool User::posverif(std::string keyPres, int iJ, int nbjoueurs, std::vector<User>& players)
{
    bool resVerif=false;

    int x=0,y=0;

    if(keyPres=="up")
        y=-1;

    if(keyPres=="down")
        y=1;

    if(keyPres=="right")
        x=1;

    if(keyPres=="left")
        x=-1;


    //blindage salle de bain
    if(( getpionX()+x== 1 ||  getpionX()+x== 2) && ( getpionY()+y>=1 &&  getpionY()+y<=5))
    {
        resVerif= true;
    }

    if(( getpionX()+x== 3) && ( getpionY()+y>=1 &&  getpionY()+y<=4))
    {
        resVerif= true;
    }

    if(( getpionX()+x== 4 ||  getpionX()+x== 5) && ( getpionY()+y>=1 &&  getpionY()+y<=5))
    {
        resVerif= true;
    }

    //blindage grande salle
    if(( getpionX()+x>= 8 &&  getpionX()+x<= 15) && (( getpionY()+y>=1 &&  getpionY()+y<=3) ||  getpionY()+y==5))
    {
        resVerif= true;
    }

    if(( getpionX()+x>= 9 &&  getpionX()+x<= 15) &&  getpionY()+y==4)
    {
        resVerif= true;
    }

    if((( getpionX()+x>= 8 &&  getpionX()+x<= 12) || ( getpionX()+x==14 ||  getpionX()+x==15)) && ( getpionY()+y==6))
    {
        resVerif= true;
    }

    //blindage les serres
    if(( getpionX()+x>= 18 &&  getpionX()+x<= 22) && ( getpionY()+y==1 ||  getpionY()+y==2))
    {
        resVerif= true;
    }

    if(( getpionX()+x>= 19 &&  getpionX()+x<= 22) && ( getpionY()+y==3 ||  getpionY()+y==4))
    {
        resVerif= true;
    }

    //blindage bureau de Dumbledore
    if(( getpionX()+x>= 18 &&  getpionX()+x<= 22) && (( getpionY()+y==7 ||  getpionY()+y==8) || ( getpionY()+y==10 ||  getpionY()+y==11)))
    {
        resVerif= true;
    }

    if(( getpionX()+x>= 19 &&  getpionX()+x<= 22) &&  getpionY()+y==9)
    {
        resVerif= true;
    }

    //blindage salle sur demande
    if(( getpionX()+x>= 18 &&  getpionX()+x<= 22) && getpionY()+y==13)
    {
        resVerif= true;
    }

    if(( getpionX()+x>= 17 &&  getpionX()+x<= 22) && ( getpionY()+y==14 ||  getpionY()+y==15 ||  getpionY()+y==16))
    {
        resVerif= true;
    }

    if((( getpionX()+x== 18) || ( getpionX()+x>= 20 &&  getpionX()+x<= 22)) &&  getpionY()+y==17)
    {
        resVerif= true;
    }


    //blindage tour d'astronomie
    if(( getpionX()+x>= 17 &&  getpionX()+x<= 22) && ( getpionY()+y==20 ||  getpionY()+y==21))
    {
        resVerif= true;
    }

    if((getpionX()+x>=18 &&  getpionX()+x<= 22) && getpionY()+y==22)
    {
        resVerif= true;
    }

    //blindage chambre des secrets
    if(( getpionX()+x>= 9 &&  getpionX()+x<= 14) &&  getpionY()+y==17)
    {
        resVerif= true;
    }

    if(( getpionX()+x>= 10 &&  getpionX()+x<= 14) &&  getpionY()+y==18)
    {
        resVerif= true;
    }

    if(( getpionX()+x>= 9 &&  getpionX()+x<= 14) && ( getpionY()+y>=19 &&  getpionY()+y<=22))
    {
        resVerif= true;
    }


    //blindage salle des potions
    if(getpionX()+x==1 &&  getpionY()+y==18)
    {
        resVerif= true;
    }

    if(( getpionX()+x>=3 &&  getpionX()+x<=6) &&  getpionY()+y==18)
    {
        resVerif= true;
    }

    if(( getpionX()+x>=1 &&  getpionX()+x<= 6) && ( getpionY()+y==19 ||  getpionY()+y==20 ||  getpionY()+y==22))
    {
        resVerif= true;
    }

    if(( getpionX()+x>=1 &&  getpionX()+x<=5) &&  getpionY()+y==21)
    {
        resVerif= true;
    }

    //blindage biblihothèque
    if(( getpionX()+x>= 1 &&  getpionX()+x<= 4) &&  getpionY()+y==8)
    {
        resVerif= true;
    }

    if((( getpionX()+x>= 1 &&  getpionX()+x<= 5) ||  getpionX()+x== 7) &&  getpionY()+y==9)
    {
        resVerif= true;
    }

    if(( getpionX()+x>= 1 &&  getpionX()+x<= 7) && ( getpionY()+y>=10 &&  getpionY()+y<=13))
    {
        resVerif= true;
    }

    if((( getpionX()+x>= 3 &&  getpionX()+x<= 7) ||  getpionX()+x<= 1) &&  getpionY()+y==14)
    {
        resVerif= true;
    }

    ///autres blindages (limites plateau + autres pions)
    //blindage limites plateau
    if((getpionX()+x<= 0 ||  getpionX()+x> 22) ||  (getpionY()+y<=0 ||  getpionY()+y>22))
    {
        resVerif= true;
    }

    //blindage etuie a enigme
    if((getpionX()+x>= 10 &&  getpionX()+x<= 14) &&  (getpionY()+y>=9 &&  getpionY()+y<=15))
    {
        resVerif= true;
    }

    //blindage autres pions
    for(int g=0; g<nbjoueurs; g++)
    {
        if(g!=iJ)
        {
            if(getpionX()+x==players[g].getpionX() && getpionY()+y==players[g].getpionY())
            {
                resVerif= true;
            }
        }
    }

    return resVerif;
}


int User::salleVerif()
{
    int salle;

    if(getpionX()==3 && getpionY()==5)
    {
        salle=3;
    }
    else if((getpionX()==8 && getpionY()==4) || (getpionX()==13 && getpionY()==6))
    {
        salle=4;
    }
    else if(getpionX()==18 && getpionY()==3)
    {
        salle=9;
    }
    else if(getpionX()==18 && getpionY()==9)
    {
        salle=1;
    }
    else if(getpionX()==19 && getpionY()==17)
    {
        salle=8;
    }
    else if(getpionX()==17 && getpionY()==22)
    {
        salle=7;
    }
    else if(getpionX()==9 && getpionY()==18)
    {
        salle=6;
    }
    else if((getpionX()==6 && getpionY()==21) || (getpionX()==2 && getpionY()==18))
    {
        salle=2;
    }
    else if((getpionX()==2 && getpionY()==14) || (getpionX()==6 && getpionY()==9))
    {
        salle=5;
    }
    else
    {
        salle=0;
    }

    return salle;
}

void De::affichageDE(BITMAP *page, int k)
{
    BITMAP *de1;
    BITMAP *de2;
    BITMAP *de3;
    BITMAP *de4;
    BITMAP *de5;
    BITMAP *de6;

    de1=load_bitmap("images/de/1.bmp",NULL);
    de2=load_bitmap("images/de/2.bmp",NULL);
    de3=load_bitmap("images/de/3.bmp",NULL);
    de4=load_bitmap("images/de/4.bmp",NULL);
    de5=load_bitmap("images/de/5.bmp",NULL);
    de6=load_bitmap("images/de/6.bmp",NULL);

    if(getValeur()-k==1)
    {
        draw_sprite(page, de1, 952, 31);
    }
    else if(getValeur()-k==2)
    {
        draw_sprite(page, de2, 952, 31);
    }
    else if(getValeur()-k==3)
    {
        draw_sprite(page, de3, 952, 31);
    }
    else if(getValeur()-k==4)
    {
        draw_sprite(page, de4, 952, 31);
    }
    else if(getValeur()-k==5)
    {
        draw_sprite(page, de5, 952, 31);
    }
    else if(getValeur()-k==6)
    {
        draw_sprite(page, de6, 952, 31);
    }
    else if(getValeur()-k==7)
    {
        draw_sprite(page, de6, 952, 31);
        draw_sprite(page, de1, 992, 31);
    }
    else if(getValeur()-k==8)
    {
        draw_sprite(page, de6, 952, 31);
        draw_sprite(page, de2, 992, 31);
    }
    else if(getValeur()-k==9)
    {
        draw_sprite(page, de6, 952, 31);
        draw_sprite(page, de3, 992, 31);
    }
    else if(getValeur()-k==10)
    {
        draw_sprite(page, de6, 952, 31);
        draw_sprite(page, de4, 992, 31);
    }


    blit(page,screen,0,0,0,0,1200,650);

    destroy_bitmap(de1);
    destroy_bitmap(de2);
    destroy_bitmap(de3);
    destroy_bitmap(de4);
    destroy_bitmap(de5);
    destroy_bitmap(de6);
}

void User::affichageCartes(std::map<int, Carte*> myMap, BITMAP* page)
{
    BITMAP* fond;
    fond=load_bitmap("images/fond.bmp",NULL);

    clear(screen);
    clear(page);
    blit(fond,page,0,0,0,0,SCREEN_W,SCREEN_H);
    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

    for(unsigned long int i=0; i<getHand().size(); i++)
    {
        std::cout<<"JE SUIS LA "<<std::endl;
        BITMAP* img=myMap[getHand()[i]]->getImage();
        stretch_blit(img,fond,0,0,59,88,i*59+200,100,59,88);
        destroy_bitmap(img);
    }

    blit(fond,page,0,0,0,0,SCREEN_W,SCREEN_H);
    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

    rest(2000);

    destroy_bitmap(fond);
}


void User::verifHypo(std::string lieu, std::string arme, std::string suspect, std::vector<User>player, std::map<int, Carte*> cartes, BITMAP* page, unsigned long int joueur)
{
    std::cout << "" <<  std::endl;
    bool verif=false;

    do   //tant qu'un joueur n'a pas montré une carte de son jeu
    {
        if(player.size() == 1)
        {
            for(unsigned long int j=0; j<player[0].getHand().size(); j++)
            {
                std::cout << "" << cartes[player[0].getHand()[j]]->getNom() << std::endl;
                if(j != joueur)
                {
                    //si une des cartes d'un des jeux des joueurs est celle de l'hypothèse du joueur
                    if((cartes[player[0].getHand()[j]]->getNom()== arme || cartes[player[0].getHand()[j]]->getNom()== lieu || cartes[player[0].getHand()[j]]->getNom()== suspect ) &&  verif == false)
                    {
                        textprintf_ex(page,font,60,440,makecol(0,0,0),-1,"CARTE INDICE");
                        BITMAP* img= cartes[player[0].getHand()[j]]->getImage();
                        stretch_blit(img,page,0,0,59,88,75,470,59,88);  //on affichage la carte
                        verif = true;
                    }
                }
            }
        }
        else
        {
            //on parcourt le jeu de tous les joueurs hormis celui qui vient de faire l'hypothèse
            for(unsigned long int i=0; i<player.size(); i++)
            {
                if(i != joueur)
                {
                    for(unsigned long int j=0; j<player[i].getHand().size(); j++)
                    {
                        if(j != joueur)
                        {
                            //si une des cartes d'un des jeux des joueurs est celle de l'hypothèse du joueur
                            if((cartes[player[i].getHand()[j]]->getNom()== arme || cartes[player[i].getHand()[j]]->getNom()== lieu || cartes[player[i].getHand()[j]]->getNom()== suspect ) &&  verif == false)
                            {
                                textprintf_ex(page,font,60,440,makecol(0,0,0),-1,"CARTE INDICE");
                                BITMAP* img= cartes[player[i].getHand()[j]]->getImage();
                                stretch_blit(img,page,0,0,59,88,75,470,59,88);  //on affichage la carte
                                verif = true;

                            }
                            else
                            {

                                 blit(page,screen,0,0,0,0,1200,650);
                            }

                        }
                    }
                }
            }

        }
    }
    while (verif != true);
}


int User::caseMverif()
{
    int caseM;

    if(getpionX()==9  && getpionY()==8)
    {
        caseM=1; //+ relancer de
    }
    else if(getpionX()==7 && getpionY()==2)
    {
        caseM=2; //+
    }
    else if(getpionX()==12 && getpionY()==16)
    {
        caseM=3; //-2
    }
    else if(getpionX()==16 && getpionY()==11)
    {
        caseM=4; //fin du tour
    }
    else if(getpionX()==8 && getpionY()==22)
    {
        caseM=5; //screamer
    }
    else
    {
        caseM=0;
    }

    return caseM;
}
