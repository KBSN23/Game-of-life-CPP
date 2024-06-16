#include <SFML/Graphics.h>
#include <stdio.h>
#include <string>
#include "include/simulation.h"
#include "include/board.h"
#include "include/cell.h"
#include "string.h"
#include "include/colors.h"

using namespace std;

const int SIMBTN_POSITION_X = 200;
const int SIMBTN_POSITION_Y = 800;
const sfVector2f SIMBTN_SIZE = {150, 30};

const int RESETBTN_POSITION_X = 350;
const int RESETBTN_POSITION_Y = 800;
const sfVector2f RESETBTN_SIZE = {150, 30};

const int INCREASEBTN_POSITION_X = 240;
const int INCREASEBTN_POSITION_Y = 850;
const int INCREASEBTN_SIZE = 20;

const int DECREASEBTN_POSITION_X = 50;
const int DECREASEBTN_POSITION_Y = 850;
const int DECREASEBTN_SIZE = 20;

const int SPEED_DISPLAY_POSITION_X = 125;
const int SPEED_DISPLAY_POSITION_Y = 855;

simState initSimulation()
{
    simState state;
    state.isPaused = true;
    state.speed = 1;
    return state;
}

void drawSimBtn(sfRenderWindow *window, simState state)
{
    sfRectangleShape *simBtn = sfRectangleShape_create();
    sfVector2f simBtnPosition = {SIMBTN_POSITION_X, SIMBTN_POSITION_Y};

    sfRectangleShape_setSize(simBtn, SIMBTN_SIZE);
    sfRectangleShape_setOutlineThickness(simBtn, 1.f);
    sfRectangleShape_setFillColor(simBtn, BTN_FILL_COLOR);
    sfRectangleShape_setOutlineColor(simBtn, BTN_OUTLINE_COLOR);
    sfRectangleShape_setPosition(simBtn, simBtnPosition);

    sfFont *font = sfFont_createFromFile("./assets/arial.ttf");

    if (font != NULL)
    {
        sfText *simBtnText = sfText_create();
        sfText_setFont(simBtnText, font);
        sfText_setString(simBtnText, state.isPaused ? "Start" : "Stop");
        sfText_setColor(simBtnText, sfBlack);
        sfVector2f simBtnTextPosition = {SIMBTN_POSITION_X + 55, SIMBTN_POSITION_Y + 5};
        sfText_setCharacterSize(simBtnText, 16);
        sfText_setPosition(simBtnText, simBtnTextPosition);

        sfRenderWindow_drawRectangleShape(window, simBtn, NULL);
        sfRenderWindow_drawText(window, simBtnText, NULL);

        sfText_destroy(simBtnText);
    }

    sfFont_destroy(font);
    sfRectangleShape_destroy(simBtn);
}

void drawResetBtn(sfRenderWindow *window, bool disabled)
{
    sfRectangleShape *resetBtn = sfRectangleShape_create();
    sfVector2f resetBtnPosition = {RESETBTN_POSITION_X, RESETBTN_POSITION_Y};

    sfRectangleShape_setSize(resetBtn, RESETBTN_SIZE);
    sfRectangleShape_setOutlineThickness(resetBtn, 1.f);
    sfRectangleShape_setFillColor(resetBtn, disabled ? BTN_DISABLED_FILL_COLOR : BTN_FILL_COLOR);
    sfRectangleShape_setOutlineColor(resetBtn, disabled ? BTN_DISABLED_TEXT_COLOR : BTN_OUTLINE_COLOR);
    sfRectangleShape_setPosition(resetBtn, resetBtnPosition);

    sfFont *font = sfFont_createFromFile("./assets/arial.ttf");

    if (font != NULL)
    {
        sfText *resetBtnText = sfText_create();
        sfText_setFont(resetBtnText, font);
        sfText_setString(resetBtnText, "Reset");
        sfText_setColor(resetBtnText, disabled ? BTN_DISABLED_TEXT_COLOR : sfBlack);
        sfVector2f resetBtnTextPosition = {RESETBTN_POSITION_X + 45, RESETBTN_POSITION_Y + 5};
        sfText_setCharacterSize(resetBtnText, 16);
        sfText_setPosition(resetBtnText, resetBtnTextPosition);

        sfRenderWindow_drawRectangleShape(window, resetBtn, NULL);
        sfRenderWindow_drawText(window, resetBtnText, NULL);

        sfText_destroy(resetBtnText);
    }

    sfFont_destroy(font);
    sfRectangleShape_destroy(resetBtn);
}

