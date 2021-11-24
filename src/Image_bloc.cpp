#include <stdio.h>
#include "image_ppm.h"
#include <math.h>
#include <array>
#include <algorithm>
#include <vector>
#include <random>

#include <fstream>
#include <iostream>

using namespace std;

int const SEED = 1000;
int const TAILLE = 500;
int nbBloc;

void copie(int nTaille, OCTET* ImgIn, OCTET* ImgOut){
      for (int i=0; i < (nTaille); i++)
       ImgOut[i]= ImgIn[i];
}



void Bloc(int nH, int nW,OCTET* ImgIn, OCTET* ImgOut){

   int sumR;
   int sumV;
   int sumB;
   int cptNbBlock = 0;
    for (int i = 0; i < nH * 3 ; i += nbBloc * 3){
      for (int j = 0; j < nW * 3; j += nbBloc * 3){ 
        sumR =0;
        sumV =0;
        sumB =0;
        for (int k = i ; k < i + (nbBloc*3); k += 3){
          for (int l = j; l < j + (nbBloc*3); l += 3) {
            if((l < nW * 3) && (k < nH * 3)) {
              sumR += ImgIn[k * nW +l];
              sumV += ImgIn[k * nW +(l + 1)];
              sumB += ImgIn[k * nW +(l + 2)];
              cptNbBlock++;
            }
          }
        }
        sumR /= cptNbBlock;
        sumV /= cptNbBlock;
        sumB /= cptNbBlock;

        for (int k = i ; k < i + (nbBloc*3); k += 3){
          for (int l = j ; l < j + (nbBloc*3); l += 3) {
            if((l < nW * 3) && (k < nH * 3)) {
            ImgOut[k * nW +l] = sumR;
            ImgOut[k * nW +l + 1] = sumV;
            ImgOut[k * nW +l + 2] = sumB;
            }
          }
        }
        cptNbBlock = 0;
      }
    }

}

int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nR, nG, nB;

    if (argc != 4)
    {
        printf("Usage: ImageIn.ppm ImageOut.ppm nbBloc\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &nbBloc);

    OCTET *ImgIn, *ImgOut, *ImgOut2,*ImgOut3;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);
    allocation_tableau(ImgOut2, OCTET, nTaille3);    
    allocation_tableau(ImgOut3, OCTET, nTaille3);


  printf("Creation de la nouvelle image %dx%d ...\n", nbBloc, nbBloc);
//  copie(nTaille3, ImgIn,ImgOut);
  Bloc(nH,nW,ImgIn,ImgOut);
  ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);

    free(ImgIn);
    printf("\nDone!");
    return 1;
}
