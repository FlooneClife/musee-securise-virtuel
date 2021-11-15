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
    int const TAILLE = 500;

    if (argc != 3)
    {
        printf("Usage: ImageIn.ppm ImageOut.ppm\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    std::vector<int> tabKey; //{9, 7, 4, 1, 0, 8, 3, 5, 2, 6};
    for(int nb = 0; nb < TAILLE; nb++) {
        tabKey.push_back(nb);
    }
    std::shuffle(tabKey.begin(), tabKey.end(), std::default_random_engine(SEED));
    // for(int nb = 0; nb < TAILLE - 1; nb++) {
    //     printf("%d ", tabKey.at(nb));
    // }

    for(int i = 0; i < nTaille3; i++) {
        ImgOut[i] = ImgIn[i];
    }

    int id = 0;
    int keyVal;
    int temp;

    for (int i = 0; i < nTaille3; i += 3)
    {
        keyVal = tabKey.at(id) * 3;
        if(i + 2 + keyVal < nTaille3) {
            temp = ImgOut[i];
            ImgOut[i] = ImgOut[i + keyVal];
            ImgOut[i + keyVal] = temp;
            
            temp = ImgOut[i + 1];
            ImgOut[i + 1] = ImgOut[i + 1 + keyVal];
            ImgOut[i + 1 + keyVal] = temp;

            temp = ImgOut[i + 2];
            ImgOut[i + 2] = ImgOut[i + 2 + keyVal];
            ImgOut[i + 2 + keyVal] = temp;
        }

        id = id + 1 > TAILLE - 1 ? 0 : id + 1;
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);

    printf("\nDone!");

    return 1;
}
