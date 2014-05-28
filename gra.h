#ifndef gra_h
#define gra_h

void debug (int win, int X, int Y, int grid, int klik, BITMAP* bufor);
void click(int **tab, int **gra, int X, int Y, int grid);
void odkryj_bomby (int **tab, int **gra, int grid);
int czy_wygrana(int **tab, int **gra, int ile, int grid);
void rysuj_menu(BITMAP *bufor, int grid, int ile);

#endif

