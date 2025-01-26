// test_couleur.cpp : Seuille une image couleur 

#include <cstdlib>
#include <stdio.h>
#include "image_ppm.h"
#include "codage.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s fonction [options]\n", argv[0]);
        return 1;
    }

    else if (strcmp(argv[1], "seuilPGM") == 0) {
        if (argc < 6) {
            printf("Usage: %s seuilPGM ImageIn.pgm ImageOut.pgm nb_Seuils Seuil1 [Seuil2...]\n", argv[0]);
            return 1;
        }
        int nb_Seuils = atoi(argv[4]);
        if (argc != 5 + nb_Seuils) {
            printf("Usage: %s seuilPGM ImageIn.pgm ImageOut.pgm nb_Seuils Seuil1 [Seuil2...]\n", argv[0]);
            printf("Nombre incorrect de seuils fournis.\n");
            return 1;
        }
        int seuils[nb_Seuils];
        for (int i = 0; i < nb_Seuils; i++) {
            seuils[i] = atoi(argv[5 + i]);
        }

        if (strstr(argv[2], ".pgm") != NULL) {
            seuil_image_pgm(argv[2], argv[3], seuils, nb_Seuils);
        } else {
            printf("Erreur : Le fichier d'entrée n'est pas un fichier PGM.\n");
            return 1;
        }
    }

    else if (strcmp(argv[1], "seuilPPM") == 0) {
        if (argc != 4) {
            printf("Usage: %s seuilPPM ImageIn.ppm ImageOut.ppm \n", argv[0]);
            return 1;
        }
        if (strstr(argv[2], ".ppm") != NULL) {
            seuil_image_ppm(argv[2], argv[3]);
        } else {
            printf("Erreur : Le fichier d'entrée n'est pas un fichier PPM.\n");
            return 1;
        }

    } 
    
    
    else if (strcmp(argv[1], "histogrammePGM") == 0) {
        if (argc != 4) {
            printf("Usage: %s histogrammePGM ImageIn.pgm FichierOut.dat\n", argv[0]);
            return 1;
        }
        histogramme_pgm(argv[2], argv[3]);
    } 
    
    
    else if (strcmp(argv[1], "profilLignePGM") == 0) {
        if (argc != 5) {
            printf("Usage: %s profilLignePGM ImageIn.pgm indice FichierOut.dat\n", argv[0]);
            return 1;
        }
        int indice = atoi(argv[3]);
        profil_ligne_pgm(argv[2], indice, argv[4]);
    } 
    
    
    else if (strcmp(argv[1], "profilColonnePGM") == 0) {
        if (argc != 5) {
            printf("Usage: %s profilColonnePGM ImageIn.pgm indice FichierOut.dat\n", argv[0]);
            return 1;
        }
        int indice = atoi(argv[3]);
        profil_colonne_pgm(argv[2], indice, argv[4]);
    } 
    
    
    else if (strcmp(argv[1], "histogrammePPM") == 0) {
        if (argc != 4) {
            printf("Usage: %s histogrammePPM ImageIn.ppm FichierOut.dat\n", argv[0]);
            return 1;
        }
        histogramme_ppm(argv[2], argv[3]);
    } 
    
    
    else if (strcmp(argv[1], "erosionPGM") == 0 || strcmp(argv[1], "dilatationPGM") == 0 || strcmp(argv[1], "fermeturePGM") == 0 || strcmp(argv[1], "ouverturePGM") == 0) {
        if (argc != 5) {
            printf("Usage: %s %s ImageIn.pgm ImageOut.pgm rayon\n", argv[0], argv[1]);
            return 1;
        }
        int rayon = atoi(argv[4]);
        if (strcmp(argv[1], "erosionPGM") == 0) {
            erosion_pgm(argv[2], argv[3], rayon);
        } else if (strcmp(argv[1], "dilatationPGM") == 0) {
            dilatation_pgm(argv[2], argv[3], rayon);
        } else if (strcmp(argv[1], "fermeturePGM") == 0) {
            fermeture_pgm(argv[2], argv[3], rayon);
        } else if (strcmp(argv[1], "ouverturePGM") == 0) {
            ouverture_pgm(argv[2], argv[3], rayon);
        }
    } 
    
    
    else if (strcmp(argv[1], "differencePGM") == 0) {
        if (argc != 5) {
            printf("Usage: %s differencePGM ImageIn1.pgm ImageIn2.pgm ImageOut.pgm\n", argv[0]);
            return 1;
        }
        difference_pgm(argv[2], argv[3], argv[4]);
    } 
    
    
    else if (strcmp(argv[1], "inversePGM") == 0) {
        if (argc != 4) {
            printf("Usage: %s inversePGM ImageIn.pgm ImageOut.pgm\n", argv[0]);
            return 1;
        }
        inverse_pgm(argv[2], argv[3]);
    } 
    
    
    else if (strcmp(argv[1], "flouterPGM") == 0 || strcmp(argv[1], "flouterPPM") == 0) {
        if (argc != 5) {
            printf("Usage: %s %s ImageIn.pgm/ppm ImageOut.pgm/ppm rayon\n", argv[0], argv[1]);
            return 1;
        }
        int rayon = atoi(argv[4]);
        if (strcmp(argv[1], "flouterPGM") == 0) {
            flouter_image_pgm(argv[2], argv[3], rayon);
        } else if (strcmp(argv[1], "flouterPPM") == 0) {
            flouter_image_ppm(argv[2], argv[3], rayon);
        }
    } 
    
    
    else if (strcmp(argv[1], "normeGradientPGM") == 0 ) {
        if (argc != 6) {
            printf("Usage: %s ImageIn.pgm/ppm ImageOut.pgm/ppm filtreMoyenne(F/V) filtreGauss(F/V)\n", argv[1]);
            return 1;
        } else {
            norme_gradient_pgm(argv[2], argv[3], argv[4], argv[5]);
        }
    } 
    
    
    else if (strcmp(argv[1], "seuilHPGM") == 0 ) {
        if (argc != 6) {
            printf("Usage: %s ImageIn.pgm/ppm ImageOut.pgm/ppm SeuilBas SeuilHaut\n", argv[1]);
            return 1;
        } else {
            seuil_hysteresis_pgm(argv[2], argv[3],atoi(argv[4]), atoi(argv[5]));
        }
    } 
    
    
    else if (strcmp(argv[1], "RGBtoY") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s ImageIn.ppm ImageOut.pgm\n", argv[1]);
            return 1;
        } else {
            RGBtoY(argv[2], argv[3]);
        }
    } 
    
    
    else if (strcmp(argv[1], "calculerEQM") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s ImageIn1.pgm ImageIn2.pgm\n", argv[1]);
            return 1;
        } else {
            printf("EQM : %f",calculerEQM(argv[2], argv[3]));
        }
    } 
    
    
    else if (strcmp(argv[1], "RGBtoYCbCr") == 0 ) {
        if (argc != 3) {
            printf("Usage: %s ImageIn.ppm", argv[1]);
            return 1;
        } else {
            RGBtoYCbCr(argv[2]);
        }
    } 
    
    
    else if (strcmp(argv[1], "YCbCrtoRGB") == 0 ) {
        if (argc != 6) {
            printf("Usage: %s ImageInY.pgm ImageInCb.pgm ImageInCr.pgm ImgOut.ppm", argv[1]);
            return 1;
        } else {
            YCbCrtoRGB(argv[2], argv[3], argv[4], argv[5]);
        }
    } 
    
    
    else if (strcmp(argv[1], "modifY") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s ImageIn.ppm k ImageOut.ppm\n", argv[1]);
            return 1;
        }else if (atoi(argv[3]) > -128 && atoi(argv[3]) < 128) {
            modifY(argv[2], atoi(argv[3]), argv[4]);

        }else {
            printf("k doit etre compris entre -128 et 128");
        }
    } 

    else if (strcmp(argv[1], "k_mean") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s %s ImageIn.ppm ImageOut.ppm ImageOut2.ppm \n", argv[0], argv[1]);
            return 1;
        }else {
            k_mean(argv[2], argv[3], argv[4]);
        }
    
    }

    else if (strcmp(argv[1], "k_mean_256") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s %s ImageIn.ppm ImageOut.ppm \n", argv[0], argv[1]);
            return 1;
        }else {
            k_mean_256(argv[2], argv[3]);
        }
    
    }

    else if (strcmp(argv[1], "k_mean_256_pgm") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s %s ImageIn.ppm ImageOut.pgm \n", argv[0], argv[1]);
            return 1;
        }else {
            k_mean_256_pgm(argv[2], argv[3]);
        }
    
    }

    else if (strcmp(argv[1], "decode_indexed_pgm") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s %s ImageIn.pgm FichierPalette.txt ImageOut.ppm  \n", argv[0], argv[1]);
            return 1;
        }else {
            decode_indexed_pgm(argv[2], argv[3], argv[4]);
        }
    
    }

    else if (strcmp(argv[1], "pnsr") == 0 ) {

        if (argc != 4) {
            printf("Usage: %s %s ImageOriginale.ppm ImageModifie.ppm \n", argv[0], argv[1]);
        }else {
            PSNR(argv[2], argv[3]);
        }
    }
    
    
    else if (strcmp(argv[1], "help") == 0){
        printf("\nVoici la liste des fonctions disponibles :\n\n");

        printf("  seuilPGM        - Appliquer un seuillage a une image PGM.\n");
        printf("  Usage: seuilPGM ImageIn.pgm ImageOut.pgm nb_Seuils Seuil1 [Seuil2...]\n\n");

        printf("  histogrammePGM  - Calculer et ecrire l'histogramme d'une image PGM.\n");
        printf("  Usage: histogrammePGM ImageIn.pgm FichierOut.dat\n\n");

        printf("  histogrammePPM  - Calculer et ecrire l'histogramme d'une image PPM.\n");
        printf("  Usage: histogrammePPM ImageIn.ppm FichierOut.dat\n\n");

        printf("  profilLignePGM  - Extraire et ecrire le profil d'une ligne specifique d'une image PGM.\n");
        printf("  Usage: profilLignePGM ImageIn.pgm indice FichierOut.dat\n\n");
        
        printf("  profilColonnePGM- Extraire et ecrire le profil d'une colonne specifique d'une image PGM.\n");
        printf("  Usage: profilColonnePGM ImageIn.pgm indice FichierOut.dat\n\n");
        
        printf("  erosionPGM      - Appliquer une erosion a une image PGM.\n");
        printf("  Usage: erosionPGM ImageIn.pgm ImageOut.pgm rayon\n\n");
        
        printf("  dilatationPGM   - Appliquer une dilatation a une image PGM.\n");
        printf("  Usage: dilatationPGM ImageIn.pgm ImageOut.pgm rayon\n\n");
        
        printf("  fermeturePGM    - Appliquer une fermeture a une image PGM.\n");
        printf("  Usage: fermeturePGM ImageIn.pgm ImageOut.pgm rayon\n\n");
        
        printf("  ouverturePGM    - Appliquer une ouverture a une image PGM.\n");
        printf("  Usage: ouverturePGM ImageIn.pgm ImageOut.pgm rayon\n\n");
        
        printf("  differencePGM   - Calculer la difference entre deux images PGM.\n");
        printf("  Usage: differencePGM ImageIn1.pgm ImageIn2.pgm ImageOut.pgm\n\n");
        
        printf("  inversePGM      - Inverser les niveaux de gris d'une image PGM.\n");
        printf("  Usage: inversePGM ImageIn.pgm ImageOut.pgm\n\n");
        
        printf("  flouterPGM      - Flouter une image PGM.\n");
        printf("  Usage: flouterPGM ImageIn.pgm ImageOut.pgm rayon\n\n");
        
        printf("  flouterPPM      - Flouter une image PPM.\n");
        printf("  Usage: flouterPPM ImageIn.ppm ImageOut.ppm rayon\n\n");
        return 1;
    }
    
    
    
    
    else if (strcmp(argv[1], "liste") == 0){
        printf("\nVoici la liste des fonctions disponibles :\n\n");

        printf("  seuilPGM        - Appliquer un seuillage a une image PGM.\n");

        printf("  histogrammePGM  - Calculer et ecrire l'histogramme d'une image PGM.\n");

        printf("  profilLignePGM  - Extraire et ecrire le profil d'une ligne specifique d'une image PGM.\n");
        
        printf("  profilColonnePGM- Extraire et ecrire le profil d'une colonne specifique d'une image PGM.\n");
        
        printf("  histogrammePPM  - Calculer et ecrire l'histogramme d'une image PPM.\n");
        
        printf("  erosionPGM      - Appliquer une erosion a une image PGM.\n");
        
        printf("  dilatationPGM   - Appliquer une dilatation a une image PGM.\n");
        
        printf("  fermeturePGM    - Appliquer une fermeture a une image PGM.\n");
        
        printf("  ouverturePGM    - Appliquer une ouverture a une image PGM.\n");
        
        printf("  differencePGM   - Calculer la difference entre deux images PGM.\n");
        
        printf("  inversePGM      - Inverser les niveaux de gris d'une image PGM.\n");
        
        printf("  flouterPGM      - Flouter une image PGM.\n");
        
        printf("  flouterPPM      - Flouter une image PPM.\n");
        printf("  normeGradientPGM   - Trouver les contours d'une image je crois \n");
        printf("  seuilHPGM       - Seuil avec 2 seuils (un haut et un bas donc on a 3 \"couleurs\")\n");
        printf("  RGBtoY          - \n");
        printf("  calculerEQM          - \n");
        printf("  RGBtoYCbCr          - \n");
        printf("  modifY          - \n");
        printf("\n");
        return 1;
    }else{
        printf("Fonction non reconnue.\n");
        return 1;
    }
    

    return 0;
}
