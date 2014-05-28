#include "pliki.h"
#include <fstream>
using namespace std;

void zapisz_gre(int **tab, int **gra, int grid, int ile) {
    fstream plik;
    plik.open("gra.txt", ios::out);
    plik<<grid<<endl;
    plik<<ile<<endl;
    for (int i=0; i<grid; i++) {
        for (int j=0; j<grid; j++) {
            plik<<tab[j][i]<<" ";
        }
        plik<<endl;
    }
    for (int i=0; i<grid; i++) {
        for (int j=0; j<grid; j++) {
            plik<<gra[j][i]<<" ";
        }
        plik<<endl;
    }
    plik.close();
}

void wczytaj_gre(int **tab, int **gra, int* grid, int* ile) {
    fstream plik("gra.txt");
    plik>>*grid;
    plik>>*ile;
    for (int i=0; i<*grid; i++) {
        for (int j=0; j<*grid; j++) {
            plik>>tab[j][i];
        }
    }
    for (int i=0; i<*grid; i++) {
        for (int j=0; j<*grid; j++) {
            plik>>gra[j][i];
        }
    }
    plik.close();
}
