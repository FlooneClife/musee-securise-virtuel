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
int const nbBlocs = 20;

void copie(int nTaille, OCTET *ImgIn, OCTET *ImgOut)
{
    for (int i = 0; i < (nTaille); i++)
        ImgOut[i] = ImgIn[i];
}

void printKey(vector<int> tabKey)
{

    for (int nb = 0; nb < TAILLE; nb++)
    {
        printf("TabKey[%i] %d \n", nb, tabKey[nb]);
    }
}

void shuffleKey(vector<int> tabKey)
{
    for (int nb = 0; nb < TAILLE; nb++)
    {
        tabKey.push_back(nb);
    }
    shuffle(tabKey.begin(), tabKey.end(), default_random_engine(SEED));
}

void Chiffrement(int nTaille3, OCTET *ImgOut, vector<int> tabKey)
{

    int id = 0;
    int keyVal;
    int temp;

    for (int i = 0; i < nTaille3; i += 3)
    {
        keyVal = tabKey.at(id) * 3;
        if (i + 2 + keyVal < nTaille3)
        {
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

void Dechiffrement(int nTaille3, OCTET *ImgOut, vector<int> tabKey)
{
    int id = 0;
    int cpt = 0;
    for (int i = 0; i < nTaille3; i += 3)
    {
        id = id + 1 > TAILLE - 1 ? 0 : id + 1;
        if (id == 0)
        {
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
        if (i + 2 + keyVal < nTaille3)
        {
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

void Bloc(int nH, int nW, OCTET *ImgIn, OCTET *ImgOut)
{

    int sumR;
    int sumV;
    int sumB;
    int cptNbBlock = 0;
    for (int i = 0; i < nH * 3; i += nbBlocs * 3)
    {
        for (int j = 0; j < nW * 3; j += nbBlocs * 3)
        {
            sumR = 0;
            sumV = 0;
            sumB = 0;
            for (int k = i; k < i + (nbBlocs * 3); k += 3)
            {
                for (int l = j; l < j + (nbBlocs * 3); l += 3)
                {
                    if ((l < nW * 3) && (k < nH * 3))
                    {
                        sumR += ImgIn[k * nW + l];
                        sumV += ImgIn[k * nW + (l + 1)];
                        sumB += ImgIn[k * nW + (l + 2)];
                        cptNbBlock++;
                    }
                }
            }
            sumR /= cptNbBlock;
            sumV /= cptNbBlock;
            sumB /= cptNbBlock;

            for (int k = i; k < i + (nbBlocs * 3); k += 3)
            {
                for (int l = j; l < j + (nbBlocs * 3); l += 3)
                {
                    if ((l < nW * 3) && (k < nH * 3))
                    {
                        ImgOut[k * nW + l] = sumR;
                        ImgOut[k * nW + l + 1] = sumV;
                        ImgOut[k * nW + l + 2] = sumB;
                    }
                }
            }
            cptNbBlock = 0;
        }
    }
}

void Mini(int nH, int nW, OCTET *ImgIn, OCTET *ImgOut)
{
    int pxi = 0;
    int pxj = 0;

    for (int i = 0; i < nH * 3; i += nbBlocs * 3)
    {
        for (int j = 0; j < nW * 3; j += nbBlocs * 3)
        {
            ImgOut[pxi * (nW / nbBlocs) + pxj] = ImgIn[i * nW + j];
            ImgOut[pxi * (nW / nbBlocs) + (pxj + 1)] = ImgIn[i * nW + (j + 1)];
            ImgOut[pxi * (nW / nbBlocs) + (pxj + 2)] = ImgIn[i * nW + (j + 2)];
            pxj += 3;
        }
        pxi += 3;
        pxj = 0;
    }
}

void Reechantillonnage(int nH, int nW, OCTET *ImgIn, OCTET *ImgOut)
{
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
                    ImgOut[(i + y) * (nW * nbBlocs) + (j + x)] = ImgIn[pxi * nW + pxj];
                    ImgOut[(i + y) * (nW * nbBlocs) + (j + x + 1)] = ImgIn[pxi * nW + (pxj + 1)];
                    ImgOut[(i + y) * (nW * nbBlocs) + (j + x + 2)] = ImgIn[pxi * nW + (pxj + 2)];
                }
            }
            pxj += 3;
        }
        pxi += 3;
        pxj = 0;
    }
}

int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nR, nG, nB, D;

    if (argc != 3)
    {
        printf("Usage: ImageIn.ppm ImageOut.ppm\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgBloc, *ImgMini;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);

    nTaille = nH * nW;
    int nTaille3 = nTaille * 3;
    int nTailleMini = (nH / nbBlocs) * (nW / nbBlocs) * 3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgBloc, OCTET, nTaille3);
    allocation_tableau(ImgMini, OCTET, nTailleMini);

    string const nomFichier("Key.txt");

    ifstream fichier(nomFichier.c_str()); //Ouverture d'un fichier en lecture

    vector<int> TABkey;

    if (fichier)
    {
        //Tout est prêt pour la lecture.

        string ligne; //Une variable pour stocker les lignes lues
        int i;
        int val;
        fichier >> i;
        fichier >> val;
        TABkey.push_back(val);
        while (getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
        {
            // cout << ligne << endl;
            fichier >> i;
            fichier >> val;
            TABkey.push_back(val);
            // printf("i %i %i \n",i,val );
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }

    fichier.close();

    //conversion en blocs de 20x20
    printf("Conversion en blocs de 20x20 pixels...\n");
    Bloc(nH, nW, ImgIn, ImgBloc);

    //conversion en minis blocs de 1x1
    printf("Preparation au dechiffrement...\n");
    Mini(nH, nW, ImgBloc, ImgMini);

    //déchiffrement
    printf("Dechiffrement ... \n");
    // printf("%d \n", TABkey[0]);
    Dechiffrement(nTailleMini, ImgMini, TABkey);

    //rééchantillonnage (agrandir)
    printf("Finalisation du dechiffrement... \n");
    Reechantillonnage(nH/nbBlocs, nW/nbBlocs, ImgMini, ImgBloc);

    printf("Ecriture de l'image dechiffree... \n");
    ecrire_image_ppm(cNomImgEcrite, ImgBloc, nH, nW);
    // break;

    free(ImgIn);

    printf("\nDone!");

    return 1;
}
