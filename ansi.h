#include <stdio.h>

enum { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE } ;

#define FGCOLOR(V)	printf("\x1b[%dm", 30 + (V) )	// Foreground Color
#define BGCOLOR(V)	printf("\x1b[%dm", 40 + (V) )	// Background Color
#define UNDERLINE	printf("\x1b[4m" )
#define	RESET		printf("\x1b[0m" )				// Reset attributes

#define CUU(N)		printf("\x1b[%dA", N )			// Cursor Up
#define CUD(N)		printf("\x1b[%dB", N )			// Cursor Down
#define CUF(N)		printf("\x1b[%dC", N )			// Cursor Forward
#define CUB(N)		printf("\x1b[%dD", N )			// Cursor Back
#define CHA(X)		printf("\x1b[%dG", X )			// Cursor Horizontal Absolute
#define	CUP(X,Y)	printf("\x1b[%d;%dH", Y, X )	// Cursor Position
#define CLRSCR		CUP(1,1) ; printf("\x1b[2J")	// Clear Screen
