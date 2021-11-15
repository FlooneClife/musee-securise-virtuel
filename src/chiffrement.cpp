#include <stdio.h>
#include "image_ppm.h"
#include <math.h>
#include <array>
#include <algorithm>
#include <vector>
#include <random>

int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nR, nG, nB;
    int const SEED = 1000;

    if (argc != 3)
    {
        printf("Usage: ImageIn.ppm ImageOut.ppm \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut, *ImgOutY, *ImgOutCr, *ImgOutCb;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    int const TAILLE = 1000;
    std::vector<int> tabKey;
    for(int nb = 0; nb < TAILLE; nb++) {
        tabKey.push_back(nb);
    }
    std::shuffle(tabKey.begin(), tabKey.end(), std::default_random_engine(SEED));

    int id = 0;
    int keyVal;

    for (int i = 0; i < nTaille3; i += 3)
    {
        keyVal = tabKey[id] * 3;
        id = id >= SEED - 1 ? 0 : (id + 1);
        ImgOut[i] = ImgIn[i + keyVal];
        ImgOut[i + 1] = ImgIn[i + 1 + keyVal];
        ImgOut[i + 2] = ImgIn[i + 2 + keyVal];

        ImgOut[i + keyVal] = ImgIn[i];
        ImgOut[i + 1 + keyVal] = ImgIn[i + 1];
        ImgOut[i + 2 + keyVal] = ImgIn[i + 2];
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);

    printf("\nDone!");

    return 1;
}
