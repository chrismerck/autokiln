
/*****************************************************
Autokiln Simulation
(c) 2015 Chris Merck
All Rights Reserved
*****************************************************/

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <SDL.h>
#include "SDL_ttf.h"
#include "SDL_gfxPrimitives.h"
#include "swmath.h"
#include "swgfx.h"
#include "SDL_net.h"

// define size of screen
#define XMAX 800
#define YMAX 500

#define SAMPLE_CUT_TIME 1



int main(int argc, char *argv[])
{
  SDL_Surface    *screen;
  SDL_Event       event;

  int             kspace = false, kup = false, kdown = false, kleft = false, kright = false;
  int             my, mx;

  srand(1);                     /* Fetch a set of fresh random numbers */

  /* Initialize SDL, exit if there is an error. */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Could not initialize SDL: %s\n",
            SDL_GetError());
    return -1;
  }
  TTF_Init();

  /* When the program is through executing, call SDL_Quit */
  atexit(SDL_Quit);

  /* Grab a surface on the screen */
  screen = SDL_SetVideoMode(XMAX, YMAX, 32, SDL_SWSURFACE | SDL_ANYFORMAT);
  if (!screen) {
    fprintf(stderr, "Couldn't create a surface: %s\n",
            SDL_GetError());
    return -1;
  }
  SDL_WM_SetCaption("SteamingPot - Real-Time Plotting of Glass Data",
                    "steamingpot.png");

  // screen state
  char lcdbuf[20*4+1];
  memset(lcdbuf,' ',sizeof(lcdbuf));
  lcdbuf[sizeof(lcdbuf)-1] = 0;

  // buttons
  bool button_menu = false;
  bool button_reset = false;
  bool button_manual = false;

  /* START OF MAIN PROGRAM LOOP */
  do {

    SDL_Flip(screen);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

#if 0
    setpixel(screen, pos, 130 + i * 32, 0, b, 0);

    aalineColor(screen,
                pos - 1, 130 - hist[i - 1][0],
                pos, 130 - hist[i][0],
                0xFFFFFF00 + b);


    drawGuage(screen, 10, GLOW, 20,
              "Vbatt (V)",
              0, 6.99, 1, .25,
              5.5,
              vbatt);
#endif

    drawTextColor(screen, "pitch", 12, 20, 130 + 15, GREEN, BLACK, FONT_MONO);

    // draw the elements
    drawLCD(screen, 400, 100, lcdbuf);

  //determine frame rate

//do_events:
    SDL_PumpEvents();
    SDL_GetMouseState(&mx, &my);

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        printf("Got quit event!\n");
        return 0;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          printf("Got quit key!\n");
          return 0;
          break;
        case SDLK_UP:
          kup = true;
          break;
        case SDLK_DOWN:
          kdown = true;
          break;
        case SDLK_LEFT:
          kleft = true;
          break;
        case SDLK_RIGHT:
          kright = true;
          break;
        case SDLK_SPACE:
          kspace = true;
          break;
        case SDLK_TAB:
          break;
        default:
          break;
        }
        break;
      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
        case SDLK_UP:
          kup = false;
          break;
        case SDLK_DOWN:
          kdown = false;
          break;
        case SDLK_LEFT:
          kleft = false;
          break;
        case SDLK_RIGHT:
          kright = false;
          break;
        case SDLK_SPACE:
          kspace = false;
          break;
        case SDLK_TAB:
          break;
        default:
          break;
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        break;
      case SDL_MOUSEBUTTONUP:
        break;
      default:
        break;
      }
    }

  } while (1);

  printf("should never reach here\n");

  return 0;
}

