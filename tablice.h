#ifndef tablice_h
#define tablice_h
void dodaj_bombe (int **tab, int X, int Y, int grid);
void wstaw_bomby(int **tab, int ile, int grid);
void porzadek_z_bombami(int **tab, int grid);
void wyswietl_tablice(int **tab, int grid, BITMAP *bufor);
void wyswietl_plansze(int **tab, int **gra, int rozmiar, int grid, BITMAP *bufor);
void zeruj_tablice(int **tab, int grid);
void odkryj(int **tab, int grid);
#endif
