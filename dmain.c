/* DUNGEON-- MAIN PROGRAM */

/*COPYRIGHT 1980, INFOCOM COMPUTERS AND COMMUNICATIONS, CAMBRIDGE MA. 02142*/
/* ALL RIGHTS RESERVED, COMMERCIAL USAGE STRICTLY PROHIBITED */
/* WRITTEN BY R. M. SUPNIK */

#define EXTERN
#define INIT

#include "funcs.h"
#include "vars.h"

int main(int argc, char **argv)
{
/* 1) INITIALIZE DATA STRUCTURES */
/* 2) PLAY GAME */

#ifdef __ANDROID__
    for (;;) {
#endif

        if (init_()) {
	    game_();
        }
#ifdef __ANDROID__
    }
#endif
/* 						!IF INIT, PLAY GAME. */
    return 0;  //exit_();
/* 						!DONE */
} /* MAIN__ */
