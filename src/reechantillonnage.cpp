#include <stdio.h>
#include "image_ppm.h"
#include <math.h>

int main(int argc, char *argv[])
{
    char cNomImgEcrite[250], cNomImgLue[250];
    int nH, nW, nTaille, nR, nG, nB, nbBlocs;

    if (argc != 4)
    {
        printf("Usage: ImageIn.ppm ImageOut.ppm nombreBlocs\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &nbBlocs);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3 * (nbBlocs * nbBlocs));

    int pxi = 0;
    int pxj = 0;
    int val;

    for (int i = 0; i < nH * 3 * nbBlocs; i += nbBlocs * 3)
    {
        for (int j = 0; j < nW * 3 * nbBlocs; j += nbBlocs * 3)
        {
            for (int y = 0; y < nbBlocs * 3; y += 3)
            {
                for (int x = 0; x < nbBlocs * 3; x += 3)
                {
                    ImgOut[(i + y) * (nW*nbBlocs) + (j + x)] = ImgIn[pxi * nW + pxj];
                    ImgOut[(i + y) * (nW*nbBlocs) + (j + x + 1)] = ImgIn[pxi * nW + (pxj + 1)];
                    ImgOut[(i + y) * (nW*nbBlocs) + (j + x + 2)] = ImgIn[pxi * nW + (pxj + 2)];
                }
            }
            pxj+=3;
        }
        pxi+=3;
        pxj=0;
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH * nbBlocs, nW * nbBlocs);
    free(ImgIn);

    printf("\nFini");
    return 1;
}
