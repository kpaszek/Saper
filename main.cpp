#include <allegro.h>
#include <fstream>
#include <iostream>
#include "tablice.h"
#include "gra.h"
#include "pliki.h"
#define N 100
#define width 600
#define height 630
using namespace std;

int dx[]={-1,0,1,-1,1,-1,0,1};
int dy[]={-1,-1,-1,0,0,1,1,1};

extern int ramka;
extern int przerwa;

inline void init()
{
	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);

	install_timer();
	install_keyboard();
	install_mouse();
}

inline void deinit()
{
	clear_keybuf();
	allegro_exit();
}

BITMAP *bufor = NULL;


int main()
{
	init();

    show_mouse(screen);
    unscare_mouse();
    bufor = create_bitmap(width, height);

    int ile = 10;
    int grid = 10;
    int wcisniety_kier = 0;
    int rozmiar;

    int X, Y;

    int klik=0;
    int win=0;
    int cheat=0;
    int wcisniety_c=0;
    int wcisniety_r=0;
    int wcisniety_z=0;
    int wcisniety_w=0;
    int zapisano=0;
    int edytor=0;
    int czy_wyzerowane=0;

    //int tab[N][N];
    //int gra[N][N];

    int **tab = new int*[N];
    for (int i=0; i<=N; i++) {
        tab[i] = new int[N];
    }
    int **gra = new int*[N];
    for (int i=0; i<=N; i++) {
        gra[i] = new int[N];
    }

    zeruj_tablice(tab, grid);
    odkryj(gra, grid);

    while (!key[KEY_ENTER] && !key[KEY_ESC] && !key[KEY_W]) {
        clear_to_color(bufor, makecol(0,0,0));
        if(key[KEY_E]) edytor=1;

        if (mouse_b==0) klik=0;

        if (edytor) {
            //odkryj(gra, grid);
            rozmiar = (height-30-(2*ramka)-(grid*przerwa))/grid;
            if (!czy_wyzerowane) {czy_wyzerowane=1; ile=0;}
            clear_to_color(bufor, makecol(0,0,0));
            wyswietl_plansze(tab, gra, rozmiar, grid, bufor);

            X=(mouse_x-ramka)/(rozmiar+przerwa);
            Y=(mouse_y-ramka)/(rozmiar+przerwa);

            textprintf_ex(bufor, font, width-580, height-20, makecol(0,255,0),-1,"Rozmiar: %d", grid);
            textprintf_ex(bufor, font, width-330, height-20, makecol(0,255,0),-1,"bombs: %d", ile);
            if (key[KEY_D]) debug(win, X, Y, grid, klik, bufor);

            if (X>=0 && X<grid && Y>=0 && Y<grid && mouse_b==1 && tab[X][Y]!=9 && !klik) {klik=1; dodaj_bombe(tab, X, Y, grid); porzadek_z_bombami(tab, grid); gra[X][Y]=9; ile++;}

        } else {
            rysuj_menu(bufor, grid, ile);
            if (key[KEY_D]) debug(win, X, Y, grid, klik, bufor);
            if (mouse_b && !klik) {
                klik=1;

                if (mouse_x>=10 && mouse_x<=147 && mouse_y>=10 && mouse_y<=197) {grid=8; ile=5; break;}
                if (mouse_x>=157 && mouse_x<=294 && mouse_y>=10 && mouse_y<=197) {grid=8; ile=15; break;}
                if (mouse_x>=304 && mouse_x<=441 && mouse_y>=10 && mouse_y<=197) {grid=8; ile=25;break;}
                if (mouse_x>=452 && mouse_x<=589 && mouse_y>=10 && mouse_y<=197) {grid=8; ile=40;break;}

                if (mouse_x>=10 && mouse_x<=147 && mouse_y>=207 && mouse_y<=394) {grid=25; ile=10;break;}
                if (mouse_x>=157 && mouse_x<=294 && mouse_y>=207 && mouse_y<=394) {grid=25; ile=30;break;}
                if (mouse_x>=304 && mouse_x<=441 && mouse_y>=207 && mouse_y<=394) {grid=25; ile=60;break;}
                if (mouse_x>=452 && mouse_x<=589 && mouse_y>=207 && mouse_y<=394) {grid=25; ile=125;break;}

                if (mouse_x>=10 && mouse_x<=90 && mouse_y>=404 && mouse_y<=510) { grid--;}
                if (mouse_x>=510 && mouse_x<=590 && mouse_y>=404 && mouse_y<=510) { grid++;}
                if (mouse_x>=10 && mouse_x<=90 && mouse_y>=520 && mouse_y<=620) { ile--;}
                if (mouse_x>=510 && mouse_x<=590 && mouse_y>=520 && mouse_y<=620) { ile++;}

                zeruj_tablice(tab, grid);
                odkryj(gra, grid);
            }
        }
        blit(bufor, screen, 0,0,0,0, width, height);
    }

    srand(time(0));
    rozmiar = (height-30-(2*ramka)-(grid*przerwa))/grid;
    zeruj_tablice(gra, grid);

    if (!edytor) {
        zeruj_tablice(tab, grid);
        wstaw_bomby(tab, ile, grid);
        porzadek_z_bombami(tab, grid);
    }

    int false_ile = ile;
    int fi;
	while (!key[KEY_ESC])
	{
        clear_to_color(bufor, makecol(0,0,0));

		wyswietl_plansze(tab, gra, rozmiar, grid, bufor);

        if (!key[KEY_C]) wcisniety_c=0;
		if (key[KEY_C] && !wcisniety_c) {
            cheat=cheat^1;
            wcisniety_c=1;
		}
		if (cheat) {
                wyswietl_tablice(tab, grid, bufor);
		}

		X=(mouse_x-ramka)/(rozmiar+przerwa);
        Y=(mouse_y-ramka)/(rozmiar+przerwa);

        int test_zaz;

        if (win==0) {
            if (mouse_b==0) klik=0;
            if (mouse_b==1) {if (gra[X][Y]!=-1) {if(klik==0) click(tab, gra, X, Y, grid); klik=1;}}
            if (mouse_b==2) {
                if (!gra[X][Y] && !klik) {
                    gra[X][Y]=-1;
                    klik = 1;
                    false_ile--;
                } else if (gra[X][Y]==-1 && !klik) {
                    gra[X][Y]=0;
                    klik = 1;
                    false_ile++;
                } else if (gra[X][Y] && !klik) {
                    klik=1;
                    test_zaz = 0;
                    for (int i=0; i<8; i++) {if (X+dx[i]>=0 && Y+dy[i]>=0 && X+dx[i]<grid && Y+dy[i]<grid) if (gra[X+dx[i]][Y+dy[i]]==-1) test_zaz++;}
                    if (test_zaz>=tab[X][Y]) {
                        for (int i=0; i<8; i++) {
                            if (X+dx[i]>=0 && Y+dy[i]>=0 && X+dx[i]<grid && Y+dy[i]<grid) if(!gra[X+dx[i]][Y+dy[i]]) click(tab, gra, X+dx[i], Y+dy[i], grid);
                        }
                    }
                }
            }
            fi = false_ile;
            if (fi<0) fi=0;
            textprintf_ex(bufor, font, width-370, height-20, makecol(255,255,0),-1,"Pozostalo bomb: %d", fi);
        }

        if (key[KEY_D]) debug(win, X, Y, grid, klik, bufor);
        //if (zapisano) textprintf_ex(bufor, font, width-190, height-240, makecol(255,0,0),-1,"ZAPISANO");

		win = czy_wygrana(tab, gra, ile, grid);
        if (win==1) {
            textprintf_ex(bufor, font, width-355, height-20, makecol(0,255,0),-1,"WYGRANA (R/ESC)");
        } else if (win==-1) {
            textprintf_ex(bufor, font, width-345, height-20, makecol(255,0,0),-1,"FAIL (R/ESC)");
            odkryj_bomby(tab, gra, grid);
            if (key[KEY_R]) {
                zeruj_tablice(tab, grid);
                zeruj_tablice(gra, grid);
                wstaw_bomby(tab, ile, grid);
                porzadek_z_bombami(tab, grid);
            }
        }

        blit(bufor, screen, 0,0,0,0, width, height);

        if (key[KEY_R] && !wcisniety_r) {
            wcisniety_r = 1;
            zeruj_tablice(tab, grid);
            zeruj_tablice(gra, grid);
            wstaw_bomby(tab, ile, grid);
            porzadek_z_bombami(tab, grid);
        }
        if (!key[KEY_R]) wcisniety_r = 0;
        if (key[KEY_Z] && !wcisniety_z) {zapisz_gre(tab, gra, grid, ile); wcisniety_z=1; zapisano=1;}
        if (!key[KEY_Z]) wcisniety_z = 0;
        if (key[KEY_W] && !wcisniety_w) {wczytaj_gre(tab, gra, &grid, &ile); wcisniety_w=1; rozmiar = (height-30-(2*ramka)-(grid*przerwa))/grid; false_ile = ile;}
        if (!key[KEY_W]) wcisniety_w = 0;
	}

	deinit();
	return 0;
}
END_OF_MAIN()
