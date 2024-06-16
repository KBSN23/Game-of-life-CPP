#include <SFML/Graphics.h>
#include <stdbool.h>

extern const int RANDBTN_POSITION_X;
extern const int RANDBTN_POSITION_Y;
extern const sfVector2f RANDBTN_SIZE;

void drawRandBtn(sfRenderWindow *window, bool disabled);
bool isRandBtnClicked(sfVector2i mousePosition);
void handleRandBtnClick(int **cellsMatrix);
