#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "chunk.h"

#define CELL_SIZE 4
/* simulated fps, SDL events are still polled */
#define MAXFPS 30
#define SCREEN_WIDTH (CHUNKSIZE * CELL_SIZE)
#define SCREEN_HEIGHT (CHUNKSIZE * CELL_SIZE)

void renderInit();
void renderClose();
int renderStep(Chunk *chnk);

#endif