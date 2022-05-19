#include <SFML/Graphics.hpp>
#include "header/createBgr.h"

int createBackground(VertexArray& rVA, IntRect arena)
{
    //how big is each tile/texture
    const int TILE_SIZE = 50;
    const int TILE_TYPES = 3;
    const int VERTS_IN_QUAD = 4;

    int worldWidth = arena.width / TILE_SIZE;
    int worldHeight = arena.height / TILE_SIZE;

    rVA.setPrimitiveType(Quads);

    //set the size of the vertex array
    rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

    //start at the beginning of the vertex array
    int currVertex = 0;

    for (int i = 0; i < worldWidth; i++)
    {
        for (int j = 0; j < worldHeight; j++)
        {
            //position each vertex in the current quad
            rVA[currVertex + 0].position = Vector2f(i * TILE_SIZE, j * TILE_SIZE);
            rVA[currVertex + 1].position = Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
            rVA[currVertex + 2].position = Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
            rVA[currVertex + 3].position = Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);

            // Define the position in the Texture to draw for current quad
			// Either mud, stone, grass or wall
            if (j == 0 || j == worldHeight - 1 || i == 0 || i == worldWidth - 1)
            {
                // use the wall texture
                rVA[currVertex + 0].texCoords = Vector2f(0, 0 + TILE_SIZE * TILE_TYPES);
                rVA[currVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + TILE_SIZE * TILE_TYPES);
                rVA[currVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + TILE_SIZE * TILE_TYPES);
                rVA[currVertex + 3].texCoords = Vector2f(0, TILE_SIZE + TILE_SIZE * TILE_TYPES);
            }
            else
            {
                // use random floor texture
                srand(time(NULL) + j * i -j);
                int mOrG = rand() % TILE_TYPES;
                int verticalOffset = mOrG * TILE_SIZE;

                rVA[currVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
                rVA[currVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
                rVA[currVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
                rVA[currVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
            }

            //position ready for the next for vertices
            currVertex += VERTS_IN_QUAD;
        }
    }

    return TILE_SIZE;
}
