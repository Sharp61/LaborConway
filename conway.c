#include <c64.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define P_SCREEN0 ((unsigned char *)0x2000)
#define P_COLOR0  ((unsigned char *)0x0400)

#define P_SCREEN1 ((unsigned char *)0x6000)
#define P_COLOR1  ((unsigned char *)0x4400)

//HighRes Mode 300x200px
#define XMAX 40
#define YMAX 25
#define BOXSIZE 3
#define ROUNDS 1

// void findNachbarn();
// void initSpielfeld(char spielfeld [][YMAX]);
void printSpielfeld();
// void zaehlLebende();
// void pruefeRegeln(char x, char y,  char lebende, char temp[][YMAX], char spielfeld[][YMAX]);

//static const char array[XMAX][YMAX] 
/*const static*/ char spielfeld[XMAX][YMAX]= {
{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
};

// static char spielfeld[XMAX][YMAX];
static char temp[XMAX][YMAX];
// static char nachbarn[BOXSIZE][BOXSIZE];
char lebende;

char main(void)
{
	  clock_t       t;
	  unsigned long sec;
	  unsigned      sec10;
	  unsigned long fps;
	  unsigned      fps10;
	  unsigned char background;
	  unsigned char text;

	  register char x, y, top, bottom, left, right, round = 0;


	
	// initSpielfeld(spielfeld);
		clrscr();
		background = bgcolor(COLOR_BLACK);
		text = textcolor(COLOR_WHITE);
		printSpielfeld();
	//	signal (int sig, __sigfunc func);
		t = clock ();


	while(round < ROUNDS && !kbhit())
	{
		for(y = 0; y< YMAX; y++)
		{
			for(x = 0; x< XMAX; x++)
			{

				// findNachbarn();
				// zaehlLebende();
				
				left = x-1;
				right = x+1;
				top = y-1;
				bottom = y+1;

					if(x==0)
					{
						left = XMAX-1;
					}
					else if(x==XMAX-1)
					{
						right = 0;
					}
					if(y==0)
					{
						top=YMAX-1;
					}
					else if(y==YMAX-1)
					{
						bottom=0;
					}

					lebende = 0;
	
					lebende += spielfeld[left][top];
					lebende += spielfeld[left][bottom];
					lebende += spielfeld[left][y];
					lebende += spielfeld[right][top];
					lebende += spielfeld[right][bottom];
					lebende += spielfeld[right][y];
					lebende += spielfeld[x][top];
					lebende += spielfeld[x][bottom];

					switch(lebende)
					{
						case 2:	temp[x][y] = spielfeld[x][y];
						break;
						case 3: temp[x][y] = 1;
						break;
						default: temp[x][y] = 0;
						break;
					}
				
			}// for x
		}// for y

		memmove(spielfeld,temp,XMAX*YMAX);
	
		round++;
		printSpielfeld();	
	}
		t = clock() - t;
	
  /* Reset screen colors */
    bgcolor (background);
    textcolor (text);
    clrscr ();

    /* Calculate stats */
    sec   = (t * 10) / CLK_TCK;
    sec10 = sec % 10;
    sec  /= 10;
    fps   = (round * (CLK_TCK * 10)) / t;
    fps10 = fps % 10;
    fps  /= 10;

    /* Output stats */
    gotoxy (0, 0); cprintf ("time  : %lu.%us", sec, sec10);
    // gotoxy (0, 1); cprintf ("frames: %lu", round);
    // gotoxy (0, 2); cprintf ("fps   : %lu.%u", fps, fps10);

    /* Wait for a key, then end */
    cputsxy (0, 4, "Press any key when done...");
    (void) cgetc ();

    /* Done */
    return EXIT_SUCCESS;
}



/* void pruefeRegeln(char x, char y, char lebende, char temp[][YMAX], char spielfeld[][YMAX])
{
	switch(lebende)
	{
		case 2:	temp[x][y] = spielfeld[x][y];
		break;
		case 3: temp[x][y] = 1;
		break;
		default: temp[x][y] = 0;
		break;
	}
}

void zaehlLebende()
{
	lebende = 0;
	
	lebende += nachbarn[0][0];
	lebende += nachbarn[0][1];
	lebende += nachbarn[0][2];
	lebende += nachbarn[1][0];
	lebende += nachbarn[2][0];
	lebende += nachbarn[2][1];
	lebende += nachbarn[1][2];
	lebende += nachbarn[2][2];
}



void findNachbarn()
{
	//gehe über alle nachbarn
	unsigned int osx, ix;
	unsigned int osy, iy; 
	signed int ofy;
	signed int ofx;
	
	for(ofy = y-1, iy=0; ofy <= (signed int)y+1; ++ofy , ++iy){
		for(ofx = x-1,ix = 0; ofx <= (signed int)x+1; ++ofx , ++ix){
	
			if( ofy < 0)	{
				osy = YMAX-1;
			}
			else if( ofy > YMAX-1)	{
					osy = 0;
				}
				else {
					osy = ofy;
				}
			
			
			if( ofx < 0)	{
				osx = XMAX-1;
			} else if( ofx > XMAX-1)	{
					osx = 0;
				}
				else {
					osx = ofx;
				}
			nachbarn[ix][iy] = spielfeld[osx][osy];				
		}//for ofx
	} //for ofy	

	if( y - 1 < 0)
	{
        y = YMAX-1;
    }
    else if( y > YMAX-1)
	{
        y = 0;
    }
    else{
        y = y;
    }    
    if( x - 1 < 0)
	{
        x = XMAX-1;
    } 
    else if( x > XMAX-1)
	{
        x = 0;
    }
    else
	{
        x = x;
    }

    nachbarn[0][0] = spielfeld[x - 1][y - 1];
    nachbarn[0][1] = spielfeld[x][y - 1];
    nachbarn[0][2] = spielfeld[x + 1][y - 1];
    nachbarn[1][0] = spielfeld[x - 1][y];
    nachbarn[1][2] = spielfeld[x + 1][y];
    nachbarn[2][0] = spielfeld[x - 1][y + 1];
    nachbarn[2][1] = spielfeld[x][y + 1];
    nachbarn[2][2] = spielfeld[x + 1][y + 1];

}
*/



void printSpielfeld()
{
	char x,y;
	for(y = 0; y< YMAX; y++){
		for(x = 0; x< XMAX; x++){
			if(spielfeld[x][y] == 1){
				revers(1);
			} else{
				revers(0);
			}		
 			cputcxy (x, y, 32);
		}
	}
}



/*void initSpielfeld(char spielfeld [][YMAX]){
	char x,y;
	//fülle das feld mit zufallswerten und gibs aus
	for(y = 0; y< YMAX; y++){
		for(x = 0; x< XMAX; x++){
				spielfeld[x][y] = array[x][y];
		}
	}
}*/
