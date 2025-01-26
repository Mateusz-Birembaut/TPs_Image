#ifndef CODAGE_H
#define CODAGE_H

#include <vector>
#include "RGB.h"
#include "ImageBase.h"

void ecrire_couleurs_index_pgm(char nom_fichier[250], RGB centroids[], int n);

void k_mean_recursive(std::vector<RGB>& grp1, std::vector<RGB>& grp2, RGB& c1, RGB& c2, int depth, int depthMax);

void k_mean(char cNomImgLue[250], char cNomImgEcrite[250], char cNomImgEcrite2[250]);

void k_mean_256(char cNomImgLue[250], char cNomImgEcrite[250]);

void k_mean_256_pgm(char cNomImgLue[250], char cNomImgEcrite[250]);

void PSNR(char cNomImgLue[250], char cNomImgLue2[250]);

void decode_indexed_pgm(char cNomImgIndexed[250], char cNomPalette[250], char cNomImgSortie[250]);

#endif // CODAGE_H