bool isResetBtnClicked(sfVector2i mousePosition)
{

    return (mousePosition.x >= RESETBTN_POSITION_X && mousePosition.x <= RESETBTN_POSITION_X + RESETBTN_SIZE.x &&
            mousePosition.y >= RESETBTN_POSITION_Y && mousePosition.y <= RESETBTN_POSITION_Y + RESETBTN_SIZE.y);
}

bool isSimBtnClicked(sfVector2i mousePosition)
{
    return (mousePosition.x >= SIMBTN_POSITION_X && mousePosition.x <= SIMBTN_POSITION_X + SIMBTN_SIZE.x &&
            mousePosition.y >= SIMBTN_POSITION_Y && mousePosition.y <= SIMBTN_POSITION_Y + SIMBTN_SIZE.y);
}

bool isIncreaseBtnClicked(sfVector2i mousePosition)
{
    return (mousePosition.x >= INCREASEBTN_POSITION_X && mousePosition.x <= INCREASEBTN_POSITION_X + INCREASEBTN_SIZE * 2 &&
            mousePosition.y >= INCREASEBTN_POSITION_Y && mousePosition.y <= INCREASEBTN_POSITION_Y + INCREASEBTN_SIZE * 2);
};

bool isDecreaseBtnClicked(sfVector2i mousePosition)
{
    return (mousePosition.x >= DECREASEBTN_POSITION_X && mousePosition.x <= DECREASEBTN_POSITION_X + DECREASEBTN_SIZE * 2 &&
            mousePosition.y >= DECREASEBTN_POSITION_Y && mousePosition.y <= DECREASEBTN_POSITION_Y + DECREASEBTN_SIZE * 2);
};

void handleResetBtnClick(int **cellsMatrix)
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            cellsMatrix[i][j] = 0;
        }
    }
}

void handleSimBtnClick(simState *state)
{
    if (state->isPaused)
    {
        state->isPaused = false;
    }
    else
    {
        state->isPaused = true;
    }
}

void nextTick(void *args)
{
    nextTickArgs *actualArgs = (nextTickArgs *) args;
    simState *simulation = actualArgs->simulation;
    int **cellsMatrix = actualArgs->cellsMatrix;

    if (simulation->isPaused)
    {
        return;
    }
    int **tempMatrix = cellsMatrix_create();

    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            tempMatrix[i][j] = cellsMatrix[i][j];
        }
    }

    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            int live_neighbors = 0;

            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (x == 0 && y == 0)
                    {
                        continue;
                    }
                    int ni = i + x;
                    int nj = j + y;
                    if (ni >= 0 && ni < BOARD_ROWS && nj >= 0 && nj < BOARD_COLS)
                    {
                        live_neighbors += cellsMatrix[ni][nj];
                    }
                }
            }

            if (cellsMatrix[i][j] == 1)
            {
                if (live_neighbors < 2 || live_neighbors > 3)
                {
                    tempMatrix[i][j] = 0;
                }
            }
            else
            {
                if (live_neighbors == 3)
                {
                    tempMatrix[i][j] = 1;
                }
            }
        }
    }

    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            cellsMatrix[i][j] = tempMatrix[i][j];
        }
    }

    sfTime waitTime = sfMilliseconds(1000 / simulation->speed);
    sfSleep(waitTime);
    nextTick(args);
};

