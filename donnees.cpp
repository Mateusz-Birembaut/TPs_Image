#include "donnees.h"

int getValeurMoyenne(ImageBase &image, int ligne, int colonne, int rayon) {
    int moyenne = 0;
    int nb_voisins = 0;
    int nW = image.getWidth();
    int nH = image.getHeight();
    
    for (int i = -rayon; i <= rayon; i++) {
        for (int j = -rayon; j <= rayon; j++) {
            int voisinLigne = ligne + i;
            int voisinColonne = colonne + j;
            
            if (voisinLigne >= 0 && voisinLigne < nH && voisinColonne >= 0 && voisinColonne < nW) {
                moyenne = moyenne + image[voisinLigne][voisinColonne];
                nb_voisins++;
            }
        }
    }
    return moyenne / nb_voisins;
}

int getCouleurMinimal(ImageBase &image, int ligne, int colonne, int rayon) {
    int minimum = image[ligne][colonne];
    int nW = image.getWidth();
    int nH = image.getHeight();
    
    for (int i = -rayon; i <= rayon; i++) {
        for (int j = -rayon; j <= rayon; j++) {
            int voisinLigne = ligne + i;
            int voisinColonne = colonne + j;
            if (voisinLigne >= 0 && voisinLigne < nH && voisinColonne >= 0 && voisinColonne < nW) {
                int valeurVoisin = image[voisinLigne][voisinColonne];
                if (valeurVoisin < minimum) {
                    minimum = valeurVoisin;
                }
            }
        }
    }
    return minimum;
}

int getCouleurMaximal(ImageBase &image, int ligne, int colonne, int rayon) {
    int maximum = image[ligne][colonne];
    int nW = image.getWidth();
    int nH = image.getHeight();
    
    for (int i = -rayon; i <= rayon; i++) {
        for (int j = -rayon; j <= rayon; j++) {
            int voisinLigne = ligne + i;
            int voisinColonne = colonne + j;
            if (voisinLigne >= 0 && voisinLigne < nH && voisinColonne >= 0 && voisinColonne < nW) {
                int valeurVoisin = image[voisinLigne][voisinColonne];
                if (valeurVoisin > maximum) {
                    maximum = valeurVoisin;
                }
            }
        }
    }
    return maximum;
}

int getPixelValueWithMirrorPadding(ImageBase &image, int ligne, int colonne) {
    int nW = image.getWidth();
    int nH = image.getHeight();
    
    if (ligne < 0) ligne = -ligne;
    else if (ligne >= nH) ligne = 2 * nH - ligne - 1;
    if (colonne < 0) colonne = -colonne;
    else if (colonne >= nW) colonne = 2 * nW - colonne - 1;

    return image[ligne][colonne];
}

int getNormeGradient(ImageBase &image, int ligne, int colonne, int rayon, int masqueHorizontal[], int masqueVertical[]) {
    int gradientHorizontal = 0;
    int gradientVertical = 0;
    int nW = image.getWidth();
    int nH = image.getHeight();
    
    for (int i = -rayon; i <= rayon; i++) {
        for (int j = -rayon; j <= rayon; j++) {
            int voisinLigne = ligne + i;
            int voisinColonne = colonne + j;
            if (voisinLigne >= 0 && voisinLigne < nH && voisinColonne >= 0 && voisinColonne < nW) {
                int valeurVoisin = image[voisinLigne][voisinColonne];
                gradientHorizontal += valeurVoisin * masqueHorizontal[(i + rayon) * 3 + (j + rayon)];
                gradientVertical += valeurVoisin * masqueVertical[(i + rayon) * 3 + (j + rayon)];
            }
        }
    }
    return sqrt(pow(gradientHorizontal, 2) + pow(gradientVertical, 2));
}

