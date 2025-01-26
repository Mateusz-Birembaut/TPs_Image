#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

// c1 : 9;68;84
// c2 : 253;186;12

class Vec3{
    public: 
        float r,v,b;

        Vec3(float a, float b, float c){
            r = a;
            v = b;
            this->b = c;
        }
        
        Vec3() : r(0), v(0), b(0) {}

    Vec3& operator/=(const float& a) {
        if (a != 0) {  
            r /= a;
            v /= a;
            b /= a;
        }
        return *this;
    }


    Vec3& operator+=(const Vec3& a) {  
        r += a.r;
        v += a.v;
        b += a.b;
        return *this;
    }

    Vec3& operator-=(const Vec3& a) {  
        r -= a.r;
        v -= a.v;
        b -= a.b;
        return *this;
    }

    bool operator ==(const Vec3& a) {  
        return r == a.r && v == a.v && b == a.b;
    }


    public:
        static float dist(const Vec3& a, const Vec3& b) {  // Utilisation de const Vec3&
            return sqrt(pow((b.r - a.r), 2) + pow((b.v - a.v), 2) + pow((b.b - a.b), 2));
        }

};

void ecrire_couleurs_index_pgm(char nom_fichier[250], Vec3 centroids[], int n) {
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



void k_mean_recursive(std::vector<Vec3>& grp1, std::vector<Vec3>& grp2, Vec3& c1, Vec3& c2, int depth, int depthMax) {
    if (depth == depthMax) {
        return;
    }

    Vec3 newC1(0, 0, 0);
    for (const Vec3& color : grp1) {
        newC1 += color;
    }
    if (!grp1.empty()) {
        newC1 /= grp1.size();
    }


    Vec3 newC2(0, 0, 0);
    for (const Vec3& color : grp2) {
        newC2 += color;
    }
    if (!grp2.empty()) {
        newC2 /= grp2.size();
    }


    std::vector<Vec3> new_grp1;
    std::vector<Vec3> new_grp2;


    for (const Vec3& color : grp1) {
        float distToC1 = Vec3::dist(color, newC1);
        float distToC2 = Vec3::dist(color, newC2);
        if (distToC1 < distToC2) {
            new_grp1.push_back(color);
        } else {
            new_grp2.push_back(color);
        }
    }

    for (const Vec3& color : grp2) {
        float distToC1 = Vec3::dist(color, newC1);
        float distToC2 = Vec3::dist(color, newC2);
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


void k_mean(char cNomImgLue[250], char cNomImgEcrite[250], char cNomImgEcrite2[250]){
    int nH, nW, nTaille;

    OCTET *ImgIn, *ImgOut, *ImgOut2;
    
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW * 3;
  
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);
    allocation_tableau(ImgOut2, OCTET, nTaille);

    std::vector<Vec3> grp1;
    std::vector<Vec3> grp2;

    Vec3 c1 (9, 68, 84);
    Vec3 c2 (253, 186, 12);

    Vec3 baseC1 (9, 68, 84);
    Vec3 baseC2 (253, 186, 12);
    
    for (int i = 0; i < nTaille; i += 3) {
        Vec3 color(ImgIn[i], ImgIn[i + 1], ImgIn[i + 2]);
        float distToC1 = Vec3::dist(color, c1);
        float distToC2 = Vec3::dist(color, c2);

        if (distToC1 < distToC2) {
            grp1.push_back(color);
        } else {
            grp2.push_back(color);
        }
    }


    k_mean_recursive(grp1, grp2, c1, c2, 0, 20);

    for (int i = 0; i < nTaille; i += 3) {
        Vec3 color(ImgIn[i], ImgIn[i + 1], ImgIn[i + 2]);
        float distToC1 = Vec3::dist(color, baseC1);
        float distToC2 = Vec3::dist(color, baseC2);

        if (distToC1 < distToC2) {
            ImgOut[i] = static_cast<int>(baseC1.r);
            ImgOut[i + 1] = static_cast<int>(baseC1.v);
            ImgOut[i + 2] = static_cast<int>(baseC1.b);
        } else {
            ImgOut[i] = static_cast<int>(baseC2.r);
            ImgOut[i + 1] = static_cast<int>(baseC2.v);
            ImgOut[i + 2] = static_cast<int>(baseC2.b);
        }
    }

    for (int i = 0; i < nTaille; i += 3) {
        Vec3 color(ImgIn[i], ImgIn[i + 1], ImgIn[i + 2]);
        float distToC1 = Vec3::dist(color, c1);
        float distToC2 = Vec3::dist(color, c2);

        if (distToC1 < distToC2) {
            ImgOut2[i] = static_cast<int>(c1.r);
            ImgOut2[i + 1] = static_cast<int>(c1.v);
            ImgOut2[i + 2] = static_cast<int>(c1.b);
        } else {
            ImgOut2[i] = static_cast<int>(c2.r);
            ImgOut2[i + 1] = static_cast<int>(c2.v);
            ImgOut2[i + 2] = static_cast<int>(c2.b);
        }
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    ecrire_image_ppm(cNomImgEcrite2, ImgOut2, nH, nW);

}

void k_mean_256(char cNomImgLue[250], char cNomImgEcrite[250]) {
    int nH, nW, nTaille;

    OCTET *ImgIn, *ImgOut;
    
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW * 3;
  
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    Vec3  centroids[256];

    for (int i = 0; i < 256; i++) { // initialisation des centroids aléatoires
        int randomIndex = rand() % (nTaille / 3) * 3;
        centroids[i] = Vec3(ImgIn[randomIndex], ImgIn[randomIndex + 1], ImgIn[randomIndex + 2]);
    }

 
    for (int iteration = 0; iteration < 20; iteration++) { // 15 interations max
        std::vector<std::vector<Vec3>> groups(256);

        for (int i = 0; i < nTaille; i += 3) {
            Vec3 color(ImgIn[i], ImgIn[i + 1], ImgIn[i + 2]);
            int bestCentroid = 0;
            float minDist = Vec3::dist(color, centroids[0]);

            for (int c = 1; c < 256; c++) { // trouver le centroid le plus proche et l'ajouter au groupe
                float dist = Vec3::dist(color, centroids[c]);
                if (dist < minDist) {
                    minDist = dist;
                    bestCentroid = c;
                }
            }
            groups[bestCentroid].push_back(color);
        }

        bool stop = true;

        for (int c = 0; c < 256; c++) {
            Vec3 newCentroid(0, 0, 0);
            for (const Vec3& color : groups[c]) {
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

        if (stop) { // Si les centroids ne changent plus, on arrête
            break;
        }
    }

    for (int i = 0; i < nTaille; i += 3) {
        Vec3 color(ImgIn[i], ImgIn[i + 1], ImgIn[i + 2]);
        int bestCentroid = 0;
        float minDist = Vec3::dist(color, centroids[0]);

        for (int c = 1; c < 256; c++) { // trouver le centroid le plus proche
            float dist = Vec3::dist(color, centroids[c]);
            if (dist < minDist) {
                minDist = dist;
                bestCentroid = c;
            }
        }

        // Remplacer la couleur par celle du centroid le plus proche
        ImgOut[i] = static_cast<int>(centroids[bestCentroid].r);
        ImgOut[i + 1] = static_cast<int>(centroids[bestCentroid].v);
        ImgOut[i + 2] = static_cast<int>(centroids[bestCentroid].b);
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
}

void k_mean_256_pgm(char cNomImgLue[250], char cNomImgEcrite[250]) {
    int nH, nW, nTaille;

    OCTET *ImgIn, *ImgOut;
    
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW * 3;
  
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille / 3);

    Vec3  centroids[256];

    for (int i = 0; i < 256; i++) { // initialisation des centroids aléatoires
        int randomIndex = rand() % (nTaille / 3) * 3;
        centroids[i] = Vec3(ImgIn[randomIndex], ImgIn[randomIndex + 1], ImgIn[randomIndex + 2]);
    }

 
    for (int iteration = 0; iteration < 20; iteration++) { // 15 interations max
        std::vector<std::vector<Vec3>> groups(256);

        for (int i = 0; i < nTaille; i += 3) {
            Vec3 color(ImgIn[i], ImgIn[i + 1], ImgIn[i + 2]);
            int bestCentroid = 0;
            float minDist = Vec3::dist(color, centroids[0]);

            for (int c = 1; c < 256; c++) { // trouver le centroid le plus proche et l'ajouter au groupe
                float dist = Vec3::dist(color, centroids[c]);
                if (dist < minDist) {
                    minDist = dist;
                    bestCentroid = c;
                }
            }
            groups[bestCentroid].push_back(color);
        }

        bool stop = true;

        for (int c = 0; c < 256; c++) {
            Vec3 newCentroid(0, 0, 0);
            for (const Vec3& color : groups[c]) {
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

        if (stop) { // Si les centroids ne changent plus, on arrête
            break;
        }
    }

    for (int i = 0; i < nTaille; i += 3) {
        Vec3 color(ImgIn[i], ImgIn[i + 1], ImgIn[i + 2]);
        int bestCentroid = 0;
        float minDist = Vec3::dist(color, centroids[0]);

        for (int c = 1; c < 256; c++) { // trouver le centroid le plus proche
            float dist = Vec3::dist(color, centroids[c]);
            if (dist < minDist) {
                minDist = dist;
                bestCentroid = c;
            }
        }

        // Remplacer par l'index du centroid le plus proche
        ImgOut[i/3] = bestCentroid;
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    std::string fileName = std::string(cNomImgEcrite) + "_couleurs.txt";
    ecrire_couleurs_index_pgm(const_cast<char*>(fileName.c_str()), centroids, 256);
}

void PSNR (char cNomImgLue[250], char cNomImgLue2[250]){
    int nH, nW, nTaille;

    OCTET *ImgOriginal, *ImgModifiee;
    
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW * 3;
  
    allocation_tableau(ImgOriginal, OCTET, nTaille);
    lire_image_ppm(cNomImgLue, ImgOriginal, nH * nW);

    allocation_tableau(ImgModifiee, OCTET, nTaille);
    lire_image_ppm(cNomImgLue2, ImgModifiee, nH * nW);


    float eqm = 0.0;

    for (int i = 0; i < nTaille; i += 3) {
        int diffR = ImgOriginal[i] - ImgModifiee[i];
        int diffG = ImgOriginal[i + 1] - ImgModifiee[i + 1];
        int diffB = ImgOriginal[i + 2] - ImgModifiee[i + 2];

        eqm += diffR * diffR + diffG * diffG + diffB * diffB;
    }

    eqm /= nTaille; 
    std::cout << " EQM : " << eqm << std::endl;
    
    float pnsr = 10* log10(pow(255,2) / eqm);
    std::cout << " PNSR : " << pnsr  << " dB " << std::endl;
}


void decode_indexed_pgm(char cNomImgIndexed[250], char cNomPalette[250], char cNomImgSortie[250]) {
    int nH, nW;
    lire_nb_lignes_colonnes_image_pgm(cNomImgIndexed, &nH, &nW);
    int nTaille = nH * nW;

    OCTET *ImgIn, *ImgOut;
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgIndexed, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille * 3);

    Vec3 palette[256];

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
                palette[index] = Vec3(r, g, b);
            }
        }
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier " << cNomPalette << std::endl;
    }

    for (int i = 0; i < nTaille; i++) {
        int idx = ImgIn[i];
        ImgOut[i * 3]     = (int)palette[idx].r;
        ImgOut[i * 3 + 1] = (int)palette[idx].v;
        ImgOut[i * 3 + 2] = (int)palette[idx].b;
    }

    ecrire_image_ppm(cNomImgSortie, ImgOut, nH, nW);
}


