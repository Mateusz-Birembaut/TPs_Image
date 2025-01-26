#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "codage.h"


void ecrire_couleurs_index_pgm(char nom_fichier[250], RGB centroids[], int n) {
    FILE *fichier;

    if ((fichier = fopen(nom_fichier, "w")) == NULL) {
        printf("\nPas d'acces en ecriture sur le fichier %s \n", nom_fichier);
        exit(EXIT_FAILURE);
    } else {
        for (int i = 0; i < n; i++) {
            fprintf(fichier, "%d %f %f %f\n", i, centroids[i].r, centroids[i].v, centroids[i].b);
        }

        fclose(fichier);
    }
}

void k_mean_recursive(std::vector<RGB>& grp1, std::vector<RGB>& grp2, RGB& c1, RGB& c2, int depth, int depthMax) {
    if (depth == depthMax) {
        return;
    }

    RGB newC1(0, 0, 0);
    for (const RGB& color : grp1) {
        newC1 += color;
    }
    if (!grp1.empty()) {
        newC1 /= grp1.size();
    }

    RGB newC2(0, 0, 0);
    for (const RGB& color : grp2) {
        newC2 += color;
    }
    if (!grp2.empty()) {
        newC2 /= grp2.size();
    }

    std::vector<RGB> new_grp1;
    std::vector<RGB> new_grp2;

    for (const RGB& color : grp1) {
        float distToC1 = RGB::dist(color, newC1);
        float distToC2 = RGB::dist(color, newC2);
        if (distToC1 < distToC2) {
            new_grp1.push_back(color);
        } else {
            new_grp2.push_back(color);
        }
    }

    for (const RGB& color : grp2) {
        float distToC1 = RGB::dist(color, newC1);
        float distToC2 = RGB::dist(color, newC2);
        if (distToC1 < distToC2) {
            new_grp1.push_back(color);
        } else {
            new_grp2.push_back(color);
        }
    }

    grp1 = new_grp1;
    grp2 = new_grp2;

    if (c1 == newC1 && c2 == newC2) {
        return;
    }

    c1 = newC1;
    c2 = newC2;

    k_mean_recursive(grp1, grp2, c1, c2, depth + 1, depthMax);
}

void k_mean(char cNomImgLue[250], char cNomImgEcrite[250], char cNomImgEcrite2[250]) {
    ImageBase imgIn, imgOut, imgOut2;
    imgIn.load(cNomImgLue);

    imgOut = ImageBase(imgIn.getWidth(), imgIn.getHeight(), imgIn.getColor());
    imgOut2 = ImageBase(imgIn.getWidth(), imgIn.getHeight(), imgIn.getColor());

    std::vector<RGB> grp1;
    std::vector<RGB> grp2;

    RGB c1(9, 68, 84);
    RGB c2(253, 186, 12);

    RGB baseC1(9, 68, 84);
    RGB baseC2(253, 186, 12);

    for (int i = 0; i < imgIn.getTotalSize(); i += 3) {
        RGB color(imgIn.getData()[i], imgIn.getData()[i + 1], imgIn.getData()[i + 2]);
        float distToC1 = RGB::dist(color, c1);
        float distToC2 = RGB::dist(color, c2);

        if (distToC1 < distToC2) {
            grp1.push_back(color);
        } else {
            grp2.push_back(color);
        }
    }

    k_mean_recursive(grp1, grp2, c1, c2, 0, 20);

    for (int i = 0; i < imgIn.getTotalSize(); i += 3) {
        RGB color(imgIn.getData()[i], imgIn.getData()[i + 1], imgIn.getData()[i + 2]);
        float distToC1 = RGB::dist(color, baseC1);
        float distToC2 = RGB::dist(color, baseC2);

        if (distToC1 < distToC2) {
            imgOut.getData()[i] = static_cast<int>(baseC1.r);
            imgOut.getData()[i + 1] = static_cast<int>(baseC1.v);
            imgOut.getData()[i + 2] = static_cast<int>(baseC1.b);
        } else {
            imgOut.getData()[i] = static_cast<int>(baseC2.r);
            imgOut.getData()[i + 1] = static_cast<int>(baseC2.v);
            imgOut.getData()[i + 2] = static_cast<int>(baseC2.b);
        }
    }

    for (int i = 0; i < imgIn.getTotalSize(); i += 3) {
        RGB color(imgIn.getData()[i], imgIn.getData()[i + 1], imgIn.getData()[i + 2]);
        float distToC1 = RGB::dist(color, c1);
        float distToC2 = RGB::dist(color, c2);

        if (distToC1 < distToC2) {
            imgOut2.getData()[i] = static_cast<int>(c1.r);
            imgOut2.getData()[i + 1] = static_cast<int>(c1.v);
            imgOut2.getData()[i + 2] = static_cast<int>(c1.b);
        } else {
            imgOut2.getData()[i] = static_cast<int>(c2.r);
            imgOut2.getData()[i + 1] = static_cast<int>(c2.v);
            imgOut2.getData()[i + 2] = static_cast<int>(c2.b);
        }
    }

    imgOut.save(cNomImgEcrite);
    imgOut2.save(cNomImgEcrite2);
}