int checkVoisinsHysteresis(ImageBase &image, int ligne, int colonne, int rayon, int seuilBas, int seuilHaut) {
    int valeur = image[ligne][colonne];
    int nW = image.getWidth();
    int nH = image.getHeight();
    
    if (valeur > seuilBas && valeur < seuilHaut) {
        for (int i = -rayon; i <= rayon; i++) {
            for (int j = -rayon; j <= rayon; j++) {
                int voisinLigne = ligne + i;
                int voisinColonne = colonne + j;
                if (voisinLigne >= 0 && voisinLigne < nH && voisinColonne >= 0 && voisinColonne < nW) {
                    int valeurVoisin = image[voisinLigne][voisinColonne];
                    if (valeurVoisin == 255) {
                        return 255;
                    }
                }
            }
        }
        return 0;
    }
    return valeur;
}

int checkVoisinsHysteresisV2(ImageBase &image, int ligne, int colonne, int rayon, int seuilBas, int seuilHaut) {
    int valeur = image[ligne][colonne];
    int nW = image.getWidth();
    int nH = image.getHeight();
    
    if (valeur > seuilBas && valeur < seuilHaut) {
        for (int i = -rayon; i <= rayon; i++) {
            for (int j = -rayon; j <= rayon; j++) {
                int voisinLigne = ligne + i;
                int voisinColonne = colonne + j;
                if (voisinLigne >= 0 && voisinLigne < nH && voisinColonne >= 0 && voisinColonne < nW) {
                    int valeurVoisin = image[voisinLigne][voisinColonne];
                    if (valeurVoisin == 255) {
                        return 255;
                    }
                }
            }
        }
        return 0;
    }
    return valeur;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int getValeurMediane(ImageBase &image, int ligne, int colonne, int rayon) {
    int voisins[(2 * rayon + 1) * (2 * rayon + 1)];
    int compteur = 0;
    int nW = image.getWidth();
    int nH = image.getHeight();
    
    for (int i = -rayon; i <= rayon; i++) {
        for (int j = -rayon; j <= rayon; j++) {
            int voisinLigne = ligne + i;
            int voisinColonne = colonne + j;
            if (voisinLigne >= 0 && voisinLigne < nH && voisinColonne >= 0 && voisinColonne < nW) {
                voisins[compteur] = image[voisinLigne][voisinColonne];
                compteur++;
            }
        }
    }
    qsort(voisins, compteur, sizeof(int), compare);

    if (compteur % 2 == 0) {
        return (voisins[compteur / 2 - 1] + voisins[compteur / 2]) / 2;
    } else {
        return voisins[compteur / 2];
    }
}

void filtreMoyenneurPGM(ImageBase &image, int rayon) {
    int nTaille = image.getTotalSize();
    int nW = image.getWidth();
    int nH = image.getHeight();

    ImageBase ImgOut(nW, nH, false);

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[i][j] = getValeurMediane(image, i, j, rayon);
        }
    }

    for (int i = 0; i < nTaille; i++) {
        image.getData()[i] = ImgOut.getData()[i];
    }
}

int getValeurGauss(ImageBase &image, int ligne, int colonne, int rayon) {
    int masqueGauss[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
    int value = 0;
    int sommeMasque = 0;
    int nW = image.getWidth();
    int nH = image.getHeight();

    for (int i = -rayon; i <= rayon; i++) {
        for (int j = -rayon; j <= rayon; j++) {
            int voisinLigne = ligne + i;
            int voisinColonne = colonne + j;
            if (voisinLigne >= 0 && voisinLigne < nH && voisinColonne >= 0 && voisinColonne < nW) {
                value += (image[voisinLigne][voisinColonne] * masqueGauss[(i + rayon) * 3 + (j + rayon)]);
                sommeMasque += masqueGauss[(i + rayon) * (2 * rayon + 1) + (j + rayon)];
            }
        }
    }

    if (sommeMasque != 0) {
        value /= sommeMasque;
    }

    return value;
}

void filtreGaussienPGM(ImageBase &image, int rayon) {
    int nTaille = image.getTotalSize();
    int nW = image.getWidth();
    int nH = image.getHeight();

    ImageBase ImgOut(nW, nH, false);

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[i][j] = getValeurGauss(image, i, j, rayon);
        }
    }

    for (int i = 0; i < nTaille; i++) {
        image.getData()[i] = ImgOut.getData()[i];
    }
}

OCTET clamp(double valeur) {
    if (valeur < 0) return 0;
    if (valeur > 255) return 255;
    return (OCTET)valeur;
}


