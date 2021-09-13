#include "chunk.h"

Chunk* newChunk() {
    Chunk *chnk = malloc(sizeof(Chunk));
    int x, y;

    /* setup grid, define everything as an empty air cell */
    for (x = 0; x < CHUNKSIZE; x++) 
        for (y = 0; y < CHUNKSIZE; y++)
            chnk->grid[x][y] = (y < CHUNKSIZE - 4 ? (Cell){0, TYPE_AIR} : CREATECELLBYTYPE(TYPE_STONE));

    return chnk;
}

void freeChunk(Chunk *chnk) {
    free(chnk);
}

void chunkStep(Chunk *chunk) {
    int x, y;

    /* zero out marked grid */
    memset(&chunk->markedGrid, 0, sizeof(chunk->markedGrid));

    for (y = 0; y < CHUNKSIZE; y++)
        for (x = 0; x < CHUNKSIZE; x++)
            if (!chunk->markedGrid[x][y])
                stepCell(chunk, x, y);
}

void paintChunk(Chunk *chnk, int x, int y, int brush, Cell c) {
    int bX, bY;

    /* set all cells within the brush */
    for (bX = -brush/2; bX <= brush/2; bX++)
        for (bY = -brush/2; bY <= brush/2; bY++)
            setCell(chnk, x+bX, y+bY, c);
}