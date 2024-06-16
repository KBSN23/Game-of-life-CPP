#include "include/randbtn.h"
#include "include/functions.h"
#include "include/board.h"
#include <random>
#include "include/colors.h"

using namespace std;


const int RANDBTN_POSITION_X = 50;
const int RANDBTN_POSITION_Y = 800;
const sfVector2f RANDBTN_SIZE = {150, 30};

void drawRandBtn(sfRenderWindow *window, bool disabled)
{
    sfRectangleShape *randBtn = sfRectangleShape_create();
    sfVector2f randBtnPosition = {RANDBTN_POSITION_X, RANDBTN_POSITION_Y};

    sfRectangleShape_setSize(randBtn, RANDBTN_SIZE);
    sfRectangleShape_setOutlineThickness(randBtn, 1.f);
    sfRectangleShape_setFillColor(randBtn, disabled ? BTN_DISABLED_FILL_COLOR : BTN_FILL_COLOR);
    sfRectangleShape_setOutlineColor(randBtn, disabled ? BTN_DISABLED_TEXT_COLOR : BTN_OUTLINE_COLOR);
    sfRectangleShape_setPosition(randBtn, randBtnPosition);

    sfFont *font = sfFont_createFromFile("./assets/arial.ttf");

    if (font != NULL)
    {
        sfText *randBtnText = sfText_create();
        sfText_setFont(randBtnText, font);
        sfText_setString(randBtnText, "Random");
        sfText_setColor(randBtnText, disabled ? BTN_DISABLED_TEXT_COLOR : sfBlack);
        sfVector2f randBtnTextPosition = {RANDBTN_POSITION_X + 55, RANDBTN_POSITION_Y + 5};
        sfText_setCharacterSize(randBtnText, 16);
        sfText_setPosition(randBtnText, randBtnTextPosition);

        sfRenderWindow_drawRectangleShape(window, randBtn, NULL);
        sfRenderWindow_drawText(window, randBtnText, NULL);

        sfText_destroy(randBtnText);
    }

    sfFont_destroy(font);
    sfRectangleShape_destroy(randBtn);
}

bool isRandBtnClicked(sfVector2i mousePosition)
{
    return mousePosition.x >= RANDBTN_POSITION_X && mousePosition.x <= RANDBTN_POSITION_X + RANDBTN_SIZE.x &&
           mousePosition.y >= RANDBTN_POSITION_Y && mousePosition.y <= RANDBTN_POSITION_Y + RANDBTN_SIZE.y;
}

void handleRandBtnClick(int **cellsMatrix)
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            int randVal = rand() % 100;
            if (randVal > 80)
            {

                cellsMatrix[i][j] = 1;
            }
            else
            {
                cellsMatrix[i][j] = 0;
            }
        }
    }
}