// ------------------------------------- TP 1 -------------------------------------


void seuil_image_pgm(char cNomImgLue[250], char cNomImgEcrite[250], int seuils[], int nb_Seuils) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgLue);
    int nH = ImgIn.getHeight();
    int nW = ImgIn.getWidth();
    int nTaille = nH * nW;

    ImageBase ImgOut(nW, nH, false);

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            int lvl = 0;
            for (int k = 0; k < nb_Seuils; k++) {
                if (ImgIn[i][j] >= seuils[k]) {
                    lvl++;
                }
            }
            ImgOut[i][j] = lvl * (255 / nb_Seuils);
        }
    }

    ImgOut.save(cNomImgEcrite);
}

void seuil_image_ppm(char cNomImgLue[250], char cNomImgEcrite[250]) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgLue);
    int nH = ImgIn.getHeight();
    int nW = ImgIn.getWidth();
    int nTaille = nH * nW;

    ImageBase PlanR(nW, nH, false);
    ImageBase PlanV(nW, nH, false);
    ImageBase PlanB(nW, nH, false);

    ImageBase* PlanR_ptr = ImgIn.getPlan(ImageBase::PLAN_R);
    ImageBase* PlanV_ptr = ImgIn.getPlan(ImageBase::PLAN_G);
    ImageBase* PlanB_ptr = ImgIn.getPlan(ImageBase::PLAN_B);

    PlanR = *PlanR_ptr;
    PlanV = *PlanV_ptr;
    PlanB = *PlanB_ptr;

    delete PlanR_ptr;
    delete PlanV_ptr;
    delete PlanB_ptr;

    int nb_SeuilsR, nb_SeuilsV, nb_SeuilsB;
    printf("Entrez le nombre de seuils pour la composante Rouge (0 pour pas de seuil) : ");
    scanf("%d", &nb_SeuilsR);

    printf("Entrez le nombre de seuils pour la composante Verte (0 pour pas de seuil) : ");
    scanf("%d", &nb_SeuilsV);

    printf("Entrez le nombre de seuils pour la composante Bleue (0 pour pas de seuil) : ");
    scanf("%d", &nb_SeuilsB);

    int *seuilsR = NULL, *seuilsV = NULL, *seuilsB = NULL;

    if (nb_SeuilsR > 0) {
        seuilsR = (int *)malloc(nb_SeuilsR * sizeof(int));
        printf("Entrez les seuils pour la composante Rouge :\n");
        for (int i = 0; i < nb_SeuilsR; i++) {
            printf("Seuil %d : ", i + 1);
            scanf("%d", &seuilsR[i]);
        }
    }

    if (nb_SeuilsV > 0) {
        seuilsV = (int *)malloc(nb_SeuilsV * sizeof(int));
        printf("Entrez les seuils pour la composante Verte :\n");
        for (int i = 0; i < nb_SeuilsV; i++) {
            printf("Seuil %d : ", i + 1);
            scanf("%d", &seuilsV[i]);
        }
    }

    if (nb_SeuilsB > 0) {
        seuilsB = (int *)malloc(nb_SeuilsB * sizeof(int));
        printf("Entrez les seuils pour la composante Bleue :\n");
        for (int i = 0; i < nb_SeuilsB; i++) {
            printf("Seuil %d : ", i + 1);
            scanf("%d", &seuilsB[i]);
        }
    }

    for (int i = 0; i < nTaille; i++) {
        if (nb_SeuilsR > 0) {
            int lvlR = 0;
            for (int k = 0; k < nb_SeuilsR; k++) {
                if (PlanR.getData()[i] >= seuilsR[k]) {
                    lvlR++;
                }
            }
            PlanR.getData()[i] = lvlR * (255 / nb_SeuilsR);
        }

        if (nb_SeuilsV > 0) {
            int lvlV = 0;
            for (int k = 0; k < nb_SeuilsV; k++) {
                if (PlanV.getData()[i] >= seuilsV[k]) {
                    lvlV++;
                }
            }
            PlanV.getData()[i] = lvlV * (255 / nb_SeuilsV);
        }

        if (nb_SeuilsB > 0) {
            int lvlB = 0;
            for (int k = 0; k < nb_SeuilsB; k++) {
                if (PlanB.getData()[i] >= seuilsB[k]) {
                    lvlB++;
                }
            }
            PlanB.getData()[i] = lvlB * (255 / nb_SeuilsB);
        }
    }

    ImageBase ImgOut(nW, nH, true);
    for (int i = 0; i < nTaille; i++) {
        ImgOut.getData()[i * 3] = PlanR.getData()[i];
        ImgOut.getData()[i * 3 + 1] = PlanV.getData()[i];
        ImgOut.getData()[i * 3 + 2] = PlanB.getData()[i];
    }

    ImgOut.save(cNomImgEcrite);

    if (seuilsR) free(seuilsR);
    if (seuilsV) free(seuilsV);
    if (seuilsB) free(seuilsB);
}

