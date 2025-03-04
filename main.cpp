// test_couleur.cpp : Seuille une image couleur 

#include <cstdlib>
#include <stdio.h>
#include "image_ppm.h"
#include "codage.h"
#include "traitement.h"


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

    else if (strcmp(argv[1], "seuil_image_extrema_ppm") == 0) {
        if (argc != 4) {
            printf("Usage: %s histogrammePPM ImageIn.ppm ImageOut.ppm\n", argv[0]);
            return 1;
        }
        seuil_image_extrema_ppm(argv[2], argv[3]);
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
    
    else if (strcmp(argv[1], "differencePPM") == 0) {
        if (argc != 5) {
            printf("Usage: %s differencePGM ImageIn1.ppm ImageIn2.ppm ImageOut.ppm\n", argv[0]);
            return 1;
        }
        difference_ppm(argv[2], argv[3], argv[4]);
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
    else if (strcmp(argv[1], "psnr_ppm") == 0 ) {

        if (argc != 4) {
            printf("Usage: %s %s ImageOriginale.ppm ImageModifie.ppm \n", argv[0], argv[1]);
        }else {
            PSNR_PPM(argv[2], argv[3]);
        }
    }
    else if (strcmp(argv[1], "psnr_pgm") == 0 ) {

        if (argc != 4) {
            printf("Usage: %s %s ImageOriginale.ppm ImageModifie.ppm \n", argv[0], argv[1]);
        }else {
            PSNR_PGM(argv[2], argv[3]);
        }
    }


    else if (strcmp(argv[1], "ex3_tp2") == 0 ) {

        if (argc != 4) {
            printf("Usage: %s %s ImageOriginale.ppm ImageModifie.ppm \n", argv[0], argv[1]);
        }else {
            ex3_tp2(argv[2], argv[3]);
        }
    }

    else if (strcmp(argv[1], "reduce_resample_YCbCr") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s ImageInY.pgm ImageInCb.pgm ImageInCr.pgm", argv[1]);
            return 1;
        } else {
            re_sample_ycbcr(argv[2], argv[3], argv[4]);
        }
    } 

    else if (strcmp(argv[1], "erosionPPM") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s ImageIn.ppm ImageOut.ppm rayon", argv[1]);
            return 1;
        } else {
            erosion_ppm(argv[2], argv[3], atoi(argv[4]));
        }
    } 

    else if (strcmp(argv[1], "dilatationPPM") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s ImageIn.ppm ImageOut.ppm rayon", argv[1]);
            return 1;
        } else {
            dilatation_ppm(argv[2], argv[3], atoi(argv[4]));
        }
    } 
    
    else if (strcmp(argv[1], "fermeturePPM") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s ImageIn.ppm ImageOut.ppm rayon", argv[1]);
            return 1;
        } else {
            fermeture_ppm(argv[2], argv[3], atoi(argv[4]));
        }
    } 

    else if (strcmp(argv[1], "ouverturePPM") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s ImageIn.ppm ImageOut.ppm rayon", argv[1]);
            return 1;
        } else {
            fermeture_ppm(argv[2], argv[3], atoi(argv[4]));
        }
    } 


    else if (strcmp(argv[1], "t1") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s ImageIn.ppm ImageOut.ppm rayon", argv[1]);
            return 1;
        } else {
            traitement1(argv[2], argv[3], atoi(argv[4]));
        }
    } 

    else if (strcmp(argv[1], "t1PPM") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s ImageIn.ppm ImageOut.ppm rayon", argv[1]);
            return 1;
        } else {
            traitement1_ppm(argv[2], argv[3], atoi(argv[4]));
        }
    } 

    else if (strcmp(argv[1], "t2PPM") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s ImageIn.ppm ImageOut.ppm rayon", argv[1]);
            return 1;
        } else {
            traitement2_ppm(argv[2], argv[3], atoi(argv[4]));
        }
    }

    
    else if (strcmp(argv[1], "t2") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s ImageIn.ppm ImageOut.ppm rayon", argv[1]);
            return 1;
        } else {
            traitement2(argv[2], argv[3], atoi(argv[4]));
        }
    } 

    else if (strcmp(argv[1], "difference_map_PGM") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s ImageIn.pgm ImageOut.pgm", argv[1]);
            return 1;
        } else {
            difference_map_pgm(argv[2], argv[3]);
        }
    } 

    else if (strcmp(argv[1], "entropie") == 0 ) {
        if (argc != 3) {
            printf("Usage: %s ImageIn.pgm ", argv[1]);
            return 1;
        } else {
            entropie(argv[2]);
        }
    } 

    else if (strcmp(argv[1], "extension_hist_pgm") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s ImageIn.pgm fichierOut.dat", argv[1]);
            return 1;
        } else {
            extension_histogramme_pgm(argv[2], argv[3]);
        }
    } 

    else if (strcmp(argv[1], "extension_hist_ppm") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s ImageIn.ppm fichierOut.dat", argv[1]);
            return 1;
        } else {
            extension_histogramme_ppm(argv[2], argv[3]);
        }
    } 

    else if (strcmp(argv[1], "ddp_pgm") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s ImageIn.pgm fichierOut.dat", argv[1]);
            return 1;
        } else {
            ddp_pgm(argv[2], argv[3]);
        }
    } 

    else if (strcmp(argv[1], "extension_img_pgm") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s ImageIn.pgm ImgOut.pgm", argv[1]);
            return 1;
        } else {
            extension_img_pgm(argv[2], argv[3]);
        }
    } 

    else if (strcmp(argv[1], "extension_img_ppm") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s ImageIn.ppm ImgOut.ppm", argv[1]);
            return 1;
        } else {
            extension_img_ppm(argv[2], argv[3]);
        }
    } 

    
    else if (strcmp(argv[1], "repartition_pgm") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s ImageIn.ppm fichierOut.ppm", argv[1]);
            return 1;
        } else {
            repartition_pgm(argv[2], argv[3]);
        }
    } 

    else if (strcmp(argv[1], "egalisation_pgm") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s ImageIn.ppm ImgOut.ppm", argv[1]);
            return 1;
        } else {
            egalisation_pgm(argv[2], argv[3]);
        }
    }

    else if (strcmp(argv[1], "transformee_ondelettes_pgm") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s ImageIn.pgm ImgOut.pgm", argv[1]);
            return 1;
        } else {
            transformee_ondelettes_pgm(argv[2], argv[3]);
        }
    }  

    else if (strcmp(argv[1], "transformee_ondelettes_recursive_pgm") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s ImageIn.pgm ImgOut.pgm nbRecursions", argv[1]);
            return 1;
        } else {
            transformee_ondelettes_recursive_pgm(argv[2], argv[3], atoi(argv[4]));
        }
    }  

    else if (strcmp(argv[1], "reconstruire_ondelettes_pgm") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s ImageIn.pgm ImgOut.pgm", argv[1]);
            return 1;
        } else {
            reconstruire_ondelettes_pgm(argv[2], argv[3]);
        }
    }  

    else if (strcmp(argv[1], "reconstruire_ondelettes_recursive_pgm") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s ImageIn.pgm ImgOut.pgm", argv[1]);
            return 1;
        } else {
            reconstruire_ondelettes_recursive_pgm(argv[2], argv[3], atoi(argv[4]));
        }
    }  

    else if (strcmp(argv[1], "reduce_ppm") == 0 ) {
        if (argc != 5) {
            printf("Usage: %s ImageIn.ppm ImgOut.pgm factor", argv[1]);
            return 1;
        } else {
            reduce_ppm(argv[2], argv[3], atoi(argv[4]));
        }
    }  

    else if (strcmp(argv[1], "RGBtoPGM") == 0 ) {
        if (argc != 4) {
            printf("Usage: %s ImageIn.ppm ImgOut.pgm", argv[1]);
            return 1;
        } else {
            RGBtoPGM(argv[2], argv[3]);
        }
    }  

    else if (strcmp(argv[1], "flouter_background_ppm") == 0 ) {
        if (argc != 6) {
            printf("Usage: %s ImageOriginale.ppm ImgSeuillé.pgm imgOut.ppm rayonFlou", argv[1]);
            return 1;
        } else {
            flouter_background_ppm(argv[2], argv[3], argv[4], atoi(argv[5]));
        }
    }  

    else if (strcmp(argv[1], "roc") == 0 ) {
        if (argc != 6) {
            printf("Usage: %s ImageOriginale.pgm ImgSeuilléReference.pgm fichier.dat nbDeSeuils", argv[1]);
            return 1;
        } else {
            roc(argv[2], argv[3], argv[4], atoi(argv[5]));
        }
    } 
    
    else if (strcmp(argv[1], "calculer_metrics") == 0 ) {
        if (argc != 6) {
            printf("Usage: %s ImageOriginale.pgm ImgSeuilléReference.pgm fichier.dat nbDeSeuils", argv[1]);
            return 1;
        } else {
            calculer_metrics(argv[2], argv[3], argv[4], atoi(argv[5]));
        }
    } 

    else if (strcmp(argv[1], "analyse_ondelettes") == 0 ) {
        if (argc != 3) {
            printf("Usage: %s ImageIn.pgm", argv[1]);
            return 1;
        } else {
            analyse_ondelettes_multi_niveaux(argv[2]);
        }
    }

    else if (strcmp(argv[1], "ondelettes_quantifiees") == 0) {
        if (argc != 8) {
            printf("Usage: %s ondelettes_quantifiees image.pgm image_out.pgm QBF QMFh QMFv QHF\n", argv[0]);
            return 1;
        }
        transformee_ondelettes_quantifiee_pgm(argv[2], argv[3], 
                                            atoi(argv[4]), atoi(argv[5]), 
                                            atoi(argv[6]), atoi(argv[7]));
    }

    else if (strcmp(argv[1], "analyse_ondelettes_quantifiees") == 0) {
        if (argc != 7) {
            printf("Usage: %s analyse_ondelettes_quantifiees image.pgm QBF QMFh QMFv QHF\n", argv[0]);
            return 1;
        }
        analyse_ondelettes_quantifiees_multi_niveaux(argv[2], 
                                                    atoi(argv[3]), atoi(argv[4]), 
                                                    atoi(argv[5]), atoi(argv[6]));
    }


    else if (strcmp(argv[1], "debit_distorsion") == 0) {
        if (argc != 3) {
            printf("Usage: %s debit_distorsion image.pgm\n", argv[0]);
            return 1;
        }
        analyse_debit_distorsion(argv[2]);
    }

    else if (strcmp(argv[1], "debit_distorsion_ppm") == 0) {
        if (argc != 3) {
            printf("Usage: %s debit_distorsion_ppm image.ppm\n", argv[0]);
            return 1;
        }
        analyse_debit_distorsion_ppm(argv[2]);
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
