#include <allegro.h>
#include "tablice.h"
int dx2[]={-1,0,1,-1,1,-1,0,1};
int dy2[]={-1,-1,-1,0,0,1,1,1};

int ramka = 5;
int przerwa = 2;

void dodaj_bombe (int **tab, int X, int Y, int grid) {
    tab[X][Y]=9;
    for (int i=0; i<8; i++) if (X+dx2[i] >= 0 && Y+dy2[i] >= 0 && Y+dy2[i]<grid && X+dx2[i]<grid) tab[X+dx2[i]][Y+dy2[i]]++;
}

void wstaw_bomby(int **tab, int ile, int grid) {
    for (int licznik=0; licznik<ile; licznik++) {
        int i=rand()%grid;
        int j=rand()%grid;
        if (tab[i][j]<9) dodaj_bombe(tab, i, j, grid);
        else licznik--;
    }
}

void porzadek_z_bombami(int **tab, int grid) {
    for (int i=0; i<grid; i++) {
        for (int j=0; j<grid; j++) {
            if (tab[i][j]>9) tab[i][j]=9;
        }
    }
}

void wyswietl_tablice(int **tab, int grid, BITMAP *bufor) {
    for (int i=0; i<grid; i++) {
        for (int j=0; j<grid; j++) {
            if (tab[i][j]==0) textprintf_ex(bufor, font, 10+i*20, 10+j*20, makecol(0, 255, 255), -1, "%d", tab[i][j]);
            else if (tab[i][j]<9 && tab[i][j]>0) textprintf_ex(bufor, font, 10+i*20, 10+j*20, makecol(255, 255, 0), -1, "%d", tab[i][j]);
            else textprintf_ex(bufor, font, 10+i*20, 10+j*20, makecol(255, 0, 0), -1, "B");
        }
    }
}

void wyswietl_plansze(int **tab, int **gra, int rozmiar, int grid, BITMAP *bufor) {
    for (int i=0; i<grid; i++) {
        for (int j=0; j<grid; j++) {
            if (gra[i][j]==-1) rectfill(bufor, i*(rozmiar+przerwa)+ramka, j*(rozmiar+przerwa)+ramka, i*(rozmiar+przerwa)+ramka+rozmiar, j*(rozmiar+przerwa)+ramka+rozmiar, makecol(255,255,0));
            if (gra[i][j]==0) rectfill(bufor, i*(rozmiar+przerwa)+ramka, j*(rozmiar+przerwa)+ramka, i*(rozmiar+przerwa)+ramka+rozmiar, j*(rozmiar+przerwa)+ramka+rozmiar, makecol(100,100,100));
            if (gra[i][j]==1) {
                    rectfill(bufor, i*(rozmiar+przerwa)+ramka, j*(rozmiar+przerwa)+ramka, i*(rozmiar+przerwa)+ramka+rozmiar, j*(rozmiar+przerwa)+ramka+rozmiar, makecol(30,30,30));
                    if (tab[i][j]>0) textprintf_ex(bufor, font, i*(rozmiar+przerwa)+ramka+rozmiar/2-3, j*(rozmiar+przerwa)+ramka+rozmiar/2-3, makecol(255, 255, 0), -1, "%d", tab[i][j]);
            }
            if (gra[i][j]==9) rectfill(bufor, i*(rozmiar+przerwa)+ramka, j*(rozmiar+przerwa)+ramka, i*(rozmiar+przerwa)+ramka+rozmiar, j*(rozmiar+przerwa)+ramka+rozmiar, makecol(255,0,0));
        }
    }
}

void zeruj_tablice(int **tab, int grid) {
    for (int i=0; i<grid; i++) {
        for (int j=0; j<grid; j++) {
            tab[i][j]=0;
        }
    }
}

void odkryj(int **tab, int grid) {
    for (int i=0; i<grid; i++) {
        for (int j=0; j<grid; j++) {
            tab[i][j]=1;
        }
    }
}
