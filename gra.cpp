#include<allegro.h>
#include "gra.h"
#define width 600
#define height 630

int dx3[]={-1,0,1,-1,1,-1,0,1};
int dy3[]={-1,-1,-1,0,0,1,1,1};

void debug (int win, int X, int Y, int grid, int klik, BITMAP* bufor) {
    textprintf_ex(bufor, font, width-190, height-80, makecol(0,255,0),-1,"mouse_b: %d", mouse_b);
    textprintf_ex(bufor, font, width-190, height-60, makecol(0,255,0),-1,"klik: %d", klik);
    textprintf_ex(bufor, font, width-190, height-40, makecol(0,255,0),-1,"win: %d", win);
    textprintf_ex(bufor, font, width-190, height-20, makecol(0,255,0),-1,"X = %d/%d, Y = %d/%d", X, grid-1, Y, grid-1);
}

void click(int **tab, int **gra, int X, int Y, int grid) {
    if (tab[X][Y]==9) gra[X][Y]=9;
    else gra[X][Y]=1;
    if (tab[X][Y]==0) {
        for (int i=0; i<8; i++) {
            if (X+dx3[i]>=0 && Y+dy3[i]>=0 && X+dx3[i]<grid && Y+dy3[i]<grid) if(!gra[X+dx3[i]][Y+dy3[i]]) /*if(!tab[X-1][Y-1])*/ click(tab, gra, X+dx3[i], Y+dy3[i], grid);
        }
    }
}

void odkryj_bomby (int **tab, int **gra, int grid) {
    for (int i=0;i<grid;i++) {
        for (int j=0;j<grid;j++) {
            if (tab[i][j]==9) click(tab, gra, i, j, grid);
        }
    }
}

int czy_wygrana(int **tab, int **gra, int ile, int grid) {
    int bombs = ile;
    for (int i=0; i<grid; i++) {
        for (int j=0; j<grid; j++) {
            if (gra[i][j]==9) return -1;
            if (gra[i][j]==-1 || gra[i][j]==0) {
                ile--;
                if (gra[i][j]==-1 && tab[i][j]==9) {
                    bombs--;
                }
            }
        }
    }
    if (!ile && !bombs) return 1;
    else return 0;
}

void rysuj_menu(BITMAP *bufor, int grid, int ile) {
    //pierwsze cztery kwadraty
    rectfill(bufor, 10, 10, 147, 197, makecol(100,100,100));
    rectfill(bufor, 157, 10, 294, 197, makecol(100,100,100));
    rectfill(bufor, 304, 10, 441, 197, makecol(100,100,100));
    rectfill(bufor, 452, 10, 589, 197, makecol(100,100,100));
    //drugie cztery kwadraty
    rectfill(bufor, 10, 207, 147, 394, makecol(100,100,100));
    rectfill(bufor, 157, 207, 294, 394, makecol(100,100,100));
    rectfill(bufor, 304, 207, 441, 394, makecol(100,100,100));
    rectfill(bufor, 452, 207, 589, 394, makecol(100,100,100));
    //rozmiary planszy
    rectfill(bufor, 10, 404, 90, 510, makecol(100,100,100));
    rectfill(bufor, 100, 404, 500, 510, makecol(100,100,100));
    rectfill(bufor, 510, 404, 590, 510, makecol(100,100,100));
    //ilosc bomb
    rectfill(bufor, 10, 520, 90, 620, makecol(100,100,100));
    rectfill(bufor, 100, 520, 500, 620, makecol(100,100,100));
    rectfill(bufor, 510, 520, 590, 620, makecol(100,100,100));

    textprintf_ex(bufor, font, width-565, height-550, makecol(0,255,0),-1,"MALA PLANSZA");
    textprintf_ex(bufor, font, width-540, height-530, makecol(0,255,0),-1,"LATWY");

    textprintf_ex(bufor, font, width-418, height-550, makecol(0,255,0),-1,"MALA PLANSZA");
    textprintf_ex(bufor, font, width-395, height-530, makecol(0,255,0),-1,"SREDNI");

    textprintf_ex(bufor, font, width-270, height-550, makecol(0,255,0),-1,"MALA PLANSZA");
    textprintf_ex(bufor, font, width-250, height-530, makecol(0,255,0),-1,"TRUDNY");

    textprintf_ex(bufor, font, width-125, height-550, makecol(0,255,0),-1,"MALA PLANSZA");
    textprintf_ex(bufor, font, width-110, height-530, makecol(0,255,0),-1,"PIEKIELNY");

    textprintf_ex(bufor, font, width-565, height-350, makecol(0,255,0),-1,"DUZA PLANSZA");
    textprintf_ex(bufor, font, width-540, height-330, makecol(0,255,0),-1,"LATWY");

    textprintf_ex(bufor, font, width-418, height-350, makecol(0,255,0),-1,"DUZA PLANSZA");
    textprintf_ex(bufor, font, width-395, height-330, makecol(0,255,0),-1,"SREDNI");

    textprintf_ex(bufor, font, width-270, height-350, makecol(0,255,0),-1,"DUZA PLANSZA");
    textprintf_ex(bufor, font, width-250, height-330, makecol(0,255,0),-1,"TRUDNY");

    textprintf_ex(bufor, font, width-125, height-350, makecol(0,255,0),-1,"DUZA PLANSZA");
    textprintf_ex(bufor, font, width-110, height-330, makecol(0,255,0),-1,"PIEKIELNY");

    textprintf_ex(bufor, font, width-370, height-175, makecol(0,255,0),-1,"ROZMIAR PLANSZY: %d", grid);
    textprintf_ex(bufor, font, width-350, height-60, makecol(0,255,0),-1,"ILOSC BOMB: %d", ile);
    textprintf_ex(bufor, font, width-50, height-175, makecol(0,255,0),-1,">");
    textprintf_ex(bufor, font, width-50, height-60, makecol(0,255,0),-1,">");
    textprintf_ex(bufor, font, width-555, height-175, makecol(0,255,0),-1,"<");
    textprintf_ex(bufor, font, width-555, height-60, makecol(0,255,0),-1,"<");
}

