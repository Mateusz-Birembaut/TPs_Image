#include <cstdlib>
#include <math.h>
#include <vector>
#include <iostream>

/* 

plot "BHist.dat" using 1:2 title "Rouge" with lines lw 2 lc rgb "red", \
     "BHist.dat" using 1:3 title "Vert" with lines lw 2 lc rgb "green", \
     "BHist.dat" using 1:4 title "Bleu" with lines lw 2 lc rgb "blue"

plot "BHist_base.dat" using 1:2 title "Rouge" with lines lw 2 lc rgb "red", \
     "BHist_base.dat" using 1:3 title "Vert" with lines lw 2 lc rgb "green", \
     "BHist_base.dat" using 1:4 title "Bleu" with lines lw 2 lc rgb "blue"

     plot "lenaS_egal.dat" using 1:2 title "Rouge" with lines lw 2 lc rgb "red", \
     "lenaS_egal.dat" using 1:3 title "Vert" with lines lw 2 lc rgb "green", \
     "lenaS_egal.dat" using 1:4 title "Bleu" with lines lw 2 lc rgb "blue"

 */

void extension_histogramme_pgm(char cNomImgLue[250], char cNomFichierEcrit[250]){
    int nH, nW, nTaille;
    OCTET *ImgIn;
   
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
  
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    
    int histogramme[256] = {0};
    int min = ImgIn[0];
    int max = ImgIn[0];
    for (int i = 0; i < nTaille; i++) {
        if (ImgIn[i] > max) {
            max = ImgIn[i];
        }
        if (ImgIn[i] < min) {
            min = ImgIn[i];
        }
    }

    double d = -(255.0 *min) / (max - min);
    double g = 255.0 / (max -min);

    std::cout <<  "Alpha : "<<d << std::endl;
    std::cout << "Beta : " << g << std::endl;

    for (int i = 0; i < nTaille; i++) {
        int indexH = ImgIn[i]*g + d;
        histogramme[indexH]++;
    }


    ecrire_histogramme_pgm(cNomFichierEcrit, histogramme, 256);
    free(ImgIn);
}

void extension_img_pgm(char cNomImgLue[250], char cNomFichierEcrit[250]){
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;
   
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
  
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);

    allocation_tableau(ImgOut, OCTET, nTaille);
    
    int min = ImgIn[0];
    int max = ImgIn[0];
    for (int i = 0; i < nTaille; i++) {
        if (ImgIn[i] > max) {
            max = ImgIn[i];
        }
        if (ImgIn[i] < min) {
            min = ImgIn[i];
        }
    }

    double d = -(255.0 *min) / (max - min);
    double g = 255.0 / (max -min);

    std::cout <<  "Alpha : "<<d << std::endl;
    std::cout << "Beta : " << g << std::endl;

    for (int i = 0; i < nTaille; i++) {
        ImgOut[i] = ImgIn[i]*g + d;
    }


    ecrire_image_pgm(cNomFichierEcrit, ImgOut, nH, nW);
    free(ImgIn);
}

void extension_histogramme_ppm(char cNomImgLue[250], char cNomFichierEcrit[250]) {
    int nH, nW, nTaille;
    OCTET *ImgIn;
   
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW * 3;
  
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_ppm(cNomImgLue, ImgIn, nTaille / 3);

    int histogramme[3][256] = {{0}};
    int min [3] = {ImgIn[0], ImgIn[1], ImgIn[2]}; 
    int max [3] = {ImgIn[0], ImgIn[1], ImgIn[2]}; 
	
    for (int i = 0; i < nTaille; i += 3) {
        if (ImgIn[i] < min[0]) {
            min[0] = ImgIn[i];
        }
        if (ImgIn[i+1] < min[1]) {
            min[1] = ImgIn[i+1];
        }
        if (ImgIn[i+2] < min[2]) {
            min[2] = ImgIn[i+2];
        }

        if (ImgIn[i] > max[0]) {
            max[0] = ImgIn[i];
        }
        if (ImgIn[i+1] > max[1]) {
            max[1] = ImgIn[i+1];
        }
        if (ImgIn[i+2] > max[2]) {
            max[2] = ImgIn[i+2];
        }
    }

    double d_r = -(255.0 *min[0]) / (max[0] - min[0]);
    double g_r = 255.0 / (max[0] -min[0]);

    std::cout << "Alpha R : " << d_r << std::endl;
    std::cout << "Beta R : " << g_r << std::endl;


    double d_v = -(255.0 *min[1]) / (max[1] - min[1]);
    double g_v = 255.0 / (max[1] -min[1]);

    std::cout << "Alpha V : " << d_v << std::endl;
    std::cout << "Beta V : " << g_v << std::endl;


    double d_b = -(255.0 *min[2]) / (max[2] - min[2]);
    double g_b = 255.0 / (max[2] -min[2]);

    std::cout << "Alpha B : " << d_b << std::endl;
    std::cout << "Beta B : " << g_b << std::endl;


    for (int i = 0; i < nTaille; i+=3) {
        int indexR = ImgIn[i]*g_r + d_r;
        int indexV = ImgIn[i+1]*g_v + d_v;
        int indexB = ImgIn[i+2]*g_b + d_b;

        histogramme[0][indexR]++;
        histogramme[1][indexV]++;
        histogramme[2][indexB]++;
    }

    ecrire_histogramme_ppm(cNomFichierEcrit, histogramme, 256);
    free(ImgIn);
}

