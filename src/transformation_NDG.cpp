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
        printf("Usage: ImageIn.pgm ImageOut.pgm\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    float angle = 45.0f;
    int translationX = 30 * 3;
    int translationY = 30 * 3;
    float c = cos(angle * PI / 180.0f);
    float s = sin(angle * PI / 180.0f);
    float x, y;

    float centreX = (float)nW / 2.0;
    float centreY = (float)nH / 2.0;

    for (int i = 0; i < nH; i++) {
        for(int j = 0; j < nW; j++) {
            x = c * (float)(j - centreX) - s * (float)(i - centreY) + centreX;
            y = s * (float)(j - centreX) + c * (float)(i - centreY) + centreY;

            if((x >= 0 && x < nH) && (y >= 0 && y < nW)) {
                ImgOut[i * nW + j] = ImgIn[(int)y * nW + (int)x];
            } else {
                ImgOut[i * nW + j] = 128;
            }
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);

    printf("\nDone!");

    return 1;
}