void ecrire_histogramme_pgm(char nom_fichier[250], int histogramme[], int taille_histogramme) {
    FILE *fichier;
    
    if ((fichier = fopen(nom_fichier, "w")) == NULL) {
        printf("\nPas d'acces en ecriture sur le fichier %s \n", nom_fichier);
        exit(EXIT_FAILURE);
    } else {
        fprintf(fichier, "%s %s\n", "Indice", "Niveau Gris");
        for (int i = 0; i < taille_histogramme; i++) {
            fprintf(fichier, "%d %d\n", i, histogramme[i]);
        }

        fclose(fichier);
    }
}

void histogramme_pgm(char cNomImgLue[250], char cNomFichierEcrit[250]) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgLue);
    int nTaille = ImgIn.getTotalSize();
    
    int histogramme[256] = {0};
    for (int i = 0; i < nTaille; i++) {
        histogramme[ImgIn.getData()[i]]++;
    }

    ecrire_histogramme_pgm(cNomFichierEcrit, histogramme, 256);
}

void ecrire_profil(const char* nom_fichier, int profil[], int tailleProfil) {
    FILE *fichier;
    
    if ((fichier = fopen(nom_fichier, "w")) == NULL) {
        printf("\nPas d'accès en écriture sur le fichier %s \n", nom_fichier);
        exit(EXIT_FAILURE);
    } else {
        for (int i = 0; i < tailleProfil; i++) {
            fprintf(fichier, "%d %d\n", i, profil[i]);
        }
        fclose(fichier);
    }
}

void profil_ligne_pgm(char cNomImgLue[250], int indice, char cNomFichierEcrit[250]) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgLue);
    int nW = ImgIn.getWidth();
    
    int profil[nW];
    for (int i = 0; i < nW; i++) {
        profil[i] = ImgIn[indice][i];
    }
    ecrire_profil(cNomFichierEcrit, profil, nW);
}

void profil_colonne_pgm(char cNomImgLue[250], int indice, char cNomFichierEcrit[250]) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgLue);
    int nH = ImgIn.getHeight();
    
    int profil[nH];
    for (int i = 0; i < nH; i++) {
        profil[i] = ImgIn[i][indice];
    }
    ecrire_profil(cNomFichierEcrit, profil, nH);
}

void ecrire_histogramme_ppm(const char* nom_fichier, int histogramme[][256], int taille_histogramme) {
    FILE *fichier;
    
    if ((fichier = fopen(nom_fichier, "w")) == NULL) {
        printf("\nPas d'accès en écriture sur le fichier %s \n", nom_fichier);
        exit(EXIT_FAILURE);
    } else {
        fprintf(fichier, "Indice R G B\n");
        for (int i = 0; i < taille_histogramme; i++) {
            fprintf(fichier, "%d %d %d %d\n", i, histogramme[0][i], histogramme[1][i], histogramme[2][i]);
        }
        fclose(fichier);
    }
}

void histogramme_ppm(char cNomImgLue[250], char cNomFichierEcrit[250]) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgLue);
    int nTaille = ImgIn.getTotalSize();
    
    int histogramme[3][256] = {{0}};
    for (int i = 0; i < nTaille; i += 3) {
        histogramme[0][ImgIn.getData()[i]]++;
        histogramme[1][ImgIn.getData()[i + 1]]++;
        histogramme[2][ImgIn.getData()[i + 2]]++;
    }

    ecrire_histogramme_ppm(cNomFichierEcrit, histogramme, 256);
}


