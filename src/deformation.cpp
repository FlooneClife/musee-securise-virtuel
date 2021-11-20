#include <stdio.h>
#include "image_ppm.h"
#include <math.h>
#include <tgmath.h>

#define PI 3.14159265

int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nR, nG, nB;

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

    float alpha = -0.3f;
    float beta = -0.2f;
    float x, y;

    float centreX = (float)(nW * 3.0) / 2.0;
    float centreY = (float)(nH * 3.0) / 2.0;

    int intX, intY;

    for (int i = 0; i < nH * 3; i+=3) {
        for(int j = 0; j < nW * 3; j+=3) {
            x = j + alpha * i;
            y = i + beta * j;
            intX = (int)x - ((int)x % 3);
            intY = (int)y - ((int)y % 3);

            if((x >= 0 && x < nH * 3) && (y >= 0 && y < nW * 3)) {
                ImgOut[i * nW + j] = ImgIn[intY * nW + intX];
                ImgOut[i * nW + (j+1)] = ImgIn[intY * nW + intX + 1];
                ImgOut[i * nW + (j+2)] = ImgIn[intY * nW + intX + 2];
            } else {
                ImgOut[i * nW + j] = 128;
                ImgOut[i * nW + (j+1)] = 128;
                ImgOut[i * nW + (j+2)] = 128;
            }
        }
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);

    printf("\nDone!");

    return 1;
}
