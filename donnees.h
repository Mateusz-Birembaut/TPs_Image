#ifndef DONNEES_H
#define DONNEES_H

#include "ImageBase.h"
#include "image_ppm.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int getValeurMoyenne(ImageBase &image, int ligne, int colonne, int rayon);
int getCouleurMinimal(ImageBase &image, int ligne, int colonne, int rayon);
int getCouleurMaximal(ImageBase &image, int ligne, int colonne, int rayon);
int getPixelValueWithMirrorPadding(ImageBase &image, int ligne, int colonne);
int getNormeGradient(ImageBase &image, int ligne, int colonne, int rayon, int masqueHorizontal[], int masqueVertical[]);
int checkVoisinsHysteresis(ImageBase &image, int ligne, int colonne, int rayon, int seuilBas, int seuilHaut);
int checkVoisinsHysteresisV2(ImageBase &image, int ligne, int colonne, int rayon, int seuilBas, int seuilHaut);
int compare(const void *a, const void *b);
int getValeurMediane(ImageBase &image, int ligne, int colonne, int rayon);
void filtreMoyenneurPGM(ImageBase &image, int rayon);
int getValeurGauss(ImageBase &image, int ligne, int colonne, int rayon);
void filtreGaussienPGM(ImageBase &image, int rayon);
OCTET clamp(double valeur);
void seuil_image_pgm(char cNomImgLue[250], char cNomImgEcrite[250], int seuils[], int nb_Seuils);
void seuil_image_ppm(char cNomImgLue[250], char cNomImgEcrite[250]);
void ecrire_histogramme_pgm(char nom_fichier[250], int histogramme[], int taille_histogramme);
void histogramme_pgm(char cNomImgLue[250], char cNomFichierEcrit[250]);
void ecrire_profil(const char* nom_fichier, int profil[], int tailleProfil);
void profil_ligne_pgm(char cNomImgLue[250], int indice, char cNomFichierEcrit[250]);
void profil_colonne_pgm(char cNomImgLue[250], int indice, char cNomFichierEcrit[250]);
void ecrire_histogramme_ppm(const char* nom_fichier, int histogramme[][256], int taille_histogramme);
void histogramme_ppm(char cNomImgLue[250], char cNomFichierEcrit[250]);
void erosion_pgm(char cNomImgLue[250], char cNomImgEcrite[250], int rayon);
void dilatation_pgm(char cNomImgLue[250], char cNomImgEcrite[250], int rayon);
void fermeture_pgm(char cNomImgLue[250], char cNomImgEcrite[250], int rayon);
void ouverture_pgm(char cNomImgLue[250], char cNomImgEcrite[250], int rayon);
void difference_pgm(char cNomImgLue1[250], char cNomImgLue2[250], char cNomImgEcrite[250]);
void inverse_pgm(char cNomImgLue[250], char cNomImgEcrite[250]);
void flouter_image(ImageBase &image, int rayon);
void flouter_image_pgm(char cNomImgLue[250], char cNomImgEcrite[250], int rayon);
void flouter_image_ppm(char cNomImgLue[250], char cNomImgEcrite[250], int rayon);
void norme_gradient_pgm(char cNomImgLue[250], char cNomImgEcrite[250], char* filtreMoyenne, char* filtreGauss);
void seuil_hysteresis_pgm(char cNomImgLue[250], char cNomImgEcrite[250], int seuilBas, int seuilHaut);
void RGBtoY(char cNomImgPPM[250], char cNomImgPGM[250]);
double calculerEQM(char cNomImgPGM1[250], char cNomImgPGM2[250]);
void RGBtoYCbCr(char cNomImgPPM[250]);
void YCbCrtoRGB(char cNomImgY[250], char cNomImgCb[250], char cNomImgCr[250], char cNomImgPPM[250]);
void modifY(char cNomImgY[250], int k, char cNomImgOut[250]);

#endif // DONNEES_H