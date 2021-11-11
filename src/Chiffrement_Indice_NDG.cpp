// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

void copie(int nTaille, OCTET* ImgIn, OCTET* ImgOut){
      for (int i=0; i < (nTaille); i++)
       ImgOut[i]= ImgIn[i];
}

void EchangeLigne(int nK ,int tabKey[], int nW ,  OCTET* ImgIn, OCTET* ImgOut, int i, int j){

	int tabKeyCopie[nK];
	for (int k=0; k < nK;k++){

		tabKeyCopie[k]= i + tabKey[k];
	
	}

	for (int p=0; p<nK ; p++){
		int I = tabKeyCopie[p];

		for(int J=j; J<nW;J++){
		
			ImgOut[(i + p)*nW+J] = ImgIn[I*nW+J];

		//ImgOut[I*nW+j] = ImgIn[(i + p)*nW+j];
		
		}
	}

}

void ChiffrementIndice(int nW, int nH, int tabKey[], int nTabKey, OCTET* ImgIn, OCTET* ImgOut){

	int taille = nW;
	int i=0;
	int j=0;
	while (taille >= nTabKey){
		
		EchangeLigne(nTabKey ,tabKey, nW ,ImgIn,ImgOut,  i,  j);
		taille = taille - nTabKey;
	 	i+=nTabKey;
	 	
	}

//	EchangeLigne(taille,tabKey, nW ,ImgIn,ImgOut,  i,  j);

}

void EchangeLigneBIS(int nTabKey ,int tabKey[], int nW ,  OCTET* ImgIn, OCTET* ImgOut, int i, int j){

	int tabKeyCopie[nTabKey];
	for (int k=0; k < nTabKey;k++){

		tabKeyCopie[k]= i + tabKey[k];
	
	}

	for (int p=0; p<nTabKey ; p++){
		int I = tabKeyCopie[p];

		for(int J=j; J<nW;J++){
		
		//	ImgOut[(i + p)*nW+J] = ImgIn[I*nW+J];

			ImgOut[I*nW+J] = ImgIn[(i + p)*nW+J];
		
		}
	}

}

void DeChiffrementIndice(int nW, int nH, int tabKey[], int nTabKey,  OCTET* ImgIn, OCTET* ImgOut){

	int taille = nW;
	int i=0;
	int j=0;
	while (taille >= nTabKey){
		
		EchangeLigneBIS(nTabKey ,tabKey, nW ,ImgIn,ImgOut,  i,  j);
		taille = taille - nTabKey;
	 	i+=nTabKey;
	 	
	}

}

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 2) 
     {
       printf("Usage: ImageIn.pgm  \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
  // sscanf (argv[2],"%s",cNomImgEcrite);
  // sscanf (argv[3],"%d",&S);

   OCTET *ImgIn, *ImgOut, *ImgOutC;
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

   allocation_tableau(ImgOut, OCTET, nTaille);
   allocation_tableau(ImgOutC, OCTET, nTaille);
 
 int tabKey[10]={9,7,4,1,0,8,3,5,2,6};
 
 printf("Chiffrement Indice \n");
 copie( nTaille, ImgIn, ImgOut);
 ChiffrementIndice( nW,  nH,  tabKey,10, ImgIn, ImgOut);
 char nomOut[250]= "ChiffrementLigne.pgm";
 ecrire_image_pgm(nomOut, ImgOut, nH,  nW );

/*
  printf("Déchiffrement Indice \n");
 DeChiffrementIndice( nW,  nH,  tabKey,10, ImgOut, ImgOutC);
  char nomOut1[250]= "DeChiffrementLigne.pgm";
  ecrire_image_pgm(nomOut1, ImgOut, nH,  nW );
*/

  free(ImgIn);
  return 1;
}
