#include "common.h"
#include "chunk.h"
#include "render.h"

int main() {
    Chunk *chnk = newChunk();

    renderInit();

    while (renderStep(chnk));

    renderClose();
    freeChunk(chnk);

    return 0;
}