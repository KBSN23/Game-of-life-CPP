#include <SFML/Graphics.h>
#include <stdbool.h>

extern const int BOARD_POSITION_X;
extern const int BOARD_POSITION_Y;
extern const int BOARD_COLS;
extern const int BOARD_ROWS;

bool isBoardClicked(sfVector2i mousePosition);
void drawBoard(sfRenderWindow *window, int **CellsMatrix);