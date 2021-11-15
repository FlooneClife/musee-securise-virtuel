// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

void copie(int nTaille, OCTET* ImgIn, OCTET* ImgOut){
      for (int i=0; i < (nTaille); i++){
       ImgOut[i]= ImgIn[i];

     }
}

int genKey(int nTaille){
  int res;
  res = rand()%nTaille;
 //printf( "Résultat de la génération pseudo aléatoire: %i \n",res);
 return res;
}

bool verifTab(int tabKey[], int taille){
  bool x = false;
  for (int i=0;i<taille;i++){ 
    for (int j=0;j<taille;j++){
      if ( i != j && tabKey[i] == tabKey[j] )
        x=true;
     }
  }
printf("%s", x ? "true \n " : "false \n ");
return x;
}

void afficheTab(int tabKey[], int taille){
  for (int i=0;i<taille;i++){ 
  printf(" Tab [%i] = %i \n", i, tabKey[i]);
  }
}


void aleatKey(int tabKey[],int taille){

  for (int i=0;i<taille;i++){
    tabKey[i]=-1;
  }
 
 for (int i=0;i<taille;i++){
    int rand = genKey(taille);
    bool existe=true;
    int cpt = 0;
      while( existe  ){

        for (int j=0;j<taille;j++){
           if (rand == tabKey[j] && verifTab(tabKey,taille) ){
            rand = genKey(taille);

           // printf("test i %i j %i rand %i \n",i ,j,rand);
           }        
        }
        cpt++;
        if (cpt == 25) existe = false;
      }

    tabKey[i]=rand;
  }

}

void EchangeLigne(int nK ,int tabKey[], int nW ,  OCTET* ImgIn, OCTET* ImgOut, int i, int j){

	int tabKeyCopie[nK];
	for (int k=0; k < nK;k++){

		tabKeyCopie[k]= i + tabKey[k];
	
	}


	for (int p=0; p<nK ; p++){
		int I = tabKeyCopie[p] ;

		for(int J=j; J< nW*nW ;J+=3){
		
      ImgOut[(i + p)*3*nW+J] = ImgIn[I*3*nW+J];

      ImgOut[(i + p)*3*nW+(J+1)] = ImgIn[I*3*nW+(J+1)];
      ImgOut[(i + p)*3*nW+(J+2)] = ImgIn[I*3*nW+(J+2)];

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
//Piste: pour gérer le fait que la clé soit "plus courte" que l'image, 
// on peut refaire une clé aléatoire avec le nb de ligne qui reste 

//	EchangeLigne(taille,tabKey, nW ,ImgIn,ImgOut,  i,  j);

}

void EchangeLigneBIS(int nTabKey ,int tabKey[], int nW ,  OCTET* ImgIn, OCTET* ImgOut, int i, int j){

	int tabKeyCopie[nTabKey];
	for (int k=0; k < nTabKey;k++){

		tabKeyCopie[k]= i + tabKey[k];
	
	}

	for (int p=0; p<nTabKey ; p++){
		int I = tabKeyCopie[p];

		for(int J=j; J< nW*nW; J+=3){
		
		//	ImgOut[(i + p)*nW+J] = ImgIn[I*nW+J];

      ImgOut[I*3*nW+J] = ImgIn[(i + p)*3*nW+J];
      ImgOut[I*3*nW+(J+1)] = ImgIn[(i + p)*3*nW+(J+1)];
      ImgOut[I*3*nW+(J+2)] = ImgIn[(i + p)*3*nW+(J+2)];
		

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
       printf("Usage: ImageIn.ppm  \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
  // sscanf (argv[2],"%s",cNomImgEcrite);
  // sscanf (argv[3],"%d",&S);

   OCTET *ImgIn, *ImgOut, *ImgOutC;
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

   allocation_tableau(ImgOut, OCTET, nTaille3);
   allocation_tableau(ImgOutC, OCTET, nTaille3);
/*
  int key1 = 97410;
  srand(key1);

  int tabKey[100];
  aleatKey(tabKey,100);
 
  printf(" Dernière vérif : \n");
  verifTab(tabKey,100);
  afficheTab(tabKey,100);
*/
 int tabKey2[10]={9,7,4,1,0,8,3,5,2,6};
 
 printf("Chiffrement Indice \n");
 //copie( nTaille3, ImgIn, ImgOut);
 ChiffrementIndice( nW,  nH,  tabKey2,10, ImgIn, ImgOut);
 char nomOut[250]= "Chiffrement_Couleur.ppm";
 ecrire_image_ppm(nomOut, ImgOut, nH,  nW );

  printf("Déchiffrement Indice \n");
 DeChiffrementIndice( nW,  nH,  tabKey2,10, ImgOut, ImgOutC);
  char nomOut1[250]= "Dechiffrement_Couleur.ppm";
  ecrire_image_ppm(nomOut1, ImgOutC, nH,  nW );

  
  free(ImgIn);
  return 1;
}
