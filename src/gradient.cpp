#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nR, nG, nB;

    if (argc != 3) {
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

    int gradHor;
    int gradVer;
    int Y; //current Y
    int YVer; //pixel next to current
    int YHor; //pixel below current
    double norme;
    int finalVal;

    for (int i = 0; i < nH * 3 - 4; i += 3)
        for (int j = 0; j < nW * 3 - 4; j += 3) {
            Y = 0.299 * ImgIn[i * nW + j] + 0.587 * ImgIn[i * nW + (j + 1)] + 0.114 * ImgIn[i * nW + (j + 2)];
            YVer = 0.299 * ImgIn[i * nW + (j + 3)] + 0.587 * ImgIn[i * nW + (j + 4)] + 0.114 * ImgIn[i * nW + (j + 5)];
            YHor = 0.299 * ImgIn[(i + 3) * nW + j] + 0.587 * ImgIn[(i + 3) * nW + (j + 1)] + 0.114 * ImgIn[(i + 3) * nW + (j + 2)];
            gradVer = YVer - Y;
            gradHor = YHor - Y;
            norme = sqrt((gradVer * gradVer) + (gradHor * gradHor));
            finalVal = norme + 128;
            finalVal = finalVal > 255 ? 255 : finalVal < 0 ? 0 : finalVal;
            // ImgOut[i * nW + j] = finalVal;
            // ImgOut[i * nW + (j + 1)] = finalVal;
            // ImgOut[i * nW + (j + 2)] = finalVal;
            if(finalVal > 128) {
                ImgOut[i * nW + j] = 0;
                ImgOut[i * nW + (j + 1)] = 0;
                ImgOut[i * nW + (j + 2)] = 0;
            } else {
                ImgOut[i * nW + j] = 255;
                ImgOut[i * nW + (j + 1)] = 255;
                ImgOut[i * nW + (j + 2)] = 255;
            }
        }

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);

    printf("Done!");

    return 1;
}