// ------------------------------------- TP 2 -------------------------------------

void erosion_pgm(char cNomImgLue[250], char cNomImgEcrite[250], int rayon) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgLue);
    int nH = ImgIn.getHeight();
    int nW = ImgIn.getWidth();

    ImageBase ImgOut(nW, nH, false);

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[i][j] = getCouleurMinimal(ImgIn, i, j, rayon);
        }
    }

    ImgOut.save(cNomImgEcrite);
}

void dilatation_pgm(char cNomImgLue[250], char cNomImgEcrite[250], int rayon) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgLue);
    int nH = ImgIn.getHeight();
    int nW = ImgIn.getWidth();

    ImageBase ImgOut(nW, nH, false);

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[i][j] = getCouleurMaximal(ImgIn, i, j, rayon);
        }
    }

    ImgOut.save(cNomImgEcrite);
}

void fermeture_pgm(char cNomImgLue[250], char cNomImgEcrite[250], int rayon) {
    char cNomImgTemp[250] = "temp.pgm"; // Nom temporaire pour le fichier intermédiaire

    // Appliquer l'érosion, puis la dilatation sur l'image
    erosion_pgm(cNomImgLue, cNomImgTemp, rayon); // Érosion et sauvegarde dans un fichier temporaire
    dilatation_pgm(cNomImgTemp, cNomImgEcrite, rayon); // Dilatation du résultat de l'érosion et sauvegarde dans le fichier final

    remove(cNomImgTemp); 
}

void ouverture_pgm(char cNomImgLue[250], char cNomImgEcrite[250], int rayon) {
    char cNomImgTemp[250] = "temp.pgm"; // Nom temporaire pour le fichier intermédiaire

    // Appliquer la dilatation sur l'image, puis l'érosion
    dilatation_pgm(cNomImgLue, cNomImgTemp, rayon); // Dilatation et sauvegarde dans un fichier temporaire
    erosion_pgm(cNomImgTemp, cNomImgEcrite, rayon); // Érosion et sauvegarde dans le fichier final

    remove(cNomImgTemp); 
}

void difference_pgm(char cNomImgLue1[250], char cNomImgLue2[250], char cNomImgEcrite[250]) {
    ImageBase ImgIn1, ImgIn2;
    ImgIn1.load(cNomImgLue1);
    ImgIn2.load(cNomImgLue2);
    int nH = ImgIn1.getHeight();
    int nW = ImgIn1.getWidth();

    ImageBase ImgOut(nW, nH, false);

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[i][j] = abs(ImgIn2[i][j] - ImgIn1[i][j]);
        }
    }

    ImgOut.save(cNomImgEcrite);
}

// ------------------------------------- TP 3 -------------------------------------

void inverse_pgm(char cNomImgLue[250], char cNomImgEcrite[250]) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgLue);
    int nH = ImgIn.getHeight();
    int nW = ImgIn.getWidth();

    ImageBase ImgOut(nW, nH, false);

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[i][j] = 255 - ImgIn[i][j];
        }
    }

    ImgOut.save(cNomImgEcrite);
}

void flouter_image(ImageBase &image, int rayon) {
    int nH = image.getHeight();
    int nW = image.getWidth();
    int nTaille = nH * nW;

    ImageBase ImgOut(nW, nH, false);

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[i][j] = getValeurMoyenne(image, i, j, rayon);
        }
    }

    for (int i = 0; i < nTaille; i++) {
        image.getData()[i] = ImgOut.getData()[i];
    }
}

void flouter_image_pgm(char cNomImgLue[250], char cNomImgEcrite[250], int rayon) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgLue);
    flouter_image(ImgIn, rayon);
    ImgIn.save(cNomImgEcrite);
}

