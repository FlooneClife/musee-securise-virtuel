#include <stdio.h>
#include "image_ppm.h"
#include <math.h>
#include <array>
#include <algorithm>
#include <vector>
#include <random>

#include <fstream>
#include <iostream>
#include <string>


using namespace std;

int const SEED = 1000;
int const TAILLE = 500;

void copie(int nTaille, OCTET* ImgIn, OCTET* ImgOut){
      for (int i=0; i < (nTaille); i++)
       ImgOut[i]= ImgIn[i];
}

void printKey(  vector<int> tabKey){

  for(int nb = 0; nb < TAILLE; nb++) {
      printf("TabKey[%i] %d \n",nb,tabKey[nb] );   
  }

}

void suffleKey( vector<int> tabKey){
  for(int nb = 0; nb < TAILLE; nb++) {
        tabKey.push_back(nb);
  }
  shuffle(tabKey.begin(), tabKey.end(), default_random_engine(SEED));
}


void Chiffrement(int nTaille3, OCTET* ImgOut, vector<int> tabKey){

    int id = 0;
    int keyVal;
    int temp;

    for (int i = 0; i < nTaille3; i += 3)
    {
        keyVal = tabKey.at(id) * 3;
        if(i + 2 + keyVal < nTaille3) {
            temp = ImgOut[i];
            ImgOut[i] = ImgOut[i + keyVal];
            ImgOut[i + keyVal] = temp;
            
            temp = ImgOut[i + 1];
            ImgOut[i + 1] = ImgOut[i + 1 + keyVal];
            ImgOut[i + 1 + keyVal] = temp;

            temp = ImgOut[i + 2];
            ImgOut[i + 2] = ImgOut[i + 2 + keyVal];
            ImgOut[i + 2 + keyVal] = temp;
        }

        id = id + 1 > TAILLE - 1 ? 0 : id + 1;
    }

}

void Dechiffrement(int nTaille3,OCTET* ImgOut, vector<int> tabKey){

    int id = 0;
    int cpt = 0;
    for(int i = 0; i < nTaille3; i += 3) {
        id = id + 1 > TAILLE - 1 ? 0 : id + 1;
        if(id == 0) {
            cpt++;
        }
    }
    // printf("lastid = %d, cpt = %d\n", id, cpt);
    // printf("%d -- %d\n", nTaille / TAILLE, (nTaille / TAILLE) % TAILLE);

    id--;
    int keyVal;
    int temp;

    for (int i = nTaille3 - 3; i >= 0; i -= 3)
    {
        keyVal = tabKey.at(id) * 3;
        if(i + 2 + keyVal < nTaille3) {
            temp = ImgOut[i];
            ImgOut[i] = ImgOut[i + keyVal];
            ImgOut[i + keyVal] = temp;
            
            temp = ImgOut[i + 1];
            ImgOut[i + 1] = ImgOut[i + 1 + keyVal];
            ImgOut[i + 1 + keyVal] = temp;

            temp = ImgOut[i + 2];
            ImgOut[i + 2] = ImgOut[i + 2 + keyVal];
            ImgOut[i + 2 + keyVal] = temp;
        }

        id = id - 1 < 0 ? TAILLE - 1 : id - 1;
    }

}

int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nR, nG, nB ,D ;

    if (argc != 3)
    {
        printf("Usage: ImageIn.ppm  Chiffre\n");        
        printf("0 = Chiffrement et Déchiffrement\n");
        printf("1 = Chiffrement \n");
        printf("2 = Déchiffrement\n");

        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%d", &D);

    OCTET *ImgIn, *ImgOut, *ImgOut2;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);
    allocation_tableau(ImgOut2, OCTET, nTaille3);

   
    vector<int> tabKey;
    for(int nb = 0; nb < TAILLE; nb++) {
        tabKey.push_back(nb);
    }
    shuffle(tabKey.begin(), tabKey.end(), default_random_engine(SEED));

   // printKey(tabKey);
  
  string const nomFichier("Key.txt");

  ofstream monFlux(nomFichier.c_str());

  if(monFlux)  //On teste si tout est OK
  {
    //Tout est OK, on peut utiliser le fichier
    for(int nb = 0; nb < TAILLE; nb++) {
      monFlux << nb << " " <<tabKey[nb] << endl;
    }

  }
  else
  {
      cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
  }

  monFlux.close();


ifstream fichier(nomFichier.c_str());  //Ouverture d'un fichier en lecture

int TABkey[TAILLE];

if(fichier)
{
    //Tout est prêt pour la lecture. 

    string ligne; //Une variable pour stocker les lignes lues
         int i; int val;         
        fichier>>i;
         fichier>>val;
        TABkey[i]=val;
      while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
      {
        // cout << ligne << endl;
         fichier>>i;
         fichier>>val;
        TABkey[i]=val;
        //printf("i %i %i \n",i,val );

      }
}
else
{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
}

 fichier.close();

for (int i=0;i<TAILLE;i++){
    printf("TABkey[%i] =%i \n",i,TABkey[i] );
}

switch (D){
    case 0:{
         printf("Chiffrement ...\n");
          char nomOut[250]= "Chiffrement.ppm";
          copie(nTaille3, ImgIn,ImgOut);
          Chiffrement(nTaille3,ImgOut,  tabKey );
          ecrire_image_ppm(nomOut, ImgOut, nH, nW);


          printf("Déchiffrement ... \n");
          copie(nTaille3, ImgOut,ImgOut2 );
          Dechiffrement(nTaille3,ImgOut2,  tabKey );
          char nomOut1[250]= "Dechiffrement.ppm";
          ecrire_image_ppm(nomOut1, ImgOut2, nH,  nW );
          break;
      }
    case 1:
        {
          printf("Chiffrement ...\n");
          char nomOut2[250]= "Chiffrement.ppm";
          copie(nTaille3, ImgIn,ImgOut);
          Chiffrement(nTaille3,ImgOut,  tabKey );
          ecrire_image_ppm(nomOut2, ImgOut, nH, nW);
          break;
        }

    case 2:{
            
          printf("Déchiffrement ... \n");
          copie(nTaille3, ImgIn,ImgOut );
          Dechiffrement(nTaille3,ImgOut,  tabKey );
          char nomOut3[250]= "Dechiffrement.ppm";
          ecrire_image_ppm(nomOut3, ImgOut, nH,  nW );
          break;
      }
}
 



    free(ImgIn);

    printf("\nDone!");

    return 1;
}
