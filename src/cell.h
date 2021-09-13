#ifndef CELL_H
#define CELL_H

#include "common.h"

#define CREATECELL(attr, type) ((Cell){attr, type})
#define CREATECELLBYTYPE(type) CELLTYPEMAP[type]
#define NULLCELL CREATECELL(0, TYPE_AIR)

typedef enum {
    TYPE_AIR, /* empty cell */
    TYPE_WATER,
    TYPE_STONE,
    TYPE_MAX
} CELLTYPE;

typedef enum {
    ATTR_VISIBLE    = 0b00000001,
    ATTR_SOLID      = 0b00000010,
    ATTR_LIQUID     = 0b00000100, /* if this flag is set, ATTR_SOLID should also be set (though technically not required ig) */
    ATTR_GRAVITY    = 0b00001000,
} ATTRFLAGS;

typedef struct {
    uint8_t attr; /* is it solid, flamable, etc. */
    uint8_t type;
} Cell;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB;

extern Cell CELLTYPEMAP[TYPE_MAX];
extern RGB CELLCOLORMAP[TYPE_MAX];

Cell getCell(Chunk *chunk, int x, int y);
void setCell(Chunk *chunk, int x, int y, Cell cell);
void stepCell(Chunk *chunk, int x, int y);

#endif