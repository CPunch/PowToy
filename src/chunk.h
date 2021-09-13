#ifndef CHUNK_H
#define CHUNK_H

#include "common.h"
#include "cell.h"

#define CHUNKSIZE 128
#define INBOUNDS(x, y) (x < CHUNKSIZE && x >= 0 && y < CHUNKSIZE && y >= 0)

struct Chunk {
    Cell grid[CHUNKSIZE][CHUNKSIZE];
    uint8_t markedGrid[CHUNKSIZE][CHUNKSIZE]; /* marked previously updated cells (so don't update them!) */
};

Chunk* newChunk();
void freeChunk(Chunk *chnk);

void chunkStep(Chunk *chnk);
void paintChunk(Chunk *chnk, int x, int y, int brush, Cell c);

#endif