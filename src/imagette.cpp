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
  allocation_tableau(ImgOut, OCTET, nTaille3/nbBlocs);

  int pxi = 0;
  int pxj = 0;

  for (int i = 0; i < nH * 3; i += nbBlocs * 3)
  {
    for (int j = 0; j < nW * 3; j += nbBlocs * 3)
    {
      ImgOut[pxi * (nW/nbBlocs) + pxj] = ImgIn[i * nW + j];
      ImgOut[pxi * (nW/nbBlocs) + (pxj + 1)] = ImgIn[i * nW + (j + 1)];
      ImgOut[pxi * (nW/nbBlocs) + (pxj + 2)] = ImgIn[i * nW + (j + 2)];
      pxj += 3;
    }
    pxi += 3;
    pxj = 0;
  }

  ecrire_image_ppm(cNomImgEcrite, ImgOut, nH/nbBlocs, nW/nbBlocs);
  free(ImgIn);

  printf("\nFini");
  return 1;
}