void flouter_image_ppm(char cNomImgLue[250], char cNomImgEcrite[250], int rayon) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgLue);
    int nH = ImgIn.getHeight();
    int nW = ImgIn.getWidth();
    int nTaille = nH * nW;

    ImageBase *PlanR = ImgIn.getPlan(ImageBase::PLAN_R);
    ImageBase *PlanV = ImgIn.getPlan(ImageBase::PLAN_G);
    ImageBase *PlanB = ImgIn.getPlan(ImageBase::PLAN_B);

    flouter_image(*PlanR, rayon);
    flouter_image(*PlanV, rayon);
    flouter_image(*PlanB, rayon);

    ImageBase ImgOut(nW, nH, true);
    for (int i = 0; i < nTaille; i++) {
        ImgOut.getData()[i * 3] = PlanR->getData()[i];
        ImgOut.getData()[i * 3 + 1] = PlanV->getData()[i];
        ImgOut.getData()[i * 3 + 2] = PlanB->getData()[i];
    }

    ImgOut.save(cNomImgEcrite);

    delete PlanR;
    delete PlanV;
    delete PlanB;
}


// ------------------------------------- TP 4 -------------------------------------


void norme_gradient_pgm(char cNomImgLue[250], char cNomImgEcrite[250], char* filtreMoyenne, char* filtreGauss) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgLue);
    int nH = ImgIn.getHeight();
    int nW = ImgIn.getWidth();

    ImageBase ImgOut(nW, nH, false);

/*     int masqueHorizontal[] = {-1, 0, 1,
                              -2, 0, 2,
                              -1, 0, 1};

    int masqueVertical[] = {-1, -2, 1,
                            0, 0, 0,
                            1, 2, 1}; */

    // appliquer filtre moyenneur
    if (strcmp(filtreMoyenne, "V") == 0) {
        filtreMoyenneurPGM(ImgIn, 1);
    }
    // appliquer filtre gaussien
    if (strcmp(filtreGauss, "V") == 0) {
        filtreGaussienPGM(ImgIn, 1);
    }

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            int diffY = 0;
            int diffX = 0;

            if (j < nW - 1) {
                diffX = ImgIn[i][j + 1] - ImgIn[i][j];
            }
            if (i < nH - 1) {
                diffY = ImgIn[i + 1][j] - ImgIn[i][j];
            }
            int res = sqrt(pow(diffX, 2) + pow(diffY, 2));
            ImgOut[i][j] = clamp(res);
        }
    }

    ImgOut.save(cNomImgEcrite);
}

void seuil_hysteresis_pgm(char cNomImgLue[250], char cNomImgEcrite[250], int seuilBas, int seuilHaut) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgLue);
    int nH = ImgIn.getHeight();
    int nW = ImgIn.getWidth();

    ImageBase ImgTemp(nW, nH, false);
    ImageBase ImgOut(nW, nH, false);

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            if (ImgIn[i][j] <= seuilBas) {
                ImgTemp[i][j] = 0;
            } else if (ImgIn[i][j] >= seuilHaut) {
                ImgTemp[i][j] = 255;
            } else {
                ImgTemp[i][j] = 127;
            }
        }
    }

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[i][j] = checkVoisinsHysteresisV2(ImgTemp, i, j, 1, seuilBas, seuilHaut);
        }
    }

    ImgOut.save(cNomImgEcrite);
}

// ------------------------------------- TP 5 -------------------------------------


void RGBtoY(char cNomImgPPM[250], char cNomImgPGM[250]) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgPPM);
    int nH = ImgIn.getHeight();
    int nW = ImgIn.getWidth();
    int nTaille = nH * nW;

    ImageBase ImgOut(nW, nH, false); // Pour l'image en niveaux de gris

    for (int i = 0; i < nTaille; i++) {
        int r = ImgIn.getData()[3 * i];
        int g = ImgIn.getData()[3 * i + 1];
        int b = ImgIn.getData()[3 * i + 2];
        ImgOut.getData()[i] = (OCTET)(0.299 * r + 0.587 * g + 0.114 * b);
    }

    ImgOut.save(cNomImgPGM);
}

