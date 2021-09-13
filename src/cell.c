#include "cell.h"
#include "chunk.h"

typedef void(*cellBehavior)(Chunk*, int x, int y);

Cell getCell(Chunk *chunk, int x, int y) {
    if (INBOUNDS(x, y))
        return chunk->grid[x][y];

    /* cell doesn't exist */
    return NULLCELL;
}

void setCell(Chunk *chunk, int x, int y, Cell cell) {
    if (INBOUNDS(x, y)) {
        chunk->grid[x][y] = cell;
        chunk->markedGrid[x][y] = 1;
    }
}

/* swaps cells */
static void swapCell(Chunk *chunk, int xFrom, int yFrom, int xTo, int yTo) {
    Cell from = getCell(chunk, xFrom, yFrom);
    Cell to = getCell(chunk, xTo, yTo);

    setCell(chunk, xTo, yTo, from);
    setCell(chunk, xFrom, yFrom, to);
}

/* ====================== [[ cell type behavior ]] ====================== */

cellBehavior CELLBEHAVIORMAP[TYPE_MAX] = {
    [TYPE_AIR]      = NULL,
    [TYPE_WATER]    = NULL,
    [TYPE_STONE]    = NULL
}; /* TODO */

Cell CELLTYPEMAP[TYPE_MAX] = {
    [TYPE_AIR]      = CREATECELL(0, TYPE_AIR),
    [TYPE_WATER]    = CREATECELL(ATTR_SOLID | ATTR_VISIBLE | ATTR_LIQUID | ATTR_GRAVITY, TYPE_WATER),
    [TYPE_STONE]    = CREATECELL(ATTR_SOLID | ATTR_VISIBLE, TYPE_STONE)
};

RGB CELLCOLORMAP[TYPE_MAX] = {
    [TYPE_WATER] = {48, 117, 255},
    [TYPE_STONE] = {150, 150, 150},
};

void stepCell(Chunk *chunk, int x, int y) {
    Cell c = getCell(chunk, x, y);
    cellBehavior func = CELLBEHAVIORMAP[c.type];

    /* if cell has gravity enabled, try to move down */
    if (c.attr & ATTR_GRAVITY) {
        if (!(getCell(chunk, x, y+1).attr & ATTR_SOLID)) { /* check if the cell below us is non-collidable */
            swapCell(chunk, x, y, x, y+1);
            ++y;
        }
    }

    /* if the cell is a liquid, move around a bit */
    if (c.attr & ATTR_LIQUID) {
        /* random left or right (50% chance to move left (-1) or right (1)) */
        int tmp = ((rand() > RAND_MAX/2) ? -1 : 1);
        if (!(getCell(chunk, x+tmp, y).attr)) {
            swapCell(chunk, x, y, x+tmp, y);
            x+=tmp; /* update x so we keep track of the position */
        }
    }

    /* if we have special behavior rules for this cell type, run it */
    if (func != NULL)
        func(chunk, x, y);
}