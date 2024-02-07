#include "CasePlateau.h"
#include <time.h>
#include "Menu.h"

//Tout ce qui est en rapport avec la musique et allegro n'appartient pas � des classes
//car ce sont des librairies a part qui ont leurs propres methodes


int main(int argc, char *argv[])
{
    // Graphismes charg�s depuis des fichiers .bmp
    BITMAP *fond = new BITMAP;
    BITMAP *attente;
    /// INITIALISATION ALLEGRO et services
    lancerToutAllegro(1200,650);

    attente=load_bitmap("images/attente.bmp",NULL);
    blit(attente, screen,0,0,0,0,1200,650);

    srand(time(NULL));

    Menu menuP;

    menuP.menuPrincipal();
    destroy_bitmap(attente);
    delete fond;
    return 0;
}
END_OF_MAIN();
