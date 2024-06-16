#include "include/board.h"
#include "include/functions.h"
#include "include/cell.h"
#include <stdbool.h>

using namespace std;


const int BOARD_POSITION_X = 10;
const int BOARD_POSITION_Y = 10;
const int BOARD_COLS = 65;
const int BOARD_ROWS = 50;

bool isBoardClicked(sfVector2i mousePosition)
{
    return mousePosition.x >= BOARD_POSITION_X && mousePosition.x <= BOARD_POSITION_X + BOARD_COLS * CELL_SIZE &&
           mousePosition.y >= BOARD_POSITION_Y && mousePosition.y <= BOARD_POSITION_Y + BOARD_ROWS * CELL_SIZE;
}

void drawBoard(sfRenderWindow *window, int **cellsMatrix)
{

    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            sfVector2f cellPosition = {j * CELL_SIZE + BOARD_POSITION_X, i * CELL_SIZE + BOARD_POSITION_Y};
            sfVector2f cellSize = {CELL_SIZE, CELL_SIZE};
            unsigned short alive = cellsMatrix[i][j];
            sfRectangleShape *cell = createCell(cellSize, cellPosition, alive);
            sfRenderWindow_drawRectangleShape(window, cell, NULL);
            sfRectangleShape_destroy(cell);
        }
    }
}
