/* supp.c -- support routines for dungeon */

#include <stdio.h>

#ifdef unix
#include <sys/types.h>
#endif

#ifdef BSD4_2
#include <sys/time.h>
#else /* ! BSD4_2 */
#include <time.h>
#endif /* ! BSD4_2 */

#include "funcs.h"

/* Define these here to avoid using <stdlib.h> */

extern void exit P((int));
extern int rand P((void));

/* We should have a definition for time_t and struct tm by now.  Make
 * sure we have definitions for the functions we want to call.
 * The argument to localtime should be P((const time_t *)), but Ultrix
 * 4.0 leaves out the const in their prototype.  Damn them.
 */

extern time_t time P((time_t *));
extern struct tm *localtime ();

/* Terminate the game */

void exit_()
{
    fprintf(stderr, "The game is over.\n");
    fflush(stdout);
    exit(0);
}

/* Get time in hours, minutes and seconds */

void itime_(int *hrptr, int *minptr, int *secptr)
{
	time_t timebuf;
	struct tm *tmptr;

	time(&timebuf);
	tmptr = localtime(&timebuf);
	
	*hrptr  = tmptr->tm_hour;
	*minptr = tmptr->tm_min;
	*secptr = tmptr->tm_sec;
}
/* Random number generator */

int rnd_(int maxval)
{
	return rand() % maxval;
}

/* Terminal support routines for dungeon */
/* By Ian Lance Taylor ian@airs.com or uunet!airs!ian */

/* The dungeon game can often output long strings, more than enough
 * to overwhelm a typical 24 row terminal (I assume that back when
 * dungeon was written people generally used paper terminals (I know
 * I did) so this was not a problem).  The functions in this file
 * provide a very simplistic ``more'' facility.  They are necessarily
 * somewhat operating system dependent, although I have tried to
 * minimize it as much as I could.
 */

/* The following macro definitions may be used to control how these
 * functions work:
 *
 *	MORE_NONE	Don't use the more facility at all
 *	MORE_24		Always assume a 24 row terminal
 *	MORE_TERMCAP	Use termcap routines to get rows of terminal
 *	MORE_TERMINFO	Use terminfo routines to get rows of terminal
 *	MORE_AMOS	Use AMOS monitor calls to get rows of terminal
 *
 * If none of these are defined then this will use termcap routines on
 * unix and AMOS routines on AMOS.
 */

#ifndef MORE_NONE
#ifndef MORE_24
#ifndef MORE_TERMCAP
#ifndef MORE_TERMINFO
#ifndef MORE_AMOS
#ifdef __AMOS__
#define MORE_AMOS
#else /* ! __AMOS__ */
#ifdef unix
#define MORE_TERMCAP
#else /* ! unix */
#define MORE_NONE
#endif /* ! unix */
#endif /* ! __AMOS__ */
#endif /* ! MORE_AMOS */
#endif /* ! MORE_TERMINFO */
#endif /* ! MORE_TERMCAP */
#endif /* ! MORE_24 */
#endif /* ! MORE_NONE */

#ifdef MORE_TERMCAP

extern char *getenv P((const char *));
extern void tgetent P((char *, const char *));
extern int tgetnum P((const char *));

#else /* ! MORE_TERMCAP */

#ifdef MORE_TERMINFO

#include <cursesX.h>
#include <term.h>
extern void setupterm P((const char *, int, int));

#else /* ! MORE_TERMINFO */

#ifdef MORE_AMOS

#include <moncal.h>
#include <unistd.h>

#endif /* MORE_AMOS */
#endif /* ! MORE_TERMINFO */
#endif /* ! MORE_TERMCAP */

/* Initialize the more waiting facility (determine how many rows the
 * terminal has).
 */

static int crows;
static int coutput;

void more_init()
{
    crows = 24;
}

/* The program wants to output a line to the terminal.  If z is not
 * NULL it is a simple string which is output here; otherwise it
 * needs some sort of formatting, and is output after this function
 * returns (if all computers had vprintf I would just it, but they
 * probably don't).
 */

void more_output(const char *z)
{
/* pager code remarked out to allow streamed input and output */
/*
     if (crows > 0  &&  coutput > crows - 2) {
	printf("Press return to continue: ");

        fflush(stdout);
	(void) fflush(stdout);
	while (getchar() != '\n')
	    ;
	coutput = 0;
    }
*/
    if (z != NULL)
	printf("%s\n", z);
    fflush(stdout);
    coutput++;
}

/* The terminal is waiting for input (clear the number of output lines) */

void more_input()
{
    coutput = 0;
}