void k_mean_256(char cNomImgLue[250], char cNomImgEcrite[250]) {
    ImageBase imgIn, imgOut;
    imgIn.load(cNomImgLue);

    imgOut = ImageBase(imgIn.getWidth(), imgIn.getHeight(), imgIn.getColor());

    RGB centroids[256];

    for (int i = 0; i < 256; i++) {
        int randomIndex = rand() % (imgIn.getTotalSize() / 3) * 3;
        centroids[i] = RGB(imgIn.getData()[randomIndex], imgIn.getData()[randomIndex + 1], imgIn.getData()[randomIndex + 2]);
    }

    for (int iteration = 0; iteration < 20; iteration++) {
        std::vector<std::vector<RGB>> groups(256);

        for (int i = 0; i < imgIn.getTotalSize(); i += 3) {
            RGB color(imgIn.getData()[i], imgIn.getData()[i + 1], imgIn.getData()[i + 2]);
            int bestCentroid = 0;
            float minDist = RGB::dist(color, centroids[0]);

            for (int c = 1; c < 256; c++) {
                float dist = RGB::dist(color, centroids[c]);
                if (dist < minDist) {
                    minDist = dist;
                    bestCentroid = c;
                }
            }
            groups[bestCentroid].push_back(color);
        }

        bool stop = true;

        for (int c = 0; c < 256; c++) {
            RGB newCentroid(0, 0, 0);
            for (const RGB& color : groups[c]) {
                newCentroid += color;
            }
            if (!groups[c].empty()) {
                newCentroid /= groups[c].size();
            }
            if (centroids[c].r != newCentroid.r || centroids[c].v != newCentroid.v || centroids[c].b != newCentroid.b) {
                stop = false;
            }
            centroids[c] = newCentroid;
        }

        if (stop) {
            break;
        }
    }

    for (int i = 0; i < imgIn.getTotalSize(); i += 3) {
        RGB color(imgIn.getData()[i], imgIn.getData()[i + 1], imgIn.getData()[i + 2]);
        int bestCentroid = 0;
        float minDist = RGB::dist(color, centroids[0]);

        for (int c = 1; c < 256; c++) {
            float dist = RGB::dist(color, centroids[c]);
            if (dist < minDist) {
                minDist = dist;
                bestCentroid = c;
            }
        }

        imgOut.getData()[i] = static_cast<int>(centroids[bestCentroid].r);
        imgOut.getData()[i + 1] = static_cast<int>(centroids[bestCentroid].v);
        imgOut.getData()[i + 2] = static_cast<int>(centroids[bestCentroid].b);
    }

    imgOut.save(cNomImgEcrite);
}

