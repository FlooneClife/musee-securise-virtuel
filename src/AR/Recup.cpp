#include "image_ppm.h"
#include <stdio.h>



void copie(int nTaille, OCTET* ImgIn, OCTET* ImgOut){
      for (int i=0; i < (nTaille); i++)
       ImgOut[i]= ImgIn[i];
}



int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgLue2[250];
    int nH, nW, nTaille, nR, nG, nB;

    if (argc != 3)
    {
        printf("Usage: ImageIn.ppm ImageContour.ppm \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgLue2);
    //sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgContour, *ImgOut, *ImgOut2;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    allocation_tableau(ImgContour, OCTET, nTaille3);

    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    lire_image_ppm(cNomImgLue2, ImgContour, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille3);
    allocation_tableau(ImgOut2, OCTET, nTaille3);

    int cpt=0; int k=0;
	while (ImgContour[k] == 0){
		k++;
		cpt++;
	}

	int incr=nTaille3; int l=nTaille3;
	while (ImgContour[l] == 0){
		incr--;
		l--;
	}
	printf("%i %i \n",cpt , incr );
   
   for(int i=0;i<nW*3;i++){
   		
		for(int j=0;j<nW*3;j++){
			
			if(ImgContour[i * nW + j] == 0 && ( (i * nW + j) > cpt  && (i * nW + j) < incr ) )   {
				ImgOut[i * nW + j]=ImgIn[i * nW + j];
			}
			else{
				ImgOut[i * nW + j]=0;
			}

		}
   	
   }   
/*
 int a=0,b=0; bool trouv=true;
while(trouv){
	a=0;
 for(int i=0;i<nW*3;i++){
   		
		for(int j=0;j<nW*3;j++){
			if(ImgOut[j * nW + i]==0)
				a++;
	}
	if (a==nW-1) {b=i; trouv=false;}
}
}
printf("%i \n", b );

   for(int i=0;i<nW*3;i++){
   		
		for(int j=0;j<nW*3;j++){

			if( ( (j * nW + i) > cpt  && (j * nW + i) < incr )  && (ImgOut[j * nW + i] !=0) ) {
				ImgOut2[j * nW + i]=ImgOut[j * nW + i];
			}
			else{
				ImgOut2[j * nW + i]=255;
			}

		}
   	
   }
*/


  printf("Recuperation de l'image ...\n");
  char nomOut[250]= "Recup.ppm";

  ecrire_image_ppm(nomOut, ImgOut, nH, nW);

  //char nomOut2[250]= "Recup2.ppm";
  //ecrire_image_ppm(nomOut2, ImgOut2, nH, nW);



    

    free(ImgIn);
    printf("\nDone!");
    return 1;
}