void drawSpeedIncreaseBtn(sfRenderWindow *window, bool disabled)
{
    sfCircleShape *increaseBtn = sfCircleShape_create();
    sfVector2f increaseBtnPosition = {INCREASEBTN_POSITION_X, INCREASEBTN_POSITION_Y};

    sfCircleShape_setRadius(increaseBtn, INCREASEBTN_SIZE);
    sfCircleShape_setOutlineThickness(increaseBtn, 1.f);
    sfCircleShape_setFillColor(increaseBtn, disabled ? BTN_DISABLED_FILL_COLOR : BTN_FILL_COLOR);
    sfCircleShape_setOutlineColor(increaseBtn, disabled ? BTN_DISABLED_TEXT_COLOR : BTN_OUTLINE_COLOR);
    sfCircleShape_setPosition(increaseBtn, increaseBtnPosition);

    sfFont *font = sfFont_createFromFile("./assets/arial.ttf");

    if (font != NULL)
    {
        sfText *increaseBtnText = sfText_create();
        sfText_setFont(increaseBtnText, font);
        sfText_setString(increaseBtnText, "+");
        sfText_setColor(increaseBtnText, disabled ? BTN_DISABLED_TEXT_COLOR : sfBlack);
        sfVector2f increaseBtnTextPosition = {INCREASEBTN_POSITION_X + 14, INCREASEBTN_POSITION_Y + 5};
        sfText_setCharacterSize(increaseBtnText, 24);
        sfText_setPosition(increaseBtnText, increaseBtnTextPosition);

        sfRenderWindow_drawCircleShape(window, increaseBtn, NULL);
        sfRenderWindow_drawText(window, increaseBtnText, NULL);

        sfText_destroy(increaseBtnText);
    }

    sfFont_destroy(font);
    sfCircleShape_destroy(increaseBtn);
};

void drawSpeedDisplayText(sfRenderWindow *window, simState state)
{

    sfFont *font = sfFont_createFromFile("./assets/arial.ttf");

    if (font != NULL)
    {
        sfText *speedDisplayText = sfText_create();
        sfText_setFont(speedDisplayText, font);
        char text[50] = "Speed: ";
        char speedStr[3];
        itoa(state.speed, speedStr, 10);
        strcat(text, speedStr);
        strcat(text, "x");
        sfText_setString(speedDisplayText, text);
        sfText_setColor(speedDisplayText, sfBlack);
        sfVector2f speedDisplayTextPosition = {SPEED_DISPLAY_POSITION_X, SPEED_DISPLAY_POSITION_Y};
        sfText_setCharacterSize(speedDisplayText, 18);
        sfText_setPosition(speedDisplayText, speedDisplayTextPosition);

        sfRenderWindow_drawText(window, speedDisplayText, NULL);

        sfText_destroy(speedDisplayText);
    }

    sfFont_destroy(font);
};

void drawSpeedDecreaseBtn(sfRenderWindow *window, bool disabled)
{
    sfCircleShape *decreaseBtn = sfCircleShape_create();
    sfVector2f decreaseBtnPosition = {DECREASEBTN_POSITION_X, DECREASEBTN_POSITION_Y};

    sfCircleShape_setRadius(decreaseBtn, DECREASEBTN_SIZE);
    sfCircleShape_setOutlineThickness(decreaseBtn, 1.f);
    sfCircleShape_setFillColor(decreaseBtn, disabled ? BTN_DISABLED_FILL_COLOR : BTN_FILL_COLOR);
    sfCircleShape_setOutlineColor(decreaseBtn, disabled ? BTN_DISABLED_TEXT_COLOR : BTN_OUTLINE_COLOR);
    sfCircleShape_setPosition(decreaseBtn, decreaseBtnPosition);

    sfFont *font = sfFont_createFromFile("./assets/arial.ttf");

    if (font != NULL)
    {
        sfText *decreaseBtnText = sfText_create();
        sfText_setFont(decreaseBtnText, font);
        sfText_setString(decreaseBtnText, "-");
        sfText_setColor(decreaseBtnText, disabled ? BTN_DISABLED_TEXT_COLOR : sfBlack);
        sfVector2f decreaseBtnTextPosition = {DECREASEBTN_POSITION_X + 16, DECREASEBTN_POSITION_Y + 3};
        sfText_setCharacterSize(decreaseBtnText, 24);
        sfText_setPosition(decreaseBtnText, decreaseBtnTextPosition);

        sfRenderWindow_drawCircleShape(window, decreaseBtn, NULL);
        sfRenderWindow_drawText(window, decreaseBtnText, NULL);

        sfText_destroy(decreaseBtnText);
    }

    sfFont_destroy(font);
    sfCircleShape_destroy(decreaseBtn);
};

void increaseSpeed(simState *state)
{
    if (state->speed < 20)
    {
        state->speed++;
    }
};

void decreaseSpeed(simState *state)
{
    if (state->speed > 1)
    {
        state->speed--;
    }
}