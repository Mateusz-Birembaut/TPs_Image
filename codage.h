#include <cstdlib>
#include <math.h>
#include <vector>
#include <iostream>

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


    public:
        static float dist(const Vec3& a, const Vec3& b) {  // Utilisation de const Vec3&
            return sqrt(pow((b.r - a.r), 2) + pow((b.v - a.v), 2) + pow((b.b - a.b), 2));
        }

};


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

    std::vector<Vec3> centroids(256);
    for (int i = 0; i < 256; i++) {
        int randomIndex = rand() % (nTaille / 3) * 3;
        centroids[i] = Vec3(ImgIn[randomIndex], ImgIn[randomIndex + 1], ImgIn[randomIndex + 2]);
    }

    for (int iteration = 0; iteration < 12; iteration++) {
        std::vector<std::vector<Vec3>> groups(256);

        for (int i = 0; i < nTaille; i += 3) {
            Vec3 color(ImgIn[i], ImgIn[i + 1], ImgIn[i + 2]);
            int bestCentroid = 0;
            float minDist = Vec3::dist(color, centroids[0]);

            for (int c = 1; c < 256; c++) {
                float dist = Vec3::dist(color, centroids[c]);
                if (dist < minDist) {
                    minDist = dist;
                    bestCentroid = c;
                }
            }
            groups[bestCentroid].push_back(color);
        }

        for (int c = 0; c < 256; c++) {
            Vec3 newCentroid(0, 0, 0);
            for (const Vec3& color : groups[c]) {
                newCentroid += color;
            }
            if (!groups[c].empty()) {
                newCentroid /= groups[c].size();
            }
            centroids[c] = newCentroid;
        }
    }

    for (int i = 0; i < nTaille; i += 3) {
        Vec3 color(ImgIn[i], ImgIn[i + 1], ImgIn[i + 2]);
        int bestCentroid = 0;
        float minDist = Vec3::dist(color, centroids[0]);

        for (int c = 1; c < 256; c++) {
            float dist = Vec3::dist(color, centroids[c]);
            if (dist < minDist) {
                minDist = dist;
                bestCentroid = c;
            }
        }

        ImgOut[i] = static_cast<int>(centroids[bestCentroid].r);
        ImgOut[i + 1] = static_cast<int>(centroids[bestCentroid].v);
        ImgOut[i + 2] = static_cast<int>(centroids[bestCentroid].b);
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
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

void reduce_image_pgm(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW, int reduction) {
    int nH2 = nH / reduction; 
    int nW2 = nW / reduction;

    for (int i = 0; i < nH2; i++) {
        for (int j = 0; j < nW2; j++) {
            ImgOut[i * nW2 + j] = ImgIn[(i * reduction) * nW + (j * reduction)];
        }
    }
}


float interpolate(float q11, float q12, float q21, float q22, float x, float y) {
    return q11 * (1 - x) * (1 - y) +
           q12 * x * (1 - y) +
           q21 * (1 - x) * y +
           q22 * x * y;
}

void resample_image_pgm(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW, int nH2, int nW2) {
    for (int i = 0; i < nH2; i++) {
        for (int j = 0; j < nW2; j++) {
            // Calcul des coordonnées dans l'image d'entrée
            float x = (float)j * (nW - 1) / (nW2 - 1); // Position x dans l'image d'entrée
            float y = (float)i * (nH - 1) / (nH2 - 1); // Position y dans l'image d'entrée

            int x1 = (int)x; // Coordonnée entière de gauche
            int y1 = (int)y; // Coordonnée entière du haut
            int x2 = (x1 + 1 < nW) ? x1 + 1 : x1; // Coordonnée entière de droite (limité au bord droit)
            int y2 = (y1 + 1 < nH) ? y1 + 1 : y1; // Coordonnée entière du bas (limité au bord bas)

            // Valeurs des 4 pixels environnants (x1, y1), (x2, y1), (x1, y2), (x2, y2)
            float q11 = ImgIn[y1 * nW + x1];
            float q12 = ImgIn[y1 * nW + x2];
            float q21 = ImgIn[y2 * nW + x1];
            float q22 = ImgIn[y2 * nW + x2];

            // Calcul des fractions pour l'interpolation
            float x_frac = x - x1; // Fraction de la distance dans la direction x
            float y_frac = y - y1; // Fraction de la distance dans la direction y

            // Interpolation bilinéaire
            ImgOut[i * nW2 + j] = (OCTET)(
                q11 * (1 - x_frac) * (1 - y_frac) + 
                q12 * x_frac * (1 - y_frac) + 
                q21 * (1 - x_frac) * y_frac + 
                q22 * x_frac * y_frac
            );
        }
    }
}




void ex3_tp2(char cNomImgLue[250], char cNomImgSortie[250]){

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

    char R[] = "img_R.pgm";
    char G[] = "img_G.pgm";
    char B[] = "img_B.pgm";

    ecrire_image_pgm(R, PlanR, nH, nW);
    ecrire_image_pgm(G, PlanV, nH, nW);
    ecrire_image_pgm(B, PlanB, nH, nW);

    OCTET *ImgR_reduite, *ImgB_reduite;
    allocation_tableau(ImgR_reduite, OCTET, nTaille/2);
    allocation_tableau(ImgB_reduite, OCTET, nTaille/2);

    reduce_image_pgm(PlanR, ImgR_reduite, nH, nW, 2);
    reduce_image_pgm(PlanB, ImgB_reduite, nH, nW, 2);

    OCTET *ImgR_re_sampled, *ImgB_re_sampled;
    allocation_tableau(ImgR_re_sampled, OCTET, nTaille);
    allocation_tableau(ImgB_re_sampled, OCTET, nTaille);


    resample_image_pgm(ImgR_reduite, ImgR_re_sampled, nH/2 , nW/2, nH, nW);
    resample_image_pgm( ImgB_reduite, ImgB_re_sampled, nH/2 , nW/2, nH, nW);

    char RR[] = "R_resampled.pgm";
    char GR[] = "B_resampled.pgm";

    ecrire_image_pgm(RR, ImgR_re_sampled, nH, nW);
    ecrire_image_pgm(GR, ImgB_re_sampled, nH, nW);

    allocation_tableau(ImgOut, OCTET, nTaille3);
    for (int i = 0; i < nTaille; i++) {
        ImgOut[i*3] = ImgR_re_sampled[i];
        ImgOut[i*3+1] = PlanV[i];
        ImgOut[i*3+2] = ImgB_re_sampled[i];
    }

    ecrire_image_ppm(cNomImgSortie, ImgOut, nH, nW);

    free(ImgR_reduite);
    free(ImgB_reduite);

    free(ImgR_re_sampled);
    free(ImgB_re_sampled);

    free(ImgIn);
    free(ImgOut);

    free(PlanR);
    free(PlanV);
    free(PlanB);


}


void re_sample_ycbcr(char cNomImgLue[250], char cNomImgLue2[250], char cNomImgLue3[250]){

    int nH, nW, nTaille;
    
    OCTET *ImgY, *ImgCb, * ImgCr;

    OCTET *ImgYOut, *ImgCbOut, * ImgCrOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    // lectures de images

    allocation_tableau(ImgY, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgY, nTaille);

    allocation_tableau(ImgCb, OCTET, nTaille);
    lire_image_pgm(cNomImgLue2, ImgCb, nTaille);

    allocation_tableau(ImgCr, OCTET, nTaille);
    lire_image_pgm(cNomImgLue3, ImgCr, nTaille);


    //declaration images réduite

    OCTET *ImgCb_reduite, *ImgCr_reduite;
    allocation_tableau(ImgCb_reduite, OCTET, nTaille/2);
    allocation_tableau(ImgCr_reduite, OCTET, nTaille/2);

    reduce_image_pgm(ImgCb, ImgCb_reduite, nH, nW, 2);
    reduce_image_pgm(ImgCr, ImgCr_reduite, nH, nW, 2);

    // declaration image re sampled

    OCTET *ImgCb_re_sampled, *ImgCr_re_sampled;
    allocation_tableau(ImgCb_re_sampled, OCTET, nTaille);
    allocation_tableau(ImgCr_re_sampled, OCTET, nTaille);

    resample_image_pgm(ImgCb_reduite, ImgCb_re_sampled, nH/2 , nW/2, nH, nW);
    resample_image_pgm(ImgCr_reduite, ImgCr_re_sampled, nH/2 , nW/2, nH, nW);

    // ecriture out

    allocation_tableau(ImgYOut, OCTET, nTaille);
    allocation_tableau(ImgCbOut, OCTET, nTaille);
    allocation_tableau(ImgCrOut, OCTET, nTaille);

    for (int i = 0; i < nTaille; i++) {
        ImgCbOut[i] = ImgCb_re_sampled[i];
        ImgCrOut[i] = ImgCr_re_sampled[i];
    }

    ecrire_image_pgm(cNomImgLue2, ImgCbOut, nH, nW);
    ecrire_image_pgm(cNomImgLue3, ImgCrOut, nH, nW);


}


/* void difference_map_pgm(char cNomImgLue[250], char cNomImgEcrite[250]){
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);

    allocation_tableau(ImgOut, OCTET, nTaille);

    ImgOut[0] = ImgIn[0];

    for (int i = 1; i < nTaille; i++) {
        if ( i % nW == 0 ){
            ImgOut[i] = ImgIn[i] - ImgOut[i - nW] + 128;
        }else {
            ImgOut[i] = ImgIn[i] - ImgOut[i-1] + 128;
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);

} */


void entropie(char cNomImgLue[250]){
    int nH, nW, nTaille;
    OCTET *ImgIn;
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    
    int histo[256] = {0};
    for (int i = 0; i < nTaille; i++) {
        histo[ImgIn[i]]++;
    }
    
    double entropy = 0.0;
    for (int i = 0; i < 256; i++) {
        if (histo[i] > 0) {
            double p = (double)histo[i] / nTaille;
            entropy -= p * log2(p);
        }
    }
    
    printf("Entropie de l'image : %f\n", entropy);
    
    free(ImgIn);
}


void difference_map_pgm(char cNomImgLue[250], char cNomImgEcrite[250]){
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    
    allocation_tableau(ImgOut, OCTET, nTaille);

    ImgOut[0] = ImgIn[0];

    for (int i = 1; i < nTaille; i++) {
        if ( i % nW == 0 ){
            ImgOut[i] = ImgIn[i] - ImgIn[i - nW] + 128;
            //std::cout<< "index : " << i << ", valeur : " << (int)ImgOut[i] << std::endl;
        }else {
            ImgOut[i] = ImgIn[i] - ImgIn[i-1] + 128;
            //std::cout<< "index : " << i << ", valeur : " << (int)ImgOut[i] << std::endl;
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);

}

void difference_map_pgm_alternate(char cNomImgLue[250], char cNomImgEcrite[250]) {
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);

    allocation_tableau(ImgOut, OCTET, nTaille);

    ImgOut[0] = ImgIn[0];

    for (int i = 1; i < nTaille; i++) {
        int row = i / nW;   
        int col = i % nW;   

        if (row == 0) {
            ImgOut[i] = ImgIn[i] - ImgIn[i - 1] + 128;
        }
        else if (col == 0) {
            ImgOut[i] = ImgIn[i] - ImgIn[i - nW] + 128;
        }
        else {

            int gauche   = ImgIn[i - 1];
            int dessus   = ImgIn[i - nW];
            int diagonal = ImgIn[i - nW - 1];

            int prediction = gauche + dessus - diagonal;

            ImgOut[i] = ImgIn[i] - prediction + 128;
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);

    free(ImgIn);
    free(ImgOut);
}

//-------------------------------TP 4-----------------------------------------


void transformee_ondelettes_pgm(char cNomImgLue[250], char cNomImgEcrite[250]) {
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut, *ImgBF, *ImgMFh , *ImgMFv , *ImgHF ;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    
    allocation_tableau(ImgOut, OCTET, nTaille);

    allocation_tableau(ImgBF, OCTET, nTaille/4);
    allocation_tableau(ImgMFh, OCTET, nTaille/4);
    allocation_tableau(ImgMFv, OCTET, nTaille/4);
    allocation_tableau(ImgHF, OCTET, nTaille/4);

    for (int i = 0; i < nH; i += 2) { 
        for (int j = 0; j < nW; j += 2) {
            
            int idxA = i * nW + j;
            int idxB = i * nW + (j + 1);
            int idxC = (i + 1) * nW + j;
            int idxD = (i + 1) * nW + (j + 1);


            if (i + 1 >= nH) { idxC = idxA; idxD = idxB; } 
            if (j + 1 >= nW) { idxB = idxA; idxD = idxC; }

            int A = ImgIn[idxA];
            int B = ImgIn[idxB];
            int C = ImgIn[idxC];
            int D = ImgIn[idxD];

            int BF = (A + B + C + D) / 4;
            int MFh = (A + B - C - D) / 2;
            int MFv = (A - B + C - D) / 2;
            int HF = A - B - C + D;


            ImgOut[idxA] = BF;
            ImgOut[idxB] = MFh;
            ImgOut[idxC] = MFv;
            ImgOut[idxD] = HF;

            int index = (i / 2) * (nW/2) + (j / 2);
            ImgBF[index]  = BF;
            ImgMFh[index] = MFh;
            ImgMFv[index] = MFv;
            ImgHF[index]  = HF;

        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);

    ecrire_image_pgm("imgBF.pgm", ImgBF, nH/2, nW/2);
    ecrire_image_pgm("ImgMFh.pgm", ImgMFh, nH/2, nW/2);
    ecrire_image_pgm("ImgMFv.pgm", ImgMFv, nH/2, nW/2);
    ecrire_image_pgm("ImgHF.pgm", ImgHF, nH/2, nW/2);

    free(ImgIn);
    free(ImgBF);
    free(ImgMFh);
    free(ImgMFv);
    free(ImgHF);
    free(ImgOut);
}

/* void reconstruire_ondelettes_pgm(char cNomImgLue[250], char cNomImgEcrite[250]){
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut, *ImgBF, *ImgMFh , *ImgMFv , *ImgHF ;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    
    allocation_tableau(ImgOut, OCTET, nTaille);

    for (int i = 0; i < nH; i += 2) { 
        for (int j = 0; j < nW; j += 2) {
            
            int idxA = i * nW + j;
            int idxB = i * nW + (j + 1);
            int idxC = (i + 1) * nW + j;
            int idxD = (i + 1) * nW + (j + 1);

            if (i + 1 >= nH) { idxC = idxA; idxD = idxB; } 
            if (j + 1 >= nW) { idxB = idxA; idxD = idxC; }

            int BF = ImgIn[idxA];
            int MFh = ImgIn[idxB];
            int MFv = ImgIn[idxC];
            int HF = ImgIn[idxD];

            int A = ;
            int B = ;
            int C = ;
            int D = ;

            ImgOut[idxA] = A;
            ImgOut[idxB] = B;
            ImgOut[idxC] = C;
            ImgOut[idxD] = D;

        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);

    free(ImgIn);
    free(ImgOut);

}
 */