void k_mean_256_pgm(char cNomImgLue[250], char cNomImgEcrite[250]) {
    ImageBase imgIn, imgOut;
    imgIn.load(cNomImgLue);

    imgOut = ImageBase(imgIn.getWidth(), imgIn.getHeight(), false);

    RGB centroids[256];

    for (int i = 0; i < 256; i++) {
        int randomIndex = rand() % (imgIn.getTotalSize() / 3) * 3;
        centroids[i] = RGB(imgIn.getData()[randomIndex], imgIn.getData()[randomIndex + 1], imgIn.getData()[randomIndex + 2]);
    }

    for (int iteration = 0; iteration < 20; iteration++) {
        std::vector<std::vector<RGB>> groups(256);

        for (int i = 0; i < imgIn.getTotalSize(); i += 3) {
            RGB color(imgIn.getData()[i], imgIn.getData()[i + 1], imgIn.getData()[i + 2]);
            int bestCentroid = 0;
            float minDist = RGB::dist(color, centroids[0]);

            for (int c = 1; c < 256; c++) {
                float dist = RGB::dist(color, centroids[c]);
                if (dist < minDist) {
                    minDist = dist;
                    bestCentroid = c;
                }
            }
            groups[bestCentroid].push_back(color);
        }

        bool stop = true;

        for (int c = 0; c < 256; c++) {
            RGB newCentroid(0, 0, 0);
            for (const RGB& color : groups[c]) {
                newCentroid += color;
            }
            if (!groups[c].empty()) {
                newCentroid /= groups[c].size();
            }
            if (centroids[c].r != newCentroid.r || centroids[c].v != newCentroid.v || centroids[c].b != newCentroid.b) {
                stop = false;
            }
            centroids[c] = newCentroid;
        }

        if (stop) {
            break;
        }
    }

    for (int i = 0; i < imgIn.getTotalSize(); i += 3) {
        RGB color(imgIn.getData()[i], imgIn.getData()[i + 1], imgIn.getData()[i + 2]);
        int bestCentroid = 0;
        float minDist = RGB::dist(color, centroids[0]);

        for (int c = 1; c < 256; c++) {
            float dist = RGB::dist(color, centroids[c]);
            if (dist < minDist) {
                minDist = dist;
                bestCentroid = c;
            }
        }

        imgOut.getData()[i / 3] = bestCentroid;
    }

    imgOut.save(cNomImgEcrite);
    std::string fileName = std::string(cNomImgEcrite) + "_couleurs.txt";
    ecrire_couleurs_index_pgm(const_cast<char*>(fileName.c_str()), centroids, 256);
}

void PSNR(char cNomImgLue[250], char cNomImgLue2[250]) {
    ImageBase imgOriginal, imgModifiee;
    imgOriginal.load(cNomImgLue);
    imgModifiee.load(cNomImgLue2);

    float eqm = 0.0;

    for (int i = 0; i < imgOriginal.getTotalSize(); i += 3) {
        int diffR = imgOriginal.getData()[i] - imgModifiee.getData()[i];
        int diffG = imgOriginal.getData()[i + 1] - imgModifiee.getData()[i + 1];
        int diffB = imgOriginal.getData()[i + 2] - imgModifiee.getData()[i + 2];

        eqm += diffR * diffR + diffG * diffG + diffB * diffB;
    }

    eqm /= imgOriginal.getTotalSize();
    std::cout << " EQM : " << eqm << std::endl;

    float pnsr = 10 * log10(pow(255, 2) / eqm);
    std::cout << " PNSR : " << pnsr << " dB " << std::endl;
}

void decode_indexed_pgm(char cNomImgIndexed[250], char cNomPalette[250], char cNomImgSortie[250]) {
    ImageBase imgIn, imgOut;
    imgIn.load(cNomImgIndexed);

    imgOut = ImageBase(imgIn.getWidth(), imgIn.getHeight(), true);

    RGB palette[256];

    std::ifstream infile(cNomPalette);
    if (infile.is_open()) {
        std::cout << "Fichier ouvert avec succès : " << cNomPalette << std::endl;
        std::string line;
        if (infile.peek() == std::ifstream::traits_type::eof()) {
            std::cerr << "Le fichier est vide." << std::endl;
        } else {
            while (std::getline(infile, line)) {
                std::istringstream iss(line);
                int index;
                float r, g, b;
                if (!(iss >> index >> r >> g >> b)) {
                    std::cerr << "Erreur de lecture de la ligne : " << line << std::endl;
                    continue;
                }
                palette[index] = RGB(r, g, b);
            }
        }
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier " << cNomPalette << std::endl;
    }

    for (int i = 0; i < imgIn.getTotalSize(); i++) {
        int idx = imgIn.getData()[i];
        imgOut.getData()[i * 3] = (int)palette[idx].r;
        imgOut.getData()[i * 3 + 1] = (int)palette[idx].v;
        imgOut.getData()[i * 3 + 2] = (int)palette[idx].b;
    }

    imgOut.save(cNomImgSortie);
}