double calculerEQM(char cNomImgPGM1[250], char cNomImgPGM2[250]) {
    ImageBase Img1, Img2;
    Img1.load(cNomImgPGM1);
    Img2.load(cNomImgPGM2);
    int nH = Img1.getHeight();
    int nW = Img1.getWidth();
    int nTaille = nH * nW;

    double eqm = 0.0;

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            eqm += pow((double)Img1[i][j] - (double)Img2[i][j], 2);
        }
    }
    eqm /= nTaille;

    return eqm;
}

void RGBtoYCbCr(char cNomImgPPM[250]) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgPPM);
    int nH = ImgIn.getHeight();
    int nW = ImgIn.getWidth();
    int nTaille = nH * nW;

    ImageBase ImgY(nW, nH, false);
    ImageBase ImgCb(nW, nH, false);
    ImageBase ImgCr(nW, nH, false);

    char cNomImgY[250], cNomImgCb[250], cNomImgCr[250];
    char *dot = strrchr(cNomImgPPM, '.');
    int index = dot - cNomImgPPM;

    // Copier la base du nom sans l'extension pour Y
    strncpy(cNomImgY, cNomImgPPM, index);
    cNomImgY[index] = '\0'; // S'assurer que la chaîne est terminée correctement
    strcat(cNomImgY, "_Y.pgm");

    // Répéter le processus pour Cb et Cr
    strncpy(cNomImgCb, cNomImgPPM, index);
    cNomImgCb[index] = '\0';
    strcat(cNomImgCb, "_Cb.pgm");

    strncpy(cNomImgCr, cNomImgPPM, index);
    cNomImgCr[index] = '\0';
    strcat(cNomImgCr, "_Cr.pgm");

    for (int i = 0; i < nTaille; i++) {
        int r = ImgIn.getData()[3 * i];
        int g = ImgIn.getData()[3 * i + 1];
        int b = ImgIn.getData()[3 * i + 2];

        // Calcul des composantes Y, Cb, Cr
        ImgY.getData()[i] = (OCTET)(0.299 * r + 0.587 * g + 0.114 * b);
        ImgCb.getData()[i] = (OCTET)(-0.168736 * r - 0.331264 * g + 0.5 * b + 128);
        ImgCr.getData()[i] = (OCTET)(0.5 * r - 0.418688 * g - 0.081312 * b + 128);
    }

    // Écriture des images Y, Cb, Cr au format PGM
    ImgY.save(cNomImgY);
    ImgCb.save(cNomImgCb);
    ImgCr.save(cNomImgCr);
}

void YCbCrtoRGB(char cNomImgY[250], char cNomImgCb[250], char cNomImgCr[250], char cNomImgPPM[250]) {
    ImageBase ImgY, ImgCb, ImgCr;
    ImgY.load(cNomImgY);
    ImgCb.load(cNomImgCb);
    ImgCr.load(cNomImgCr);
    int nH = ImgY.getHeight();
    int nW = ImgY.getWidth();
    int nTaille = nH * nW;

    ImageBase ImgPPM(nW, nH, true);

    for (int i = 0; i < nTaille; i++) {
        double Y = ImgY.getData()[i];
        double Cb = ImgCb.getData()[i];
        double Cr = ImgCr.getData()[i];

        double R = Y + 1.402 * (Cr - 128);
        double G = Y - 0.344136 * (Cb - 128) - 0.714136 * (Cr - 128);
        double B = Y + 1.772 * (Cb - 128);

        // Ajustement des valeurs pour qu'elles soient dans l'intervalle [0, 255] et écriture dans l'image PPM
        ImgPPM.getData()[3 * i] = clamp(R);
        ImgPPM.getData()[3 * i + 1] = clamp(G);
        ImgPPM.getData()[3 * i + 2] = clamp(B);
    }

    // Écriture de l'image PPM
    ImgPPM.save(cNomImgPPM);
}

void modifY(char cNomImgY[250], int k, char cNomImgOut[250]) {
    ImageBase ImgIn;
    ImgIn.load(cNomImgY);
    int nH = ImgIn.getHeight();
    int nW = ImgIn.getWidth();
    int nTaille = nH * nW;

    ImageBase ImgOut(nW, nH, false);

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[i][j] = clamp(ImgIn[i][j] + k);
        }
    }

    ImgOut.save(cNomImgOut);
}