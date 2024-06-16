#include <SFML/Graphics.h>

extern const float CELL_SIZE;

sfRectangleShape *createCell(sfVector2f size, sfVector2f position, unsigned short alive);
int **cellsMatrix_create();
void handleCellClick(int *cell);
int *getCellByPosition(sfVector2i mousePosition, int **cellsMatrix);