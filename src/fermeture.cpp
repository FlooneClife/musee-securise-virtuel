#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nbBoucle;

  if (argc != 4)
  {
    printf("Usage: ImageIn.pgm ImageOut.pgm nbBoucle\n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgEcrite);
  sscanf(argv[3], "%d", &nbBoucle);

  OCTET *ImgIn, *ImgOut, *ImgInter;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);
  allocation_tableau(ImgInter, OCTET, nTaille);

  int i;
  int j;
  int n;

  for (i = 0; i < nH - 1; i++)
    for (j = 0; j < nW - 1; j++)
    {
      ImgOut[i * nW + j] = ImgIn[i * nW + j];
      ImgInter[i * nW + j] = ImgIn[i * nW + j];
    }

  for (n = 0; n < nbBoucle; n++)
  {
    for (i = 1; i < nH - 1; i++) {
      for (j = 1; j < nW - 1; j++)
      {
        if ((ImgIn[(i - 1) * nW + (j - 1)] == 0) || (ImgIn[(i - 1) * nW + (j)] == 0) || (ImgIn[(i - 1) * nW + (j + 1)] == 0) || (ImgIn[(i)*nW + (j - 1)] == 0) || (ImgIn[(i)*nW + (j + 1)] == 0) || (ImgIn[(i + 1) * nW + (j - 1)] == 0) || (ImgIn[(i + 1) * nW + (j)] == 0) || (ImgIn[(i + 1) * nW + (j + 1)] == 0))
        {
          ImgInter[i * nW + j] = 0;
        }
        else
        {
          ImgInter[i * nW + j] = 255;
        }
      }
    }
    for (i = 0; i < nH - 1; i++) {
      for (j = 0; j < nW - 1; j++) {
        ImgIn[i*nW+j] = ImgInter[i*nW+j];
      }
    }
  }

  for (n = 0; n < nbBoucle; n++)
  {
    for (i = 0; i < nH - 1; i++) {
      for (j = 0; j < nW - 1; j++)
      {
        if ((ImgInter[(i - 1) * nW + (j - 1)] == 255) || (ImgInter[(i - 1) * nW + (j)] == 255) || (ImgInter[(i - 1) * nW + (j + 1)] == 255) || (ImgInter[(i)*nW + (j - 1)] == 255) || (ImgInter[(i)*nW + (j + 1)] == 255) || (ImgInter[(i + 1) * nW + (j - 1)] == 255) || (ImgInter[(i + 1) * nW + (j)] == 255) || (ImgInter[(i + 1) * nW + (j + 1)] == 255))
        {
          ImgOut[i * nW + j] = 255;
        }
        else
        {
          ImgOut[i * nW + j] = 0;
        }
      }
    }
    for (i = 0; i < nH - 1; i++) {
      for (j = 0; j < nW - 1; j++) {
        ImgInter[i*nW+j] = ImgOut[i*nW+j];
      }
    }
  }

  printf("Done!");
  ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
  free(ImgIn);
  free(ImgInter);
  return 1;
  
}