void extension_img_ppm(char cNomImgLue[250], char cNomFichierEcrit[250]){
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;
   
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW * 3;
  
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_ppm(cNomImgLue, ImgIn, nTaille / 3);

    allocation_tableau(ImgOut, OCTET, nTaille);

    
int min [3] = {ImgIn[0], ImgIn[1], ImgIn[2]}; 
    int max [3] = {ImgIn[0], ImgIn[1], ImgIn[2]}; 
	
    for (int i = 0; i < nTaille; i += 3) {
        if (ImgIn[i] < min[0]) {
            min[0] = ImgIn[i];
        }
        if (ImgIn[i+1] < min[1]) {
            min[1] = ImgIn[i+1];
        }
        if (ImgIn[i+2] < min[2]) {
            min[2] = ImgIn[i+2];
        }

        if (ImgIn[i] > max[0]) {
            max[0] = ImgIn[i];
        }
        if (ImgIn[i+1] > max[1]) {
            max[1] = ImgIn[i+1];
        }
        if (ImgIn[i+2] > max[2]) {
            max[2] = ImgIn[i+2];
        }
    }

    double d_r = -(255.0 *min[0]) / (max[0] - min[0]);
    double g_r = 255.0 / (max[0] -min[0]);

    std::cout << "Alpha R : " << d_r << std::endl;
    std::cout << "Beta R : " << g_r << std::endl;


    double d_v = -(255.0 *min[1]) / (max[1] - min[1]);
    double g_v = 255.0 / (max[1] -min[1]);

    std::cout << "Alpha V : " << d_v << std::endl;
    std::cout << "Beta V : " << g_v << std::endl;


    double d_b = -(255.0 *min[2]) / (max[2] - min[2]);
    double g_b = 255.0 / (max[2] -min[2]);

    std::cout << "Alpha B : " << d_b << std::endl;
    std::cout << "Beta B : " << g_b << std::endl;


    for (int i = 0; i < nTaille; i+=3) {
        ImgOut[i] = ImgIn[i]*g_r + d_r;
        ImgOut[i+1] = ImgIn[i+1]*g_v + d_v;
        ImgOut[i+2] = ImgIn[i+2]*g_b + d_b;
    }

    ecrire_image_ppm(cNomFichierEcrit, ImgOut, nH, nW);
    free(ImgIn);
}

void ecrire_index_float_pgm(char nom_fichier[250], float valeurs[], int taille_valeurs){
    FILE *fichier;
    
    if ((fichier = fopen(nom_fichier, "w")) == NULL) {
        printf("\nPas d'acces en ecriture sur le fichier %s \n", nom_fichier);
        exit(EXIT_FAILURE);
    } else {
        for (int i = 0; i < taille_valeurs; i++) {
            fprintf(fichier, "%d %f\n", i, valeurs[i]);
        }

        fclose(fichier);
    }
}

void ddp_pgm(char cNomImgLue[250], char cNomFichierEcrit[250]){
    int nH, nW, nTaille;
    OCTET *ImgIn;
   
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
  
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);

    float valeurs[256] = {0};
    for (int i = 0; i < nTaille; i++) {
        valeurs[ImgIn[i]]++;
    }

    for (int i=0; i < 256; i++) {
        valeurs[i] = valeurs[i] / nTaille;
    }

    ecrire_index_float_pgm(cNomFichierEcrit, valeurs, 256);
    free(ImgIn);
}

