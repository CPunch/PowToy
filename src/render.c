#include "render.h"
#include "cell.h"
#include "chunk.h"

#include "stdio.h"

SDL_Window *win;
SDL_Renderer *rend;
int closed = 0;
int prevTime = 0;

void renderInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    /* create window & renderer */
    win = SDL_CreateWindow("PowToy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    rend =  SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}

void renderClose() {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void pickColor(Cell cell) {
    RGB color = CELLCOLORMAP[cell.type];

    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, 255);
}

void refresh(Chunk *chunk) {
    int x, y;
    SDL_Rect pixel;
    pixel.w = CELL_SIZE;
    pixel.h = CELL_SIZE;

    /* sets the background to black */
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

    /* clears the window */
    SDL_RenderClear(rend);

    /* walk through each row and column and draw each pixel */
    for (x = 0; x < CHUNKSIZE; x++) {
        for (y = 0; y < CHUNKSIZE; y++) {
            /* if cell isn't visible, skip */
            if (!(chunk->grid[x][y].attr & ATTR_VISIBLE))
                continue;

            /* pixel is alive, draw it */
            pickColor(chunk->grid[x][y]);
            pixel.x = x * CELL_SIZE;
            pixel.y = y * CELL_SIZE;
            SDL_RenderFillRect(rend, &pixel);
        }
    }

    /* render everything to the screen */
    SDL_RenderPresent(rend);
}

void pollEvents(Chunk *chnk) {
    SDL_Event event;
    int x, y;
    Uint32 mbutton;

    /* manage queued events */
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                closed = 1;
                return;
            case SDL_MOUSEBUTTONDOWN:
                /* mouse down, place liquid */
                mbutton = SDL_GetMouseState(&x, &y);
                if (INBOUNDS(x/CELL_SIZE, y/CELL_SIZE))
                    paintChunk(chnk, x/CELL_SIZE, y/CELL_SIZE, 4, CREATECELLBYTYPE(mbutton & SDL_BUTTON_LMASK ? TYPE_WATER : TYPE_STONE));
                break;
            default: break;
        }
    }

    SDL_Delay(10);
}

int renderStep(Chunk *chnk) {
    if (prevTime == 0 || SDL_GetTicks() - prevTime > 1000/MAXFPS) {
        chunkStep(chnk);
        refresh(chnk);
        prevTime = SDL_GetTicks();
    }

    pollEvents(chnk);

    return !closed;
}