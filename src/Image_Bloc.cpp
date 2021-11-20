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

void copie(int nTaille, OCTET* ImgIn, OCTET* ImgOut){
      for (int i=0; i < (nTaille); i++)
       ImgOut[i]= ImgIn[i];
}



void Bloc(int nH, int nW,OCTET* ImgIn, OCTET* ImgOut){

   int sumR;
   int sumV;
   int sumB;
// 12 car je fais des blocs de 4x4 pour commencer donc 3 *4 = 12
    for (int i = 0; i < nH * 3 ; i += 12){
     
      for (int j = 0; j < nW * 3; j += 12){ 
        sumR =0;
        sumV =0;
        sumB =0;

      for (int k = i ; k <= i + 12; k += 3){
        for (int l = j ; l <= j + 12; l += 3) {
         sumR += ImgIn[k * nW +l];
         sumV += ImgIn[k * nW +(l + 1)];
         sumB += ImgIn[k * nW +(l+ 2)];
      
        }}

        for (int k = i ; k <= i + 12; k += 3){
        for (int l = j ; l <= j + 12; l += 3) {
            ImgOut[k * nW +l] = (sumR / 24) > 255 ? 255 : sumR / 24 ;
            ImgOut[k * nW +l + 1] = (sumV / 24) > 255 ? 255 : sumV / 24  ;
            ImgOut[k * nW +l + 2] = (sumB / 24) > 255 ? 255 : sumB / 24  ;
      //24 car 2*12
        }}


      }


    }

}

void BlocV2(int nH, int nW,OCTET* ImgIn, OCTET* ImgOut){

   int sumR;
   int sumV;
   int sumB;
    for (int i = 0; i < nH * 3 - 48 ; i += 48){
     
      for (int j = 0; j < nW * 3 - 48 ;  j += 48){ 
        sumR =0;
        sumV =0;
        sumB =0;

      for (int k = i ; k <= i + 48; k += 3){
        for (int l = j ; l <= j + 48; l += 3) {
         sumR += ImgIn[k * nW +l];
         sumV += ImgIn[k * nW +(l + 1)];
         sumB += ImgIn[k * nW +(l+ 2)];
      
        }}

        for (int k = i ; k <= i + 48; k += 3){
        for (int l = j ; l <= j + 48; l += 3) {
            ImgOut[k * nW +l] = (sumR / (48 * 5) ) > 255 ? 255 : sumR / (48 * 5) ;
            ImgOut[k * nW +l + 1] = (sumV / (48 * 5)) > 255 ? 255 : sumV / (48 * 5)  ;
            ImgOut[k * nW +l + 2] = (sumB / (48 * 5)) > 255 ? 255 : sumB / (48 * 5)  ;
        }}


      }


    }

}


int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nR, nG, nB;

    if (argc != 2)
    {
        printf("Usage: ImageIn.ppm \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    //sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut, *ImgOut2;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);
    allocation_tableau(ImgOut2, OCTET, nTaille3);


  printf("Creation de la nouvelle image ...\n");
  char nomOut[250]= "Bloc.ppm";
//  copie(nTaille3, ImgIn,ImgOut);
  Bloc(nH,nW,ImgIn,ImgOut);
  ecrire_image_ppm(nomOut, ImgOut, nH, nW);
 
  printf("Creation de la nouvelle image BIS...\n");
  char nomOut2[250]= "BlocV2.ppm";
//  copie(nTaille3, ImgIn,ImgOut);
  BlocV2(nH,nW,ImgIn,ImgOut2);
  ecrire_image_ppm(nomOut2, ImgOut2, nH, nW);


 
    free(ImgIn);

    printf("\nDone!");

    return 1;
}