void sommePrefixe(float * valeurs, int taille_valeurs){
    for (int i = 1; i<taille_valeurs; i++) {
        valeurs[i] = valeurs[i]+valeurs[i-1];
    }
}

void repartition_pgm (char cNomImgLue[250], char cNomFichierEcrit[250]){
    int nH, nW, nTaille;
    OCTET *ImgIn;
   
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
  
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);

    float valeurs[256] = {0};
    for (int i = 0; i < nTaille; i++) {
        valeurs[ImgIn[i]]++;
    }

    for (int i=0; i < 256; i++) {
        valeurs[i] = valeurs[i] / nTaille;
    }

    sommePrefixe(valeurs, 256);

    ecrire_index_float_pgm(cNomFichierEcrit, valeurs, 256);
    free(ImgIn);
}

void egalisation_pgm (char cNomImgLue[250], char cNomImgEcrit[250]){
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;
   
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
  
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);

    allocation_tableau(ImgOut, OCTET, nTaille);

    float valeurs[256] = {0};
    for (int i = 0; i < nTaille; i++) {
        valeurs[ImgIn[i]]++;
    }

    for (int i=0; i < 256; i++) {
        valeurs[i] = valeurs[i] / nTaille;
    }

    sommePrefixe(valeurs, 256);

    for (int i = 0; i < nTaille; i++) {
        ImgOut[i] = 255 * valeurs[ImgIn[i]];
    }


    ecrire_image_pgm(cNomImgEcrit, ImgOut, nH, nW);
    free(ImgIn);
}

void seuillage_extrema(OCTET *Plan, int nTaille, int sMin, int sMax) {
    for (int i = 0; i < nTaille; i++) {
        if (Plan[i] < sMin) {
            Plan[i] = sMin;
        } else if (Plan[i] > sMax) {
            Plan[i] = sMax;
        }
    }
}

/* Entrez le seuil min et max pour la composante Rouge : 40
225
Entrez le seuil min et max pour la composante Verte : 25
175
Entrez le seuil min et max pour la composante Bleue : 25
150 */

void seuil_image_extrema_ppm(char cNomImgLue[250], char cNomImgEcrite[250]) {
    int nH, nW, nTaille;
    int nTaille3;
    
    OCTET *ImgIn, *ImgOut, *PlanR, *PlanV, *PlanB;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    nTaille3 = nTaille * 3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nTaille);

    allocation_tableau(PlanR, OCTET, nTaille);
    planR(PlanR, ImgIn, nTaille);

    allocation_tableau(PlanV, OCTET, nTaille);
    planV(PlanV, ImgIn, nTaille);

    allocation_tableau(PlanB, OCTET, nTaille);
    planB(PlanB, ImgIn, nTaille);

    int sMinR, sMaxR, sMinV, sMaxV, sMinB, sMaxB;
    
    printf("Entrez le seuil min et max pour la composante Rouge : ");
    scanf("%d %d", &sMinR, &sMaxR);
    
    printf("Entrez le seuil min et max pour la composante Verte : ");
    scanf("%d %d", &sMinV, &sMaxV);
    
    printf("Entrez le seuil min et max pour la composante Bleue : ");
    scanf("%d %d", &sMinB, &sMaxB);

    // Appliquer le seuillage aux trois composantes
    seuillage_extrema(PlanR, nTaille, sMinR, sMaxR);
    seuillage_extrema(PlanV, nTaille, sMinV, sMaxV);
    seuillage_extrema(PlanB, nTaille, sMinB, sMaxB);

    // Allocation de l'image de sortie
    allocation_tableau(ImgOut, OCTET, nTaille3);
    for (int i = 0; i < nTaille; i++) {
        ImgOut[i*3] = PlanR[i];
        ImgOut[i*3+1] = PlanV[i];
        ImgOut[i*3+2] = PlanB[i];
    }

    // Écriture de l'image de sortie
    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);

    // Libération de la mémoire
    free(ImgIn); free(ImgOut); free(PlanR); free(PlanV); free(PlanB);
}


